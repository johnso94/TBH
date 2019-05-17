#include"Util.h"


void Util::set_value(string filename, string key, string value)
{
    ifstream file(filename);
    string game_data = "";
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            size_t key_pos = line.find(key);
            if(key_pos != string::npos)
            {
                // If key is found in file. Replace its value
                if(value.back() == '\n')
                    value.pop_back();
                game_data.append(key + " " + value + "\n");
            } 
            else 
            {
                // If key is not found in file. Chance nothing
                game_data.append(line + "\n");
            }
        }
        file.close();
    } 
    else
    {
        cout << filename << " not found";
    }

    ofstream file_out(filename);
    file_out << game_data;
    file_out.close();
}

void Util::set_value(string filename, string key, int _value)
{
    string value = to_string(_value);
    ifstream file(filename);
    string game_data = "";
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            size_t key_pos = line.find(key);
            if(key_pos != string::npos)
            {
                // If key is found in file. Replace its value
                if(value.back() == '\n')
                    value.pop_back();
                game_data.append(key + " " + value + "\n");
            } 
            else 
            {
                // If key is not found in file. Chance nothing
                game_data.append(line + "\n");
            }
        }
        file.close();
    } 
    else
    {
        cout << game_data << " not found";
    }

    ofstream file_out(filename);
    file_out << game_data;
    file_out.close();
}

bool Util::find_key(string filename, string key)
{
    ifstream file(filename);
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            size_t key_pos = line.find(key);
            if(key_pos != string::npos)
            {
                return true;
            }
        }
        file.close();
    }
    else 
    {
        cout << filename << " not found";
    }
    return false;
}

void Util::delete_key(string filename, string key)
{
    ifstream file(filename);
    string game_data = "";
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            size_t key_pos = line.find(key);
            if(key_pos == string::npos)
            {
                game_data.append(line + "\n");
            } 
        }
        file.close();
    } 
    else
    {
        cout << filename << " not found";
    }

    ofstream file_out(filename);
    file_out << game_data;
    file_out.close();
}

void Util::create_key(string filename, string key)
{
    ifstream file(filename);
    string game_data = "";
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            game_data.append(line + "\n");
        }
        file.close();
    } 
    else
    {
        cout << filename << " not found";
    }
    game_data.append(key + "\n");
    ofstream file_out(filename);
    file_out << game_data;
    file_out.close();
}

string Util::get_str_value(string filename,string _key)
{
    ifstream file(filename);
    string value;
    if(file.is_open())
    {
        string line;
        while(getline(file,line))
        {
            if(line.find(_key) != string::npos)
            {
                size_t colon_pos = line.find_last_of(':');
                value = line.substr(colon_pos+1);
                cut_spaces_off_ends(value);
            }
        }
        file.close();
    } 
    else 
    {
        cout << filename << "not found";
    }
    return value;
}

int Util::get_int_value(string filename, string key)
{
    string value = get_str_value(filename,key);
    if(!is_int(value))
    {
        cout << "Value " + value + " of Key " + key + "in " + filename + "could not be convered to a int";
        return -1;
    }
    return stoi(value);
}

void Util::minus_value(string filename, string key, int minus_int)
{
    int value = get_int_value(filename,key);
    if(value != -1)
    {
        value -= minus_int;
        set_value(filename,key,value);
    }
}

void Util::add_value(string filename, string key, int add_int)
{
    int value = get_int_value(filename,key);
    if(value != -1)
    {
        value += add_int;
        set_value(filename,key,value);
    }
}

map<string,string> Util::get_data(string filename,string current_event)
{
    ifstream file_in(filename);
    map<string,string> event_data;
    event_data["Description"] = "";
    if(file_in.is_open())
    {
        string line;
        bool get_data = false;
        bool get_description = false;
        int dash_count = 0;
        while(getline(file_in,line))
        {
            // cuts all spaces off the start and end off a string
            cut_spaces_off_ends(line);

            if(!get_data && (line == current_event))
            {
                get_data = true;
            }

            // Searches for data of current event
            else if(get_data)
            {
                /*
                If the file comes across "-" twice while get_data is true: get_data = false
                                                                            get_description = true
                */
                if(line.size() == 0)
                    break;
                if(line == "-")
                {
                    dash_count++;
                    if(dash_count == 2)
                    {
                        get_data = false;
                        get_description = true;
                    }
                } 
                else 
                {
                    /*
                    If there is a colon: key == line.substr(0 to colon)
                                        value == line.substr(colon to end of line)
                                        event_data[key] == value
                    */
                    size_t pos_colon = line.find(':');
                    if(pos_colon == string::npos)
                    {
                        cout << "colon missing in \"" << line << "\" for event " << current_event << "\n"; 
                        break;
                    } 
                    else 
                    {
                        string key = line.substr(0,pos_colon);
                        string value = line.substr(pos_colon+1);
                        cut_spaces_off_ends(key);
                        cut_spaces_off_ends(value);
                        event_data[key] = value;
                    }
                }
            }

            // Searches for text description of current event
            else if(get_description)
            {
                if(line.size() == 0)
                {
                    if(line.back() == '\n')
                        line.pop_back();
                    break;
                }
                event_data["Description"].append(line + "\n");
            }
        }
    }
    else
    {
        cout << "World.txt" << " not found\n";
    }

    event_data["Name"] = current_event;

    // If type of event is not specified its set to NAV as default
    if(event_data.find("Type") == event_data.end())
        event_data["Type"] = "Nav";

    return event_data;
}

//////////////////////////////////////////
// Functions that interact with strings //
//////////////////////////////////////////

bool Util::is_int(char c)
{
    return (c >= 48 && c <= 57);
}

bool Util::is_int(string str)
{
    for(auto elem : str)
    {
        if(!is_int(elem))
        {
            return false;
        }
    }
    return true;
}

void Util::cut_spaces_off_ends(string &str)
{
    if(str.size() > 0)
    {
        while(str[0] == ' ')
        {
            str = str.substr(1);
        }
        while(str.back() == ' ')
        {
            str.pop_back();
        }
    }
}
void Util::cut_spaces_off_ends(vector<string> &v)
{
    for(auto &elem : v)
    {
        cut_spaces_off_ends(elem);
    }
}

vector<string> Util::split(string str, char c)
{
    vector<string> all_words;
    string word = "";
    
    for(unsigned int i = 0; i < str.size(); i++)
    {
        if(str[i] != c)
        {
            word += str[i];
        }
        else
        {
            all_words.push_back(word);
            word = "";
        }
    }
    all_words.push_back(word);
    return all_words;
}

//////////////////////////////////////////
// Functions that interact with strings //
//////////////////////////////////////////

string Util::select_a_event_based_on_its_likelyhood_of_happening(string _events, string chance_of_event_happening)
{
    vector<string> possible_events = split(_events, '/');
    vector<string>chance_of_each_event = split(chance_of_event_happening, '/');

    cut_spaces_off_ends(possible_events);
    cut_spaces_off_ends(chance_of_each_event);

    vector<pair<string,int> > events_and_their_chance;

    int max_roll = 0;
    for(unsigned int i = 0; i < possible_events.size(); i++)
    {
        max_roll += stoi(chance_of_each_event[i]);
        events_and_their_chance.push_back({possible_events[i],max_roll});
    }
    
    srand(time(NULL));
    int roll = rand() % max_roll;

    string chosen_event = "__NONE__";
    for(unsigned int i = 0; i < events_and_their_chance.size(); i++)
    {
        if(roll <= events_and_their_chance[i].second)
        {
            chosen_event = events_and_their_chance[i].first;
            break;
        }
    }
    return chosen_event;
}

//////////////////////////////////////
// Funcions that interact with yaml //
//////////////////////////////////////

int Util::get_yaml_input(int min,int max)
{
    // Get string from input box
    string str_input;
    cout << "<< ";
    cin >> str_input;


    // If string inputed from input box cant be converted to a int
    for(auto elem : str_input)
    {
        if(elem < 48 || elem > 57)
            return -1;
    }

    int int_input = stoi(str_input);


    if(int_input >= min && int_input <= max)
    {
        return int_input;
    } else {
        return -1;
    }
}

void Util::print_to_yaml(string display_text)
{
    /*
        Displays the Following :

        ### Location Name ###

        Location Description

        [1] nearby location1
        [2] nearby location2
        ...
        [n] Back
    */
    cout << display_text << "\n";
}