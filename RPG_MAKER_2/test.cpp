#include<iostream>
#include<fstream>
#include<string>
#include<map>

using namespace std;

int get_current_event_progress(string current_event)
{
    fstream file("progression.txt");
    string line;
    string file_str = "";
    bool found;
    int progress = 0;
    if(file.is_open())
    {
        size_t last_space;
        while(getline(file,line))
        {
            file_str += line + "\n";
            size_t last_space = line.find_last_of(' ');
            string event = line.substr(0,last_space);
            if(event == current_event)
            {
                found = true;
                progress = stoi(line.substr(last_space));
            }
        }
        if(!found)
        {
            file_str += current_event + " 0";
            ofstream file_out("progression.txt");
            file_out << file_str;
            file_out.close();
        }
    } 
    else 
        cout << "progression.txt was not found\n";
    return progress;
}


int main(){

    string current_event = "Blue Waves";
    

    cout << get_current_event_progress(current_event) << "\n";

    


    return 0;
}