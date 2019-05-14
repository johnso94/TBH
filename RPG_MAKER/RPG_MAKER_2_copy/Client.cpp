#include "Client.h"

void Client::write_value(string filename ,string str,string value)
{
    string file_str = "";
    ifstream file(filename);
    if(file.is_open())
    {
        string line;
        bool found_str = false;
        while(getline(file,line))
        {
            if(line.substr(0,str.size()) == str)
            {
                line.pop_back();
                line += value;
                found_str = true;
            }
            file_str += line + "\n";
        }
        file.close();
        if(!found_str)
            file_str += str + " : "+value;
        ofstream file_out(filename);
        file_out << file_str;
        file_out.close();
    }
    else
        cerr << "couldn't find file " << "\n";
}

void Client::run()
{
    string current_event = get_value("Player.txt","Event:");
    // string progress_str = get_value("Event_Info.txt",current_event);
    int progress = stoi(get_value("Player.txt","Progress:"));
    string event_type = get_event_value(progress,current_event,"Type:");
    string progressed_event = get_event_value(progress,current_event,"Progress:");
    if(progressed_event != "__NONE__")
    {
        vector<string>loc_and_prog = split(progressed_event,'/');
        if(loc_and_prog.size() == 2)
        {
            trim_off_whitespaces(loc_and_prog);
            int progress_from = stoi(loc_and_prog[0]);
            int progress_to = stoi(loc_and_prog[1]);
            if(progress == progress_from)
                write_value("Player.txt","Progress:",to_string(progress_to));
        } else {
            cerr << "Syntax Error: "+ progressed_event + " Progress did not follow template Progress: int / int"<< "\n";
        }
    }
    if(event_type == "__NONE__")
        event_type = "NAV";
    if(event_type == "NAV")
        navigation(current_event,progress);
    cerr << "running" << "\n";
}

void Client::navigation(string current_event, int progress)
{
    vector<pair<string, string>> nearby_locations = get_nearby_locations(current_event,progress);
    if(!is_alpha(current_event[0]))
        current_event = current_event.substr(1);
    string location_text = get_event_value(progress,current_event,"Text");
    string navigation_text = "";

    if(location_text != "__NONE__")
    {
        navigation_text += "\n" + location_text + "\n";
    }

    for (unsigned int i = 0; i < nearby_locations.size(); i++)
    {
        if(i == 0)
        {
            navigation_text += "\n###########" + nearby_locations[i].first + "##############\n";
        }
        else
        {
            navigation_text += "[" + to_string(i) + "] " + nearby_locations[i].second + "\n";
        }
    }

    
    int user_input = get_user_input(navigation_text,1,nearby_locations.size()-1);
    string current_location = nearby_locations[user_input].first;
    set_player_info("Event:",current_location);
    string forground_image = get_event_value(progress,current_location,"Foreground Image:");
    string background_image = get_event_value(progress,current_location,"Background Image:");
    set_player_info("Foreground Image:",forground_image);
    set_player_info("Background Image:",background_image);
}

void Client::set_player_info(string str1,string str2)
{
    ifstream file("Player.txt");
    string player_info = "";
    if(file.is_open())
    {
        string line;
        string info_type;
        while(getline(file,line))
        {   
            if(line.find(str1) != string::npos)
            {
                player_info += str1 + " " + str2 + "\n";
            }
            else 
                player_info += line + "\n";
        }
        file.close();
    } else
        cerr << "Player.txt not found in set_player_info";

    ofstream file_out("Player.txt");
    file_out << player_info;
    file_out.close();
}

string Client::get_event_value(int progress,string current_event,string info_type)
{
    ifstream in_file("Event_Info.txt");
    string info = "__NONE__";
    string line;
    if(in_file.is_open())
    {
        bool correct_event = false;
        int progress_num = 1;
        while(getline(in_file,line))
        {
            if(correct_event && line.size() == 0)
                break;
            else if(correct_event)
            {
                if(ctoi(line[0]) > 0)
                {
                    trim_spaces(line);
                    progress_num = stoi(line);
                }
                if(progress_num > progress)
                    break;
                if(line.find(info_type) != string::npos)
                {
                    size_t colon_pos = line.find(':');
                    info = line.substr(colon_pos+1);
                    if(progress_num == progress)
                        break;
                }
            }
            else if(is_alpha(line[0]))
            {
                int current_event_len = current_event.size();
                string event = line.substr(0,current_event_len);
                if(event == current_event)
                {
                    correct_event = true;
                }
            }
        }
        in_file.close();
    }
    trim_spaces(info);
    return info;
};

vector<pair<string, string>> Client::get_nearby_locations(string current_location,int progress)
{
    vector<string> World_Map = get_World_Map();
    vector<pair<string, string>> locations_in_reach;
    pair<string, string> location_and_script;
    string back_location;
    bool get_nearby_locations = false;
    int current_location_tabs = 0;
    int num_of_tabs;
    int back;
    bool insert_back = true;
    if(World_Map[0] == "__NO BACK__")
    {
        insert_back = false;
    }
    if(current_location[0] == '@')
    {
        current_location = current_location.substr(1);
    }
    if(current_location[0] == '#')
    {
        if(insert_back)
            insert_back = false;
        else
            insert_back = true;
    }
    for (unsigned int i = 0; i < World_Map.size(); i++)
    {
        if (!get_nearby_locations)
        {
            if (current_location == get_location_name(World_Map[i]))
            {
                location_and_script.first = location_and_script.second = get_location_name(World_Map[i]);
                locations_in_reach.push_back(location_and_script);
                current_location_tabs = count_tabs(World_Map[i]);
                get_nearby_locations = true;
                if (current_location_tabs && insert_back)
                {
                    back = i;
                    while (count_tabs(World_Map[back]) >= current_location_tabs)
                    {
                        back--;
                    }
                    back_location = World_Map[back];
                }
            }
        }
        else if (get_nearby_locations)
        {
            num_of_tabs = count_tabs(World_Map[i]);
            if (current_location_tabs == num_of_tabs || current_location_tabs - 1 == num_of_tabs || num_of_tabs == 0)
            {
                if (current_location_tabs != 0 && insert_back)
                {
                    location_and_script.first = get_location_name(back_location);
                    location_and_script.second = "Back";
                    locations_in_reach.push_back(location_and_script);
                }
                break;
            }
            else if (current_location_tabs + 1 == num_of_tabs)
            {
               trim_spaces(World_Map[i]);
               if(!is_alpha(World_Map[i][0]))
                    World_Map[i] = World_Map[i].substr(1);
                location_and_script.first = get_location_name(World_Map[i]);
                location_and_script.second = get_event_value(progress,World_Map[i],"Script");
                if(location_and_script.second == "__NONE__")
                    location_and_script.second = location_and_script.first;
                locations_in_reach.push_back(location_and_script);
            }
        }
    }
    if(locations_in_reach.size() == 0)
    {
        location_and_script.first = location_and_script.second = current_location;
        locations_in_reach.push_back(location_and_script);
        location_and_script.first = "not found";
        location_and_script.second = current_location + " was not found in World_Map.txt";
        locations_in_reach.push_back(location_and_script);
    }
    return locations_in_reach;
}
int Client::get_user_input(string event_text,int min,int max)
{
    string user_input;
    int user_input_int;
    while (1)
    {
        // string user_input;
        // int user_input_int;
        // write_at(mem,100,event_text.c_str());
        // Range t_range = find_value(yaml, "content:");
        // char testing[t_range.len];
        // write_at(testing, 0, yaml, t_range);
        // user_input = testing;
        event_text += "\n<< ";
        cout << event_text;
        cin >> user_input;
        if(user_input[0] > 48 && user_input[0] <= 57)
        {
            user_input_int = stoi(user_input);
            if(user_input_int < min || user_input_int > max)
            {
                event_text += "Input out of range";
            }
            else
                break;

        }
        else
            event_text += "Input must be int";
    }
    return user_input_int;
}




























string Client::get_value(string filename, string str)
{
    ifstream file(filename);
    string info = "__NONE__";
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            size_t str_pos = line.find(str);
            if(str_pos != string::npos)
            {
                size_t colon_pos = line.find_last_of(':');
                info = line.substr(colon_pos+1);
                trim_off_whitespaces(info);
                if(line == info)
                {
                    info = line;
                    break;
                }
            }
        }
        file.close();
    } else {
        cerr << filename + " not found in get_value" << "\n";
    }
    return info;
}



int Client::get_current_event_progress(string current_event)
{
    fstream file("Player.txt");
    string line;
    string file_str = "";
    int progress = 1;
    if(file.is_open())
    {
        while(getline(file,line))
        {
            file_str += line + "\n";
            size_t Progression_pos = line.find("Progression");
            if(Progression_pos != string::npos)
            {
                size_t last_space = line.find_last_of(' ');
                progress = stoi(line.substr(last_space));
            } 
            else
                cerr << "progression not found in Player.txt";
        }
        file.close();
    } 
    else 
        cerr << "progression.txt was not found\n";
    return progress;
}



bool Client::is_int(char c)
{
    return (c >= 48 && c <= 57);
}

vector<string> Client::split(string str, char char_to_split_by)
{
    string word = "";
    vector<string> vec_of_words;
    for(auto elem : str)
    {
        if (elem != char_to_split_by)
            word += elem;
        else
        {
            vec_of_words.push_back(word);
            word = "";
        }
    }
    vec_of_words.push_back(word);
    return vec_of_words;
}

void Client::trim_off_whitespaces(vector<string> &v)
{
    for(auto &elem : v)
    {
        while(elem.back() == ' ')
            elem.pop_back();
        while(elem[0] == ' ')
            elem = elem.substr(1);
    }
}
void Client::trim_off_whitespaces(string &str)
{
    while(str.back() == ' ')
        str.pop_back();
    while(str.front() == ' ')
        str = str.substr(1);
}


void Client::clear_screen()
{
    for (int i = 0; i < 50; i++)
        cerr << "\n";
}

int Client::count_tabs(string str)
{
    int count = 0;
    for (auto elem : str)
    {
        if (elem != ' ')
            break;
        else
            count++;
    }
    return count / 4;
}

string Client::get_location_name(string str)
{
    if (!str.size())
        return "\n";
    str += "       ";
    int spaces = 0;
    for (auto elem : str)
    {
        if (elem != ' ')
            break;
        spaces++;
    }
    int pos = spaces;
    string substr = "";
    for (unsigned int i = 0; i < str.size(); i++)
        while (str[pos] != ' ' || str[pos + 1] != ' ')
        {
            substr += str[pos];
            pos++;
        }
    return substr;
}

string Client::get_location_script(string str)
{
    size_t pos = str.find('"');
    if (pos == string::npos)
        return get_location_name(str);
    size_t pos2 = str.find_last_of('"');
    int script_len = pos2 - pos;
    string script = str.substr(pos+1,script_len-1);
    return script;
}

vector<string> Client::get_World_Map()
{
    string line;
    vector<string> World_Map;
    ifstream file("World_Map.txt");
    if (file.is_open())
    {
        while (getline(file, line))
            World_Map.push_back(line);
    }
    else
    {
        cerr << "File could not be found\n";
    }
    return World_Map;
}



