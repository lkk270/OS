#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctype.h>
#include <fstream>

using namespace std;

std::string processes = ""; 
int n;

int main ( int argc, char *argv[] )
{
    int count = 0;
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
                if(count == 0){
                    n = x - '0';
                }
                else if(count > 1 && x != ' ' && x != ')' && x != '('){
                    processes.push_back(x);
                }
                count+=1;
            }      
        }
    }

    for(int i = 0; i < processes.size(); i+=4){
        cout<<i;
    }
    cout<< processes;
    cout<<'\n';
    cout<<n;
    cout<<'\n';
    



  
}