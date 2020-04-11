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
void printVector(std::vector<vector<string>> arr);
std::vector<std::vector<string> > allocateToArray(int num);

int main ( int argc, char *argv[] )
{
    collectInput(argc, argv);
    int numOfTasks = firstLine[0] - '0';
    vector<vector<string> > tasks( numOfTasks , vector<string> (4));
    tasks = allocateToArray(numOfTasks);
    printVector(tasks);
}

vector<std::vector<string> > allocateToArray(int numTasks){
    
    vector<vector<string> > tasks( numTasks , vector<string> (4));
    std::string word = "";
    int initiateTaskIndex = -1;
    int requestIndex = -1;
    int releaseIndex = -1;
    int terminateIndex = -1;
    int whichIndex = 0;
    int whichTask = 0;
    for(char const &c: activities){
        int numOfNums = 0;
       
        if(word == "initiate"){
            whichIndex = 0;
            initiateTaskIndex++;
            whichTask = initiateTaskIndex;   
        }
        else if(word == "request"){
            whichIndex = 1;
            requestIndex++;
            whichTask = requestIndex;
        }
        else if(word == "release"){
            whichIndex = 2;
            releaseIndex++;
            whichTask = releaseIndex;
        }
        else if(word == "terminate"){
            whichIndex = 3;
            terminateIndex++;
            whichTask = terminateIndex;
        }
        if(c== '\n'){
            tasks[whichTask][whichIndex] = word;
            word = "";
        }    
        if (c != '\n'){
            word += c;
        } 
    }
    return tasks;
}


void printVector(std::vector<vector<string>> tasks){
    for ( const std::vector<string> &v : tasks ){
        for ( std::string x : v ) std::cout << x << ' ';
            std::cout << std::endl;
    }
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
