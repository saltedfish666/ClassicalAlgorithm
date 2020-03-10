#include <stdio.h>
#include <stdlib.h>

int a[10]={0};    //计算数量
int b[100]={0};    //缓存随机数

//统计数量
void count(num){    //num为随机数的数量
	int i,c;
	for(i=0;i<num;i++){
		c=b[i];
		a[c]++;
	}
}

int main() {
	int i=0,n,temp,num=0;

	FILE *fp=fopen("随机数.txt","r");
	if(!fp){
		printf("can't open\n");
	}
	while(!feof(fp)){
		fscanf(fp,"%d",b+num);
		num++;
	}
	fclose(fp);

	count(num);
	temp=a[0];
	n=0;
	for(i=1;i<10;i++){
		if(a[i]>temp){
			temp=a[i];
			n=i;
		}
	}
	printf("众数为%d\n",n);
	printf("重数为%d\n",temp);
	system("pause");
}
