//MapLoader.cpp
#include <iostream>
#include <vector>
#include "MapLoader.h"
#include <fstream>
#include<sstream>

using namespace std;


class Territory{
public:
    int id;
    string territory_name;
    int x;
    int y;
    string continent;
    vector <Territory*> neighbours; //should be a pointer that points to neighbours

    Territory(int id, string name, string cont) {//constructor
        territory_name = name;
        continent = cont;
    }
};//endof Territory class

void MapLoader::loadMap(){
    //territory --> pointer
    // a group of territories --> vector 
    cout << "Start loadmap" << endl;

    int t_id = 0;

    std::ifstream file ("/Users/hongsukchoi/CLionProjects/assignment 1/Map/Annys Piratenwelt.map");//should change the path
    std :: string input;
    std::vector <std::string> names;
    vector <Territory> territories;

    while(file >> input){ //skipiing until you hit territories section
        if(!input.compare("[Territories]")) { //compare function returns 0 when it matches so ! would be used for if statement
            cout << "hey it's here" << endl;
            break;
        }
    }
    while(file >> input) { //return file
        //names.push_back(input);
        //parsing a line with delimiter comma
        if (input != "") {//skipping blank line
            vector<string> result;
            stringstream s_stream(input); //create string stream from the string
            while (s_stream.good()) {
                string substr;
                getline(s_stream, substr, ','); //get first string delimited by comma
                result.push_back(substr);
            }


            territories.push_back(Territory(t_id, result[0], result[3]));


            t_id++;//increment of t_id
        }
    }
    for(Territory territory : territories){

        std::cout << territory.territory_name << std::endl;
    }


    for(std::string name : names){

        std::cout << name << std::endl;
    }
    
}
