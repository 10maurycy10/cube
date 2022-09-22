#include <stdio.h>
#include <math.h>
#include <time.h>
#define max(x,y) (x>y?x:y)
#define abs(a) (a<0?-a:a)
#define W 80
#define H 40
#define L 12
char a[W][H];float S[L][2][3]={{{1.0,1.0,1.0},{1.0,1.0,-1.0}},{{1.0,-1.0,1.0},{
1.0,-1.0,-1.0}},{{-1.0,1.0,1.0},{-1.0,1.0,-1.0}},{{-1.0,-1.0,1.0},{-1.0,-1.0,
-1.0}},{{1.0,1.0,1.0},{1.0,-1.0,1.0}},{{1.0,-1.0,1.0},{-1.0,-1.0,1.0}},{{-1.0,
1.0,1.0},{1.0,1.0,1.0}},{{-1.0,-1.0,1.0},{-1.0,1.0,1.0}},{{1.0,1.0,-1.0},{1.0,-
1.0,-1.0}},{{1.0,-1.0,-1.0},{-1.0,-1.0,-1.0}},{{-1.0,1.0,-1.0},{1.0,1.0,-1.0}},
{{-1.0, -1.0, -1.0},{-1.0, 1.0, -1.0}},};float t[2][2];void c(){for(int x=0;x<W
;x++)for(int y=0;y<H;y++)a[x][y]=' ';}void p(){printf("\e[1;1H\e[2J");char l[W+
1];for(int y=0;y<H;y++){for(int x=0;x<W;x++)l[x]=a[x][y];l[W] = 0;printf("%s\n"
,l);}}void d2(int x1,int y1,int x2,int y2){int dx=(x2-x1);int dy=(y2-y1);int s=
max(abs(dx),abs(dy));float dxs=(float)dx/(float)s;float dys=(float)dy/(float)s;
for (int i=0;i<s;i++){float xo=dxs*(float)i;float yo=dys*(float)i;int x=(int)xo
+x1;int y=(int)yo+y1;if(x<W&&x>=0)if(y<H&&y>=0)a[x][y]='#';}}void tp(float a[2]
,float b[2]){b[0]=0.0;b[1]=0.0;for (int i=0;i<2;i++)for(int e=0;e<2;e++)b[i]+=a
[e]*t[e][i];}void sr(float a){t[0][0]=cos(a);t[0][1]=-sin(a);t[1][0]=sin(a);t[1
][1]=cos(a);}void pp(float a[3],float b[2]){float e[3];float c[2]={a[0],a[2]};
float d[2];tp(c,d);e[0]=d[0];e[1]=a[1];e[2]=d[1];e[2]+=3.0;b[1]=e[1]/e[2];b[0]=
e[0]/e[2];}void dl(float a[3],float b[3]){float c[2];float d[2];pp(b,d);pp(a,c)
;d2((int)((c[0])*40.0+40.0),(int)((c[1])*20.0+20.0),(int)((d[0])*40.0+40.0),(
int)((d[1])*20.0+20.0));}int m(long a){struct timespec o;struct timespec r={(
int)(a/1000),(a%1000)*1000000};return nanosleep(&r,&o);}int main(void){int a=0;
setvbuf(stdout,NULL,_IOFBF,4096);while(1){c();float b=(float)a/50;sr(b);for(int
i=0;i<L;i++)dl(S[i][0],S[i][1]);p();printf("%d Lines. Frame %d\n",L,a);fflush(
stdout);m(15);a++;}}

