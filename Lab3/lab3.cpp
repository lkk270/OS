#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctype.h>
#include <fstream>

#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <array>

using namespace std;

std::string firstLine = ""; 
std::string activities = ""; 
void collectInput(int argc, char *argv[]);
void print2dStringVector(std::vector<vector<string>> arr);
void print1dIntVector(std::vector<int> arr);
std::vector<std::vector<string> > allocateToArray(int num);
void bankers(std::vector<vector<string>> arr, std::vector<int> arr2);
bool is_number(const std::string& s);
std::vector<int > allocateFirstLineToArray();
void print2dIntVector(std::vector<vector<int>> nums);

int main ( int argc, char *argv[] )
{
    collectInput(argc, argv);
    vector<int> firstLineArr = allocateFirstLineToArray();
    vector<vector<string> > tasks( firstLineArr[0] , vector<string> (0));
    tasks = allocateToArray(firstLineArr[0]);
    // print1dIntVector(firstLineArr);
    // // cout<<tasks[1 ].size();
    // cout<<'\n';
    print2dStringVector(tasks);
    // cout<<'\n';
    bankers(tasks, firstLineArr);
    cout<<'\n';
    cout<<'\n';
    cout<<tasks[0][9];

}

std::vector<std::vector<string> > allocateToArray(int numTasks){
    
    vector<vector<string> > tasks( numTasks , vector<string> (0));
    std::string line = "";
    int whichTask = -1;
    int numOfSpaces = 0;
    for(char const &c: activities){
        line += c;
        if(c== '\n'){
            numOfSpaces = 0;
            std::string wordTemp = "";
            char charTemp;
            for(char const &cc: line){
               
                wordTemp += cc;
                if(numOfSpaces > 0 && is_number(wordTemp)){
                    whichTask = stoi(wordTemp);
                    tasks[whichTask-1].push_back(line += ' ');
                    break;

                }
                else if(cc == ' '){
                    numOfSpaces++;
                    wordTemp = "";
                }
            }
            line = "";
        }    
  
    }
    
    return tasks;
}


bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

void print2dStringVector(std::vector<vector<string>> tasks){
    for ( const std::vector<string> &v : tasks ){
        for ( std::string x : v ) std::cout << x << ' ';
            std::cout << std::endl;
    }
}

void print2dIntVector(std::vector<vector<int>> nums){
    for ( const std::vector<int> &v : nums ){
        for ( int x : v ) std::cout << x << ' ';
            std::cout << std::endl;
    }
}

void print1dIntVector(std::vector<int> arr){
    for (auto i = arr.begin(); i != arr.end(); ++i)
        std::cout << *i << ' ';
    cout<<'\n';

}


void collectInput(int argc, char *argv[])
{
    int count = 0;
    if ( argc != 2 ) {
         cout<<"usage: "<< argv[0] <<" <filename>\n";
    }
    else {
        ifstream the_file ( argv[1] );
        if ( !the_file.is_open() ){
            cout<<"Could not open file\n";
        }      
        else {
            char x;
            while (the_file.get(x)){
                if(x == '\n'){
                    count = 1;
                }
                if(count == 0){
                    firstLine += x;
                }
                else{
                    activities += x;
                }         
            }      
        }
    }
}

std::vector<int > allocateFirstLineToArray(){
    vector<int> ret;
    for(char const &c: firstLine){
        if(c != ' '){
            ret.push_back(c - '0');
        }
    }
    return ret;


}

std::vector<std::vector<int> > getNumUnitsAvailablePerTaskPerResourceType(int numOfTasks, std::vector<vector<string>> tasks){
    bool init = false;
    std::string which = "";
    std::string value = "";
    int count = 0;
    std::vector<std::vector<int>>  numUnitsAvailablePerTaskPerResourceType(numOfTasks, std::vector<int>(0));

    for(int i = 0; i < numOfTasks; i++){
        for(int j = 0; j < tasks[i].size(); j++){
            init = false;
            which = "";
            for(char const &c: tasks[i][j]){
                which += c;
                if(which == "initiate"){
                    init = true;
                }     
            }
            if(init){
                value = "";
                count = 0;
                for(char const &c: which){
                    if(c != '\n' && c != ' '){
                        value += c;
                    }
                    if(value != "initiate" && c == ' ' && value != ""){
                        if(count == 3){
                            numUnitsAvailablePerTaskPerResourceType[i].push_back(stoi(value));
                            value = "";
                        }
                        else{
                            count++;
                            value = "";
                        }
                        
                    } 
                    else if(value == "initiate" || c == ' '){
                        value = "";
                    }
                }
            }
        }
    }

    return numUnitsAvailablePerTaskPerResourceType;
}


std::vector<int> getNumUnitsPerResourceType(std::vector<int> firstLineArr){
    std::vector<int> numUnitsPerResourceType;
    for(int i = 2; i < firstLineArr.size(); i++){
        numUnitsPerResourceType.push_back(firstLineArr[i]);

    }

    return numUnitsPerResourceType;
}


void bankers(std::vector<vector<string>> tasks, std::vector<int> firstLineArr){
    int numOfTasks = firstLineArr[0];
    int numOfResources = firstLineArr[1];
    std::vector<int> numUnitsPerResourceType = getNumUnitsPerResourceType(firstLineArr);
    std::vector<std::vector<int>>  numUnitsAvailablePerTaskPerResourceType = getNumUnitsAvailablePerTaskPerResourceType(numOfTasks, tasks);
    std::vector<int> timePerTask(numOfTasks, 0);
    print2dIntVector(numUnitsAvailablePerTaskPerResourceType);
    for(int i = 0; i < tasks.size(); i++){
        for(int j = 0; j < tasks[i].size(); j++){

        }
    }
    
}
