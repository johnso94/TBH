#include"Client.h"

void Client::run(string current_event)
{
    // Gets data of Current event in events.txt
    // If Current event is World then event_data would be
    // event_data["Name"] = World
    // event_data["Type"] = Type
    // event_data["Back"] = none
    // event_data["Description"] = Lots of Text for World...

    map<string,string> event_data = get_data(current_event);
    if(event_data["Type"] == "NAV")
    {
        navigation(event_data);
    }
    else if(event_data["Type"] == "Combat")
    {
        combat(event_data);
    }
}

void Client::navigation(map<string,string> event_data)
{
    // Reading in from Txt files to create location
    Location location;
    location.name = event_data["Name"];
    location.has_back_location = event_data["Back"];
    location.description = event_data["Description"];
    location.near_locations = get_location_data(location.name);

    // Get The text from location that will be prompted to yaml
    string display_text = location.to_str();
    cout << display_text;
    run_count++;
    if(run_count == 2)
        return;

    // get user input. Display text is written to yaml in get_user_input() function

    int user_input = 1;

    // If user_input is valid set new Event and Image in Game.txt
    if(user_input != -1)
    {
        string new_current_event = location.near_locations[user_input];
        set_value(game_file,"Event:",new_current_event);
        set_value(game_file,"Image:",new_current_event+".png");
        run(new_current_event);
    } 
    else 
    {
        cout << "\nInvalid Input\n\n";
    }
}

    // int number_of_locations = location.near_locations.size();
    // int user_input = get_user_input(1,number_of_locations,display_text);


void Client::combat(map<string,string> event_data)
{
    for(auto elem : event_data)
        cout << elem.first << " " << elem.second << "\n";
}



string Client::get_value(string filename,string _key)
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


void Client::set_value(string filename, string key, string value)
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
                game_data.append(key + " " + value + "\n");
            } 
            else 
            {
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

int Client::get_user_input(int min,int max, string display_text)
{
    string str_input;
    cout << display_text << endl;
    cout << "<< ";
    cin >> str_input;

    for(auto elem : str_input)
    {
        if(elem < 48 || elem > 57)
            return -1;
    }


    // int int_input;
    int int_input = stoi(str_input);
        
    if(int_input >= min && int_input <= max)
    {
        return int_input;
    } else {
        return -1;
    }
}

map<string,string> Client::get_data(string current_event)
{
    ifstream file_in(events_file);
    map<string,string> event_data;
    event_data["Description"] = "";
    event_data["Name"] = current_event;
    if(file_in.is_open())
    {
        string line;
        bool get_data = false;
        bool get_text = false;
        int dash_count = 0;
        while(getline(file_in,line))
        {
            // cuts spaces off start and end off line
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
                                                                            get_text = true
                */
                if(line.size() == 0)
                    break;
                if(line == "-")
                {
                    dash_count++;
                    if(dash_count == 2)
                    {
                        get_data = false;
                        get_text = true;
                    }
                } 
                else 
                {
                    /*
                    If there is a colon: key == line.substr(0 to colon)
                                         value == line.substr(colon to end of line)
                                         event_data[key] == value
                    else:
                        Error Message
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
            else if(get_text)
            {
                if(line.size() == 0)
                    break;
                event_data["Description"].append(line + "\n");
            }
        }
    }
    else
    {
        cout << world_map_file << " not found\n";
    }

    if(event_data.find("Type") == event_data.end())
        event_data["Type"] = "NAV";

    return event_data;
}

// Get nearby locations and Back location
vector<string> Client::get_location_data(string current_location)
{

    vector<pair<string,int> > All_Locations_and_their_tabs = get_All_locations_and_their_num_of_tabs();
    /*
       The Vector holds : Every Location name in World.txt and its number of tabs
       The pair holds   : A Single Location name in World.txt and its number of tabs
    */

    vector<string> near_locations;
    int current_location_tabs;
    int current_location_line;

    // Searching for the current location of the player
    for(unsigned int i = 0; i < All_Locations_and_their_tabs.size(); i++)
    {
        if(current_location == All_Locations_and_their_tabs[i].first)
        {
            near_locations.push_back(current_location);
            current_location_tabs = All_Locations_and_their_tabs[i].second;
            current_location_line = i;
            break;
        }
        if(current_location[0] == '@')
            if(current_location.substr(1,current_location.size()-1) == All_Locations_and_their_tabs[i].first)
                current_location = current_location.substr(1);
    }

    // Searching for locations near the current location of the player
    for(unsigned int i = current_location_line+1; i < All_Locations_and_their_tabs.size(); i++)
    {
        if((All_Locations_and_their_tabs[i].second == 0) || (All_Locations_and_their_tabs[i].second == current_location_tabs))
            break;
        if(current_location_tabs + 1 == All_Locations_and_their_tabs[i].second)
        {
            near_locations.push_back(All_Locations_and_their_tabs[i].first);
        }
    }
    // Searching for the location that that the player goes back to
    if(current_location_tabs > 0)
    {
        for(unsigned int i = current_location_line; i >= 0; i--)
        {
            if(current_location_tabs - 1 == All_Locations_and_their_tabs[i].second)
            {
                near_locations.push_back(All_Locations_and_their_tabs[i].first);
                break;
            }
        }
    }
    return near_locations;
}

// Gets Locations and their tab count from World.txt
vector<pair<string,int> > Client::get_All_locations_and_their_num_of_tabs()
{

    vector<pair<string,int> >All_locations_and_their_num_of_tabs;
    /*
        When The function ends ...
        The Vector holds : Every Location name and its amount of tabs in World.txt
        The pair holds : A Single Location name and the amount of tabs it has in World.txt 
    */

    ifstream file_in(world_map_file);
    if(file_in.is_open())
    {
        string line;
        // counting and cutting spaces of line
        while(getline(file_in,line))
        {
            int spaces = 0;
            while(line[0] == ' ')
            {
                line = line.substr(1);
                spaces++;
            }
            while(line.back() == ' ')
                line.pop_back();

            // insert location name and its tab count
            All_locations_and_their_num_of_tabs.push_back({line,spaces/4});
        }
        file_in.close();
    }
    else
    {
        cout << world_map_file << "could not be found.\n";
    }
    return All_locations_and_their_num_of_tabs;
}



// Cuts all spaces off start and end of string
void Client::cut_spaces_off_ends(string &str)
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






