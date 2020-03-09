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
array<int, 4> arr[100];
int rowIndex = 0;
int colIndex = 0;
int n;

void createArray(int argc, char *argv[]);
void printArray();
int randomOS(int U);

int main ( int argc, char *argv[] )
{
    createArray(argc, argv);
    printf("The original input was: %d %s", n, "");
    printArray();
    sort( arr, arr + n );
    printf("The (sorted) input is:  %d %s", n, "");
    printArray();
    // randomOS(5);
   
}

int randomOS(int U){
    int ret = 0;
    int x;
    ifstream inFile;
    
    inFile.open("random-numbers");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); 
    }
    
    while (inFile >> x) {
        ret = 1 + (x % U);
        cout<< ret;
    }
    
    inFile.close();
    return ret;

}
void printArray(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < 4; j++){
            if(j== 0){
                cout<<'(';
                cout<<arr[i][j];
                cout<<' ';
            }
            else if(j == 3){
                cout<<arr[i][j];
                cout<<") ";
            }
            else{
                cout<<arr[i][j];
                cout<<' ';
            } 
        }
    }
    printf ("\n");
}

void createArray(int argc, char *argv[])
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
}