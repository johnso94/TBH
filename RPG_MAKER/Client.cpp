#include "Client.h"

string Client::find_string(int pos) { // returns the string of chars starting at mem[500].
    string x = "";
    int i = 0;
    while (mem[(i++)+pos] != 0);
    for (int j = 1; j < i; j++) {
        x += mem[j+pos-1];
    }
    return x;
}

string Client::run()
{
    string current_event = find_string(500);
    int progress = stoi(get_player_info("Progression"));
    string event_info = get_event_info(current_event,progress);
    vector<string> event_info_lines = split(event_info,'-');
    trim_off_whitespaces(event_info_lines);

    // PRINT OUT TEST

    //printf("Current Event: %s\nProgress: %i\nType: %s\nInfo: %s\n",current_event.c_str(),progress,current_event_type.c_str(),event_info.c_str());
    if(event_info_lines[0] == "NAV")
    {
            string display_text = navigation(event_info_lines);
            navigation2();
            return display_text;
    }
}

void Client::navigation2()
{
    string current_event = find_string(500);
    int progress = stoi(get_player_info("Progression"));
    string event_info = get_event_info(current_event,progress);
    vector<string> event_info = split(event_info,'-');
    trim_off_whitespaces(event_info);
    string navigation_text = "";

    vector<pair<string, string>> locations_in_reach = get_nearby_locations();

    if(event_info.size() > 2)
        navigation_text += "\n" + event_info[2] + "\n";

    for (unsigned int i = 0; i < locations_in_reach.size(); i++)
    {
        if(i != 0)
        {
            string display_text = locations_in_reach[i].second;
            if(display_text[0] == '@' || display_text[0] == '#')
                display_text = display_text.substr(1);
            navigation_text += "[" + to_string(i) + "] " + display_text + "\n";
        }
        else
        {
            navigation_text += "\n###" + locations_in_reach[0].first + "###\n";
        }

    }
    cerr << navigation_text << "\n";
    write_at(mem,100,navigation_text.c_str());
}

string Client::navigation(vector<string> event_info)
{

    string navigation_text = "";
    vector<pair<string, string>> locations_in_reach = get_nearby_locations();

    if(event_info.size() > 2)
        navigation_text += "\n" + event_info[2] + "\n";

    for (unsigned int i = 0; i < locations_in_reach.size(); i++)
    {
        if(i != 0)
        {
            string display_text = locations_in_reach[i].second;
            if(display_text[0] == '@' || display_text[0] == '#')
                display_text = display_text.substr(1);
            navigation_text += "[" + to_string(i) + "] " + display_text + "\n";
        }
        else
        {
            navigation_text += "\n###" + locations_in_reach[0].first + "###\n";
        }

    }
    int user_input = get_user_input(navigation_text,1,locations_in_reach.size()-1);
    string current_location = locations_in_reach[user_input].first;
    write_at(mem, 500, current_location.c_str());
    cerr << navigation_text << "\n";
    write_at(mem,100,navigation_text.c_str());
    for (int i = 0; i < 7; i++) {
        cerr << mem[i+500];
    }
    
    cerr << "\n";
    return navigation_text;
    // display(navigation_text);

    // display(navigation_text);
    // set_pictures(current_location);
}

void Client::write_display_text(string str)
{
    ofstream file_out("display_text.txt");
    file_out << str;
}

void Client::display(string event_text)
{
    write_at(mem,100,event_text.c_str());
}

void Client::set_pictures(string current_location)
{
    int progress = stoi(get_player_info("Progression"));
    string event_info = get_event_info(current_location,progress);
    vector<string> event_info_lines = split(event_info,'-');
    trim_off_whitespaces(event_info_lines);
    string forground = event_info_lines[event_info.size()-2];
    string background = event_info_lines.back();
    set_player_info("Current Foreground",forground);
    set_player_info("Current Background",background);
}



void Client::set_player_info(string str1,string str2)
{
    ifstream file("Player_Info.txt");
    string player_info = "";
    if(file.is_open())
    {
        string line;
        string info_type;
        while(getline(file,line))
        {
            size_t colon_pos = line.find(':');

            if(colon_pos != string::npos)
                info_type = line.substr(0,colon_pos-1);

            trim_off_whitespaces(info_type);

            if(info_type == str1)
                player_info +=  str1 + " : " + str2 + "\n";
            else
                player_info += line + "\n";
        }
        file.close();
    } else
        cerr  << "Player_Info.txt not found";

    ofstream file_out("Player_Info.txt");
    file_out << player_info;
    file_out.close();
}

int Client::get_user_input(string event_text,int min,int max)
{
    string user_input;
    int user_input_int;

    Range t_range = find_value(yaml, "content:");
    char testing[t_range.len];
    write_at(testing, 0, yaml, t_range);
    user_input = testing;
    cerr << "\n" << user_input << "\n";

    if(user_input[0] > 48 && user_input[0] <= 57)
    {
        user_input_int = stoi(user_input);
        if(user_input_int < min || user_input_int > max)
        {
            event_text += "Input out of range";
        }
    }
    else
        event_text += "Input must be int";
    return user_input_int;
}



string Client::get_player_info(string str)
{
    ifstream file("Player_Info.txt");
    string info = str+" not found in Player_Info.txt";
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
        cerr  << "Player_Info.txt not found" << "\n";
    }
    return info;
}



int Client::get_current_event_progress(string current_event)
{
    fstream file("Player_Info.txt");
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
                cerr  << "progression not found in Player_Info.txt";
        }
        file.close();
    } 
    else 
        cerr  << "progression.txt was not found\n";
    return progress;
}

bool Client::is_int(char c)
{
    return (c >= 48 && c <= 57);
}

string Client::get_event_info(string current_event,int progress)
{
    ifstream file("Event_Info.txt");
    string event_info = "";
    bool get_event_text = false;
    if (file.is_open())
    {
        string line;
        bool get_event_info = false;
        while(getline(file,line))
        {
            if(get_event_info && line.size() == 0)
                break;
            if(!get_event_info)
            {
                size_t open_paren_pos = line.find('(');
                if(open_paren_pos != string::npos)
                {
                    string event = line.substr(open_paren_pos+1,current_event.size());
                    if(event == current_event)
                    {
                        size_t first_space = line.find(' ');
                        string event_type = line.substr(0,first_space);
                        event_info += event_type + " - " + event + " - ";
                        get_event_info = true;
                    }
                }
            }
            else if(get_event_info)
            {
                trim_off_whitespaces(line);
                if(line[0]-48 == progress)
                {
                    size_t period_pos = line.find('.');
                    line = line.substr(period_pos+1);
                    event_info += line;
                    get_event_text = true;
                }
                else if(get_event_text)
                {
                    if(line[0]-48 == progress+1)
                        break;
                    size_t period_pos = line.find('.');
                    line = line.substr(period_pos+1);
                    event_info += line;
                }
            }
        }
        file.close();
    } else
        cerr   << "couldn't find Event_Info.txt\n";
    if(event_info.size() == 0)
        event_info = "NAV";
    return event_info;
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
        cerr   << "\n";
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
        cerr   << "File could not be found\n";
    }
    return World_Map;
}


vector<pair<string, string>> Client::get_nearby_locations()
{
    string current_location = find_string(500);
    vector<string> World_Map = get_World_Map();
    vector<pair<string, string>> locations_in_reach;
    pair<string, string> temp_pair;
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
        current_location = current_location.substr(1);
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
                temp_pair.first = get_location_name(World_Map[i]);
                temp_pair.second = get_location_script(World_Map[i]);
                locations_in_reach.push_back(temp_pair);
                current_location_tabs = count_tabs(World_Map[i]);
                get_nearby_locations = true;
            }
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
        else if (get_nearby_locations)
        {
            num_of_tabs = count_tabs(World_Map[i]);
            if (current_location_tabs == num_of_tabs || current_location_tabs - 1 == num_of_tabs || num_of_tabs == 0)
            {
                if (current_location_tabs != 0 && insert_back)
                {
                    temp_pair.first = get_location_name(back_location);
                    temp_pair.second = "Back";
                    locations_in_reach.push_back(temp_pair);
                }
                break;
            }
            else if (current_location_tabs + 1 == num_of_tabs)
            {
                temp_pair.first = get_location_name(World_Map[i]);
                temp_pair.second = get_location_script(World_Map[i]);
                locations_in_reach.push_back(temp_pair);
            }
        }
    }
    return locations_in_reach;
}

