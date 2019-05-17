
#include"Client.h"

void Client::run()
{
    bool event_found = false;
    if(event_data["Type"] == "Select")
    {
        string possible_events = event_data["Events"];
        string chance_of_each_event = event_data["Chance"];
        string selected_event = select_a_event_based_on_its_likelyhood_of_happening(possible_events,chance_of_each_event);
        event_data = get_data("Events.txt",selected_event);
        event_found = true;
    }
    if(event_data["Type"] == "Nav")
    {
        event_found = true;
        navigation();
        return; 
    }
    if(event_data["Type"] == "Combat")
    {
        event_found = true;
        combat();
        return;
    }
    if(!event_found)
    {
        cout << "Event type " << event_data["Type"] << " is not a valid type." <<  "\n";
    }
}

void Client::navigation()
{
    // Get user input within specified parameters
    int min_input = 1;
    int max_input = player_location.get_num_of_near_locations();
    int user_input = get_yaml_input(min_input,max_input);

    // If user input is Invalid. Get_user_input returns -1
    if(user_input == -1)
    {
        print_to_yaml(player_location.to_str() + "\nInvalid Input");
    }
    // if user_input is Valid. 
    else 
    {
        current_event = player_location.get_near_locations()[user_input];
        set_value("Game.txt","Event:",current_event);
        print_event_to_yaml();
    }
}

void Client::print_event_to_yaml()
{
    bool event_found = false;
    event_data = get_data("Events.txt",current_event);
    if(event_data["Type"] == "Nav")
    {
        player_location.set_location_values(event_data);
        set_value("Game.txt","Event:",player_location.get_name());
        set_value("Game.txt","Background:",player_location.get_name()+"_B.png");
        set_value("Game.txt","Forground:",player_location.get_name()+"_F.png"); 
        print_to_yaml(player_location.to_str());
        event_found = true;
    }
    if((event_data["Type"] == "Combat") || (event_data["Type"] == "Select"))
    {
        print_to_yaml("### Combat ###\nComming soon!\n[1] Back");
        event_found = true;
    }
    if(!event_found)
    {
        cout << "Event type " << event_data["Type"] << " is not a valid type." <<  "\n";
    }
}


void Client::combat()
{
    int user_input = get_yaml_input(1,1);
    if(user_input != -1)
    {
        string back_to_event = get_str_value("Game.txt","Back to:");
        set_value("Game.txt","Event:",back_to_event);
        cout << back_to_event << "\n";
        print_event_to_yaml();
    }
}

void Client::set_player_location()
{
    current_event = get_str_value("Game.txt","Event:");
    event_data = get_data("Events.txt",current_event);
    player_location.set_location_values(event_data);
    set_value("Game.txt","Event:",player_location.get_name());
    set_value("Game.txt","Background:",player_location.get_name()+"_B.png");
    set_value("Game.txt","Forground:",player_location.get_name()+"_F.png"); 
    print_to_yaml(player_location.to_str());
}

void Client::set_player_battle()
{
    print_to_yaml("comming soon\n[1] Back");
    set_value("Game.txt","Monster Name:",event_data["Name"]);
    set_value("Game.txt","Monster Strength:",event_data["Str"]);
    set_value("Game.txt","Monster Def:",event_data["Def"]);
    set_value("Game.txt","Monster Description:",event_data["Description"]);
    set_value("Game.txt","Monster Max Hp:",event_data["Hp"]);
    set_value("Game.txt","Monster Current Hp:",event_data["Hp"]);
    set_value("Game.txt","Game State:","Combat");
}