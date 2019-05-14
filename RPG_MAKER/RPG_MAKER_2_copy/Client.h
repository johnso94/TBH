#ifndef _CLIENT_H_
#define _CLIENT_H_

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>
#include<map>
#include"sd_fun.h"

using namespace std;

class Client{
public:
    bool is_int(char a);
    void run();
    void clear_screen();
    void navigation(string str, int i);
    void combat(vector<string> v);
    void select(vector<string> v);
    void trim_off_whitespaces(vector<string> &v);
    void trim_off_whitespaces(string &str);
    void set_player_info(string str, string str2);
    void write_value(string str, string str2,string str3);
    void add_progression(string str);

    template <typename T>
    int findInVector(const vector<T> & vecOfElements, const T & element);
    int count_tabs(string str);
    int get_user_input(string str,int start, int end);
    int get_current_event_progress(string current_event);

    string get_location_name(string str);
    string get_location_script(string str);
    string get_value(string str, string str2);
    string get_event_value(int progress,string current_event,string info_type);

    vector<string> get_World_Map();
    vector<string> split(string,char c);
    vector<pair<string,string> >get_nearby_locations(string str, int i);

    bool is_alpha(char c)
    {
        return((c >= 65 && c <= 90) || (c >= 97 && c <= 122));
    }

    bool is_num(char c)
    {
        return(c >= 48 && c <= 57);
    }

    int ctoi(char c)
    {
        return(c - 48);
    }

    void trim_spaces(string &s)
    {
        while(s.back() == ' ')
            s.pop_back();
        while(s[0] == ' ')
            s = s.substr(1);
    }
};

#endif