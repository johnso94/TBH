#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include "Inventory.h"
#include <cstdlib>
#include <fstream>

int main()
{
    srand(time(0));
    int roll = rand() % 100;
    cout << roll << endl;

    fstream file("Player_Stats.txt");
    vector<int> test;
    int q = 0;
    int single_stat;
    if (file.is_open())
    {
        while (file >> single_stat)
        {
            test.push_back(single_stat);
        }
    }
    else{
        cout << "file not found";
    }
    for(auto elem : test)
    cout << elem << "\n";
}