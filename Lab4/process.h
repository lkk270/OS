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
        int time;			// total resisdency time for this process
        int processId;			// the index of this process in process list
        int status;
        void nextReference(std::ifstream rand_sc);

    Process(double AParam, double BParam, double CParam, int pageSizeParam, int processSizeParam, int numOfReferencesParam, int processIdParam){ 
        A = AParam;
		B = BParam;
		C = CParam;
		pageSize = pageSizeParam;
		processSize = processSizeParam;
		numOfReferences= numOfReferencesParam;
        status = 0;
        processId = processIdParam;
        numOfReferencesTaken = 0;
        numOfFaults= 0;
        numOfEvictions = 0;
        time = 0;
        // initial reference number
		currentReference = (111 * (processIdParam + 1)) % processSizeParam;  
        
    }
};