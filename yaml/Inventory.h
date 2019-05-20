#ifndef _INVENTORY_
#define _INVENTORY_

#include<iostream>
using namespace std;
#include<vector>
#include<string>
class Inventory{
    int gold;
    vector<string> v;
    public:
    Inventory(){
        gold = 0;
    }
    void Add_gold(int);
    void Remove_gold(int);
    void Add_Inventory(string);
    void Remove_Inventory(string);
    void Add_x_Inventory(string,int b);
    void Trade(string,string);
    string Show_Inventory();
};
#endif //_Inventory_
