#include"Client.h"

string Client::get_display_text()
{
    nearby_locations.clear();
    World.clear();
    str_to_Location.clear();

    string current_location = get_str_value("Game.txt","Location:");
    World = Get_All_Locations();
    nearby_locations = get_nearby_locations(current_location,World);

    for(auto elem : World)
    {
		if(str_to_Location.find(elem.name) == str_to_Location.end())
		{
			str_to_Location[elem.name] = elem;
		}
    }

    string display_text = "";

    Location location;
    for(unsigned int i = 0; i < nearby_locations.size(); i++)
    {
        Location location = str_to_Location[nearby_locations[i]];
        if(i == 0)
        {
            display_text.append("### " + location.title + "###\n\n");
            display_text.append(location.description + "\n");
        }
        else
        {
			if(location.script[0] == '@')
			{
				location.script = location.script.substr(1);
				display_text.append("[" + to_string(i) + "] Go to " + location.script + "\n");
			}
			else
			{
				display_text.append("[" + to_string(i) + "] " + location.script + "\n");
			}
        }
    }
    location = str_to_Location[nearby_locations[0]];
    if(location.back != "None")
    {
        int size = nearby_locations.size();
        display_text.append("[" + to_string(size) + "] " + "Back to " + location.back + "\n");
        nearby_locations.push_back(location.back);
    }
    return display_text;
}

void Client::run()
{
    int min_input = 1;
    int max_input = nearby_locations.size();
    int user_input = get_yaml_input(min_input,max_input);

    // If user input is Invalid. Get_user_input returns -1
    if(user_input == -1)
    {
        print_to_yaml(get_display_text() + "\n Invalid Input");
    }
    // if user_input is Valid. 
    else
    {
        string current_location = nearby_locations[user_input];
		if(current_location[0] == '@')
		{
			current_location = current_location.substr(1);
		}
        string foreground = str_to_Location[current_location].get_forground();
        string background = str_to_Location[current_location].get_background();
        set_value("Game.txt","Location:",current_location);
        set_value("Game.txt","Foreground:",foreground);
        set_value("Game.txt","Background:",background);
        print_to_yaml(get_display_text());
    }
}




vector<Location> Client::Get_All_Locations()
{
	fstream in_file("World.txt");

	vector<Location> World_Map;
	bool get_description = false;
	if(in_file.is_open())
	{
		string line;
		string description;
		int dash_count = 0;
		Location location;
		while(getline(in_file,line))
		{
			size_t bracket_pos;
			if(line.find('{') != string::npos)
			{
				string name;
				int tabs;
				// Count and Cut the tabs of the line
				if(line.size() > 0)
				{
					int spaces = 0;
					while (line[0] == ' ')
					{
						line = line.substr(1);
						spaces++;
					}

					while (line.back() == ' ')
					{
						line.pop_back();
					}
					tabs = spaces/4;
				}

				// Get name of line ... Name { Values } 
				bracket_pos = line.find("{");
				name = line.substr(0,bracket_pos);
				while (name.back() == ' ')
					name.pop_back();
				
				location.name = name;
				location.tabs = tabs;

				// Get Values of line ... Name { Values } 
				string values_str = line.substr(bracket_pos);
				values_str = values_str.substr(1, values_str.size() - 2 );
				vector<string> values_vec = split(values_str,',');
				map<string,string> key_to_value;
				for(auto elem : values_vec)
				{
					size_t equal_pos = elem.find('=');
					if(equal_pos != string::npos)
					{
						string key = elem.substr(0,equal_pos);
						string value = elem.substr(equal_pos+1);
						cut_spaces_off_ends(key);
						cut_spaces_off_ends(value);
						key_to_value[key] = value;
					}
				}

				// If no values where set give location default values
				for(string elem : {"Title","Script","Background","Foreground","Back"})
				{
					if(key_to_value.find(elem) == key_to_value.end())
					{
						if((elem == "Title") || (elem == "Script"))
						{
							key_to_value[elem] = name;
						}
						else if(elem == "Background")
						{
							key_to_value[elem] = "white.png";
						}
						else if(elem == "Foreground")
						{
							key_to_value[elem] = "nothing.png";
						}
						else if(elem == "Back")
						{
							key_to_value[elem] = "None";
						}
					}
				}

                location.set_back(key_to_value["Back"]);
                location.set_script(key_to_value["Script"]);
                location.set_title(key_to_value["Title"]);
                location.set_background(key_to_value["Background"]);
                location.set_foreground(key_to_value["Foreground"]);
				if(location.name[0] == '@')
				{
					World_Map.push_back(location);
					get_description = false;
				}
				else
				{
					get_description = true;					
				} 
			}
			else if(get_description)
			{
				cut_spaces_off_ends(line);
				if(line == "-")
					dash_count++;

				if(dash_count >= 2)
				{
					location.set_description(description);
					World_Map.push_back(location);
					description = "";
					get_description = false;
					dash_count = 0;
				} 
				else
				{
					if(line != "-")
						description.append(line + "\n");
				}
			}
		}
		in_file.close();
	}
	else
	{
		cerr << "World.txt could not be found\n";
	}
	return World_Map;
}

vector<string> Client::get_nearby_locations(string location_name, vector<Location> World)
{
	int current_location_tabs;
	int current_location_index;
	vector<string> near_locations;
	for(unsigned int i = 0; i < World.size(); i++)
	{
		if(location_name == World[i].name)
		{
			current_location_tabs = World[i].tabs;
			current_location_index = i;
			near_locations.push_back(World[i].name);
			break;
		}
	}
	// Searching for locations near the current location of the player
	for(unsigned int i = current_location_index+1; i < World.size(); i++)
	{
		if((World[i].tabs == 0) || (World[i].tabs == current_location_tabs))
			break;
		if(current_location_tabs + 1 == World[i].tabs)
		{
			near_locations.push_back(World[i].name);
		}
	}
	if(near_locations.size() == 0)
	{
		near_locations.push_back(location_name + "Not found in World.txt");
	}

	return near_locations;
}




















































// void Client::run()
// {
//     if(event_data["Type"] == "Select")
//         select();
    
//     switch(str_to_enum(event_data["Type"]))
//     {
//         case NAV:
//             navigation();
//             break;
//         case MONSTER:
//             combat();
//             break;
//         case ERROR:
//             cerr << "Event type " << event_data["Type"] << " is not a valid type." << "\n";
//             break;
//         default:
//             cerr << "Event type " << event_data["Type"] << " is not a valid type." << "\n";
//     }
// }




























// void Client::select()
// {
//     string possible_events = event_data["Events"];
//     string chance_of_each_event = event_data["Chance"];
//     string selected_event = select_a_event_based_on_its_likelyhood_of_happening(possible_events,chance_of_each_event);
//     event_data = get_data("Events.txt",selected_event);
//     current_event = event_data["Name"];
//     set_value("Game.txt","Event:",current_event);
// }

// void Client::navigation()
// {
//     // Get user input within specified parameters
//     int min_input = 1;
//     int max_input = current_location.get_num_of_near_locations();
//     int user_input = get_yaml_input(min_input,max_input);

//     // If user input is Invalid. Get_user_input returns -1
//     if(user_input == -1)
//     {
//         print_to_yaml(current_location.to_str() + "\nInvalid Input");
//     }
//     // if user_input is Valid. 
//     else
//     {
//         current_event = current_location.get_near_locations()[user_input];
//         set_value("Game.txt","Event:",current_event);
//         print_event_to_yaml();
//     }
// }

// void Client::print_event_to_yaml()
// {
//     string display_text;

//     current_event = get_str_value("Game.txt","Event:");
//     event_data = get_data("Events.txt",current_event);

//     if(event_data["Type"] == "Select")
//         select();

//     switch(str_to_enum(event_data["Type"]))
//     {
//         case NAV:
//             current_location.set_location_values(event_data);
//             display_text = current_location.to_str() + "\n";
//             break;
//         case MONSTER:
//             current_monster.set_monster_values(event_data);
//             display_text = current_monster.to_str() + "\n";
//             break;
//         case ERROR:
//             cerr << "Event type" << event_data["Type"] << " is not a valid type." << "\n";
//             break;
//         default:
//             cerr << "Event type" << event_data["Type"] << " is not a valid type." << "\n";
//     }
//     print_to_yaml(display_text);
// }


// void Client::combat()
// {
//     int user_input = get_yaml_input(1,2);

//     string back_location;

//     switch(user_input)
//     {
//         case -1:
//             print_to_yaml(current_monster.to_str() + "\n\nInvalid Input");
//             break;
//         case 1:
//             print_to_yaml(current_monster.to_str() + "\n\nThe " + current_event + " didn't stand a chance against you");
//             current_event = get_str_value("Game.txt","Back to:");
//             print_event_to_yaml();
//         case 2:
//             print_to_yaml(current_monster.to_str() + "\n\n");
//             back_location = get_str_value("Game.txt","Back to:");
//             set_value("Game.txt","Event:",back_location);
//             print_event_to_yaml();
//     }
// }






