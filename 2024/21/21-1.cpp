#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#define ipCount 5
using namespace std;
map<char,int> akrdX;
map<char,int> akrdY;
void init(){
    akrdX['0']=1;
    akrdY['0']=3;
    akrdX['A']=2;
    akrdY['A']=3;
    akrdX['1']=0;
    akrdY['1']=2;
    akrdX['2']=1;
    akrdY['2']=2;
    akrdX['3']=2;
    akrdY['3']=2;
    akrdX['4']=0;
    akrdY['4']=1;
    akrdX['5']=1;
    akrdY['5']=1;
    akrdX['6']=2;
    akrdY['6']=1;
    akrdX['7']=0;
    akrdY['7']=0;
    akrdX['8']=1;
    akrdY['8']=0;
    akrdX['9']=2;
    akrdY['9']=0;
    
    akrdX['a']=2;
    akrdY['a']=0;
    akrdX['<']=0;
    akrdY['<']=1;
    akrdX['>']=2;
    akrdY['>']=1;
    akrdX['v']=1;
    akrdY['v']=1;
    akrdX['^']=1;
    akrdY['^']=0;
}
string getKeypadSequence(vector<int> cord,bool pad=false)
{
    int x=2;
    int y=0;
    if(pad){
        y=3;
    }
    string outp="";
    for(int i=0;i<cord.size();i+=2){
        int dx=cord[i]-x;
        int dy=cord[i+1]-y;

        char horin;
        char verin;
        if (dx>0){
            horin='>';
        }else{
            horin='<';
        }
        if (dy>0){
            verin='v';
        }else{
            verin='^';
        }
        if((akrdX[horin]-x)*(akrdX[horin]-x)+(akrdY[horin]-y)*(akrdY[horin]-y)<(akrdX[verin]-x)*(akrdX[verin]-x)+(akrdY[verin]-y)*(akrdY[verin]-y)){
            outp+=string(abs(dy),verin);            
            outp+=string(abs(dx),horin);
        }else{
            outp+=string(abs(dx),horin);
            outp+=string(abs(dy),verin);
        }

        outp+='a';
        x=cord[i];
        y=cord[i+1];
    }
    cout<<outp<<endl;
    return outp;
}
vector<int> seqToCords(string inp){
    vector<int> outp;
    for(int i=0;i<inp.size();i++){
        outp.push_back(akrdX[inp[i]]);
        outp.push_back(akrdY[inp[i]]);
    }
    return outp;
}
int main() 
{
    init();
    int comp=0;
    ifstream input("input");
    for(int i=0;i<ipCount;i++){
        string ict;
        input>>ict;
        cout<<endl<<ict<<endl;
        int flength=getKeypadSequence(seqToCords(getKeypadSequence(seqToCords(getKeypadSequence(seqToCords(ict),true))))).size();
        cout<<"Length:"<<flength<<endl;
        bool leading=true;
        for(int ii=0;ii<ict.size();ii++){
            if(ict[ii]=='0'&&leading){
                ict=ict.substr(1,ict.size()-1);
            }else{
                leading=false;
            }
        }
        ict=ict.substr(0,ict.size()-1);
        cout<<"Numerical:"<<stoi(ict)<<endl<<endl<<"Complexity:"<<stoi(ict)*flength<<endl;
        comp+=stoi(ict)*flength;
    }
    cout<<"Total complexity:"<<comp<<endl;
    return 0;
}