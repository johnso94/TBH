
#include"Client.h"

void Client::run()
{
    if(event_data["Type"] == "Select")
        select();
    
    switch(str_to_enum(event_data["Type"]))
    {
        case NAV:
            navigation();
            break;
        case MONSTER:
            combat();
            break;
        case ERROR:
            cerr << "Event type " << event_data["Type"] << " is not a valid type." << "\n";
            break;
        default:
            cerr << "Event type " << event_data["Type"] << " is not a valid type." << "\n";
    }
}


void Client::select()
{
    string possible_events = event_data["Events"];
    string chance_of_each_event = event_data["Chance"];
    string selected_event = select_a_event_based_on_its_likelyhood_of_happening(possible_events,chance_of_each_event);
    event_data = get_data("Events.txt",selected_event);
    current_event = event_data["Name"];
    set_value("Game.txt","Event:",current_event);
}

void Client::navigation()
{
    // Get user input within specified parameters
    int min_input = 1;
    int max_input = current_location.get_num_of_near_locations();
    int user_input = get_yaml_input(min_input,max_input);

    // If user input is Invalid. Get_user_input returns -1
    if(user_input == -1)
    {
        print_to_yaml(current_location.to_str() + "\nInvalid Input");
    }
    // if user_input is Valid. 
    else
    {
        current_event = current_location.get_near_locations()[user_input];
        set_value("Game.txt","Event:",current_event);
        print_event_to_yaml();
    }
}

void Client::print_event_to_yaml()
{
    string display_text;

    current_event = get_str_value("Game.txt","Event:");
    event_data = get_data("Events.txt",current_event);

    if(event_data["Type"] == "Select")
        select();

    switch(str_to_enum(event_data["Type"]))
    {
        case NAV:
            current_location.set_location_values(event_data);
            display_text = current_location.to_str() + "\n";
            break;
        case MONSTER:
            current_monster.set_monster_values(event_data);
            display_text = current_monster.to_str() + "\n";
            break;
        case ERROR:
            cerr << "Event type" << event_data["Type"] << " is not a valid type." << "\n";
            break;
        default:
            cerr << "Event type" << event_data["Type"] << " is not a valid type." << "\n";
    }
    print_to_yaml(display_text);
}


void Client::combat()
{
    int user_input = get_yaml_input(1,2);

    string back_location;

    switch(user_input)
    {
        case -1:
            print_to_yaml(current_monster.to_str() + "\n\nInvalid Input");
            break;
        case 1:
            print_to_yaml(current_monster.to_str() + "\n\nThe " + current_event + " didn't stand a chance against you");
            current_event = get_str_value("Game.txt","Back to:");
            print_event_to_yaml();
        case 2:
            print_to_yaml(current_monster.to_str() + "\n\n");
            back_location = get_str_value("Game.txt","Back to:");
            set_value("Game.txt","Event:",back_location);
            print_event_to_yaml();
    }
}






