#ifndef _LOCATION_
#define _LOCATION_

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include"Util.h"

using namespace std;

class Location : public Util
{
    bool is_conversation;
    string name;
    string title;
    bool has_back_location;
    string description;
    vector<string> near_locations;
public:
    Location()
    {
        title = "none";
        name = "Not Found";
        description = "";
    }
    ~Location(){}

    // Functions for getting values of Location
    int get_num_of_near_locations() {return near_locations.size()-1;}
    vector<string> get_near_locations(){return near_locations;}
    string get_name() {return name;}



    /*  Creates the Following string

        ### Location name ###

        Location Description

        [1] nearby location 1
        [2] nearby location 2
        ...
        [n] Back
    */

    string to_str();

    // Functions that search through WOrld.txt and find locations near itself
    void search_for_near_locations(string location_name);
    void set_location_values(map<string,string> location_data);
    vector<pair<string,int> > get_All_locations_and_their_num_of_tabs();

};

#endif