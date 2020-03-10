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
            x[t]=i;//t皇后放在第i列 
            if(Place(t)&&Backtrack(t+1))
            return true;
        }
    } 
    return false;
} 
bool Queen::QueenLV(int stopVegas){
    //随机放置n个皇后的拉斯维加斯算法
    
    int k=1;//随机数产生器
    int count=1;
    //1<=stopVagas=<n表示允许随机放置的皇后数
    while((k<=stopVegas)&&(count>0)){
        count=0;
        for(int i=1;i<=n;i++){
            x[k]=i;
            if(Place(k))
            	y[count++]=i;
        }
        if(count>0) //如果能放置，则在这么多个能放置第k个皇后的位置中选择一个位置 
        	x[k++]=y[rand()%count];
    } 
    return(count>0);//count>0表示放置成功 
} 
bool nQueen(int n){
    //与回溯法相结合的接n后问题的拉斯维加斯算法
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
    int stop=5;    //最后5个采取回溯算法，这里 
    if(n>15)
      stop=n-15;    //最后15个采取回溯算法 
    bool found=false;
    while(!X.QueenLV(stop));//直到能放置
    //算法的回溯搜索部分
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
	cout << "运行时间: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0; 
}
