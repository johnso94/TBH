#ifndef _CLIENT_H_
#define _CLIENT_H_

#include<iostream>
#include<fstream>
#include<string>
#include<vector>

using namespace std;

class Client{
public:
    void run();
    void write_current_location_to_txt(string current_location);
    void clear_screen();
    void navigation(vector<string> v);
    void combat(vector<string> v);
    void select(vector<string> v);
    void trim_off_whitespaces(vector<string> &v);

    int count_tabs(string str);
    int get_user_input(string str,int start, int end);

    string get_location_name(string str);
    string get_location_text(string str);
    string get_event_type(string str);
    string get_current_location();
    string get_text_at(string str, char c);
    string get_event_info(string str);
    string get_player_info();

    vector<string> get_World_Map();
    vector<string> split(string,char c);

    vector<pair<string,string> >get_nearby_locations();
};

#endif