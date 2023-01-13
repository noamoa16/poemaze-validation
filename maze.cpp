#include<bits/stdc++.h>
#include<unistd.h>
#include "MT.h"
#include "split.h"
using namespace std;
typedef int8_t shorter;
typedef int64_t longer;

#define OCTO 0
#define DIAR 1
#define WALL 2

#define SIZE 8
#define ENDUR 3
#define TIME 100000000

#define ADD_TO_RESULT

shorter done[SIZE+1][SIZE+1];

class Board{
    public:
    shorter cond[SIZE+2][SIZE+2];
    
    Board(){
        for(shorter i=0;i<=SIZE+1;i++){
            for(shorter j=0;j<=SIZE+1;j++){
                if(i==0||i==SIZE+1||j==0||j==SIZE+1) cond[i][j]=WALL;
                else if((i==1&&j==1)||(i==SIZE&&j==SIZE)) cond[i][j]=OCTO;
                else{
                    cond[i][j]=genrand_int32()%3;
                }
            }
        }
    }
    
    Board(const Board &b){
        for(shorter i=0;i<=SIZE+1;i++){
            for(shorter j=0;j<=SIZE+1;j++){
                cond[i][j]=b.cond[i][j];
            }
        }
    }
    
    /*void print(){
        cout << endl;
        for(shorter i=0;i<=SIZE+1;i++){
            for(shorter j=0;j<=SIZE+1;j++){
                if(cond[i][j]==OCTO) cout << " O";
                else if(cond[i][j]==DIAR) cout << " D";
                else if(cond[i][j]==WALL) cout << " W";
                else cout << " #";
            }
            cout << endl;
        }
        cout << endl;
    }*/
    
    /*void eliminate(const int x,const int y){
        bool right=(cond[x+1][y]==WALL);
        bool left=(cond[x-1][y]==WALL);
        bool down=(cond[x][y+1]==WALL);
        bool up=(cond[x][y-1]==WALL);
        
        if(right+left+down+up>=3){
            cond[x][y]=WALL;
            
            if(!right) eliminate(x+1,y);
            if(!left) eliminate(x-1,y);
            if(!down) eliminate(x,y+1);
            if(!up) eliminate(x,y-1);
        }
    }
    
    void eliminate(){
        for(shorter i=1;i<=SIZE;i++){
            for(shorter j=1;j<=SIZE;j++){
                if((i==1&&j==1)||(i==SIZE&&j==SIZE)) continue;
                if(cond[i][j]!=WALL){
                    eliminate(i,j);
                }
            }
        }
    }*/
                
    
    bool solve(const shorter x,const shorter y,shorter diar){
        //下痢カウント
        if(cond[x][y]==DIAR&&++diar==ENDUR){
            return false;
        }
        
        //メモ化
        if(diar>=done[x][y]){
            return false;
        }
        else done[x][y]=diar;
        
        //ゴールに到達
        if(x==SIZE&&y==SIZE) return true;
        
        Board newb=Board(*this);
        newb.cond[x][y]=WALL;
        
        return(
            (newb.cond[x+1][y]!=WALL&&newb.solve(x+1,y,diar)) ||
            (newb.cond[x][y+1]!=WALL&&newb.solve(x,y+1,diar)) ||
            (newb.cond[x-1][y]!=WALL&&newb.solve(x-1,y,diar)) ||
            (newb.cond[x][y-1]!=WALL&&newb.solve(x,y-1,diar))
        );
    }
};

int main(){
    init_genrand(time(NULL));
    int cnt=0;
    clock_t start_t=clock();
    {
        for(int i=0;i<TIME;i++){
            Board mainb=Board();
            
            //doneの初期化
            for(shorter j=1;j<=SIZE;j++){
                for(shorter k=1;k<=SIZE;k++){
                    done[j][k]=ENDUR;
                }
            }
            
            //mainb.eliminate();これをすると遅くなる
            if(
            mainb.cond[SIZE-1][SIZE]==WALL&&
            mainb.cond[SIZE][SIZE-1]==WALL
            ) continue;
            if(
            mainb.cond[SIZE-2][SIZE]==WALL&&
            mainb.cond[SIZE-1][SIZE-1]==WALL&&
            mainb.cond[SIZE][SIZE-2]==WALL
            ) continue;
            cnt+=mainb.solve(1,1,0);
        }
    }
    clock_t end_t=clock();
    cout << cnt << "/" << TIME << endl;
    cout << (double)cnt/TIME*100 << "%" << endl;
    cout << "in " << (double)(end_t-start_t)/CLOCKS_PER_SEC << "sec." << endl;
    
    #ifdef ADD_TO_RESULT
    longer SumOfClear=cnt,SumOfRun=TIME;
    ifstream in("result.txt");
    if(in){
        string buf;
        getline(in,buf);
        in.close();
    
        if(buf=="") SumOfClear=SumOfRun=0;
        else{
            vector<string> strs=split(buf,'/');
            SumOfClear+=stoi(strs[0]);
            SumOfRun+=stoi(strs[1]);
        }
    }
    cout << endl;
    cout << SumOfClear << "/" << SumOfRun << endl;
    double ratio=(double)SumOfClear/SumOfRun*100;
    cout << ratio << "%" << endl;
    
    ofstream out("result.txt");
    out << SumOfClear << "/" << SumOfRun << endl;
    out << ratio;
    out.close();
    #endif
}