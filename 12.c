#include "a.h"
#define N 1000
I dp[N][N],i,m,j,k,n,sx,sy,ex,ey=-1,dx[]={0,0,-1,1},dy[4]={1,-1};B b[N][N];I h=1,t;
TD S{I y,x;}P;P q[N*N];
V BFS(V) {
    W(h-t,P p=q[t++]; LP(i,4,P np={p.y+dy[i],p.x+dx[i]};
            I(!(np.y<0||np.y>=n||np.x<0||np.x>=m||b[np.y][np.x]-b[p.y][p.x]>1||dp[np.y][np.x]<=dp[p.y][p.x]+1),dp[np.y][np.x]=dp[p.y][p.x]+1,q[h++]=np)))
}
I main(V){
    W(fgets(b[n],SZ *b,stdin),B(b[n][0]==10)n++)
    m=Sn(b[0]);
    LP(i,n,LP(j,m,I(b[i][j]=='S',sx=j,sy=i)I(b[i][j]=='E',ex=j,ey=i)))
    Ms(dp,77,SZ dp);b[sy][sx]='a';b[ey][ex]='z';
    q[0]=(P){sy,sx};dp[sy][sx]=0;BFS();
    Pf("%d ", dp[ey][ex]); h=0,t=0; Ms(dp,77,SZ dp);
    LP(i,n,LP(j,m,I(b[i][j]=='a',q[h++]=(P){i,j},dp[i][j]=0)))BFS();
    Pf("%d", dp[ey][ex]);X 0;}

