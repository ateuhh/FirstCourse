#include "Settings.h"

settings::settings(std::string const & filename) {
	file = filename;
	reload();
}

void settings::set(std::string const & name, std::string const & value) {
	VerifyData();
	Settings[name] = value;
	settings::keep();
}

void settings::reset() {
	VerifyData();
	ofstream cout (file);
	Settings.clear();
	cout.close();
}

void settings::reload() {
	VerifyData();
	Settings.clear();
	ifstream cin (file);
	string set, value;
	while (cin) {
		getline(cin, set, ' ');
		getline(cin, value);
		Settings[set] = value;
	}
	cin.close();
}


std::string const & settings::get(std::string const & name, std::string const & def) const {
	if (Settings.count(name) != 0)
		return Settings.at(name);
	else 
	        return def;
	
}


void settings::keep() {
	VerifyData();
	ofstream cout (file);
	map <string,string>::iterator keeper;
	keeper = Settings.begin();
	while ( keeper < Settings.end() ){
		cout << (*keeper).first << " " << (*keeper).second << endl;
		keeper++;
	}
	cout.close();
}



void settings::VerifyData() {
	if (file == "") {
		file = "helpfile.txt";
	}
}
