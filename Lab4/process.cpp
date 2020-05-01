#include "process.h"
#include <time.h>
#include <stdio.h>     
#include <stdlib.h> 

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


void nextReference(std::ifstream rand){
    int nextRef = 0;
    
    int randNum = rand() % rand;
    
    double p = randNum / double(std::numeric_limits<int>::max());
    
    if (p < this.A){
        nextRef = (currentReference + 1) % this.processSize;
    }else if (p < this.A + this.B){
        nextRef = (currentReference + S - 5) % this.processSize;
    }else if (p < this.A + this.B + this.C){
        nextRef = (currentReference + 4) % this.processSize;
    }else{
        int temp = rand() % rand;
        nextRef = temp % this.processSize;
    }
    
    this.currentReference = nextRef;

}