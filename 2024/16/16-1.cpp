#include <iostream>
#include <fstream>
#define size 15
const int xd[4]{0,1,0,-1};
const int yd[4]{1,0,-1,0};
using namespace std;
void printg(char (*grid)[size][size]){
    for (int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            cout<<(*grid)[i][j];
        }
        cout<<endl;
    }
}
void iterate(char (*grid)[size][size], int (*costg)[size][size][4], int x, int y, int d, int cost){
    //up, right, down, left
    if ((*grid)[y][x]=='#'){return;}
    if ((*costg)[y][x][d]>cost){
        (*costg)[y][x][d]=cost;
    }else{return;}
    if ((*grid[y][x]=='E')){
        return;
    }
    iterate(grid,costg,x+xd[d],y+yd[d],d,cost+1);
    d=(d+1)%4;
    iterate(grid,costg,x+xd[d],y+yd[d],d,cost+1000);
    d=(d-2)%4;
    iterate(grid,costg,x+xd[d],y+yd[d],d,cost+1000);
    
}
int main(){
    ifstream input("input");
    cout<<"inning"<<endl;
    char grid[size][size]={};
    int costg[size][size][4]={{{1000000}}};
    int startX;
    int startY;
    int endX;
    int endY;
    for (int i=0;i<size;i++){
        string sq;
        input>>sq;
        for(int j=0;j<size;j++){
            grid[i][j]=sq[j];
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

    iterate(&grid,&costg,startX,startY,0,0);
    iterate(&grid,&costg,startX,startY,1,0);
    iterate(&grid,&costg,startX,startY,2,0);
    iterate(&grid,&costg,startX,startY,3,0);

    cout<<costg[endY][endX][0]<<endl;
    cout<<costg[endY][endX][1]<<endl;
    cout<<costg[endY][endX][2]<<endl;
    cout<<costg[endY][endX][3]<<endl;
}