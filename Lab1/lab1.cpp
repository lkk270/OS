#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctype.h>
#include <boost/regex.hpp>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <boost/tokenizer.hpp>
// #include <array>
#include<string.h>
#include <algorithm>
#include <math.h>   

using namespace std;
using namespace boost;

std::map<std::string, int> symTable;
std::map<std::string, int> checkTable;
std::vector<int > modBaseAdd;
std::vector<std::vector<string> > useList;
std::vector<std::vector<string> >defList;
std::vector<std::vector<string> >instructions;
int mod_count = 0;
int add_offset;
int totalAdd;
std::ifstream collectInput(int argc, char *argv[]);
std::vector<string> split(string s);
void print1dVector(std::vector<string> arr);

int main ( int argc, char *argv[] )
{   
    collectInput(argc, argv);

}

std::ifstream collectInput(int argc, char *argv[]){ 
    if ( argc != 2 ) {
         cout<<"usage: "<< argv[0] <<" <filename>\n";
    }
    else {
        ifstream the_file ( argv[1] );
        if ( !the_file.is_open() ){
            cout<<"Could not open file\n";
            exit(0);
        }  
        else{
            cout<<"GOOD\n";
            return the_file;
        } 
    }
}

void print1dVector(std::vector<string> arr){
    for (auto i = arr.begin(); i != arr.end(); ++i)
        std::cout << *i << ' ';
    cout<<'\n';

}


std::vector<string> split(string s){
    vector<string> v;
    tokenizer<> tok(s);
    for_each (tok.begin(), tok.end(), [&v](const string & s) { v.push_back(s); } );
    return v;
}

void firstPass(std:: ifstream input){
    std::string num;
    getline(input, num);
    int lineNum = 0;
	int addOffset = 0;
    std::vector<string > words;
    string currentLine;
	string currentLine_check;
    std::vector<string > wordList;
    while(getline(input, currentLine_check)){
        while (currentLine_check.length() == 0){
            getline(input, currentLine_check);
        }
        currentLine = currentLine_check;
        words = split(currentLine);
        std::vector<string > useList1;
        std::vector<string > defList1;
        std::vector<string > instList1;
        words = split(currentLine);


        for (int i = 0; i < words.size(); i++){
				if ("".compar(words[i]) != 0){
					wordList.push_back(words[i]);
				}
			}
       
    }


}
