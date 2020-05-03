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
vector<Process*> processList;
vector<Frame*> frameList;
ifstream infile("random-numbers");
void collectInput(int argc, char *argv[]);
int getNextRandomNum();
void run();
void out();

int main ( int argc, char *argv[] )
{   
    srand (time(NULL));
    collectInput(argc, argv);
    run();
    out();
}

void collectInput(int argc, char *argv[]){ //allocates user inputs to appropriate vars
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
    cout<<"\n";
    printf("%s %d", "The machine size is", machineSize);
    cout<<".\n";
    printf("%s %d", "The page size is", pageSize);
    cout<<".\n";
    printf("%s %d", "The process size is", processSize);
    cout<<".\n";
    printf("%s %d", "The job mix number is is", jobMix);
    cout<<".\n";
    printf("%s %d", "The number of references per process", numOfReferences);
    cout<<".\n";
    printf("%s %s", "The replacement algorithm is", replacementAlgo.c_str());
    cout<<".\n";
    printf("%s %d", "The debug level is", debugStatus);
    cout<<".\n\n";

    if(jobMix == 1){
            Process*  p1 = new Process(1.0, 0.0, 0.0, pageSize, processSize, numOfReferences, 0);
            processList.push_back(p1);
    }
    else if(jobMix == 2){
        for(int i = 0; i < 4; i++){
            Process* p2 = new Process(1.0, 0.0, 0.0, pageSize, processSize, numOfReferences, i);
            processList.push_back(p2);
        }
    }
    else if(jobMix == 3){
        for(int i = 0; i < 4; i++){
            Process* p3 = new Process(0.0, 0.0, 0.0, pageSize, processSize, numOfReferences, i);
            processList.push_back(p3);
        }
    }
    else if(jobMix == 4){
        Process* p4 = new Process(0.75, 0.25, 0, pageSize, processSize, numOfReferences, 0);
        Process* p5 = new Process(0.75, 0.0, 0.25, pageSize, processSize, numOfReferences, 1);
        Process* p6 = new Process(0.75, 0.125, 0.125, pageSize, processSize, numOfReferences, 2);
        Process* p7 = new Process(0.5, 0.125, 0.125, pageSize, processSize, numOfReferences, 3);
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
        Frame* f = new Frame(-1, -1, -1);
        frameList.push_back(f);
    }     
}


int checkHit(Process* p, vector<Frame*>  frameList){ // Checks if the current process is in the frame table
		for (int i = 0; i < frameList.size(); i++){
			Frame* currentFrame = frameList[i];
			int currentPage = p->currentReference / pageSize;
			if (p->processId == currentFrame->processId && currentPage == currentFrame->pageNum && currentFrame->status == 1){
				return i;
			}
		}
		return -1;
}


	
int checkFull(vector<Frame*> frameList){    //checks if the frame is full
    for (int i = frameList.size() - 1; i > -1; i--){
        Frame* currentFrame = frameList[i];
        if (currentFrame->status == 0){
            return i;
        }
    }
    return -1;
}


int lru(vector<Frame*>  frameList){ //replacement algo - lru
		int smallestVal = std::numeric_limits<int>::max();
		int index = -1;
		for (int i = 0; i < frameList.size(); i++){
			Frame* currentFrame = frameList[i];
			if (currentFrame->lastAcessTime < smallestVal){
				smallestVal = currentFrame->lastAcessTime;
				index = i;
			}
		}
		return index;
	}


int fifo(vector<Frame*>  frameList){ //replacement algo - fifo
		int smallestVal = std::numeric_limits<int>::max();
		int index = -1;
		for (int i = 0; i < frameList.size(); i++){
			Frame* currentFrame= frameList[i];
			if (currentFrame->initialTime < smallestVal){
				smallestVal = currentFrame->initialTime;
				index = i;
			}
		}
		return index;
}


int random(vector<Frame*>  frameList){ //replacement algo - random
    int randNum = getNextRandomNum();
    int index = (randNum) % frameList.size();
    return index;
}


int getNextRandomNum(){ //next random num in random-numbers file
    std::string num;
    getline(infile, num);
    return stoi(num);
}


void typeOfPrint(double num){   //for printing floats nicely
    bool ret = true;
    int count = 0;
    std::string str = to_string(num);
    // cout<<"STR ";
    // cout<<str;
    // cout<<'\n';
    bool dot = false;
    int numOfZeros = 0; 
    while (true){
        if(!dot && str[count] == '.'){
            dot = true;
        }
        if(dot && str[count] == '0'){
            numOfZeros++; 
        }
        if(count + 1 == str.length()){
            break;
        }
        count++;
    }
    if(str[str.length()-1] != '0' && numOfZeros == 0) {
        printf("%1.17g", (num));
        return;
    }
    else if(str[str.length()-1] != '0') {
        printf("%1.16g", (num));
        return;
    }
    switch(numOfZeros){
        case 0: 
            printf("%1.17g", (num));
            break;
        case 6: 
            printf("%.1f", num);
            break;
        case 5: 
            printf("%.1f", num);
            break;
        case 4: 
            printf("%.2f", num);
            break;
        case 3: 
            printf("%.3f", num);
            break;
        case 2: 
            printf("%.4f", num);
            break;
        case 1:
            printf("%.5f", num);
            break;
        default: 
            printf("%1.17g", num);
            break;
        
    }
        

} 


void run(){
    int time = 1; 
	int numFinished = 0;
    while (numFinished < processList.size()){    
        for (int i = 0; i < processList.size(); i++){
            for(int j = 0; j < quantumNum; j++){
                Process* currentProcess = processList[i];
                if(currentProcess->status == 1){
                    break;
                }   
                if(currentProcess->numOfReferencesTaken == numOfReferences){
                    numFinished++;
                    currentProcess->status = 1;
                    break;
                }
                int currentPage = currentProcess->currentReference/pageSize;
                int check = checkHit(currentProcess, frameList);

                if(check != -1){
                    Frame* frameTemp = frameList[check];
                    frameTemp->lastAcessTime = time;
                    int frameTempId = currentProcess->processId + 1;
                    if(debugStatus == 1){
                        printf("%d %s %d %s %d %s %d %s %d", frameTempId, "reference word", currentProcess->currentReference, "(Page ", currentPage, ") at time", time, ":Hit in frame", check);
                        cout<<".\n";
                    }
                }

                else{
                    int check1 = checkFull(frameList);

                    if(check1 != -1){
                        Frame* free = frameList[check1];
                        free->processId = currentProcess->processId;
                        free->pageNum = currentPage;
                        free->status = 1;
                        free->initialTime = time;
                        free->lastAcessTime = time;
                        int frameTempId = currentProcess->processId + 1;
                        if(debugStatus == 1){
                            printf("%d %s %d %s %d %s %d %s %d", frameTempId, "reference word", currentProcess->currentReference, "(Page ", currentPage, ") at time", time, ":Fault, using free frame", check1);
                            cout<<".\n";
                        }
                        currentProcess->numOfFaults++;
                    }

                    else{
                        int index = -1;
                        
                        if(replacementAlgo.compare("lru") == 0){
                            index = lru(frameList);
                        }
                        else if(replacementAlgo.compare("fifo") == 0){
                            index = fifo(frameList);
                        }
                        else if(replacementAlgo.compare("random") == 0){
                            index = random(frameList);
                        }
                        else{
                            printf("INVALID REPLACEMENT ALGO!\n");
                            return;
                        }

                        Frame* replacedFrame = frameList[index];
                        int replacedPage = replacedFrame->pageNum;
                        int id = replacedFrame->processId;

                        Process* replacedProcess = processList[id];
                        replacedProcess->numOfEvictions++;
                        replacedProcess->residencyTime += time - replacedFrame->initialTime;

                        replacedFrame->initialTime = time;
                        replacedFrame->lastAcessTime = time;
                        replacedFrame->processId = currentProcess->processId;
                        replacedFrame->pageNum = currentPage;
                        replacedFrame->status = 1;
                        int frameTempId = currentProcess->processId + 1;
                        if(debugStatus == 1){
                            printf("%d %s %d %s %d %s %d %s %d %s %d %s %d", frameTempId, "references word", currentProcess->currentReference, "(Page ", currentPage, ") at time ", time, ":Fault, evicting page", replacedPage, "of", replacedProcess->processId, "from Frame", index);
                            cout<<".\n";
                        } 
                        currentProcess->numOfFaults++;                                                                   
                    }
                }
                currentProcess->nextReference(infile);
                currentProcess->numOfReferencesTaken++;
                time++;
            }
        }
    }
}


void out(){
    printf("%s", "\n");
    int totalFaults = 0;
    int totalResidency = 0;
    int totalEvictions = 0;

    for(int i = 0; i < processList.size(); i++){
        Process* p = processList[i];
        totalFaults += p->numOfFaults;
        totalResidency += p->residencyTime;
        totalEvictions += p->numOfEvictions;
        printf("%s %d %s %d %s", "Process", p->processId + 1, "had", p->numOfFaults, "faults");
        if(p->residencyTime == 0){
            printf("%s", "\n\tWith no evictons, the average residence is undefined.\n");
        }
        else{
            double averageResidency = (double) p->residencyTime/p->numOfEvictions;
            printf("%s", " and ");
            typeOfPrint(averageResidency);
            printf("%s", " average residency.\n");
            
         
        }
    }

    double totalAverageResidency = (double) totalResidency / totalEvictions;
    printf("%s", "\n");

    if(totalResidency != 0){
        printf("%s %d %s", "The total number of faults is", totalFaults, "and the overall average residency is ");
        typeOfPrint(totalAverageResidency);
        cout<<".\n";
        
    }
    else{
        printf("%s %d", "The total number of faults is", totalFaults);
        cout<<".\n\tWith no evictions, the overall average residency is undefined.\n";
    }
    printf("%s", "\n");

}




