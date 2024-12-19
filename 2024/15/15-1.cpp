#include <iostream>
#include <fstream>
#define gsize 50
#define fname "15-input"
void printarr(char (*arr)[gsize][gsize]){
    for (int i=0;i<gsize;i++){
        for(int j=0;j<gsize;j++){
            std::cout<<(*arr)[i][j];
        }
        std::cout<<std::endl;
    }
}
void move(char (*arr)[gsize][gsize],int *x, int *y,int dx, int dy){
    int bc=0; //Box counter
    int tx=*x+dx;
    int ty=*y+dy;
    while ((*arr)[ty][tx]=='O'){
        tx+=dx;
        ty+=dy;
        bc+=1;
    }
    if ((*arr)[ty][tx]=='.'){
        if (bc>0) {(*arr)[ty][tx]='O';}
        (*arr)[*y][*x]='.';
        (*arr)[*y+dy][*x+dx]='@';
        *x+=dx;
        *y+=dy;
    }
}
int main(void){
    using namespace std;
    ifstream input(fname);
    int rx;
    int ry;
    char grid[gsize][gsize]{};
    char og[gsize][gsize]{};
    for (int i=0;i<gsize;i++){
        string line;
        input>>line;
        for(int j=0;j<gsize;j++){
            grid[i][j]=line[j];
            og[i][j]=line[j];
            if (line[j]=='@'){
                rx=j;
                ry=i;
            }
        }
    }
    string movements;
    input>>movements;
    cout<<"Original:"<<endl;
    printarr(&grid);
    cout<<movements<<endl;
    cout<<"New:"<<endl;
    for(int i=0;i<movements.length();i++){
        char m=movements[i];
        if (m=='<'){
            move(&grid,&rx,&ry,-1,0);
        }
        if (m=='>'){
            move(&grid,&rx,&ry,1,0);
        }
        if (m=='^'){
            move(&grid,&rx,&ry,0,-1);
        }
        if (m=='v'){
            move(&grid,&rx,&ry,0,1);
        }
    }
    printarr(&grid);
    int total=0;
    for (int i=0;i<gsize;i++){
        for(int j=0;j<gsize;j++){
            if (grid[i][j]=='O'){
                total+=j+i*100;
            }
        }
    }
    cout<<"Changed:"<<endl;
    for (int i=0;i<gsize;i++){
        for(int j=0;j<gsize;j++){
            if (grid[i][j]!=og[i][j]){
                cout<<'x';
            }else{
                cout<<'.';
            }
        }
        cout<<endl;
    }
    cout<<"GPS:"<<endl;
    cout<<total<<endl;
}
