#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;
unsigned int mix(unsigned int a, unsigned int b){
    return a^b;
}
unsigned int prune(unsigned int a){
    return a%16777216;
}
int main() 
{
    ifstream input("input");
    int sum=0;
    unsigned int ict;
    while(input>>ict){
        cout<<ict<<" => ";
        for(int i=0;i<2000;i++){
            ict=prune(mix(ict,ict*64));
            ict=prune(mix(ict,ict/32));
            ict=prune(mix(ict,ict*2048));
        }
        cout<<ict<<endl;
        sum+=ict;
    }
    cout<<"Sum:"<<sum<<endl;
    return 0;
}