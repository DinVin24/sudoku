#include <iostream>
#include <fstream>
using namespace std;
ifstream f ("nrcurat.in");
int n,x,y;
struct {int val;bool fix;}s[101][101];
void init(){if(!s[x][y].fix)s[x][y].val=0;}
int am_succesor(){
    if(s[x][y].val<9 && !s[x][y].fix){
        s[x][y].val++;
        return 1;
    }
    if(x==1 && y==1){y++;return 1;}
    return 0;
}
int e_valid(){
    int i,j,aux1,aux2;
    if(s[x][y].val==0)return 0;
    for(i=1;i<y;i++)if(s[x][y].val==s[x][i].val && s[x][y].val!=0)return 0;
    for(i=1;i<=9;i++)if(s[x][y].val==s[x][i].val && s[x][i].fix)return 0;
    if(x%3==2)i=x-1;
    else if (x%3==0)i=x-2;
    else i = x;
    if(y%3==2)j=y-1;
    else if (y%3==0)j=y-2;
    else j=y;
    aux1=i+2;
    aux2=j+2;
    for(i=aux1-2;i<=aux1;i++)for(j=aux2-2;j<=aux2;j++)//linii
        if(s[i][j].val==s[x][y].val){
            if(i<x)return 0;
            if(i!=x && s[i][j].fix)return 0;
        }
    i=x;j=y;
    while(i>3)i-=3;
    while(j>3)j-=3;
    aux1=i+6; aux2=j+6;
    for(i=aux1-6;i<=aux1;i+=3)//coloane
        for(j=aux2-6;j<=aux2;j+=3)
            if(s[i][j].val==s[x][y].val){
            if(i<x)return 0;
            if(i!=x && s[i][j].fix)return 0;
        }
    return 1;
}
int solutie(){
    if(x==9 && y==9)return 1;
    else return 0;
}
void tipar(){
     int i,j,aux1=1,aux2;
     while(aux1<=7){
         aux2=1;
         while(aux2<=7){
             for(i=aux1;i<=aux1+2;i++){
                for(j=aux2;j<=aux2+2;j++)
                    cout<<s[i][j].val<<' ';
             }
             aux2+=3;
             cout<<'\n';
         }
         aux1+=3;
     }
}
void citire(){
    int i,j,aux1=1,aux2;
     while(aux1<=7){
         aux2=1;
         while(aux2<=7){
             for(i=aux1;i<=aux1+2;i++){
                for(j=aux2;j<=aux2+2;j++){
                    f>>s[i][j].val;
                    if(s[i][j].val!=0)s[i][j].fix=true;
                    else s[i][j].fix=false;
                }
             }
             aux2+=3;
         }
         aux1+=3;
     }
}
void bck(){
    int as;
    x=y=1;
    init();
    while (x>0 && y>0 && x<=9 && y<=9){
        do{}while((as=am_succesor()) && !e_valid());
        if(as){
            if(solutie())break;
            else {
                do{
                    //cout<<"nu-i sol1";
                    if(y==9){
                        x++;
                        y=1;
                    }
                    else {y++;//cout<<"nu-i sol2";}
                    }
                }while(s[x][y].fix);
                init();
            }
            //cout<<"as";
        }
        else
            do{
                if(y==1){
                    //cout<<"n-am succesor1";
                    y=9;
                    x--;
                }
                else {y--;//cout<<"n-am succesor2";
                }
            }while(s[x][y].fix);
    }
}
int main(){
    citire();
    bck();
    tipar();
    return 0;
}
