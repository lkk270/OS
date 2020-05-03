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
#include <string.h>
#include <algorithm>
#include <math.h>   
#include <limits>

class Frame{
    public:
        int processId;		
        int pageNum;		
        int status; 		
        int initialTime;	
        int lastAcessTime;

    Frame(int processIdParam, int pageNumParam, int timeParam){ 
        pageNum = pageNumParam;
		processId = processIdParam;
		initialTime = timeParam;
		status = 0;
		lastAcessTime = 0;
    }
};