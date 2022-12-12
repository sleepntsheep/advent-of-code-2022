#include "a.h"
#define N 500
#define CL(a,b) ({I(a<b,a++)EI(a>b,a--);});
S P{int y,x;} k[10];I t,i,j,dx[4]={1,-1},v[10][N*2][N*2],c[10],dy[]={0,0,1,-1};B d;
V fl(I hi, I ti) {S P *h=k+hi, *t=k+ti;
    W(abs(h->x-t->x)>1||abs(h->y-t->y)>1, CL(t->y,h->y)CL(t->x,h->x)
        I(!v[ti][t->y][t->x],c[ti]++,v[ti][t->y][t->x]++))}
I main(V) {
    i(10,v[i][k[i].x=N][k[i].y=N]=c[i]=1)
    W(Sf("%c %d", &d, &t)+1, 
        i(4,I("RLUD"[i]==d,k[0].x+=t*dx[i],k[0].y+=t*dy[i]))
        i(9,fl(i,i+1))
    )
    Pf("%d %d", c[1], c[9]);
    X 0;}
