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

std::string processes = ""; 
std::string temp = ""; 
vector<string> nums;
// int arr [100][4];
// array<int, 4> arr[3];
array<int, 4> arr[100];
int rowIndex = 0;
int colIndex = 0;
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
                    cout<<n;
                    cout<<'\n';
                    array<int, 4> arr[n];
                }
                else if(count > 1 && x != '(' && x != ')' && x != ' '){
                    temp.push_back(x);
                }
                else if((x == ' ' || x == ')') && (temp != "" && temp != " ")){
                    arr[rowIndex][colIndex] = std::stoi(temp);
                    colIndex++;
                    temp = "";
                }
                else if(x == ')'){
                    rowIndex++;
                    colIndex = 0;
                    temp = "";
                }
                count+=1;
            }      
        }
    }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
            cout<<arr[i][j];
            cout<<' ';
        }
    }
    cout<<"\n===================================\n";
    sort( arr, arr + n );

    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
            cout<<arr[i][j];
            cout<<' ';
        }
    }

    
    
  
}