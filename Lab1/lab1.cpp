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
void firstPass(std:: ifstream input);
void secondPass();

int main ( int argc, char *argv[] )
{   
    firstPass(collectInput(argc, argv));
	secondPass();

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
            if (!words[i].empty()){
                wordList.push_back(words[i]);
            }
		}
        if ((lineNum % 3) == 0){
            int defSize = stoi(wordList[0]);
            for (int i = 0; i < defSize; i++){
                string temp1 = wordList[1 + 2 * i];
                int temp2 = stoi(wordList[2 + 2 * i]);
                if (symTable.count(temp1) == 0){
                    defList1.push_back(temp1);
                    symTable.insert(pair<string, int>(temp1, addOffset + temp2)); 
                    checkTable.insert(pair<string, int>(temp1, 1)); 
               
                }else{
                    printf("%s %s %s", "Error: the symbol ", temp1.c_str(), " has already been defined");
                }
            }
            defList.push_back(defList1);
        }

        else if((lineNum % 3) == 1){
            int useSize = stoi(wordList[0]);
            for (int i = 0; i < useSize; i++){
                string temp = wordList[1 + i];
                useList1.push_back(temp);
            }
            useList.push_back(useList1);
        }

        else if((lineNum % 3) == 2){
            int instSize = stoi(wordList[0]);
            for (int i = 0; i < instSize; i++){
                string temp1 = wordList[1 + 2 * i];
                string temp2 = wordList[2 + 2 * i];
                instList1.push_back(temp1);
                instList1.push_back(temp2);
            }
            instructions.push_back(instList1);
            modBaseAdd.push_back(addOffset);
            addOffset += instSize;
            mod_count++;
		}
        lineNum++;
        wordList.clear();
        totalAdd = addOffset - 1;
       
    }


}


void secondPass(){
    std::vector<string > useList1;
    std::vector<string > defList1;
    std::vector<string > instList1;
    cout<<"Sumbol Table\n";

    for (auto const& x : symTable){
        std::cout << x.first  // string (key)
                    << " = "
                    << x.second // string's value 
                    << std::endl ;
    }
    cout<<"\t\tMemory Map\n";

    for(int i = 0; i < mod_count; i++){
        printf("%s %d", "+", modBaseAdd[i]);
        useList1 = useList[i];
        defList1 = defList[i];
        instList1 = instructions[i];
        int instSize = instList1.size()/2;
        std::vector<int> checkuse(useList1.size());
        for (int q = 0; q < checkuse.size(); q++){
            checkuse[q] = 1;
        }
    

        std::vector<string> def(instSize);
        for(int t = 0; t < defList1.size(); t++){
            if (symTable.find(defList1[t])->second - modBaseAdd[i] < instSize){
                def[symTable.find(defList1[t])->second - modBaseAdd[i]] = defList1[t];
            }
            else{
                printf("%s %s %s", "Error: symbol ", defList1[t].c_str(), " exceeds the module size\n");
             
            }
        }


        for(int j = 0; j < instSize; j++){
            if (!def[j].empty()){
                printf("%d %s %s %s", j, ":", def[j].c_str(), "\t\n");
            }
            else{
                printf("%d %s", j, ":\t\n");
            } 
            printf("%s %s %s %s", instList1[2 * j].c_str(), " ", instList1[2 * j + 1].c_str(), " ");
            string temp1 = instList1[2 * j];
            int temp2 = stoi(instList1[2 * j + 1]);
        
            if(temp1.compare("R") == 0){
                int result = temp2 + modBaseAdd[i];
                int check = (result % 100);
                if (check <= totalAdd){
                    printf("%s %d %s %d %s %d %s", "\t\t", temp2, "+", modBaseAdd[i], " =", result, "\n");
                }
                else{
                    int temp = result - check;
                    printf("%s %d %s", "\t\t\t", + temp, "\n");
                    printf("%s", "Error: the relative address exceeds total address, initialize as zero\n");
                }
            }
            
            else if(temp1.compare("I") == 0){
                printf("%s %d %s", "\t\t\t", + temp2, "\n");
            }
            else if(temp1.compare("E") == 0){

                int temp3 = (temp2 % 10);
                if (temp3 >= useList1.size()){
                    printf("%s %d %s", "\t\t\t", + temp2, "\n");
                    printf("%s", "Error: the address exceeds the uselist\n");
                }
                else if (symTable.count(useList1[temp3]) != 0){
                    int checkNum = checkTable[useList1[temp3]];
                    checkNum--;
                    checkTable.erase(useList1[temp3]);
                    checkTable.insert(pair<string, int>(useList1[temp3], 1)); 
                    int temp4 = temp2 - temp3 + symTable.find(useList1[temp3])->second;
                    int temp5 = checkuse[temp3];
                    checkuse[temp3] = temp5 - 1;
                    printf("%s %s %s %d %s", "->", useList1[temp3].c_str(), "\t\t", temp4, "\n");
                }
                else{
                    int temp4 = temp2 - temp3;
                    printf("%s %s %s %d %s", "->", useList1[temp3].c_str(), "\t\t", temp4, "\n");
                    printf("%s %s %s", "Error: symbol ", useList1[temp3].c_str(), " hasn't been defined, initialize as zero\n");
                    int temp5 = checkuse[temp3];
                    checkuse[temp3] = temp5 - 1;
                }
            }
            else if(temp1.compare("A") == 0){
                int temp = temp2 % 1000;
                if (temp > totalAdd){
                    int temp3 = temp2 - temp;
                    printf("%s %d %s", "\t\t\t", temp3, "\n");
                    printf("%s", "Error: the absolute address exceeds the total address, initialize to zero\n");
                }else{
                    printf("%s %d %s", "\t\t\t", temp2, "\n");
                }
            }
            
            else{
                printf("%s", "no such command\n");

            }
                  
		}

    }
    

}