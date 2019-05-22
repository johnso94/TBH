#ifndef _LOCATION_
#define _LOCATION_

#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<fstream>
#include"Util.h"

using namespace std;

class Location
{
public:
    int tabs;
    string name;
    string title;
    string script;
    string description;
    string foreground;
    string background;
    string back;
    void display()
    {
        cerr << "Name: " << name << endl;
        cerr << "Title: " << title << endl;
        cerr << "Script: " << name << endl;
        cerr << "Foreground: " << foreground << endl;
        cerr << "Background: " << background << endl;
        cerr << "Tabs : " << tabs << endl;
        cerr << "Back : " << back << endl;
        cerr << "Descripon : " << description << endl;
        cerr << "\n";
    }
    void set_name(string _name){name = _name;}
    void set_title(string _title){title = _title;}
    void set_script(string _script){script = _script;}
    void set_description(string _description){description = _description;}
    void set_foreground(string _foreground){foreground = _foreground;}
    void set_background(string _background){background = _background;}
    void set_back(string _back){back = _back;}

    string get_forground(){return foreground;}
    string get_background(){return background;}

    vector<Location> get_all_Locations;
};

#endif