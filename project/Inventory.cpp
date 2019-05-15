#include"Inventory.h"
#include<iostream>
using namespace std;

void Inventory::Add_gold(int i){
    gold += i;
}
void Inventory::Remove_gold(int i){
    gold -= i;
}
void Inventory::Add_Inventory(string a){
    v.push_back(a);
}
void Inventory::Remove_Inventory(string a){
    int len = 0;
    while(v[len] != a, len++);
    if (len < v.size() && len >= 0){
        v.erase(v.begin() + len);
    }
}
void Inventory::Add_x_Inventory(string a, int b){
    for (int i=0; i< b; i++){
        Add_Inventory(a);
    }
}
void Inventory::Trade(string a,string b){
    Add_Inventory(a);
    Remove_Inventory(b);
}
string Inventory::Show_Inventory(){
    string t = "";
    t += "gold: ";
    t += gold;
    t+= "\n";
    for(string x : v){
        t += x;
        t += "\n";
    }
    return t;
}