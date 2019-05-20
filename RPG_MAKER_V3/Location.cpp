#include "Location.h"

vector<pair<string, int>> Location::get_All_locations_and_their_num_of_tabs()
{
    vector<pair<string, int>> All_locations_and_their_num_of_tabs;
    /*
            When The function ends ...
            The Vector holds : Every Location name and its amount of tabs in World.txt
            The pair holds : A Single Location name and the amount of tabs it has in World.txt 
        */

    ifstream file_in("World.txt");
    if (file_in.is_open())
    {
        string line;
        // counting and cutting spaces of line
        while (getline(file_in, line))
        {
            int spaces = 0;
            if(line.size() > 0)
            {
                while (line[0] == ' ')
                {
                    line = line.substr(1);
                    spaces++;
                }

                while (line.back() == ' ')
                {
                    line.pop_back();
                }
            }
            // insert location name and its tab count
            All_locations_and_their_num_of_tabs.push_back({line, spaces / 4});
        }
        file_in.close();
    }
    else
    {
        cerr << "World.txt"
             << "could not be found.\n";
    }
    return All_locations_and_their_num_of_tabs;
}

void Location::set_location_values(map<string,string> location_data)
{
    has_back_location = true;
    near_locations.clear();
    name = location_data["Name"];
    description = location_data["Description"];

    // Searches through World.txt and fills near_locations with strings
    // that have 1 more tab than it does.

    search_for_near_locations(name);


    if(near_locations.back() == "_NO BACK_")
    {
        near_locations.pop_back();
        has_back_location = false;
    }

    set_value("Game.txt","Event:",name);
    set_value("Game.txt","Background:",name+"_B.png");
    set_value("Game.txt","Forground:",name+"_F.png"); 
}


// Function for creating a string to send to yaml
string Location::to_str()
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
    string display_text = "";

    display_text.append("\n### " + name + " ###\n");
    display_text.append("\n" + description);

    for (unsigned int i = 1; i < near_locations.size(); i++)
    {
        if (i == near_locations.size() - 1 && has_back_location)
        {
            display_text.append("\n[" + to_string(i) + "] Back\n");
        }
        else
        {
            // If a near location starts with a '@' it cuts it off when displaying it
            if(near_locations[i][0] == '@')
                near_locations[i] = near_locations[i].substr(1);
            
            display_text.append("\n[" + to_string(i) + "] " + near_locations[i]);
        }
    }

    display_text.append("\n");

    return display_text;
}

void Location::search_for_near_locations(string location_name)
{
    vector<pair<string,int> > All_Locations_and_their_tabs = get_All_locations_and_their_num_of_tabs();
    /*
    The Vector holds : Every Location name in World.txt and its number of tabs
    The pair holds   : A Single Location name in World.txt and its number of tabs
    */

    if(location_name.size() == 0)
    {
        cerr << "Value for key \"Event:\" in World.txt is blank" << "\n";
        near_locations.push_back(location_name);
        near_locations.push_back(All_Locations_and_their_tabs[0].first);
        return;
    }

    int current_location_tabs;
    int current_location_line;
    bool location_found = false;

    near_locations.push_back(location_name);


    // Searching for the current location of the player
    for(unsigned int i = 0; i < All_Locations_and_their_tabs.size(); i++)
    {
        if(location_name == All_Locations_and_their_tabs[i].first)
        {
            current_location_tabs = All_Locations_and_their_tabs[i].second;
            current_location_line = i;
            location_found = true;
            break;
        }
        if(location_name[0] == '@')
        {
            location_name = location_name.substr(1);
        }
    }
    if(!location_found)
    {
        cerr << "Location \"" << location_name << "\" not found in World.txt\n";
        near_locations.push_back(All_Locations_and_their_tabs[0].first); 
        return;
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

}