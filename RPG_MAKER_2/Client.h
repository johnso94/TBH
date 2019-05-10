#ifndef _CLIENT_H_
#define _CLIENT_H_

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

class Client{
public:
    bool is_int(char a);

    void run();
    void write_current_location_to_txt(string current_location);
    void clear_screen();
    void navigation(vector<string> v);
    void combat(vector<string> v);
    void select(vector<string> v);
    void trim_off_whitespaces(vector<string> &v);
    void trim_off_whitespaces_str(string &str);
    void next_actions(vector<string> v,string str);

    template <typename T>
    int findInVector(const vector<T> & vecOfElements, const T & element);
    int count_tabs(string str);
    int get_user_input(string str,int start, int end);
    int get_current_event_progress(string current_event);

    string get_location_name(string str);
    string get_location_text(string str);
    string get_event_type(string str);
    string get_current_location();
    string get_text_at(string str, char c);
    string get_event_info(string str,int progress);
    string get_player_info();

    vector<string> get_World_Map();
    vector<string> split(string,char c);
    vector<pair<string,string> >get_nearby_locations();

    pair<string,int> get_str_and_int(string str);

};

#endif