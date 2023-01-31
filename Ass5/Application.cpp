//Kareem A. Mohammed Talaat 
//900192903
//Assignment 5


#include "hashTable.h"
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	hashTable<string, vector<string>> table(951, string("Empty"));  //here we construct the hash table which will consist the cities
	ifstream mcity;  //here we just read the file normally as before using fstreams
	mcity.open("MCity List.csv");
	string city; //here we declare a variable which we will use to store the value of the cities (keys)
	string lon, lat, country;  //here we declare the longitive and latitude and country for the keys (data)
	vector<string> temp;  //here we declare a vector to hold the data to be passed into the table
	int c;
	if (mcity.is_open())  //we check if the if the folder is opened
	{
		while (!mcity.eof())  //we make a loop to enter all the keys and data into the hash table until we reach the end of file of the list to be read.
		{
			getline(mcity, city, ','); //here we read the keys
			getline(mcity, lat, ',');  //here we read the data (lat and lon and country)
			getline(mcity, lon, ',');
			getline(mcity, country, '\n');
			for (int o = 0; o < city.length(); o++)  //here we set all keys to uppercase characters to make the search for those keys more accurate
			{
				city[o] = toupper(city[o]);
			}
			vector<string> temp = { lat, lon, country }; //here we store the lat and lon and country into the vector (data)
			table.insert(city, temp);  //here we inset the city (key) and the vector (data)
			temp.clear(); //here we reset the vector to hold new values again when the loop restarts
		}
		while (1)
		{
			system("cls");  //here we clear the screen
			cout << "Please choose one of the following options: \n";  //here we ask the user to make an input which will decide what will happen next
			cout << "(1) Insert a new city into the list\n";
			cout << "(2) Enter city name to retrieve its information\n";
			cout << "(3) Update data of a city\n";
			cout << "(4) Show all cities in the table\n";
			cout << "(5) Exit the program\n";
			cout << "Please Enter your choice: ";
			cin >> c; // c is the choice of the user
			switch (c) { //here make a swtich case which depends on the user input
			case 1:
				cout << "\nPlease enter the name of city at which the data would be inserted: ";
				cin >> city;  //here we store the new city name from the user
				for (int o = 0; o < city.length(); o++) //here we make all characters to uppercase so we can compare it with the cities in the list
				{
					city[o] = toupper(city[o]);
				}
				cout << "Please enter the city's Latitude: ";  //here we store the data (lat and lon and country) then store them in the vector
				cin >> lat; 
				cout << "Please enter the city's longitude: ";
				cin >> lon;
				cout << "Please enter the city's country: ";
				cin >> country;
				cout << endl;
				temp = { lat, lon, country }; 
				table.insert(city, temp); //here we insert the new city and its data into the data
				cout << "\nInserted successfuly..\n";
				system("pause");  //here we pause for the user
				break;
			case 2:
				cout << "\nPlease enter the name of the city: ";
				cin >> city;  //here we store the city name to retreive its information
				for (int o = 0; o < city.length(); o++) //here we make all characters to uppercase so we can compare it with the cities in the list
				{
					city[o] = toupper(city[o]);
				}
				
				if (table.search(city) == false) //here we apply the hamming distance equation, if the city was not found in the table
				{
					int matches = 0; //we set the number of character matches to 0
					int distance = 0; //we set the distance that changes with every loop to 0
					int minDistance = 99999999; //we set the mindistance between cities really high to be changed later by another lower mindistance between citites
					
					for (int i = 0; i < table.occupancy(); i++) //here we make a loop to compare all the cities's characters in the table with the city that is required to find its match through hamming disantace
					{
						string city2 = table.retrieveKey(); //here we set a variable city2 to the current tablekey
						
						int smallLength = min(city.length(), city2.length()); //here we set the number of min number of characters to be checked between the two cities
						for (int j = 0; j < smallLength; j++) //here we make a loop to check for the matches between the two cities' names
						{
							if (city[j] == city2[j])
							{
								matches++;
							}
						}
						distance = max(city.length(), city2.length()) - matches; //here we apply the hamming distance equation
						if (distance < minDistance) //here we check if that new distance is less than the mindistance from last loop 
						{
							minDistance = distance; //here we set the mindisantace to the lowest distance found
							table.retrieveData(temp); //here we get the data of the current key 
						}
						table.advance(); //here we move the cursor in the table to the next key and repeat untill we go though the whole list and get the mindistance
					}
					cout << "\nCouldn't find this city, but here is the data of the closest city match: \n";  //here we display the results
					cout << "City's Latitude: " << temp[0] << endl;
					cout << "City's longitude: " << temp[1] << endl;
					cout << "City's country: " << temp[2] << endl;
				}
				else 
				{
					table.retrieveData(temp); //if we found the city name in the list we just display its data
					cout << "\nCity found, here is its data: \n";
					cout << "City's Latitude: " << temp[0] << endl;
					cout << "City's longitude: " << temp[1] << endl;
					cout << "City's country: " << temp[2] << endl;
				}
				system("pause");
				break;
			case 3:
				cout << "\nPlease enter the city's name to change its data: "; 
				cin >> city; //here we take the city's name which data will be changed and we change its character to uppercare
				for (int o = 0; o < city.length(); o++)
				{
					city[o] = toupper(city[o]);
				}
				if (table.search(city) == true) //if city is found we ask the user to change the data as follows and we change the data in the table
				{
					cout << "Please enter the city's new Latitude: ";
					cin >> lat;
					cout << "Please enter the city's new longitude: ";
					cin >> lon;
					cout << "Please enter the city's new country: ";
					cin >> country;
					cout << endl;
					temp = { lat, lon, country };
					table.updateData(temp);
					cout << "\nChanged successfuly..\n";
				}
				else cout << "City's name not found" << endl; //if the city is not found we display this
				system("pause");
				break;
			case 4:
				cout << "Displaying all cities: \n"; //here we traverse all cities in the table for the user
				table.traverse();
				cout << endl;

				system("pause");
				break;
			case 5:
					exit(1); //here we exit the program

			default:
					cout << "\nIncorrect input, please choose a valid choice (1~5)\n"; //here we ask the user to enter a valid input
					system("pause");
			}
		}
		table.~hashTable(); //here we deconstruct the table
	}
	system("pause");
	return 0;
}
