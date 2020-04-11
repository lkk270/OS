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
#include <array>

using namespace std;

std::string firstLine = ""; 
std::string activities = ""; 

int main ( int argc, char *argv[] )
{
    
    // randomOS(5);
   
}


void createArray(int argc, char *argv[])
{
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
                activities += x
            }      
        }
    }
}
