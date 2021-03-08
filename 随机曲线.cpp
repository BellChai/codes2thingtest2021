/*
*
* via cyh
* 随机生成一条曲线
* 默认设置：
* 曲线长度：100个*号 
* 图尺寸：160 x 100
* 倾向顺时针旋转 
*
* ---- 完善中 ---- 
*
*/

#include<cstdio>
#include<ctime>
#include<cstdlib>
using namespace std;

const int WID=160;
const int HEI=100;

const int DIR[]={0,1,2,3,4,5,6,7};
const int P[]={300,70,5,1,1,1,1,1};
const int GP[]={0,0,0,0,1,1,1,2,2,3,5,6,6,7,7,7};
const int M=8, SP=16;

const int BASE_A=5;
const int A[]={-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6};
const int P_A[]={1};

char mp[HEI+10][WID+10];

int rand_based_on_P(int d){
	int sum=0;
	for(int i=0; i<M; ++i){
		sum+=P[i];
	}
	int rd=rand()%sum;
	for(int i=0; i<M; ++i){
		rd-=P[i];
		if(rd<=0) return (d+i)%M;
	}
	return 0;
}

int rand_based_on_A(int a, int d){
	bool dir=a>=0;
	int rd=rand();
	int res;
	if(a==0){
		rd%=3;
		res=rd-1;
	}else if(a<BASE_A){
		rd%=5;
		res=rd<a?1:0;
	}else if(a==BASE_A){
		rd%=3;
		res=rd;
	}else{
		rd%=5;
		res=rd+BASE_A<a?2:1;
	}
	return d+dir*res;
}

void get_next(int r, int c, int d, int &tmp_r, int &tmp_c, int &tmp_d, int a=0){
	tmp_d=rand_based_on_P(d);
//	tmp_d=rand_based_on_A(a,d);
	switch(tmp_d){
		case 0: tmp_r=r+1; tmp_c=c; break;
		case 1: tmp_r=r+1; tmp_c=c-1; break;
		case 2: tmp_r=r; tmp_c=c-1; break;
		case 3: tmp_r=r-1; tmp_c=c-1; break;
		case 4: tmp_r=r-1; tmp_c=c; break;
		case 5: tmp_r=r-1; tmp_c=c+1; break;
		case 6: tmp_r=r; tmp_c=c+1; break;
		case 7: tmp_r=r+1; tmp_c=c+1; break;
	}
}

int main(){
	srand((unsigned)time(NULL));
	
	int len=200;
	int init_r=20, init_c=WID/2, init_d=0;
	int r=init_r, c=init_c, d=init_d, a=0;
	while(--len){
		int tmp_r, tmp_c, tmp_d;
		do{
			get_next(r,c,d,tmp_r,tmp_c,tmp_d);
		}while(tmp_r<=0 || tmp_r>=HEI || tmp_c<=0 || tmp_c>=WID);
		if(tmp_c>c) a++;
		else if(tmp_c<c) a--;
		r=tmp_r; c=tmp_c; d=tmp_d;
		mp[r][c]='.';
	}
	
	for(int i=1; i<=HEI; ++i){
		for(int j=1; j<=WID; ++j){
			putchar(mp[i][j]);
		}
		puts("");
	}
}
