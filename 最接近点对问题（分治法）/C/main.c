#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 100

int point_number;	//ͳ�ƶ����ĸ��� 

struct Point
{
	double x;
	double y;
}point[N];

//����x�������� 
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

//��������m��n֮����һ����ĵ����С���� 
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

	//���ļ���������㼯
	FILE *fp=fopen("����㼯.txt","r");
	if(!fp){
		printf("can't open\n");
	}
	while(!feof(fp)){
		fscanf(fp,"%lf%lf",&point[i].x,&point[i].y);
		i++;
	}
	point_number=i-1;
	fclose(fp);
	
	/****�Զ������������x���������****/
	sort_x();
	/****��S1������С����****/
	d1=min_p(0,point_number/2);
	/****��S2������С����****/
	d2=min_p(point_number/2,point_number);
	/****ȷ��S1��S2�����������С����****/
	if(d1<d2){
		d=d1;
	}
	else{
		d=d2;
	}
	
	/****ȷ��l���l-d�������ʼ����****/
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
	
	//ȷ��l�ұ�l+d�������ʼ���� 
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
	
	printf("��С����Ϊ��%f\n",d);
	system("pause"); 
}
