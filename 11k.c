#include "a.h"
I ml=1,nm=0,i,j,k;
S M{L a,i[1024],m,l,r;I n,t,f;B o;}ms[100],p1[100],p2[100];

I cm(const void*a,const void*b){X ((S M*)b)->a-((S M*)a)->a;}
V rd(S M*ms,I dv){ LP(i,nm,S M*m=ms+i;m->a+=m->n;
            LP(j,m->n,L e=m->i[j],l=m->l==-1?e:m->l,r=m->r==-1?e:m->r;
                SW(m->o,CS('+',e=l+r)CS('-',e=l-r)CS('*',e=l*r)CS('/',e=l/r))
                e/=dv;e%=ml;S M*q=ms+(e%m->m?m->f:m->t);q->i[q->n++]=e;)
            m->n=0) }
I main(V){
    B b[1024]; S M c={0};
    W(fgets(b,SZ(b),stdin),
        SW(b[8], CS(':', memset(&c,0,SZ(c));SS(b+7,"%d",&nm))
            CS('n',B*p=b+18;W(p,SS(p,"%d",&c.i[c.n++]);p=STC(p+1,',');I(p,p++)))
            CS('i',B*p=b+19;I(*p=='o',c.l=-1,p+=4)E(SS(p,"%lld", &c.l);p=STC(p+1,' ')+1);c.o=*p;I(p[2]=='o',c.r=-1)E(SS(p+2,"%lld",&c.r)))
            CS('d',SS(b+21,"%lld",&c.m);ml*=c.m)
            CS('r',SS(b+29,"%d",&c.t))CS('a',SS(b+30,"%d",&c.f);ms[nm]=c)))
    ++nm; memcpy(p1,ms,SZ(ms));memcpy(p2,ms,SZ(ms));
    LP(k,20,rd(p1,3)); qsort(p1,nm,SZ(S M),cm); printf("%lld ", p1[0].a*p1[1].a);
    LP(k,10000,rd(p2,1)); qsort(p2,nm,SZ(S M),cm); printf("%lld", p2[0].a*p2[1].a);
    X 0; }

