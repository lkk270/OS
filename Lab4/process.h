#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>     
#include <stdlib.h> 
#include <map>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <math.h>   
#include <limits>
#include <cstddef>

class Process{
    public:
        double A;
        double B;
        double C;
        int pageSize; 	
        int processSize;				
        int numOfReferences;			
        int currentReference;     	
        int numOfReferencesTaken;		
        int numOfFaults;		
        int numOfEvictions;		
        int residencyTime;		
        int processId;			
        int status;
        void nextReference(std::ifstream& infile){
            std::string num;
            getline(infile, num);
            int randNum = stoi(num);
            int nextRef = 0;  
            double p = randNum / double(std::numeric_limits<int>::max());
            if (p < this-> A){
                nextRef = (this->currentReference + 1) % this->processSize;
            }else if (p < this->A + this->B){
                nextRef = (this->currentReference + this->processSize - 5) % this->processSize;
            }else if (p < this->A + this->B + this->C){
                nextRef = (this->currentReference + 4) % this->processSize;
            }else{
                std::string numTemp;
                getline(infile, numTemp);
                int temp = stoi(numTemp);
                nextRef = temp % this->processSize;
            }
            
            this->currentReference = nextRef;
        }


    Process(double AParam, double BParam, double CParam, int pageSizeParam, int processSizeParam, int numOfReferencesParam, int processIdParam){ 
        this->A = AParam;
		this->B = BParam;
		this->C = CParam;
		this->pageSize = pageSizeParam;
		this->processSize = processSizeParam;
		this->numOfReferences= numOfReferencesParam;
        this->status = 0;
        this->processId = processIdParam;
        this->numOfReferencesTaken = 0;
        this->numOfFaults= 0;
        this->numOfEvictions = 0;
        this->residencyTime = 0;
		this->currentReference = (111 * (processIdParam + 1)) % processSizeParam;  
        
    }
};