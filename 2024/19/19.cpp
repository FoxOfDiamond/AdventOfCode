#include <iostream>
#include <fstream>
#include <vector>  
#include <map>
#define refsize 447
#define psize 400
#define ipn "input"
using namespace std;

vector<string> patterns;
map<string,int> pcache;
int registerString(string inp){
    int strl=inp.size()-1;
    if (pcache.find(inp)!=pcache.end()){
        cout<<inp;
        return pcache[inp];
    };
    while(true){
        if (pcache.find(inp.substr(0,strl))!=pcache.end()){
            if(pcache[inp.substr(0,strl)]>0){
                break;
            }
        }
        strl--;
        if (strl<1){
            pcache[inp]=0;
            return 0;
        }
    }
    int oref=pcache[inp.substr(0,strl)];
    cout<<inp.substr(0,strl)<<"|";
    while(true){
        int ref=registerString(inp.substr(strl,inp.size()-strl));
        if (ref>0){
            pcache[inp]=ref+oref;
            //cout<<endl<<inp.substr(sts,lts)<<":"<<ref<<endl;
            return ref+oref;
        }
        strl--;
        if (strl<1){
            pcache[inp]=0;
            return 0;
        }
    }
    return 0;
}
int main(void){
    ifstream input(ipn);

    string temps;
    for(int i=0;i<refsize;i++){
        input>>temps;
        pcache[temps]=1;
    }
    for(int i=0;i<psize;i++){
        input>>temps;
        patterns.push_back(temps);
    }
    cout<<"Inputted"<<endl;
    int pos=0;
    for(int i=0;i<patterns.size();i++){
        int res=registerString(patterns[i]);
        if(res>0){
            pos++;
            cout<<" possible with "<<res<<endl;
        }else{
            cout<<patterns[i]<<" not possible"<<endl;
        }
    }
    cout<<"Total possible:"<<pos<<endl;
}