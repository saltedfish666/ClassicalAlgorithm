#include <stdio.h>
#include <stdlib.h>

int a[10]={0};    //��������
int b[100]={0};    //���������

//ͳ������
void count(num){    //numΪ�����������
	int i,c;
	for(i=0;i<num;i++){
		c=b[i];
		a[c]++;
	}
}

int main() {
	int i=0,n,temp,num=0;

	FILE *fp=fopen("�����.txt","r");
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
	printf("����Ϊ%d\n",n);
	printf("����Ϊ%d\n",temp);
	system("pause");
}
