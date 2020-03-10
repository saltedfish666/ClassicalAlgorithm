#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 100

int point_number;	//统计读入点的个数 

struct Point
{
	double x;
	double y;
}point[N];

//根据x坐标排序 
void sort_x(){
	int i,j;
	struct Point temp;
	for(i=0;i<point_number;i++){
		for(j=i+1;j<point_number;j++){
			if(point[i].x>point[j].x){
				temp=point[i];
				point[i]=point[j];
				point[j]=temp;
			}
		} 
	}
}

//求坐标在m到n之间这一区域的点的最小距离 
double min_p(int m,int n){
	int i,j;
	double d,t1,t2;
	double dis=10000;
	for(i=m;i<=n;i++){
		for(j=i+1;j<=n;j++){
			d=sqrt( pow(point[i].x-point[j].x,2) + pow(point[i].y-point[j].y,2) );
			if(dis>d){
				dis=d;
			}
		}
	}
	return dis;
} 

int main() {
	int i=0,j;
	double d1,d2,d3,d;
	int m,n;

	//从文件读入坐标点集
	FILE *fp=fopen("坐标点集.txt","r");
	if(!fp){
		printf("can't open\n");
	}
	while(!feof(fp)){
		fscanf(fp,"%lf%lf",&point[i].x,&point[i].y);
		i++;
	}
	point_number=i-1;
	fclose(fp);
	
	/****对读入的坐标点根据x轴进行排序****/
	sort_x();
	/****求S1区域最小距离****/
	d1=min_p(0,point_number/2);
	/****求S2区域最小距离****/
	d2=min_p(point_number/2,point_number);
	/****确定S1和S2两个区域的最小距离****/
	if(d1<d2){
		d=d1;
	}
	else{
		d=d2;
	}
	
	/****确定l左边l-d区域的起始坐标****/
	i=point_number/2-1;
	while(1){
		if(point[i].x>(point[point_number/2].x-d)){
			i--;
		}
		else{
			m=i+1;
			break;
		}
	}  
	
	//确定l右边l+d区域的起始坐标 
	i=(point_number/2);
	while(1){
		if(point[i].x<(point[point_number/2].x+d)){
			i++;
		}
		else{
			n=i-1;
			break;
		}
	} 
	
	d3=min_p(m,n);
	
	if(d>d3){
		d=d3;
	}
	
	printf("最小距离为：%f\n",d);
	system("pause"); 
}
