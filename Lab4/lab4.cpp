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

#include "frame.h"
#include "process.h"



using namespace std;

std::ifstream randomFile; 
int machineSize, pageSize, processSize, jobMix, numOfReferences;
int debugStatus;
std::string replacementAlgo;
int quantumNum = 3;
vector<Process> processList;
vector<Frame> frameList;

void collectInput(int argc, char *argv[]);

int main ( int argc, char *argv[] )
{
    randomFile = "random-numbers";
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
			if (currentFrame.InitialTime < smallestVal){
				smallestVal = currentFrame.InitialTime;
				index = i;
			}
		}
		return index;
}

	//Find the replaced frame using random number algorithm
	
int replace_random(vector<Frame> frameList){
        int randNum = rand() % randomFile;
		int index = randNum % (frameList.size());
		return index;
}
    

