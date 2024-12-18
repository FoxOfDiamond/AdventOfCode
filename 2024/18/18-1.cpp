#include <iostream>
#include <fstream>
#include <vector>  

#define gSize 71
using namespace std;

int endX=gSize-1;
int endY=gSize-1;
vector<int> xC{0};
vector<int> yC{0};
vector<int> oldX;
vector<int> oldY;
int clayer=1;
void printg(char (*grid)[gSize][gSize]){
    for (int i=0;i<gSize;i++){
        for(int j=0;j<gSize;j++){
            cout<<(*grid)[i][j];
        }
        cout<<endl;
    }
}
void iterate(char (*grid)[gSize][gSize],char (*visual)[gSize][gSize], int (*costg)[gSize][gSize]){
    oldX.resize(xC.size());
    oldY.resize(xC.size());
    copy(xC.begin(),xC.end(),oldX.begin());
    copy(yC.begin(),yC.end(),oldY.begin());
    xC.clear();
    yC.clear();
    clayer++;
    for (int i=0;i<gSize;i++){
        for(int j=0;j<gSize;j++){
            if ((*visual)[i][j]=='X'){
                (*visual)[i][j]='o';
            }
        }
    }
    for(int i=0;i<oldX.size();i++){
        int tX=oldX[i];
        int tY=oldY[i];
        (*visual)[tY][tX]='X';
        if (tX==endX&&tY==endY){
            return;
        }
        if(tY+1<71){
            if((*costg)[tY+1][tX]==0&&(*grid)[tY+1][tX]=='.'){
                (*costg)[tY+1][tX]=clayer;
                xC.push_back(tX);
                yC.push_back(tY+1);
            }
        }
        if(tX+1<71){
            if((*costg)[tY][tX+1]==0&&(*grid)[tY][tX+1]=='.'){
                (*costg)[tY][tX+1]=clayer;
                xC.push_back(tX+1);
                yC.push_back(tY);
            }
        }
        if(tY-1>=0){
            if((*costg)[tY-1][tX]==0&&(*grid)[tY-1][tX]=='.'){
                (*costg)[tY-1][tX]=clayer;
                xC.push_back(tX);
                yC.push_back(tY-1);
            }
        }
        if(tX-1>=0){
            if((*costg)[tY][tX-1]==0&&(*grid)[tY][tX-1]=='.'){
                (*costg)[tY][tX-1]=clayer;
                xC.push_back(tX-1);
                yC.push_back(tY);
            }
        }
    }
    iterate(grid,visual,costg);
}
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
int main(){
    ifstream input("input");
    cout<<"inning"<<endl;
    char grid[gSize][gSize]={};
    char visual[gSize][gSize]={};
    int costg[gSize][gSize]{};
    for (int i=0;i<gSize;i++){
        for(int j=0;j<gSize;j++){
            costg[i][j]=0;
            grid[i][j]='.';
            visual[i][j]='.';
        }
    }
    vector<string> test=splitstr("1,2",",");
    for (int i=0;i<1024;i++){
        string sq;
        input>>sq;
        vector<string> parsed=splitstr(sq,",");
        grid[stoi(parsed[1])][stoi(parsed[0])]='#';
        visual[stoi(parsed[1])][stoi(parsed[0])]='#';
    }
    cout<<"Old:"<<endl;
    printg(&grid);
    
    iterate(&grid,&visual,&costg);

    cout<<"New:"<<endl;
    printg(&visual);
    cout<<"Optimal:"<<clayer-2<<endl;
}