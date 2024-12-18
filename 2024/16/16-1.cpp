#include <iostream>
#include <fstream>
#include <vector>
#define gSize 141
const int xd[4]{0,1,0,-1};
const int yd[4]{-1,0,1,0};
const char vd[4]{'^','>','v','<'};

using namespace std;

vector<int> optimalX={};
vector<int> optimalY={};
int optiCost=1000000;
int startX;
int startY;
int endX;
int endY;

void printg(char (*grid)[gSize][gSize]){
    for (int i=0;i<gSize;i++){
        for(int j=0;j<gSize;j++){
            cout<<(*grid)[i][j];
        }
        cout<<endl;
    }
}
int iterate(char (*grid)[gSize][gSize], int (*costg)[gSize][gSize][4], int x, int y, int d, int cost,char (*visual)[gSize][gSize]){
    //up, right, down, left
    int found=0;
    if ((*grid)[y][x]=='#'){return 0;}
    //cout<<(*costg)[y][x][d]<<endl;
    if ((*costg)[y][x][d]>=cost){
        (*costg)[y][x][d]=cost;
    }else{return 0;}
    if ((*grid)[y][x]=='E'){
        cout<<"Solution found:"<<cost<<endl;
        if (cost<optiCost){
            cout<<"New optimal found"<<endl;
            optiCost=cost;
            optimalX.clear();
            optimalY.clear();
            return 2;
        }
        if (cost==optiCost){
            return 2;

        }
        return 1;
    }
    int tpa=iterate(grid,costg,x+xd[d],y+yd[d],d,cost+1,visual);
    if(tpa>0){
        (*visual)[y][x]=vd[d];
    };
    if (tpa>found){
        found=tpa;
    }
    d=(d+1)%4;
    tpa=iterate(grid,costg,x+xd[d],y+yd[d],d,cost+1000,visual);
    if(tpa>0){
        (*visual)[y][x]=vd[d];
    };
    if (tpa>found){
        found=tpa;
    }
    d=(d+2)%4;
    tpa=iterate(grid,costg,x+xd[d],y+yd[d],d,cost+1000,visual);
    if(tpa>0){
        (*visual)[y][x]=vd[d];
    };
    if (tpa>found){
        found=tpa;
    }
    if (found==2){
        optimalX.push_back(x);
        optimalY.push_back(y);
    }
    return found;
    
}
int main(){
    ifstream input("input");
    cout<<"inning"<<endl;
    char grid[gSize][gSize]={};
    char visual[gSize][gSize]={};
    int costg[gSize][gSize][4]={10000000};
    for (int i=0;i<gSize;i++){
        for(int j=0;j<gSize;j++){
            costg[i][j][0]=10000000;
            costg[i][j][1]=10000000;
            costg[i][j][2]=10000000;
            costg[i][j][3]=10000000;
        }
    }
    for (int i=0;i<gSize;i++){
        string sq;
        input>>sq;
        for(int j=0;j<gSize;j++){
            grid[i][j]=sq[j];
            visual[i][j]=sq[j];
            if (sq[j]=='S'){
              startX=j;
              startY=i;
            }
            if (sq[j]=='E'){
              endX=j;
              endY=i;
            }
        }
    }
    cout<<"Old:"<<endl;
    printg(&grid);

    iterate(&grid,&costg,startX,startY,1,0,&visual);
    cout<<"New:"<<endl;
    printg(&visual);
    int ucount=0;
    for(int i=0;i<optimalX.size();i++){
        bool dupe=false;
        for(int j=0;j<optimalX.size();j++){
            if (optimalX[i]==optimalX[j]&&optimalY[i]==optimalY[j]&&i!=j){
                dupe=true;
                break;
            }
        }
        if (!dupe){
            ucount++;
        }
    }
    cout<<"Involved:"<<optimalX.size()<<", unique:"<<ucount;
}