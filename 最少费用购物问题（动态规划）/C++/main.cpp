#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>

using namespace std;

struct youhui{
    int price;    ///J[i].price ���� �Ż����i �ļ۸�
    int k[100];  ///J[i].k[j] ���� ���Ż����i����Ϊj����Ʒ������
}J[100];     ///J[i] ��  ��i���Żݵ����

int cost[6][6][6][6][6]; ///cost[i][j][k][l][m] ���� ��Ҫ�����һ����Ʒ����Ϊi���ڶ���Ϊj.....ʱ��С����
int P[1000];  ///P[i] ���� ���Ϊi����Ʒ�ĵ���
int num[1000];  ///num[i] ���� ��������Ʒ�ı��
int K[1000];/// K[i] ������Ϊi����Ʒ��Ҫ�������
int B,S;   ///B�������B����Ʒ��S���� ��S���Ż����

void nn(string s){
    cout<<s<<endl;
}

void init(){
    for(int i = 0; i < 6; ++i)
        for(int j = 0; j < 6; ++j)
            for(int k2 = 0; k2 < 6; ++k2)
                for(int l = 0 ; l < 6; ++l)
                    for(int m = 0; m < 6; ++m)
                        cost[i][j][k2][l][m] = 0;
    for(int i = 0; i < 100; ++i){
        memset(J[i].k,0,sizeof(int));
    }
}

void print2(){
    for(int i = 1; i <= B; ++i) printf("%d: %d---%d \n",num[i],K[num[i]],P[num[i]]);
    nn("-----------------------");
    for(int i = 1; i <= S ;++i){
        printf("price: %d\n",J[i].price);
        for(int j = 0; j < 100; ++j){
            if(J[i].k[j] != 0) printf("%d : %d\n",j,J[i].k[j]);
        }
        printf("\n");
    }
 
}

int main()
{
    int tmp_c;
    ///*************��ʼ��***********/////
    memset(P,0,sizeof(int));
    memset(K,0,sizeof(int));
    memset(num,0,sizeof(int));
    init();
    ///************��������***************////
    FILE *fp;
    fp = fopen("1.txt","r");
    if(fp == NULL) printf("wuwu\n");
    fscanf(fp,"%d",&B);
    for(int i = 1; i <= B;++i){
        int tmp;
        fscanf(fp,"%d",&num[i]);
        tmp = num[i];
        fscanf(fp,"%d%d",&K[tmp],&P[tmp]);
 
    }
    fscanf(fp,"%d",&S);
    for(int i = 1; i <= S; ++i){
        int count;
        fscanf(fp,"%d",&count);
        for(int j = 1; j <= count; ++j){
            fscanf(fp,"%d",&tmp_c);
            fscanf(fp,"%d",&J[i].k[tmp_c]);
        }
        fscanf(fp,"%d",&J[i].price);
    }
    ///********��Ҫ���㲿��*****************************///
    cost[0][0][0][0][0] = 0;
    for(int i = 0; i <= K[ num[1] ]; ++i){
        for(int j = 0; j <= K[ num[2] ]; ++j){
            for(int k1 = 0; k1 <= K[ num[3] ]; ++k1){
                for(int l = 0; l <= K[ num[4] ]; ++l){
                    for(int m = 0; m <= K[ num[5] ]; ++m){
                        int mmin = i*P[num[1]] + j*P[num[2]] + k1*P[num[3]]+ l*P[num[4]] + m*P[num[5]];  ///�����Ļ���
                        for(int n = 1; n <= S;n++){  ///�����ײ͵Ļ���
                            if(i < J[n].k[num[1]] ||
                               j < J[n].k[num[2]] ||
                               k1 < J[n].k[num[3]] ||
                               l < J[n].k[num[4]] ||
                               m < J[n].k[num[5]] ) continue;
                            int t = cost[i-J[n].k[num[1]]][j-J[n].k[num[2]]][k1-J[n].k[num[3]]][l-J[n].k[num[4]]][m-J[n].k[num[5]]] + J[n].price;
                            if(t < mmin) mmin = t;
                        }
                        cost[i][j][k1][l][m] = mmin;
                    }
                }
            }
        }
    }
    printf("%d\n",cost[K[num[1]]][K[num[2]]][K[num[3]]][K[num[4]]][K[num[5]]]);
    fclose(fp);
    system("pause\n");
    return 0;
}
