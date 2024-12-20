#include <iostream>
#include <fstream>
#include <vector>  

#define gSize 141
using namespace std;

int endX;
int endY;
int startX;
int startY;
vector<int> xC{0};
vector<int> yC{0};
vector<int> oldX;
vector<int> oldY;
vector<int> replX;
vector<int> replY;
int clayer=1;
int olc=1000000;
void printg(char (*grid)[gSize][gSize]){
    for (int i=0;i<gSize;i++){
        for(int j=0;j<gSize;j++){
            cout<<(*grid)[i][j];
        }
        cout<<endl;
    }
}
bool iterate(char (*grid)[gSize][gSize], int (*costg)[gSize][gSize]){
    oldX.clear();
    oldY.clear();
    oldX.resize(xC.size());
    oldY.resize(xC.size());
    copy(xC.begin(),xC.end(),oldX.begin());
    copy(yC.begin(),yC.end(),oldY.begin());
    xC.clear();
    yC.clear();
    clayer++;
    if(olc-clayer<100){
        return false;
    }
    for(int i=0;i<oldX.size();i++){
        int tX=oldX[i];
        int tY=oldY[i];
        if (tX==endX&&tY==endY){
            return true;
        }
        if(tY+1<gSize){
            if((*costg)[tY+1][tX]==0&&(*grid)[tY+1][tX]=='.'){
                (*costg)[tY+1][tX]=clayer;
                xC.push_back(tX);
                yC.push_back(tY+1);
            }
        }
        if(tX+1<gSize){
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
    return iterate(grid,costg);
}
int main(){
    ifstream input("input");
    cout<<"inning"<<endl;
    char grid[gSize][gSize]={};
    int costg[gSize][gSize]{};
    for (int i=0;i<gSize;i++){
        string sq;
        input>>sq;
        for(int j=0;j<gSize;j++){
            costg[i][j]=0;
            grid[i][j]=sq[j];
            if (sq[j]=='S'){
                grid[i][j]='.';
                startX=j;
                startY=i;
            }
            if (sq[j]=='E'){
                grid[i][j]='.';
                endX=j;
                endY=i;
            }
        }
    }
    for (int x=1;x<gSize-1;x++){
        for(int y=1;y<gSize-1;y++){
            if (grid[y][x]!='#'){
                continue;
            }
            char surr[4]={grid[y][x+1],grid[y][x-1],grid[y+1][x],grid[y-1][x]};
            int wc=0;
            for(int i=0;i<4;i++){
                if (surr[i]=='#'){
                    wc++;
                }
            }
            if(wc>2){
                continue;
            }
            replX.push_back(x);
            replY.push_back(y);
        }
    }
    cout<<"Old:"<<endl;
    printg(&grid);
    
    xC[0]=startX;
    yC[0]=startY;
    
    iterate(&grid,&costg);
    olc=clayer;
    cout<<"Old optimal: "<<olc<<endl;

    int skippbl=0;
    for(int i=0;i<replX.size();i++){
        grid[replY[i]][replX[i]]='.';
        
        xC.clear();
        yC.clear();
        xC.push_back(startX);
        yC.push_back(startY);
        
        fill(&costg[0][0],&costg[0][0]+gSize*gSize,0);
        clayer=1;
        if(iterate(&grid,&costg)){
            skippbl++;
            cout<<"Removing wall at "<<replX[i]<<", "<<replY[i]<<" skipped "<<olc-clayer<<" for new optimal "<<clayer<<endl;
        }else{
            cout<<"Removing wall at "<<replX[i]<<", "<<replY[i]<<" halted, inoptimal"<<endl;
        };

        grid[replY[i]][replX[i]]='#';
    }
    cout<<"Skipped enough:"<<skippbl<<endl;
    /*cout<<"New:"<<endl;
    printg(&visual);
    cout<<"Optimal:"<<clayer-2<<endl;*/
}