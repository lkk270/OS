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

class Frame{
    public:
		
        int processId;		// process id of the process which is using this frame
        int pageNum;		// page number of current reference of the process using this frame
        int status; 			// 0 for unreferenced, 1 for referenced
        int InitialTime;	// time when this frame started to be referenced by the current process
        int lastAcessTime;		// time when this frame was accessed by the current process

    Frame(int processIdParam, int pageNumParam, int timeParam){ 
        pageNum = pageNumParam;
		processId = processIdParam;
		InitialTime = timeParam;
		status = 0;
		lastAcessTime = 0;

    }
};