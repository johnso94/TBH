#ifndef _UTIL_
#define _UTIL_

#include<iostream>
#include<vector>
#include<map>
#include<fstream>
#include"sd_fun.h"

using namespace std;

class Util
{
public:

    /////////////////////////////////////////////
    // Funcations that interact with TXT files //
    /////////////////////////////////////////////

    void set_value(string filename, string key, string value);

    void set_value(string filename, string key, int _value);

    bool find_key(string filename, string key);

    void delete_key(string filename, string key);

    void create_key(string filename, string key);

    string get_str_value(string filename,string _key);

    int get_int_value(string filename, string key);

    void minus_value(string filename, string key, int minus_int);

    void add_value(string filename, string key, int add_int);

    map<string,string> get_data(string filename,string current_event);

    //////////////////////////////////////////
    // Functions that interact with strings //
    //////////////////////////////////////////

    bool is_int(char c);

    bool is_int(string str);

    void cut_spaces_off_ends(string &str);
    void cut_spaces_off_ends(vector<string> &v);

    vector<string> split(string str, char c);

    //////////////////////////////////////////
    // Functions that interact with strings //
    //////////////////////////////////////////

    string select_a_event_based_on_its_likelyhood_of_happening(string _events, string chance_of_event_happening);

    //////////////////////////////////////
    // Funcions that interact with yaml //
    //////////////////////////////////////

    int get_yaml_input(int min,int max);
    void print_to_yaml(string display_text);
};

#endif