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
#include <limits>
#include <cstddef>
#include "frame.h"
#include "process.h"



using namespace std;

int machineSize, pageSize, processSize, jobMix, numOfReferences;
int debugStatus;
std::string replacementAlgo;
int quantumNum = 3;
vector<Process> processList;
vector<Frame> frameList;
ifstream infile("random-numbers");
int randomNum();
std::ifstream& GotoLine(std::ifstream& file, unsigned int num);
void collectInput(int argc, char *argv[]);
int replace_random(vector<Frame>  frameList);

// void Process::nextReference(int r);
int main ( int argc, char *argv[] )
{   
    
    srand (time(NULL));
    collectInput(argc, argv);
    cout<<'\n';
    cout<<processList.size();
    cout<<'\n';
    cout<<frameList.size();
    cout<<'\n';
  

  

}

void collectInput(int argc, char *argv[]){
    if (argc >= 7 ) {
        machineSize = stoi(argv[1]);
        pageSize = stoi(argv[2]);
        processSize = stoi(argv[3]);
        jobMix = stoi(argv[4]);
        numOfReferences = stoi(argv[5]);
        replacementAlgo = argv[6];
    }
    if(argc == 8) {
        debugStatus = stoi(argv[7]);
    }
    if(argc > 8 || argc < 7){
        printf("INVALID INPUT! ");
        cout<<'\n';
        return;
    }

    printf("%s %d", "The machine size is ", machineSize);
    cout<<'\n';
    printf("%s %d", "The page size is ", pageSize);
    cout<<'\n';
    printf("%s %d", "The process size is ", processSize);
    cout<<'\n';
    printf("%s %d", "The job-mix number is is ", jobMix);
    cout<<'\n';
    printf("%s %d", "number of references per process ", numOfReferences);
    cout<<'\n';
    printf("%s %s", "The replacement algorithm is ", replacementAlgo.c_str());
    cout<<'\n';
    printf("%s %d", "The debug level is ", debugStatus);
    cout<<'\n';

    if(jobMix == 1){
            Process p1 = Process(1.0, 0.0, 0.0, pageSize, processSize, numOfReferences, 0);
            processList.push_back(p1);
    }
    else if(jobMix == 2){
        for(int i = 0; i < 4; i++){
            Process p2 = Process(1.0, 0.0, 0.0, pageSize, processSize, numOfReferences, i);
            processList.push_back(p2);
        }
    }
    else if(jobMix == 3){
        for(int i = 0; i < 4; i++){
            Process p3 = Process(0.0, 0.0, 0.0, pageSize, processSize, numOfReferences, i);
            processList.push_back(p3);
        }
    }
    else if(jobMix == 4){
        Process p4 = Process(0.75, 0.25, 0, pageSize, processSize, numOfReferences, 0);
        Process p5 = Process(0.75, 0.0, 0.25, pageSize, processSize, numOfReferences, 1);
        Process p6 = Process(0.75, 0.125, 0.125, pageSize, processSize, numOfReferences, 2);
        Process p7 = Process(0.5, 0.125, 0.125, pageSize, processSize, numOfReferences, 3);
        processList.push_back(p4);
        processList.push_back(p5);
        processList.push_back(p6);
        processList.push_back(p7);

    }
    else{
        cout<<"Job Mix value is invalid...Goodbye.\n";
        return;
    }  

    int totalFrameNum = machineSize / pageSize;
    for (int i = 0; i < totalFrameNum; i++){
        Frame f = Frame(-1, -1, -1);
        frameList.push_back(f);
    }     

}


// Check whether the current reference of the process is in the frame table, return the index of the hitfrmae
// If there is no hit, return -1

int checkHit(Process p, vector<Frame>  frameList){
		for (int i = 0; i < frameList.size(); i++){
			Frame currentFrame = frameList[i];
			int currentPage = p.currentReference / pageSize;
			if (p.processId == currentFrame.processId && currentPage == currentFrame.pageNum && currentFrame.status == 1){
				return i;
			}
		}
		return -1;
}


	// Check whether the frmae table is full, return the index of the highest numbered free frame
	// If the frame table is full, return -1
	
int checkFull(vector<Frame> frameList){
    for (int i = frameList.size() - 1; i > -1; i--){
        Frame currentFrame = frameList[i];
        if (currentFrame.status == 0){
            return i;
        }
    }
    return -1;
}

int replace_lru(vector<Frame>  frameList){
		// here smallest has to be max_value or there may be problems in case of input 14,16
		int smallestVal = std::numeric_limits<int>::max();
		int index = -1;
		for (int i = 0; i < frameList.size(); i++){
			Frame currentFrame = frameList[i];
			if (currentFrame.lastAcessTime < smallestVal){
				smallestVal = currentFrame.lastAcessTime;
				index = i;
			}
		}
		return index;
	}


int replace_fifo(vector<Frame>  frameList){
		// here smallest has to be max_value or there may be problems in case of input 14,16
		int smallestVal = std::numeric_limits<int>::max();
		int index = -1;
		for (int i = 0; i < frameList.size(); i++){
			Frame currentFrame= frameList[i];
			if (currentFrame.initialTime < smallestVal){
				smallestVal = currentFrame.initialTime;
				index = i;
			}
		}
		return index;
}


int replace_random(vector<Frame>  frameList){
    int index = 0;
    int count = 0;
    std::string randomNum = "";
    int randomIndex = rand() % 100000;
    cout<<"RANDOM INDEX: ";
    cout<<randomIndex;
    cout<<'\n';
    if (!infile.is_open() ){
        cout<<"Could not open file\n";
    }      
    else {
        char x;
        while (infile.get(x)){
            if(x != '\n'){
                randomNum += x; 
            }
            if(count == randomIndex-2){
                randomNum = "";
            }
            if(count == randomIndex){
                randomNum.pop_back();
                index = stoi(randomNum) % frameList.size();
                break;
            }
            if(x == '\n'){
                count++;
            }            
        }      
    }
    return index;
}


int getRandomNum(){
    int num = 0;
    int count = 0;
    std::string randomNum = "";
    int randomIndex = rand() % 100000;
    cout<<"RANDOM INDEX: ";
    cout<<randomIndex;
    cout<<'\n';
    if (!infile.is_open() ){
        cout<<"Could not open file\n";
    }      
    else {
        char x;
        while (infile.get(x)){
            if(x != '\n'){
                randomNum += x; 
            }
            if(count == randomIndex-2){
                randomNum = "";
            }
            if(count == randomIndex){
                randomNum.pop_back();
                num = stoi(randomNum);
                break;
            }
            if(x == '\n'){
                count++;
            }            
        }      
    }
    return num;
}

void run(){
    int time = 1;									// virtual clock starting from 1
	int numFinished = 0;

    while (numFinished < processList.size()){
        for (int i = 0; i < processList.size(); i++){
            for(int j = 0; j < quantumNum; j++){
                Process currentProcess = processList[i];
                if(currentProcess.status == 1){
                    break;
                }   
                if(currentProcess.numOfReferencesTaken == numOfReferences){
                    numFinished++;
                    currentProcess.status = 1;
                    break;
                }
                int currentPage = currentProcess.currentReference/pageSize;
                int check = checkHit(currentProcess, frameList);

                if(check != -1){
                    Frame frameTemp = frameList[check];
                    frameTemp.lastAcessTime = time;
                    int frameTempId = currentProcess.processId + 1;
                    if(debugStatus == 1){
                        printf("%d %s %d %s %d %s %d %s %d", frameTempId, " reference word ", currentProcess.currentReference, " (Page ", currentPage, ") at time ", time, " :Hit in frame ", check);
                    }
                }

                else{
                    int check1 = checkFull(frameList);

                    if(check1 != -1){
                        Frame free = frameList[check1];
                        free.processId = currentProcess.processId;
                        free.pageNum = currentPage;
                        free.status = 1;
                        free.initialTime = time;
                        free.lastAcessTime = time;
                        int frameTempId = currentProcess.processId + 1;
                        if(debugStatus == 1){
                            printf("%d %s %d %s %d %s %d %s %d", frameTempId, " reference word ", currentProcess.currentReference, " (Page ", currentPage, ") at time ", time, " :Fault, using free frame ", check1);
                        }
                        currentProcess.numOfFaults++;
                    }

                    else{
                        int index = -1;
                        
                        if(replacementAlgo.compare("lru") == 0){
                            index = replace_lru(frameList);
                        }
                        else if(replacementAlgo.compare("fifo") == 0){
                            index = replace_fifo(frameList);
                        }
                        else if(replacementAlgo.compare("random") == 0){
                            index = replace_random(frameList);
                        }
                        else{
                            printf("INVALID REPLACEMENT ALGO!\n");
                            return;
                        }

                        Frame replacedFrame = frameList[index];
                        int replacedPage = replacedFrame.pageNum;
                        int id = replacedFrame.processId;

                        Process replacedProcess = processList[id];
                        replacedProcess.numOfEvictions++;
                        replacedProcess.runTime += time - replacedFrame.initialTime;

                        replacedFrame.initialTime = time;
                        replacedFrame.lastAcessTime = time;
                        replacedFrame.processId = currentProcess.processId;
                        replacedFrame.pageNum = currentPage;
                        replacedFrame.status = 1;
                        int frameTempId = currentProcess.processId + 1;
                        if(debugStatus == 1){
                            printf("%d %s %d %s %d %s %d %s %d %s %d %s %d", frameTempId, " reference word ", currentProcess.currentReference, " (Page ", currentPage, ") at time ", time, " :Fault, evicting page ", replacedPage, " of ", replacedProcess.processId, " from Frame ", index);
                        } 
                        currentProcess.numOfFaults++;                                                                   
                    }
                }
                const int num = getRandomNum();
                currentProcess.nextReference(num);
                currentProcess.numOfReferencesTaken++;
                time++;

            }
        }
    }
}




