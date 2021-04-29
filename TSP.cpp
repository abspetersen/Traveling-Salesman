//
//  Salesman.hpp
//  TravelingSalesman
//
//  Created by Abby petersen on 10/25/20.
//  Copyright © 2020 Abby petersen. All rights reserved.
//

#ifndef Salesman_hpp
#define Salesman_hpp

#include <iostream>
#include <stdio.h>

using namespace std;

class Salesman{
private:
    string ident_path;
    int distance;
public:
    Salesman();
    ~Salesman();
    string getIdent_path();
    int getDistance();
    void setDistance(int d);
    void setIdentPath(string identPath);
    int fitness(double distanceOfNewPath, int temp);

};

#endif /* Salesman_hpp */

#include "Salesman.hpp"
#include <iostream>



Salesman::~Salesman(){
    distance = 0;
    ident_path = " ";
}

int Salesman::getDistance(){
    return distance;
}

string Salesman::getIdent_path(){
    return ident_path;
}

void Salesman::setDistance(int d){
    distance = d;
}

void Salesman::setIdentPath(string identPath){
    ident_path = identPath;
}

//fitness function
int Salesman::fitness(double newPathD, int temp){
    int fitness = 0;
    if(temp > 9000 && temp < 10000 && newPathD >= 2 && newPathD < 5.8 ){
        fitness = 9000;
    }
    else if(temp > 7000 && temp <= 9000 && newPathD >= 5.8 && newPathD < 9.6){
        fitness = 8000;
    }
    else if(temp > 5000 && temp <= 7000 && newPathD >= 9.6 && newPathD < 13.4){
        fitness = 6000;
    }
    else if(temp > 3000 && temp <= 5000 && newPathD >= 13.4 && newPathD < 17.2){
        fitness = 4000;
    }
    else if(temp > 1000 && temp <= 3000 && newPathD >= 17.2 && newPathD <= 21){
        fitness = 2000;
    }
    else if(temp == 10000 && newPathD == 21){
        fitness = 10000;
    }

    return fitness;

}




//  travelingSalesman.hpp
//  TravelingSalesman
//
//  Created by Abby petersen on 10/24/20.
//  Copyright © 2020 Abby petersen. All rights reserved.


#ifndef TravelingSalesman_hpp
#define TravelingSalesman_hpp

#include "Salesman.hpp"
#include <stdio.h>
#include <iostream>


using namespace std;

class TravelingSalesman{

private:
    int **distanceChart;
    int numLocations;
    static int start_val;
    int populationSize;
    int *path_array;
    int path_size;
    static int *location_list;


public:

    TravelingSalesman();
    ~TravelingSalesman();
    int** ConstructAndReturnTSPMap();
    bool char_check(string ident_string, char ch);
    int CalcAndGetDistance(string ident_string);
    int getRandomNum(int start, int end);
    string createIdentString();
    string stringMutationFunc(string ident_string);
    void travelingSalesmanAlg(int **distanceChart);
    bool compareDistances(Salesman *s1, Salesman *s2);
    int getTemp(int temp);
    void setPopulationSize(int populationSize);

};

#endif /* travelingSalesman_hpp */

//  travelingSalesman.cpp
//  TravelingSalesman
//
//  Created by Abby petersen on 10/24/20.
//  Copyright © 2020 Abby petersen. All rights reserved.

#include "TravelingSalesman.hpp"
#include <vector>
#include <limits.h>
#include <algorithm>
#include <cmath>
#include <cstddef>

TravelingSalesman::TravelingSalesman(){
    numLocations = 9;
    distanceChart = new int* [numLocations];
    path_array = new int [path_size];
    start_val = 0;
    populationSize = 0;
    path_size = 0;

    for(int i = 0; i < 9;i++){
        location_list[i] = (i+1);
    }
}

int** TravelingSalesman::ConstructAndReturnTSPMap(){

    distanceChart[1][1] = 0;
    distanceChart[1][2] = 2;
    distanceChart[1][3] = INT_MAX;
    distanceChart[1][4] = 12;
    distanceChart[1][5] = 7;

    distanceChart[2][1] = 13;
    distanceChart[2][2] = 10;
    distanceChart[2][3] = 5;
    distanceChart[2][4] = 0;
    distanceChart[2][5] = INT_MAX;


    distanceChart[3][1] = INT_MAX;
    distanceChart[3][2] = 4;
    distanceChart[3][3] = 8;
    distanceChart[3][4] = 12;
    distanceChart[3][5] = 6;


    distanceChart[4][1] = 14;
    distanceChart[4][2] = 8;
    distanceChart[4][3] = 3;
    distanceChart[4][4] = 0;
    distanceChart[4][5] = 10;

    distanceChart[5][1] = 0;
    distanceChart[5][2] = INT_MAX;
    distanceChart[5][3] = 3;
    distanceChart[5][4] = 10;
    distanceChart[5][5] = 0;



    return distanceChart;
}

void TravelingSalesman::setPopulationSize(int populationSize1){
    populationSize = populationSize1;
}


//returns the distance of a path's identifying string
int TravelingSalesman::CalcAndGetDistance(string ident_string){

    int **TSPMap = ConstructAndReturnTSPMap();
    int x = 0;
    for(int i = 0; i < ident_string.size() - 1;i++){
        if(TSPMap[ident_string[i] - 48] [ident_string[i+1] - 48] == INT_MAX){
            return INT_MAX;
        }
        else{
            x = TSPMap[ident_string[i] - 48] [ident_string[i+1] - 48];
        }
    }
    return x;
}

//makes sure there's no repeats: checks if the character has already occured in the string that identifies the path
bool TravelingSalesman::char_check(string ident_string, char character){
    for(int i = 0; i < ident_string.size(); i++){
        if(ident_string[i] == character){
            return true;
        }
    }
    return false;
}

//compares identifying path values that are members of salesman class
bool TravelingSalesman::compareDistances(Salesman *s1, Salesman *s2){
    bool isLessThan = false;
    isLessThan = s1->getDistance() < s2->getDistance();
    return isLessThan;
}

//returns random number between the start and finish
int TravelingSalesman::getRandomNum(int start, int end){
    int random = (start + rand() % (end - start));
    return random;
}

//two genes are randomly interchanged to create a variation in species
//- which is stored in the ident_string string
//mutated ident_string string is returned
string TravelingSalesman::stringMutationFunc(string ident_string){
    while(true){
        int random = getRandomNum(1,9);
        int random2 = getRandomNum(1,9);
        if(random2 != random){
            char temp = ident_string[random];
            ident_string[random] = ident_string[random2];
            ident_string[random2] = temp;
            break;
        }
    }
    return ident_string;
}


//returns the updated value of the temperature
int TravelingSalesman::getTemp(int temp){
    int newTemp = (90 * temp) / 100;
    return newTemp;
}

//function returns a valid identifier string
//identifier string is needed to create population
string TravelingSalesman::createIdentString(){
    string identString = "0";

    while(true){
        if(identString.size() == 9){
            identString += identString[0];
            break;
        }

        int temp = getRandomNum(1,9);

        if(char_check(identString,(char)(temp + 48)) == false){
            identString += (char)(temp + 48);
        }
    }
    return identString;
}

//executes algorithm by calling other functions
void TravelingSalesman::travelingSalesmanAlg(int **distanceChart){

    int generationNum = 1;
    int numOfGeneIterations = 5;
    vector<Salesman*> population;
    vector<Salesman*> locations;
    vector<Salesman*> new_locations;
    Salesman *s = new Salesman();
    Salesman *s1 = new Salesman();

    for(int i = 0; i < populationSize; i++){
        s->setIdentPath(createIdentString());
        s->setDistance(CalcAndGetDistance(s->getIdent_path()));
        population.push_back(s);
    }

    cout << "Cities: " << endl;
    cout << "Path Value." << endl;

    for(int i = 0; i < populationSize; i++){
        cout << locations[i]->getIdent_path() << " " << locations[i]->getDistance() << endl;
    }

    //bool wasFound = false;
    int temp = 10000;

    //crossing and mutation
    while((temp > 1000) && (generationNum <= numOfGeneIterations)){
        sort(locations.begin(), locations.end(), compareDistances(<#Salesman *s1#>, <#Salesman *s2#>));
             for(int i = 0; i < populationSize; i++){
                s1 = locations[i];

              while(true) {
                string new_identString = stringMutationFunc(s1->getIdent_path());
                Salesman *new_s = new Salesman();
                new_s->setIdentPath(new_identString);
                new_s->setDistance(CalcAndGetDistance(new_s->getIdent_path()));

                if(new_s->getDistance() <= locations[i]->getDistance()){
                    new_locations.push_back(new_s);
                    break;
                }

                else{

                    //fitness function is called to determine probability
                    //if probability is above threshold - path is added
                    double probability = pow(2.7, (-1 * ((double)new_s->getDistance() - (locations[i]->fitness((double)(new_s->getDistance()), temp) / temp))));

                    if(probability > 0.5){
                        new_locations.push_back(new_s);
                        break;
                    }
                }
        }
    }

    temp = getTemp(temp);
    locations = new_locations;

    cout << "Generation " << generationNum << endl;
    cout << "Path distance " << endl;

    for(int i = 0; i < populationSize; i++){
        cout << locations[i]->getIdent_path() << " " << locations[i]->getDistance() << endl;
    }

generationNum++;
}
}

//main file
#include "TravelingSalesman.hpp"

using namespace std;

int main() {

    //change population size for different tests
    int populationSize = 100;
    //construct distance chart using 2D arrays that use the int_max variable that is  private member of traveling salesman class
    int **TSPMap;
    TravelingSalesman* TSP = new TravelingSalesman();
    TSP->setPopulationSize(populationSize);
    TSPMap = TSP->ConstructAndReturnTSPMap();
    //call findpath function that is a member of traveling salesman class - to excecute traveling salesman algorithm
    TSP->travelingSalesmanAlg(TSPMap);
    return 0;
}
