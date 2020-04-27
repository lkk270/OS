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
// #include <array>
#include<string.h>
#include <algorithm>
#include <math.h>   

using namespace std;

std::string firstLine = ""; 
std::string activities = ""; 
void collectInput(int argc, char *argv[]);
void print2dStringVector(std::vector<vector<string>> arr);
void print1dIntVector(std::vector<int> arr);
std::vector<std::vector<string> > allocateToArray(int num);
void bankers(std::vector<vector<string>> arr, std::vector<int> arr2);
void fifo(std::vector<vector<string>> arr, std::vector<int> arr2);
bool is_number(const std::string& s);
std::vector<int > allocateFirstLineToArray();
// void print2dIntVector(std::vector<vector<int>> nums);

int main ( int argc, char *argv[] )
{
    collectInput(argc, argv);
    vector<int> firstLineArr = allocateFirstLineToArray();
    vector<vector<string> > tasks( firstLineArr[0] , vector<string> (0));
    tasks = allocateToArray(firstLineArr[0]);

    // bankers(tasks, firstLineArr);
    fifo(tasks, firstLineArr);

}


std::vector<std::vector<string> > allocateToArray(int numTasks){
    std::vector<vector<string> > tasks( numTasks , vector<string> (0));
    std::string line = "";
    int whichTask = -1;
    int numOfSpaces = 0;
    for(char const &c: activities){
        
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
        line += c;   
  
    }
    
    return tasks;
}


bool is_number(const std::string& s){
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


void collectInput(int argc, char *argv[]){
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
    return "";
}


int getNumOfInitiatesForGivenTask(std::vector<vector<string>> tasks, int taskIndex){
    int ret = 0;
    for(int i = 0; i < tasks[taskIndex].size(); i++){
        if(getActivityName(tasks[taskIndex][i]) == "initiate"){
            ret++;
        }
    }
    return ret;
}


std::pair<std::vector<std::vector<string> >, int>  checkForInitialAbort(std::vector<int> numUnitsPerResourceType, std::vector<vector<string>>& tasks, int& addToNumOfActivitesCompleted){
    for(int i = 0; i < numUnitsPerResourceType.size(); i++){
        for(int j = 0; j < tasks.size(); j++){
            for(int k = 0; k < tasks[j].size(); k++){ 
                if(getValue(tasks[j][k], 3)> numUnitsPerResourceType[i] && getValue(tasks[j][k], 0) == j+1){
                    addToNumOfActivitesCompleted += (tasks[j].size() - 1 - getNumOfInitiatesForGivenTask(tasks, j));
                    tasks[j].push_back("\nabort");
                    break;
                }
                // tasks[j][k] += "0 ";
            }
        }
    } 
    return std::make_pair(tasks,addToNumOfActivitesCompleted);
}


int getTotalNumOfActivities(std::vector<vector<string>> tasks){
    int ret = 0;
    for(int i = 0; i < tasks.size(); i++){
        for(int j = 0; j < tasks[i].size(); j++){
            ret++;
        }
    }
    return ret;
}


std::pair<int, std::vector<vector<string>> > getNumOfInitiates(std::vector<vector<string>>& tasks){
    int additional = 0;
    for(int i = 0; i < tasks.size(); i++){
        for(int j = 0; j < tasks[i].size() - 1; j++){
            if(getActivityName(tasks[i][j]) == "initiate"){
                tasks[i][j] +=  to_string(j+1) + " ";
                additional++;
            }
        }
    }
    return std::make_pair(additional, tasks);  
}


std::vector<int> getNumTasksValidForStart(std::vector<int>& checkIfValid,  std::vector<vector<string>> tasks){
    int count = 0;
    for(int i = 0; i < tasks.size(); i++){
        for(int j = 0; j < tasks[i].size(); j++){
               if(getActivityName(tasks[i][j]) == "initiate"){
                // tasks[i][j] += "1 ";
                    if(getValue(tasks[i][j], 2) - 1 == count){
                        if(checkIfValid[getValue(tasks[i][j], 2) - 1] == 0){
                            checkIfValid[getValue(tasks[i][j], 2) - 1] = 0;
                        }
                        else if(checkIfValid[getValue(tasks[i][j], 2) - 1] % getValue(tasks[i][j], 3) != 0) {
                            checkIfValid[getValue(tasks[i][j], 2) - 1] = (checkIfValid[getValue(tasks[i][j], 2) - 1]/getValue(tasks[i][j], 3)) + 1;
                        }
                        else{
                            checkIfValid[getValue(tasks[i][j], 2) - 1] = (checkIfValid[getValue(tasks[i][j], 2) - 1]/getValue(tasks[i][j], 3));
                        }
                        count++;
                    }
            }

        }
    }
    return checkIfValid;
}


std::vector<int> initializeBlocked(std::vector<int> checkIfValid,  std::vector<vector<string>> tasks){
    std::vector<int> blocked;
    int count = 0;
    for(int i = checkIfValid[0]; i < tasks.size(); i++){
        blocked.push_back(i);
    }
    return blocked;
}


std::pair<std::vector<int> , std::vector<string> > initializeDelaysPerTask(std::vector<vector<string>> tasks, std::vector<string>& delayedTasks){
    std::vector<int> delaysPerTask(tasks.size());
    for(int i = 0; i < tasks.size(); i++){
        for(int j = 0; j < tasks[i].size(); j++){
            if(getValue(tasks[i][j], 4) == 0){
                std::string delayedIndex = to_string(i) + "-" + to_string(j);
                delaysPerTask[i] = getValue(tasks[i][j], 1);
                delayedTasks.push_back(delayedIndex);
                break;
            }
        }
    }
    return std::make_pair(delaysPerTask, delayedTasks);
}


int getTrueSizeOfBlocked(std::vector<int> blocked){
    int ret = 0;
    for(int i = 0; i < blocked.size(); i++){
        if(blocked[i] != -1){
            ret++;
        }
    }
    return ret;
}


float calculateWaitingTime(std::vector<vector<string>> tasks, int taskIndex){
    float finalTime = getValue(tasks[taskIndex][tasks[taskIndex].size() - 1 ], 4);
    float valueIfNoWait = tasks[taskIndex].size() - 1;
    for(int j = 0; j < tasks[taskIndex].size(); j++){
        valueIfNoWait += getValue(tasks[taskIndex][j], 1);
    }
    return float(getValue(tasks[taskIndex][tasks[taskIndex].size() - 1], 4) - valueIfNoWait);
}


void printBankers(std::vector<vector<string>> tasks){
    float totalTime = 0.0;
    float totalWaitTime = 0.0;
    float waitTime = 0.0;
    float endTime = 0.0;
    for(int i = 0; i < tasks.size(); i++){
        std:: cout << "Task " << i << "        ";
        if(tasks[i][tasks[i].size()-1] == "\nabort"){
            std::cout << "aborted";
        }
        else{
            waitTime = calculateWaitingTime(tasks, i);
            totalWaitTime+=waitTime;
            endTime =  getValue(tasks[i][tasks[i].size()-1], 4);
            totalTime+=  endTime;
            int percentage= round(100 * (waitTime / endTime));
            std::cout << getValue(tasks[i][tasks[i].size()-1], 4) << "   " << to_string(int(waitTime)) << "  " << to_string(percentage) << "%";;
        }

    cout<<'\n';
 
    }
   
    int percentage= round(100 * (totalWaitTime / totalTime));
    std:: cout << "total " << "        " << to_string(int(totalTime)) << "   " << to_string(int(totalWaitTime)) << "  " << to_string(percentage) << "%";
    cout<<'\n';
}


void bankers(std::vector<vector<string>> tasks, std::vector<int> firstLineArr){
    int numOfTasks = firstLineArr[0];
    int numOfResources = firstLineArr[1];
    int addToNumOfActivitesCompleted = 0;
    std::vector<int> numUnitsPerResourceType = getNumUnitsPerResourceType(firstLineArr);
    std::vector<int> numUnitsPerResourceTypeRemaining = numUnitsPerResourceType;
    int totalNumOfActivities = getTotalNumOfActivities(tasks) - numOfTasks;
    std::vector<vector<int>> numUnitsPerResourceTypePerTaskUsed( numOfTasks , vector<int> (numOfResources));
    int cycle = numOfResources;
    int res = 0;
    bool cont = true;
    int count = -1;
    bool endTask = false;
    checkForInitialAbort(numUnitsPerResourceType, tasks, addToNumOfActivitesCompleted);
    std::vector<int> checkIfValid = numUnitsPerResourceTypeRemaining;
    getNumTasksValidForStart(checkIfValid, tasks);
    int numOfCompletedTasks = 0;
    int numOfCompletedTasksTemp = 0;
    std::vector<int> blocked = initializeBlocked(checkIfValid, tasks);
    std::vector<int> delaysPerTask(numOfTasks);
    std::vector<string> activityNamePerDelayedTask(numOfTasks);
    int numOfActivitesCompleted = addToNumOfActivitesCompleted + getNumOfInitiates(tasks).first;
    bool parseBlocked = true;
    int blockedSizeTemp = blocked.size();
    std::vector<string> delayedTasks;
    bool justDecreasedDelays = false;
    while(cont && numOfActivitesCompleted != totalNumOfActivities ){
        count++;
        cycle++;
        parseBlocked = true;
        justDecreasedDelays = false;
        if(count > 0 && getTrueSizeOfBlocked(blocked) > 0 ){
            for(int d = 0; d < delaysPerTask.size(); d++){
                if(delaysPerTask[d] != 0){
                    delaysPerTask[d] -= 1;
                    justDecreasedDelays = true;

                }
            }
        }
        if(count > 0 && parseBlocked){
            for(int b = 0; b < blocked.size(); b++){
                if(blocked[b] != -1){
                    if(tasks[blocked[b]][tasks[blocked[b]].size()-1] != "\nabort"){         
                        for(int t = 1; t < tasks[blocked[b]].size() - 1; t++){               
                            if(getValue(tasks[blocked[b]][t], 4) == 0){
                                if(getActivityName(tasks[blocked[b]][t]) == "request"){
                                    if(getActivityName(tasks[blocked[b]][t-1]) != "initiate" && getValue(tasks[blocked[b]][t-1], 4) == 0){
                                        break;
                                    }
                                    if((getValue(tasks[blocked[b]][t], 3) <=  numUnitsPerResourceType[getValue(tasks[blocked[b]][t], 2) - 1]) && (blockedSizeTemp + 1 == blocked.size()|| numOfCompletedTasksTemp + 1 ==  numOfCompletedTasks)){
                                        blocked[b] = -1;
                                        parseBlocked = false;
                                        break;

                                    }
                                    else{
                                        break;
                                    }
                                }    
                            }
                        }
                        if(!parseBlocked){
                            break;
                        }
                    }
                }
                else{
                    continue;
                }
            }
        }

        for(int i = 0; i < tasks.size(); i++){
            if (!std::count(blocked.begin(), blocked.end(), i)){
                if(tasks[i][tasks[i].size()-1] != "\nabort"){
                    for(int j = 1; j < tasks[i].size() - 1; j++){
                        if(getValue(tasks[i][j], 4) == 0){
                            if(getActivityName(tasks[i][j]) == "request"){
                                std::string delayedIndex = to_string(i) + "-" + to_string(j);
                                if(delaysPerTask[i] == 0 && getValue(tasks[i][j], 1) != 0 && !std::count(delayedTasks.begin(), delayedTasks.end(), delayedIndex)){
                                    delaysPerTask = initializeDelaysPerTask(tasks, delayedTasks).first;
                                    delayedTasks = initializeDelaysPerTask(tasks, delayedTasks).second;
                                    activityNamePerDelayedTask[i] = "request";
                                    break;
                                }
                                if(getActivityName(tasks[i][j-1]) != "initiate" && getValue(tasks[i][j-1], 4) == 0){
                                    break;
                                }
                                if(delaysPerTask[i] != 0){
                                    break;
                                }
                                if((getValue(tasks[i][j], 3) +  numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1]) > (getValue(tasks[i][getValue(tasks[i][j], 2) - 1], 3))){
                                    // above checks corresponding initiate 
                                    numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] +=  numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1];
                                    numOfActivitesCompleted = numOfActivitesCompleted + tasks[i].size() - j - 1;
                                    tasks[i].push_back("\nabort");
                                    cycle++;
                                    if(blocked.size() > 0 && blocked[0] != -1){
                                        blocked[0] = -1;
                                    }
                                    break;
                                }

                                if(getValue(tasks[i][j], 3) <=  numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1]){
                                    tasks[i][j] += to_string(cycle) + " ";
                                    numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] -= getValue(tasks[i][j], 3);
                                    numOfActivitesCompleted++;
                                    blockedSizeTemp = -1;
                                    numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1] += getValue(tasks[i][j], 3); 
                                    break;

                                }
                                else{
                                    blockedSizeTemp = blocked.size();
                                    blocked.push_back(i);
                                    break;
                                }

                                
                                }
                            if(getActivityName(tasks[i][j]) == "release"){
                                std::string delayedIndex = to_string(i) + "-" + to_string(j);
                                if(delaysPerTask[i] == 0 && getValue(tasks[i][j], 1) != 0 && !std::count(delayedTasks.begin(), delayedTasks.end(), delayedIndex)){
                                    delaysPerTask = initializeDelaysPerTask(tasks, delayedTasks).first;
                                    delayedTasks = initializeDelaysPerTask(tasks, delayedTasks).second;
                                    activityNamePerDelayedTask[i] = "release";
                                    break;
                                }
                                if(getActivityName(tasks[i][j-1]) != "initiate" && getValue(tasks[i][j-1], 4) == 0){
                                    break;
                                }
                                if(delaysPerTask[i] != 0){
                                    break;
                                }
                                else{
                                    tasks[i][j] += to_string(cycle) + " ";
                                    numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] += getValue(tasks[i][j], 3);
                                    numOfActivitesCompleted++;
                                    numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1] -= getValue(tasks[i][j], 3); 
                                    if(getActivityName(tasks[i][j+1]) == "terminate"){
                                        tasks[i][j+1] += to_string(cycle + getValue(tasks[i][j+1], 1)) + " ";
                                    }
                                                
                                    if(j == tasks[i].size() - 2){
                                        numOfCompletedTasksTemp = numOfCompletedTasks;
                                        numOfCompletedTasks++;
                                    }
                                    if(j+1 <= tasks[i].size() - 2){
                                        if(getActivityName(tasks[i][j+1]) == "release" && getValue(tasks[i][j], 2) - 1 != getValue(tasks[i][j+1], 2) - 1){
                                            break;
                                        }
                                    }
                                    blockedSizeTemp = blocked.size();
                                    blocked.push_back(i);
                                    
                                    break;

                                }

                                
                            }

                            


                        }


                    }
                }
            }
            

        }
       
    }
    //0 = task number, 1 = delay, 2 = resource-type, 3 = number-requested (units), 4 = cycle
    cout<<"        BANKER'S\n";
    printBankers(tasks);
   
}

//deadlock is when all cannot request. so remove lastActivity != release thing. check for deadlock case and then proceed with aborts until avail num of resources is stable for the next non aborted task. otherwise just block it.
void fifo(std::vector<vector<string>> tasks, std::vector<int> firstLineArr){
    int numOfAbortsPerRound = 0;
    int numOfTasks = firstLineArr[0];
    int numOfResources = firstLineArr[1];
    int addToNumOfActivitesCompleted = 0;
    std::vector<int> numUnitsPerResourceType = getNumUnitsPerResourceType(firstLineArr);
    std::vector<int> numUnitsPerResourceTypeRemaining = numUnitsPerResourceType;
    int totalNumOfActivities = getTotalNumOfActivities(tasks) - numOfTasks;
    std::vector<vector<int>> numUnitsPerResourceTypePerTaskUsed( numOfTasks , vector<int> (numOfResources));
    int cycle = numOfResources;
    int res = 0;
    bool cont = true;
    int count = -1;
    bool endTask = false;
    std::string lastActivity = "";
    std::string lastActivity2 = "";
    // checkForInitialAbort(numUnitsPerResourceType, tasks, addToNumOfActivitesCompleted);
    std::vector<int> checkIfValid = numUnitsPerResourceTypeRemaining;
    getNumTasksValidForStart(checkIfValid, tasks);
    int numOfCompletedTasks = 0;
    int numOfCompletedTasksTemp = 0;
    // std::vector<int> blocked = initializeBlocked(checkIfValid, tasks);
    std::vector<int> blocked;
    std::vector<int> delaysPerTask(numOfTasks);
    std::vector<string> activityNamePerDelayedTask(numOfTasks);
    int numOfActivitesCompleted = addToNumOfActivitesCompleted + getNumOfInitiates(tasks).first;
    bool parseBlocked = true;
    int blockedSizeTemp = blocked.size();
    std::vector<string> delayedTasks;
    bool justDecreasedDelays = false;
    cout<<numOfActivitesCompleted;
    cout<<'\n';
    cout<<totalNumOfActivities;
    cout<<'\n';
    while(cont && numOfActivitesCompleted != totalNumOfActivities ){
        lastActivity = "";
        numOfAbortsPerRound = 0;
        cout<<numOfActivitesCompleted;
        cout<<'\n';
        cout<<totalNumOfActivities;
        cout<<'\n';
        cout<<"CYCLE: ";
        cout<<cycle;
        cout<<'\n';
        cout<<"================\n";
        count++;
        cycle++;
        parseBlocked = true;
        justDecreasedDelays = false;
        if(count > 0){
            for(int d = 0; d < delaysPerTask.size(); d++){
                if(delaysPerTask[d] != 0){
                    delaysPerTask[d] -= 1;
                    justDecreasedDelays = true;

                }
            }
        }

        if(count > 0 && parseBlocked){
            for(int b = 0; b < blocked.size(); b++){
                if(blocked[b] != -1){
                    if(tasks[blocked[b]][tasks[blocked[b]].size()-1] != "\nabort"){         
                        for(int t = 1; t < tasks[blocked[b]].size() - 1; t++){               
                            if(getValue(tasks[blocked[b]][t], 4) == 0){
                                if(getActivityName(tasks[blocked[b]][t]) == "request"){
                                    if(getActivityName(tasks[blocked[b]][t-1]) != "initiate" && getValue(tasks[blocked[b]][t-1], 4) == 0){
                                        break;
                                    }
                                    if((getValue(tasks[blocked[b]][t], 3) <=  numUnitsPerResourceType[getValue(tasks[blocked[b]][t], 2) - 1]) && (blockedSizeTemp + 1 == blocked.size()|| numOfCompletedTasksTemp + 1 ==  numOfCompletedTasks)){
                                        blocked[b] = -1;
                                        parseBlocked = false;
                                        break;

                                    }
                                    else{
                                        break;
                                    }
                                }    
                            }
                        }
                        if(!parseBlocked){
                            break;
                        }
                    }
                }
                else{
                    continue;
                }
            }
        }

        for(int i = 0; i < tasks.size(); i++){
            if (!std::count(blocked.begin(), blocked.end(), i)){
                if(tasks[i][tasks[i].size()-1] != "\nabort"){
                    for(int j = 1; j < tasks[i].size() - 1; j++){
                        if(getValue(tasks[i][j], 4) == 0){
                            if(getActivityName(tasks[i][j]) == "request"){
                                std::string delayedIndex = to_string(i) + "-" + to_string(j);
                                if(delaysPerTask[i] == 0 && getValue(tasks[i][j], 1) != 0 && !std::count(delayedTasks.begin(), delayedTasks.end(), delayedIndex)){
                                    delaysPerTask = initializeDelaysPerTask(tasks, delayedTasks).first;
                                    delayedTasks = initializeDelaysPerTask(tasks, delayedTasks).second;
                                    activityNamePerDelayedTask[i] = "request";
                                    break;
                                }
                                if(getActivityName(tasks[i][j-1]) != "initiate" && getValue(tasks[i][j-1], 4) == 0){
                                    break;
                                }
                                if(delaysPerTask[i] != 0){
                                    break;
                                }

                                if(getValue(tasks[i][j], 3) >  numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1]){
                                    numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] +=  numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1];
                                    numOfActivitesCompleted = numOfActivitesCompleted + tasks[i].size() - j - 1;
                                    tasks[i].push_back("\nabort");
                                    numOfAbortsPerRound++;
                                    if(numOfAbortsPerRound == 1){
                                        cycle++;
                                    }
                                    break;
                                    
                                }
                               
                                if((getValue(tasks[i][j], 3) +  numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1]) > (getValue(tasks[i][getValue(tasks[i][j], 2) - 1], 3))){
                                    // above checks corresponding initiate 
                                    numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] +=  numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1];
                                    numOfActivitesCompleted = numOfActivitesCompleted + tasks[i].size() - j - 1;
                                    tasks[i].push_back("\nabort");
                                    cycle++;
                                    if(blocked.size() > 0 && blocked[0] != -1){
                                        blocked[0] = -1;
                                    }
                                    break;
                                }

                                if(getValue(tasks[i][j], 3) <=  numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] && lastActivity != "release"){
                                    lastActivity = "request";
                                    tasks[i][j] += to_string(cycle) + " ";
                                    numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] -= getValue(tasks[i][j], 3);
                                    numOfActivitesCompleted++;
                                    blockedSizeTemp = -1;
                                    numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1] += getValue(tasks[i][j], 3); 
                                    break;

                                }

                                else{
                                    blockedSizeTemp = blocked.size();
                                    blocked.push_back(i);
                                    break;
                                }
                             

                                
                            }
                            if(getActivityName(tasks[i][j]) == "release"){
                                std::string delayedIndex = to_string(i) + "-" + to_string(j);
                                if(delaysPerTask[i] == 0 && getValue(tasks[i][j], 1) != 0 && !std::count(delayedTasks.begin(), delayedTasks.end(), delayedIndex)){
                                    delaysPerTask = initializeDelaysPerTask(tasks, delayedTasks).first;
                                    delayedTasks = initializeDelaysPerTask(tasks, delayedTasks).second;
                                    activityNamePerDelayedTask[i] = "release";
                                    break;
                                }
                                if(getActivityName(tasks[i][j-1]) != "initiate" && getValue(tasks[i][j-1], 4) == 0){
                                    break;
                                }
                                if(delaysPerTask[i] != 0){
                                    break;
                                }
                                else{
                                    lastActivity = "release";
                                    tasks[i][j] += to_string(cycle) + " ";
                                    numUnitsPerResourceType[getValue(tasks[i][j], 2) - 1] += getValue(tasks[i][j], 3);
                                    numOfActivitesCompleted++;
                                    numUnitsPerResourceTypePerTaskUsed[i][getValue(tasks[i][j], 2) - 1] -= getValue(tasks[i][j], 3); 
                                    if(getActivityName(tasks[i][j+1]) == "terminate"){
                                        tasks[i][j+1] += to_string(cycle + getValue(tasks[i][j+1], 1)) + " ";
                                    }
                                                
                                    if(j == tasks[i].size() - 2){
                                        numOfCompletedTasksTemp = numOfCompletedTasks;
                                        numOfCompletedTasks++;
                                    }
                                    if(j+1 <= tasks[i].size() - 2){
                                        if(getActivityName(tasks[i][j+1]) == "release" && getValue(tasks[i][j], 2) - 1 != getValue(tasks[i][j+1], 2) - 1){
                                            break;
                                        }
                                    }
                                    blockedSizeTemp = blocked.size();
                                    blocked.push_back(i);
                                    
                                    break;

                                }

                                
                            }

                            


                        }


                    }
                }
            }
            

        }

       
        print2dStringVector(tasks);

    }
        

}


