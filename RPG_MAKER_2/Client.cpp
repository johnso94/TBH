#include "Client.h"

void Client::run()
{
    while (1)
    {
        string current_event = get_current_location();
        string current_event_type = get_event_type(current_event);
        string event_info = get_event_info(current_event);
        // string get_player_info = 
        vector<string> event_info_lines = split(event_info,'-');
        trim_off_whitespaces(event_info_lines);

        if(current_event_type == "NAV")
            navigation(event_info_lines);
        else if(current_event_type == "SELECT")
            select(event_info_lines);
        else if(current_event_type == "COMBAT")
            combat(event_info_lines);
    }
}

int Client::get_user_input(string event_text,int min,int max)
{
    int user_input = 0;
    while (1)
    {
        event_text += "\n<< ";
        clear_screen();
        cout << event_text;
        cin >> user_input;
        if (user_input < min || user_input > max)
        {
            event_text += "Invalid Input";
        }
        else
            break;
    }
    return user_input;
}


void Client::navigation(vector<string> event_info)
{
    string navigation_text = "";
    vector<pair<string, string>> locations_in_reach = get_nearby_locations();

    if(event_info.size() > 1)
        navigation_text += event_info[2] + "\n";


    for (unsigned int i = 0; i < locations_in_reach.size(); i++)
    {
        if (i == 0)
        {
            navigation_text += "\n###########" + locations_in_reach[0].first + "##############\n";
        }
        else
        {
            navigation_text += "[" + to_string(i) + "] " + locations_in_reach[i].second + "\n";
        }
    }

    int user_input = get_user_input(navigation_text,1,locations_in_reach.size()-1);
    string current_location = locations_in_reach[user_input].first;
    write_current_location_to_txt(current_location);
}

void Client::select(vector<string> event_info)
{
    string select_text = "";

    for(auto elem : event_info)
        if(elem != event_info.back())
            select_text += elem + "\n";
        else
            select_text += "[1] Back\n";


    get_user_input(select_text,1,1);
    string current_location = event_info.back();
    write_current_location_to_txt(current_location);
}




void Client::combat(vector<string> event_info)
{
    string combat_text = "";
    

    for(auto elem : event_info)
        if(elem != event_info.back())
            combat_text += elem + "\n";
        else
            combat_text += "[1] Back\n";


    get_user_input(combat_text,1,1);
    string current_location = event_info.back();
    write_current_location_to_txt(current_location);
}




string Client:: get_player_info()
{
    string line;
    ifstream file("Player.txt");
    string player_info = "";
    bool get_lines = false;
    size_t pos_colon;
    if (file.is_open())
    {
        while(getline(file,line))
        {
            player_info += line;
        }
    } else {
        cout << "couldn't find Event_Info.txt\n";
    }
    return player_info;
}



string Client::get_event_info(string current_event){
    string line;
    ifstream file("Event_Info.txt");
    string event_info = "";
    bool get_lines = false;
    size_t pos_colon;
    if (file.is_open())
    {
        while(getline(file,line))
        {
            if(get_lines && !line.size())
                break;
            if(!get_lines)
            {
                pos_colon = line.find(':');
                if(pos_colon != string::npos)
                {
                    if(current_event == line.substr(0,pos_colon-1))
                    {
                        event_info += line;
                        get_lines = true;
                    }
                }
            } 
            else if(get_lines)
            {
                event_info += line;
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


string Client::get_event_type(string current_event)
{
    string line;
    ifstream file("Event_Info.txt");
    string event_type = "NAV";
    size_t pos_colon;
    if (file.is_open())
    {
        while(getline(file,line))
        {
            if(line == "__END__")
                break;
            pos_colon = line.find(':');
            if(pos_colon != string::npos)
            {
                if(current_event == line.substr(0,pos_colon-1))
                {
                    while(line.back() == ' ')
                        line.pop_back();
                    event_type = line.substr(pos_colon+2);
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
    if(current_location[0] == '@')
        current_location = current_location.substr(1);
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
            if (current_location_tabs)
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
                if (current_location_tabs != 0)
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
