#include<iostream>
#include<vector>
#include<map>
#include<fstream>

using namespace std;

void cut_spaces_off_ends(string &str)
{
	if(str.size() > 0)
	{
		while(str[0] == ' ')
			str = str.substr(1);
		while(str.back() == ' ')
			str.pop_back();
	}
}
void cut_spaces_off_ends(vector<string> &vec)
{
	for(auto &elem : vec)
	{
		cut_spaces_off_ends(elem);
	}
}

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
	vector<Location> nearby_locations;
	void display()
	{
		cout << "Name: " << name << endl;
		cout << "Title: " << title << endl;
		cout << "Script: " << name << endl;
		cout << "Foreground: " << foreground << endl;
		cout << "Background: " << background << endl;
		cout << "Tabs : " << tabs << endl;
		cout << "Back : " << back << endl;
		cout << "Descripon : " << description << endl;
		cout << "\n";
	}
	void set_description(string _description){description = _description;}
};

vector<string> split(const string str, char c)
{
	vector<string> all_words;
	string word = "";
	
	for(unsigned int i = 0; i < str.size(); i++)
	{
		if(str[i] != c)
		{
			word += str[i];
		}
		else
		{
			all_words.push_back(word);
			word = "";
		}
	}
	all_words.push_back(word);
	return all_words;
}


vector<Location> Get_All_Locations()
{
	fstream in_file("World.txt");

	vector<Location> World_Map;
	bool get_description = false;
	if(in_file.is_open())
	{
		string line;
		string description;
		int dash_count = 0;
		Location location;
		while(getline(in_file,line))
		{
			size_t bracket_pos;
			if(line.find('{') != string::npos)
			{
				string name;
				int tabs;
				// Count and Cut the tabs of the line
				if(line.size() > 0)
				{
					int spaces = 0;
					while (line[0] == ' ')
					{
						line = line.substr(1);
						spaces++;
					}

					while (line.back() == ' ')
					{
						line.pop_back();
					}
					tabs = spaces/4;
				}

				// Get name of line ... Name { Values } 
				bracket_pos = line.find("{");
				name = line.substr(0,bracket_pos);
				while (name.back() == ' ')
					name.pop_back();
				
				location.name = name;
				location.tabs = tabs;

				// Get Values of line ... Name { Values } 
				string values_str = line.substr(bracket_pos);
				values_str = values_str.substr(1, values_str.size() - 2 );
				vector<string> values_vec = split(values_str,',');
				map<string,string> key_to_value;
				for(auto elem : values_vec)
				{
					size_t equal_pos = elem.find('=');
					if(equal_pos != string::npos)
					{
						string key = elem.substr(0,equal_pos);
						string value = elem.substr(equal_pos+1);
						cut_spaces_off_ends(key);
						cut_spaces_off_ends(value);
						key_to_value[key] = value;
					}
				}

				// If no values where set give location default values
				for(string elem : {"Title","Script","Background","Foreground","Back"})
				{
					if(key_to_value.find(elem) == key_to_value.end())
					{
						if((elem == "Title") || (elem == "Script"))
						{
							key_to_value[elem] = name;
						}
						else if(elem == "Background")
						{
							key_to_value[elem] = name + "_B.png";
						}
						else if(elem == "Foreground")
						{
							key_to_value[elem] = name + "_F.png";
						}
						else if(elem == "Back")
						{
							key_to_value[elem] = "None";
						}
					}
				}
				location.back = key_to_value["Back"];
				location.script = key_to_value["Script"];
				location.title = key_to_value["Title"];
				location.foreground = key_to_value["Background"];
				location.background = key_to_value["Foreground"];
				get_description = true;
			}
			else if(get_description)
			{
				cut_spaces_off_ends(line);
				if(line == "-")
					dash_count++;

				if(dash_count >= 2)
				{
					location.set_description(description);
					World_Map.push_back(location);
					description = "";
					get_description = false;
					dash_count = 0;
				} 
				else
				{
					if(line != "-")
						description.append(line + "\n");
				}
			}
		}
		in_file.close();
	}
	else
	{
		cout << "World.txt could not be found\n";
	}
	return World_Map;
}

vector<string> get_nearby_locations(string location_name, vector<Location> World)
{
	int current_location_tabs;
	int current_location_index;
	vector<string> near_locations;
	for(unsigned int i = 0; i < World.size(); i++)
	{
		if(location_name == World[i].name)
		{
			current_location_tabs = World[i].tabs;
			current_location_index = i;
			near_locations.push_back(World[i].name);
			break;
		}
	}
	// Searching for locations near the current location of the player
	for(unsigned int i = current_location_index+1; i < World.size(); i++)
	{
		if((World[i].tabs == 0) || (World[i].tabs == current_location_tabs))
			break;
		if(current_location_tabs + 1 == World[i].tabs)
		{
			near_locations.push_back(World[i].name);
		}
	}
	return near_locations;
}

int main()
{
	
string current_location = "Greece";


vector<Location> World;
vector<string> nearby_locations;

World = Get_All_Locations();
nearby_locations = get_nearby_locations(current_location,World);

map<string,Location> str_to_loc;
for(auto elem : World)
{
	str_to_loc[elem.name] = elem;
}

string display_text = "";

Location location;
for(unsigned int i = 0; i < nearby_locations.size(); i++)
{
	Location location = str_to_loc[nearby_locations[i]];
	if(i == 0)
	{
		display_text.append("### " + location.title + "###\n\n");
		display_text.append(location.description + "\n");
	}
	else
	{
		display_text.append("[" + to_string(i) + "] " + location.script + "\n");
	}
}
location = str_to_loc[nearby_locations[0]];
if(location.back != "None")
{
	int size = nearby_locations.size();
	display_text.append("[" + to_string(size) + "] " + "Back\n");
	nearby_locations.push_back(location.back);
}

int user_input;
cout << display_text << "\n";
std::cout << "\n<< ";
std::cin >> user_input;

current_location = nearby_locations[user_input];

// Loop Number 2
World = Get_All_Locations();
nearby_locations = get_nearby_locations(current_location,World);


for(auto elem : World)
{
	str_to_loc[elem.name] = elem;
}

display_text = "";

for(unsigned int i = 0; i < nearby_locations.size(); i++)
{
	Location location = str_to_loc[nearby_locations[i]];
	if(i == 0)
	{
		display_text.append("### " + location.title + "###\n\n");
		display_text.append(location.description + "\n");
	}
	else
	{
		display_text.append("[" + to_string(i) + "] " + location.script + "\n");
	}
}
location = str_to_loc[nearby_locations[0]];
if(location.back != "None")
{
	int size = nearby_locations.size();
	display_text.append("[" + to_string(size) + "] " + "Back\n");
	nearby_locations.push_back(location.back);
}

cout << display_text << "\n";






	return 0;
}