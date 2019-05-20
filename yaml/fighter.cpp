#include"fighter.h"

    void set_value(string filename, string key, string value)
    {
        ifstream file(filename);
        string game_data = "";
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                size_t key_pos = line.find(key);
                if (key_pos != string::npos)
                {
                    // If key is found in file. Replace its value
                    if (value.back() == '\n')
                        value.pop_back();
                    game_data.append(key + " " + value + "\n");
                }
                else
                {
                    // If key is not found in file. Chance nothing
                    game_data.append(line + "\n");
                }
            }
            file.close();
        }
        else
        {
            cout << game_data << " not found";
        }

        ofstream file_out(filename);
        file_out << game_data;
        file_out.close();
    }
    void cut_spaces_off_ends(string &str)
    {
        if (str.size() > 0)
        {
            while (str[0] == ' ')
            {
                str = str.substr(1);
            }
            while (str.back() == ' ')
            {
                str.pop_back();
            }
        }
    }
    string get_value(string filename, string _key)
    {
        ifstream file(filename);
        string value;
        if (file.is_open())
        {
            string line;
            while (getline(file, line))
            {
                if (line.find(_key) != string::npos)
                {
                    size_t colon_pos = line.find_last_of(':');
                    value = line.substr(colon_pos + 1);
                    cut_spaces_off_ends(value);
                }
            }
            file.close();
        }
        else
        {
            cout << filename << " not found";
        }
        return value;
    }
    int find_len(int pos) { // returns the pos of a string of chars starting at mem[pos].
    int i = 0;
    while (mem[(i++)+pos] != 0);
    return i;
    }

    string get_yaml_input() {
        string str_input;
        Range t_range = find_value(yaml, "content:");
        char testing[t_range.len];
        write_at(testing,0,yaml,t_range);
        str_input = testing;
        return str_input;
    }