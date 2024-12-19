#include <iostream>
#include <fstream>
#include <functional>
#define ysize 50
#define fname "15-input"
#define xsize ysize*2
    using namespace std;

void printarr(char (*arr)[ysize][xsize]){
    for (int i=0;i<ysize;i++){
        for(int j=0;j<xsize;j++){
            cout<<(*arr)[i][j];
        }
        cout<<endl;
    }
}
void movehor(char (*arr)[ysize][xsize],int *x, int *y,int d){
    int bc=0; //Box ocunter??
    int tx=*x+d;
    while ((*arr)[*y][tx]=='['||(*arr)[*y][tx]==']'){
        tx+=d;
        bc+=1;
    }
    if ((*arr)[*y][tx]=='.'){
        for (int i=tx;i!=*x+d;i-=d*2){
            if(d>0){
                (*arr)[*y][i-1]='[';
                (*arr)[*y][i]=']';

            }else{
                (*arr)[*y][i]='[';
                (*arr)[*y][i+1]=']';
            }
        }
        (*arr)[*y][*x]='.';
        (*arr)[*y][*x+d]='@';
        *x+=d;
    }
}
bool _movable=false;
vector<int> mboxes_x;
vector<int> mboxes_y;
void movbox(char (*arr)[ysize][xsize],int x, int y,int d){
    //x marks [
    mboxes_x.insert(mboxes_x.begin(),x);
    mboxes_y.insert(mboxes_y.begin(),y);
    if((*arr)[y+d][x]=='#'||(*arr)[y+d][x+1]=='#'){
       _movable=false;
       return;
    }
    if((*arr)[y+d][x]=='['){
        movbox(arr,x,y+d,d);
    }
    if((*arr)[y+d][x]==']'){
        movbox(arr,x-1,y+d,d);
    }
    if((*arr)[y+d][x+1]=='['){
        movbox(arr,x+1,y+d,d);
    }
}
void movert(char (*arr)[ysize][xsize],int *x, int *y,int d){
    int bc=0; 
    int ty=*y+d;

    if ((*arr)[ty][*x]=='#'){
        return;
    }

    _movable=true;
    mboxes_x.clear();
    mboxes_y.clear();
    if ((*arr)[ty][*x]=='.'){
        (*arr)[ty][*x]='@';
        (*arr)[*y][*x]='.';
        *y+=d;
        return;
    }
    if((*arr)[ty][*x]=='['){
        movbox(arr,*x,ty,d);
    }
    if((*arr)[ty][*x]==']'){
        movbox(arr,*x-1,ty,d);
    }
    if (_movable){
        for (int i=0;i<mboxes_x.size();i++){
            (*arr)[mboxes_y[i]][mboxes_x[i]]='.';
            (*arr)[mboxes_y[i]][mboxes_x[i]+1]='.';
        }
        for (int i=0;i<mboxes_x.size();i++){
            (*arr)[mboxes_y[i]+d][mboxes_x[i]]='[';
            (*arr)[mboxes_y[i]+d][mboxes_x[i]+1]=']';
        }
        (*arr)[ty][*x]='@';
        (*arr)[*y][*x]='.';
        *y+=d;
    }
}
int main(void){
    ifstream input(fname);
    int rx;
    int ry;
    char grid[ysize][xsize]{};
    for (int i=0;i<ysize;i++){
        string line;
        input>>line;
        for(int j=0;j<ysize;j++){
            if (line[j]=='@'){
                rx=j*2;
                ry=i;
                grid[i][j*2]='@';
                grid[i][j*2+1]='.';
            }else
            if (line[j]=='O'){
                grid[i][j*2]='[';
                grid[i][j*2+1]=']';
            }else
            {
                grid[i][j*2]=line[j];
                grid[i][j*2+1]=line[j];
            }
        }
    }
    string movements;
    input>>movements;
    cout<<"Original:"<<endl;
    printarr(&grid);
    //cout<<movements<<endl;
    cout<<"New:"<<endl;
    for(int i=0;i<movements.length();i++){
        char m=movements[i];
        if (m=='<'){
            movehor(&grid,&rx,&ry,-1);
        }
        if (m=='>'){
            movehor(&grid,&rx,&ry,1);
        }
        if (m=='^'){
            movert(&grid,&rx,&ry,-1);
        }
        if (m=='v'){
            movert(&grid,&rx,&ry,1);
        }
    }
    printarr(&grid);
    int total=0;
    for (int i=0;i<ysize;i++){
        for(int j=0;j<xsize;j++){
            if (grid[i][j]=='['){
                total+=j+i*100;
            }
        }
    }
    cout<<"GPS:"<<endl;
    cout<<total<<endl;
}
