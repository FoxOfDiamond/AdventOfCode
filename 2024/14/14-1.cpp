#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

vector<string> splitstr(string input, string delimiter){
    vector<string> result;
    string t="";
    for (int i=0;i<input.size();i++){
        if (input.substr(i,delimiter.size())==delimiter){
            i+=delimiter.size()-1;
            result.push_back(t);
            t="";
        }else{
            t+=input[i];
        }
    }
    result.push_back(t);
    return result;
}

int main(void){

}