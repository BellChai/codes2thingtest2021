/*
随机生成的螺旋线，它的参数有：
画布高度 HEI
画布宽度 WID
1/4圆个数 LEN
初始半径 INITR
半径缩小比例 RAT
特点：
逆时针旋转，由于旋转方向由概率决定，可能出现锐角
改进方向：
增加顺时针旋转，防止锐角出现
*/

#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;

//参数设定  
const int WID=160;
const int HEI=100;
const double RAT=0.8;
const int LEN=40;
const int INITR=40;

//常数 
const double PI=3.1415926;

typedef pair<int,int> PII;

vector<PII> VII;
char mp[HEI+10][WID+10];

//绘画出每一个1/4圆，并旋转和位移 
void paint(int r, int c, int pos, int R){	
	VII.clear();
	double xx, yy;
	for(int i=0; i<=90; ++i){
		xx=cos(i*1.0/360*2*PI)*R;
		yy=sin(i*1.0/360*2*PI)*R;
		VII.push_back(PII(round(xx),round(yy)));
	}
	switch(pos){
		case 2:
			for(int i=0; i<=90; ++i){
				VII[i].first*=-1;
			}
			break;
		case 3:
			for(int i=0; i<=90; ++i){
				VII[i].first*=-1;
				VII[i].second*=-1;
			}
			break;
		case 4:
			for(int i=0; i<=90; ++i){
				VII[i].second*=-1;
			}
			break;
	}
	for(int i=0; i<=90; ++i){
		int tmpr=VII[i].first+r, tmpc=VII[i].second+c;
		if(tmpr>0 && tmpr<=HEI && tmpc>0 && tmpc<=WID){
			mp[tmpr][tmpc]='0'+pos;
		}
	}
}

// 由此个1/4圆，依据概率获得下一个1/4圆 
void get_next(int r, int c, int pos, int R, int &tmp_r, int &tmp_c, int &tmp_pos, int &tmp_R){
	tmp_R=R*RAT; if(tmp_R<3) tmp_R=INITR;
	tmp_pos=pos+1>4?1:pos+1;
	// 此处10%的概率tmp_pos随机生成 
	if(rand()%100<10) tmp_pos=rand()%4+1;
	
	int ro=r, co=c;
	switch(tmp_pos){
		case 1: ro-=tmp_R; tmp_c=co; tmp_r=ro; tmp_c+=tmp_R; break;
		case 2: co-=tmp_R; tmp_c=co; tmp_r=ro; tmp_r-=tmp_R; break;
		case 3: ro+=tmp_R; tmp_c=co; tmp_r=ro; tmp_c-=tmp_R; break;
		case 4: co+=tmp_R; tmp_c=co; tmp_r=ro; tmp_r+=tmp_R; break;
	}
	paint(ro,co,tmp_pos,tmp_R);
}

int main(){
	srand((unsigned)time(NULL));
	
	int len=LEN;
	
//初始值设定 
	int init_r=HEI/2, init_c=WID/2, init_pos=rand()%4+1, init_R=INITR;
	int r=init_r, c=init_c, pos=init_pos, R=init_R;

//生成len个1/4圆 
	while(--len){
		int tmp_r, tmp_c, tmp_pos, tmp_R;
		get_next(r,c,pos,R,tmp_r,tmp_c,tmp_pos,tmp_R);
		r=tmp_r; c=tmp_c; pos=tmp_pos; R=tmp_R;
	}
	
//输出画布 
	for(int i=1; i<=HEI; ++i){
		for(int j=1; j<=WID; ++j){
			putchar(mp[i][j]);
		}
		puts("");
	}
	system("pause");
}
