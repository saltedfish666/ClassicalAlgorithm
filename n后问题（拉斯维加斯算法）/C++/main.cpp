#include<iostream>
#include<stdlib.h>
#include<ctime>
using namespace std;
clock_t startTime,endTime;
class Queen{
   friend bool nQueen(int);
private:
   bool Place(int k);
   bool Backtrack(int t);
   bool QueenLV(int stopVegas);
   int n,*x,*y;
};
bool Queen::Place(int k){
    for(int j=1;j<k;j++)
        if((abs(k-j)==abs(x[j]-x[k]))||(x[j]==x[k]))
        return false;
    return true;
}
bool Queen::Backtrack(int t){
    if(t>n){
        for(int i=1;i<=n;i++)
        y[i]=x[i];
        return true;
    }
    else{
        for(int i=1;i<=n;i++){
            x[t]=i;//t�ʺ���ڵ�i�� 
            if(Place(t)&&Backtrack(t+1))
            return true;
        }
    } 
    return false;
} 
bool Queen::QueenLV(int stopVegas){
    //�������n���ʺ����˹ά��˹�㷨
    
    int k=1;//�����������
    int count=1;
    //1<=stopVagas=<n��ʾ����������õĻʺ���
    while((k<=stopVegas)&&(count>0)){
        count=0;
        for(int i=1;i<=n;i++){
            x[k]=i;
            if(Place(k))
            	y[count++]=i;
        }
        if(count>0) //����ܷ��ã�������ô����ܷ��õ�k���ʺ��λ����ѡ��һ��λ�� 
        	x[k++]=y[rand()%count];
    } 
    return(count>0);//count>0��ʾ���óɹ� 
} 
bool nQueen(int n){
    //����ݷ����ϵĽ�n���������˹ά��˹�㷨
    Queen X;
    X.n=n;
    int *p=new int[n+1];
    int *q=new int[n+1];
    for(int i=0;i<=n;i++){
        p[i]=0;
        q[i]=0;
    } 
    X.y=p;
    X.x=q;
    int stop=5;    //���5����ȡ�����㷨������ 
    if(n>15)
      stop=n-15;    //���15����ȡ�����㷨 
    bool found=false;
    while(!X.QueenLV(stop));//ֱ���ܷ���
    //�㷨�Ļ�����������
    if(X.Backtrack(stop+1)){
        for(int i=1;i<=n;i++)
        cout<<p[i]<<" ";
        found=true;
    }
    cout<<endl;
    delete []p;
    delete []q;
    return found; 
} 
int main(){
    int n;
    int k;
    k = 1;
    cout<<"n:";cin>>n;
    startTime = clock();
	while(k){
		if(!nQueen(n)){
			
		}
      	else{
      		k=0;
      	}
	}
	endTime = clock();
	cout << "����ʱ��: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0; 
}
