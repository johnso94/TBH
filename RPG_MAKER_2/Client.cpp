#include "Client.h"
#include"sd_fun.h"

void Client::run()
{
    // 1. Get current event
    // 2. Get progress
    // 3. Get text of current event at progress
    string current_event = get_current_location();
    int progress = get_current_event_progress(current_event);
    string current_event_type = get_event_type(current_event);
    string event_info = get_event_info(current_event,progress);
    vector<string> event_info_lines = split(event_info,'-');
    trim_off_whitespaces(event_info_lines);

    if(current_event_type == "NAV")
        navigation(event_info_lines);
}

void Client::navigation(vector<string> event_info)
{
    string navigation_text = "";
    vector<pair<string, string>> locations_in_reach = get_nearby_locations();

    if(event_info.size() > 0)
        navigation_text += event_info[0] + "\n";

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
            navigation_text += "\n###########" + locations_in_reach[0].first + "##############\n";
        }
    }
    vector<string> actions;
    for(auto elem : locations_in_reach)
        actions.push_back(elem.first);
    next_actions(actions,navigation_text);

}

void Client::next_actions(vector<string> nearby_locations,string event_text)
{
    cout << event_text << "\n";
    string text_str = "";
    int num_of_actions = nearby_locations.size();
    text_str += to_string(num_of_actions) + "\n";
    for(auto elem : nearby_locations)
        text_str += elem + "\n";

    ofstream file_out("Next_Actions.txt");
    if(file_out.is_open())
    {
        file_out << text_str;
        file_out.close();
    } 
    else
        cout << "couldn't find Next_Actions.txt" << "\n";
}
































pair<string,int> Client::get_str_and_int(string str)
{
    pair<string,int> str_and_int;
    size_t last_space = str.find_first_of(' ');
    str_and_int.first = str.substr(0,last_space);
    str_and_int.second = stoi(str.substr(last_space));
    return str_and_int;
}

int Client::get_current_event_progress(string current_event)
{
    fstream file("progression.txt");
    string line;
    string file_str = "";
    bool found;
    int progress = 1;
    if(file.is_open())
    {
        while(getline(file,line))
        {
            file_str += line + "\n";
            size_t last_space = line.find_last_of(' ');
            string event = line.substr(0,last_space);
            if(event == current_event)
            {
                found = true;
                progress = stoi(line.substr(last_space));
            }
        }
        if(!found)
        {
            file_str += current_event + " 1";
            ofstream file_out("progression.txt");
            file_out << file_str;
            file_out.close();
        }
    } 
    else 
        cout << "progression.txt was not found\n";
    return progress;
}



bool Client::is_int(char c)
{
    return (c >= 48 && c <= 57);
}

string Client::get_event_info(string current_event,int progress)
{
    string line;
    ifstream file("Event_Info.txt");
    string event_info = "";
    bool get_event_info = false;
    size_t open_paren_pos;
    if (file.is_open())
    {
        while(getline(file,line))
        {
            if(get_event_info && line.size() == 0)
                break;
            if(!get_event_info)
            {
                open_paren_pos = line.find('(');
                if(open_paren_pos != string::npos)
                {
                    string event = line.substr(open_paren_pos+1,current_event.size());
                    if(event == current_event)
                        get_event_info = true;
                }
            }
            else if(get_event_info)
            {
                trim_off_whitespaces_str(line);
                if(line[0]-48 == progress)
                {
                    size_t period_pos = line.find('.');
                    line = line.substr(period_pos+1);
                    event_info = line;
                    break;
                }
            }
        }
    } else {
        cout << "couldn't find Event_Info.txt\n";
    }
    return event_info;
}

vector<string> Client::split(string str, char char_to_split_by)
{
    string word = "";
    vector<string> vec_of_words;
    for (unsigned int i = 0; i < str.size(); i++)
        if (str[i] != char_to_split_by)
            word += str[i];
        else
        {
            vec_of_words.push_back(word);
            word = "";
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
void Client::trim_off_whitespaces_str(string &str)
{
    while(str.back() == ' ')
        str.pop_back();
    while(str.front() == ' ')
        str = str.substr(1);
}


string Client::get_event_type(string current_event)
{
    string line;
    ifstream file("Event_Info.txt");
    string event_type = "NAV";
    if (file.is_open())
    {
        while(getline(file,line))
        {
            size_t open_paren = line.find('(');
            if(open_paren != string::npos)
            {
                string event = line.substr(open_paren+1,current_event.size());
                if(current_event == event)
                {
                    size_t first_space = line.find(' ');
                    event_type = line.substr(0,first_space);
                    break;
                }
            }
        }
    } else {
        cout << "couldn't find file" << "\n";
    }
    return event_type;
}

void Client::clear_screen()
{
    for (int i = 0; i < 50; i++)
        cout << "\n";
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

string Client::get_location_text(string str)
{
    size_t pos = str.find('|');
    size_t pos2 = str.find('+');
    if (pos == string::npos && pos2 == string::npos)
        return get_location_name(str);
    else if (pos == string::npos)
        pos = pos2;
    str += "    ";
    string substr = "";
    pos += 2;
    while (str[pos] != ' ' || str[pos + 1] != ' ')
    {
        substr += str[pos];
        pos++;
    }
    return substr;
}

string Client::get_text_at(string str, char c)
{
    size_t pos = str.find(c);
    string error_msg;
    if (pos == string::npos)
    {
        return "ERROR: " + to_string(c) + " not found in " + str + "\n";
    }
    str += "    ";
    string substr = "";
    pos += 2;
    while (str[pos] != ' ' || str[pos + 1] != ' ')
    {
        substr += str[pos];
        pos++;
    }
    return substr;
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
        cout << "File could not be found"
             << "\n";
    }
    return World_Map;
}

string Client::get_current_location()
{
    string current_location;
    ifstream file("Current_Location.txt");
    if (file.is_open())
    {
        getline(file, current_location);
    }
    return current_location;
}

vector<pair<string, string>> Client::get_nearby_locations()
{
    string current_location = get_current_location();
    vector<string> World_Map = get_World_Map();
    vector<pair<string, string>> locations_in_reach;
    pair<string, string> temp_pair;
    string back_location;
    bool get_nearby_locations = false;
    int current_location_tabs = 0;
    int num_of_tabs;
    int back;
    bool insert_back = true;
    if(current_location[0] == '@')
        current_location = current_location.substr(1);
    if(current_location[0] == '#')
    {

        insert_back = false;
    }
    for (unsigned int i = 0; i < World_Map.size(); i++)
    {
        if (!get_nearby_locations)
        {
            if (current_location == get_location_name(World_Map[i]))
            {
                temp_pair.first = current_location;
                temp_pair.second = current_location;
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
                temp_pair.second = get_location_text(World_Map[i]);
                locations_in_reach.push_back(temp_pair);
            }
        }
    }
    return locations_in_reach;
}

void Client::write_current_location_to_txt(string current_location)
{
    ofstream file("Current_Location.txt");
    if (file.is_open())
    {
        file << current_location << "\n";
    }
    else
    {
        cout << "File Current_Location.txt not found"
             << "\n";
    }
}
