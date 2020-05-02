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
// #include <array>
#include<string.h>
#include <algorithm>
#include <math.h>   
#include <limits>
#include <cstddef>

class Process{
    public:
        double A;
        double B;
        double C;
        int pageSize; 					// page size
        int processSize;					// process size
        int numOfReferences;					// number of references
        int currentReference;     		// current reference
        int numOfReferencesTaken;				// number of references taken
        int numOfFaults;			// number of faults
        int numOfEvictions;		// number of evictions
        int residencyTime;			// total residency time for this process
        int processId;			// the index of this process in process list
        int status;
        void nextReference(int randNum){
            int nextRef = 0;
            // std::cout<<"\nBEFORE CURRENT REFERENCE ";
            // std::cout<<this->currentReference;
            // std::cout<<'\n';
            // int randNum = rand() % rand;
            
            double p = randNum / double(std::numeric_limits<int>::max());
            // std::cout<<"randNum ";
            // std::cout<<randNum;
            // std::cout<<'\n';
            // std::cout<<"p ";
            // std::cout<<p;
            // std::cout<<'\n';
            if (p < this-> A){
                //std::cout<<"COCK1\n";
                nextRef = (this->currentReference + 1) % this->processSize;
            }else if (p < this->A + this->B){
                //std::cout<<"COCK2\n";
                nextRef = (this->currentReference + this->processSize - 5) % this->processSize;
            }else if (p < this->A + this->B + this->C){
                //std::cout<<"COCK3\n";
                nextRef = (this->currentReference + 4) % this->processSize;
            }else{
                ///std::cout<<"COCK4\n";
                int temp = rand() % randNum;
                nextRef = temp % this->processSize;
            }
            
            this->currentReference = nextRef;
            // std::cout<<"AFTER CURRENT REFERENCE ";
            // std::cout<<this->currentReference;
            // std::cout<<'\n';
            
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
        // initial reference number
		this->currentReference = (111 * (processIdParam + 1)) % processSizeParam;  
        
    }
};