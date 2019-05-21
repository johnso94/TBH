#ifndef _CLIENT_H_
#define _CLIENT_H_

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include"sd_fun.h"

using namespace std;

class Client{
public:
    bool is_int(char a);

    string find_string(int pos);
    void write_display_text(string str);
    string run();
    void display(string str);
    void navigation2();
    void clear_screen();
    string navigation(vector<string> v);
    void combat(vector<string> v);
    void select(vector<string> v);
    void trim_off_whitespaces(vector<string> &v);
    void trim_off_whitespaces(string &str);
    void set_player_info(string str, string str2);
    void set_pictures(string str);

    template <typename T>
    int findInVector(const vector<T> & vecOfElements, const T & element);
    int count_tabs(string str);
    int get_user_input(string str,int start, int end);
    int get_current_event_progress(string current_event);

    string get_location_name(string str);
    string get_location_script(string str);
    string get_event_info(string str,int progress);
    string get_player_info(string str);

    vector<string> get_World_Map();
    vector<string> split(string,char c);
    vector<pair<string,string> >get_nearby_locations();

};

#endif