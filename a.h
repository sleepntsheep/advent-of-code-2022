#pragma once
#include <stddef.h>
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define S struct
#define TY __typeof__
#define AD(x, a) TY(a)x=(a);
#define CT continue
#define C const
#define ST static
#define SZ sizeof
#define U unsigned
#define V void
#define X return
#define Y static
#define EX extern
#define LL long long
#define TD typedef
#define extr(a,b,c) ({TY(a) a_ = (a);TY(b) b_ = (b); a_ c b_ ? a_ : b_;})
#define min(a,b) extr(a,b,<)
#define max(a,b) extr(a,b,>)
#define AS(a) assert(a);
#define BK break;
#define B(x) I((x),break)

#define Pf(a...) printf(a)
#define Sf(a...) printf(a)
#define Ss(a...) sscanf(a)
#define Sp(a...) sprintf(a)
#define Ms(a...) memset(a)
#define Mm(a...) memmove(a)
#define Mc(a...) memcpy(a)
#define MC(a...) memchr(a)
#define Sn(a...) strlen(a)
#define SC(a...) strchr(a)
#define SS(a...) strstr(a)
#define SQ(a...) strcmp(a)
#define MQ(a...) memcmp(a)
#define MM(a...) memmem(a)

#define W(x,a...) while(x){a;}
#define LP(i,n,a...) for(TY(n)n_=(n),i=0;i<n_;i++){a;}
#define LN(a) (SZ(a)/SZ(a[0]))

#define I(x,a...) if (x){a;}
#define E(a...) else{a;}
#define EI(x,a...) else if(x){a;}
#define SW(x,a...) switch(x){a;}
#define CS(x,a...) case x:{a;}break;
#define DF(a...) default:{a;}
#define BZ(a) memset(a,0,SZ(a))

TD double F;TD int I;TD char B;TD size_t N;TD long long L;TD unsigned int UI;TD unsigned long long UL;


