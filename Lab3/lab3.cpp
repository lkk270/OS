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
#include<string.h>

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
// void print2dIntVector(std::vector<vector<int>> nums);

int main ( int argc, char *argv[] )
{
    collectInput(argc, argv);
    vector<int> firstLineArr = allocateFirstLineToArray();
    vector<vector<string> > tasks( firstLineArr[0] , vector<string> (0));
    tasks = allocateToArray(firstLineArr[0]);
    // print1dIntVector(firstLineArr);
    // // cout<<tasks[1 ].size();
    // cout<<'\n';
    // print2dStringVector(tasks);
    // cout<<'\n';
    bankers(tasks, firstLineArr);
    // cout<<'\n';
    // cout<<'\n';
    // cout<<tasks[0][9];

}

std::vector<std::vector<string> > allocateToArray(int numTasks){
    
    std::vector<vector<string> > tasks( numTasks , vector<string> (0));
    std::string line = "";
    int whichTask = -1;
    int numOfSpaces = 0;
    for(char const &c: activities){
        
        if(c== '\n'){
            // line += " ";
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
        line += c;   
  
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

// std::vector<std::vector<int> > getNumUnitsAvailablePerTaskPerResourceType(int numOfTasks, std::vector<vector<string>> tasks){
//     bool init = false;
//     std::string which = "";
//     std::string value = "";
//     int count = 0;
//     std::vector<std::vector<int>>  numUnitsAvailablePerTaskPerResourceType(numOfTasks, std::vector<int>(0));

//     for(int i = 0; i < numOfTasks; i++){
//         for(int j = 0; j < tasks[i].size(); j++){
//             init = false;
//             which = "";
//             for(char const &c: tasks[i][j]){
//                 which += c;
//                 if(which == "initiate"){
//                     init = true;
//                 }     
//             }
//             if(init){
//                 value = "";
//                 count = 0;
//                 for(char const &c: which){
//                     if(c != '\n' && c != ' '){
//                         value += c;
//                     }
//                     if(value != "initiate" && c == ' ' && value != ""){
//                         if(count == 3){
//                             numUnitsAvailablePerTaskPerResourceType[i].push_back(stoi(value));
//                             value = "";
//                         }
//                         else{
//                             count++;
//                             value = "";
//                         }
                        
//                     } 
//                     else if(value == "initiate" || c == ' '){
//                         value = "";
//                     }
//                 }
//             }
//         }
//     }

//     return numUnitsAvailablePerTaskPerResourceType;
// }


std::vector<int> getNumUnitsPerResourceType(std::vector<int> firstLineArr){
    std::vector<int> numUnitsPerResourceType;
    for(int i = 2; i < firstLineArr.size(); i++){
        numUnitsPerResourceType.push_back(firstLineArr[i]);

    }

    return numUnitsPerResourceType;
}

int getValue(const std::string& line, int which){
    std::string value = "";
    int count = 0;
    int ret;
    bool empty = true;
    for(char const &c: line){
        if(c != '\n' && c != ' '){
            value += c;
        }
        if(value != "initiate" && c == ' ' &&  value != "" && value != "request" && value != "release" && value != "terminate"){
            if(count == which){
                ret = stoi(value);  
                empty = false;   
                break;
            }
            else{  
                count++;
                value = "";
            } 
        }
        else if(value == "initiate" || c == ' ' || value == "request" || value == "release" || value == "terminate"){
            value = "";
        }
    }

    if(empty && which == 4){
        // cout<<"empty \n";
        return 0;
    }
    else{
        return ret;
    }
    
}

std::string getActivityName(const std::string& line){
    std::string value = "";
    for(char const &c: line){
        if(c != '\n' && c != ' '){
            value += c;
        }
        else if(c == ' '){
           return value;
        }
    }
}

std::pair<std::vector<std::vector<string> >, int>  checkForInitialAbort(std::vector<int> numUnitsPerResourceType, std::vector<vector<string>>& tasks, int& addToNumOfActivitesCompleted){
    for(int i = 0; i < numUnitsPerResourceType.size(); i++){
        for(int j = 0; j < tasks.size(); j++){
            for(int k = 0; k < tasks[j].size(); k++){ 
                if(getValue(tasks[j][k], 3)> numUnitsPerResourceType[i] && getValue(tasks[j][k], 0) == j+1){
                    tasks[j].push_back("\nabort");
                    addToNumOfActivitesCompleted += tasks[j].size() - 2;
                    break;
                }
                // tasks[j][k] += "0 ";
            }
        }
    }
    
    return std::make_pair(tasks,addToNumOfActivitesCompleted);

}


int getTotalNumOfActivities(std::vector<vector<string>>& tasks){
    int ret = 0;
    for(int i = 0; i < tasks.size(); i++){
        for(int j = 0; j < tasks[i].size(); j++){
            ret++;
        }
    }
    return ret;
}

void bankers(std::vector<vector<string>> tasks, std::vector<int> firstLineArr){
    int numOfTasks = firstLineArr[0];
    int numOfResources = firstLineArr[1];
    int addToNumOfActivitesCompleted = 0;
    std::vector<int> numUnitsPerResourceType = getNumUnitsPerResourceType(firstLineArr);
    // std::vector<std::vector<int>>  numUnitsAvailablePerTaskPerResourceType = getNumUnitsAvailablePerTaskPerResourceType(numOfTasks, tasks);
   
    std::vector<int> waitingTimePerTask(numOfTasks, 0);
    int next = (numOfTasks > 1 ? 1 : 0);
    int totalNumOfActivities = getTotalNumOfActivities(tasks);
    
    int cycle = 0;
    int res = 0;
    bool cont = true;
    
    // print2dIntVector(numUnitsAvailablePerTaskPerResourceType);
    checkForInitialAbort(numUnitsPerResourceType, tasks, addToNumOfActivitesCompleted);
    int numOfActivitesCompleted = numOfTasks + addToNumOfActivitesCompleted;
    cout<<numOfActivitesCompleted;
    cout<<"sfsf\n";
    while(cont && numOfActivitesCompleted != totalNumOfActivities ){
        cycle++;
        for (int r = 0; r < numOfResources; r++){
            for(int i = 0; i < tasks.size(); i++){
                next =  (next + 1 <= numOfTasks-1 ? next + 1 : 0);
                if(tasks[i][tasks[i].size()-1] != "\nabort"){
                    cout<<"i = ";
                    cout<<i;
                    cout<<'\n';
                    for(int j = 0; j < tasks[i].size(); j++){
                        if(tasks[i][tasks[i].size()-1] != "\nabort" && getValue(tasks[i][j], 4) == 0){
                            res =  getValue(tasks[i][j], 2);
                            // printf("%d", res);
                            // cout<<" \n ";
                            if(numOfActivitesCompleted == totalNumOfActivities){
                                cout<<" numOfActivitesCompleted == totalNumOfActivities\n";
                                cont = false;
                                break;
                            }
                            if(r+1 == res){
                                if(getActivityName(tasks[i][j]) == "request"){
                                    tasks[i][j] += to_string(cycle) + " ";
                                    cycle++;
                                    numOfActivitesCompleted++;
                                    break;
                                }
                                else{
                                    cout<<"added";
                                    tasks[i][j] += to_string(cycle) + " ";
                                    // cout<<tasks[i][j];
                                    numOfActivitesCompleted++;
                                    break;    
                                }
                               
                            }
                         
                            
                            // if(i == numOfTasks-1 && j == tasks[i].size()-1){
                            //     cycle++;
                            // }     
                            cout<<" \n=================\n";
        
                                    
                        }
                       
                    
                        
                        // else{
                        //     cout<<totalNumOfActivities;
                        //     cout<<' ';
                        //     cout<<numOfActivitesCompleted;
                        //     cout<<tasks[i][tasks[i].size()-1];
                        //     cout<<'\n';
                        //     printf("%s %d", " cycle",  getValue(tasks[i][j], 4));
                        //     cout<<'\n';
                        // }
                    }
                }   
                if(!cont){
                        break;
                }
                print2dStringVector(tasks);
                cout<< "numOfActivitesCompleted = ";
                cout<<numOfActivitesCompleted;
                cout<<'\n';
                cout<< "totalNumOfActivities = ";
                cout<<totalNumOfActivities;
                cout<<'\n';


            //keep track of each execution - add cycle count to each execution
            //need function that updates tasks arr with cycle count for each activity
            }
            if(!cont){
                break;
            }
        }

    }
    

    //0 = task number, 1 = delay, 2 = resource-type, 3 = number-requested (units), 4 = cycle
   
    print2dStringVector(tasks);
    // print2dIntVector(numUnitsAvailablePerTaskPerResourceType);
    cout<<'\n';
    print1dIntVector(numUnitsPerResourceType);
    cout<<'\n';

    
}

