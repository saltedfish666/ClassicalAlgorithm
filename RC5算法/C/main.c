/*RC5  C����ʵ�� 
w/r/b=32/12/16 
������RC5 3���㷨��ɣ�����Կ��չ�㷨�������㷨�ͽ����㷨����RC5��C����ʵ��Ҳ�����¼������ֹ��ɡ� 
1�������Ķ��� 
*/ 

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <math.h>     

int w=32;//�ֳ� 32bit 4�ֽ� 
int r=12;//12;//��������12 
int b=16;//����Կ(�ֽ�Ϊ��λ8bit)����  ������16��
int t=26;//2*r+2=12*2+2=26 
int c=4; //����Կ����*8/w = 16*8/32    //4��int��һ��int4���ֽڣ�һ���ֽ�8bit��һ��4*4*8=128bit
int fsize;

typedef unsigned long int FOURBYTEINT;//4�ֽ� 
typedef unsigned short int TWOBYTEINT;//2�ֽ� 
typedef unsigned char BYTE; 

void InitialKey(unsigned char* KeyK,int b); 
void generateChildKey(unsigned char* KeyK,FOURBYTEINT* ChildKeyS); 
void Encipher(FOURBYTEINT* In,FOURBYTEINT* Out,FOURBYTEINT* S); 
void Decipher(FOURBYTEINT* In,FOURBYTEINT* Out,FOURBYTEINT* S); 

#define NoOfData 173000

/**2��ѭ����λ���� 
��������������Կ�����ܣ����ܹ����ж�Ҫ����ѭ����λ����Ҫ���ȶ���ѭ����Ϊ������ 
* ѭ�����ƺ����ƺ��� 
* x : ��ѭ������ 
* y : ��Ҫѭ����λ�� 
*/ 
#define ROTL(x,y) ( ((x)<<(y&(w-1))) | ((x)>>(w-(y&(w-1)))) ) 
#define ROTR(x,y) (((x)>>(y&(w-1))) | ((x)<<(w-(y&(w-1))))) 

/**3����ʼ��Կ�������� 
����һ����ʼ�ĳ���Ϊb�ֽڵ���Կ�� 
  ������ʼ��Կ�ĺ��� 
*/ 
void InitialKey(unsigned char* KeyK,int b){
    int i,j;
	int intiSeed=3;
    for(i=0;i<b;i++){//��ʼ��
        KeyK[i]=0;
    }
    KeyK[0]=intiSeed;
	printf("��ʼ����Կ(16�ֽڹ�128λ)��%.2lx ",KeyK[0]);
    for(j=1;j<b;j++)//���� 
    {
        KeyK[j] = (BYTE)( (int)pow(3,j)%(255-j) );  //pow(x,y)  x^y: 2^3=8
		printf("%.2X ",KeyK[j]);
        //KeyK[j] = (BYTE) ( ((int)(pow(double(3),j))%(255-j))); 
    } 
	printf("\n");
} 

/**4����Կ��չ���� 
���������r�֣�ÿ����Ҫ��������Կ��������Ҫ��Կ��չ�������ݳ�ʼ��Կ����չ��2r+2������Կ�� 
  ��������Կ�ĺ��� 
*/ 
void generateChildKey(unsigned char* KeyK,FOURBYTEINT* ChildKeyS){ 
    //const double e = 2.718281828459; 
    //const double Phia = 1.618033988749; 
    int PW = 0xB7E15163;//0xb7e1; 
    int QW = 0x9E3779B9;//0x9e37;//���� 
    int i; 
	int u =w/8;    //u=4; 
	FOURBYTEINT A,B,X,Y; 
    FOURBYTEINT L[4]; //c=16*8/32=4 
	A=B=X=Y=0; 
    //��ʼ������S 
    ChildKeyS[0]=PW; 
	printf("\n��ʼ����Կ��û������Կ�Ĳ��룩��\n%.8X ", ChildKeyS[0]);
    for (i=1;i<t;i++){   //t=26 
		if(i%13==0)printf("\n");
        ChildKeyS[i]=(ChildKeyS[i-1]+ QW);    //�򵥵���Ӳ�����һ������Կ 
		printf("%.8X ", ChildKeyS[i]);
    }
	printf("\n");

    //��K����ת��ΪL���� 
    for(i=0;i<c;i++){	//��ʼ��L����c=4 
       L[i]=0;
    }
    for (i=b-1;i!=-1; i--){    //ת������Կ���飨16�� ��λΪ8bit��ΪL���飨8����λΪ16bit��������LÿһԪ�س�Ϊ16bit������KÿһԪ�س�Ϊ8bit
        L[i/u] = (L[i/u]<<8)+KeyK[i];
    }
	printf("\n������Կ�任Ϊ4�ֽڵ�λ��\n");
    for (i=0;i<c;i++){    //16��������Ķ� 
        printf("%.8X ",L[i]); 
    } 
    printf("\n\n"); 

    //��������Կ���洢��ChildKeyS�� 
    for(i=0;i<3*t;i++){    //t=26 
        X = ChildKeyS[A] = ROTL(ChildKeyS[A]+X+Y,3);  
        A = (A+1) % t; 
        Y = L[B] = ROTL(L[B]+X+Y,(X+Y));  
        B = (B+1) % c; 
    } 
	printf("���ɵ�����Կ����ʼ����Կ����ͳ�ʼ����ԿҲ���룩��"); 
    for (i=0;i<t;i++){    //16�������
		if(i%13==0)printf("\n");
            printf("%.8X ",ChildKeyS[i]);  
    } 
    printf("\n\n"); 
}

/**5�����ܺ��� 
  ���ܺ��� 
*/ 
void Encipher(FOURBYTEINT * In,FOURBYTEINT * Out,FOURBYTEINT* S){
    FOURBYTEINT X,Y; //��������32λ�洢��
    int i,j;
    for(j=0;j<(fsize/4+2);j+=2){
        X = In[j]+S[0];    //In[j]+S[0];
        Y = In[j+1]+S[1];    //In[j+1]+S[1];
        for( i=1;i<=r;i++){
			X=ROTL((X^Y),Y) + S[2*i];    // X=ROTL((X^Y),Y) + S[2*i];   ���ѭ����λ����� //ROTL(x,y) (((x)<<(y&(w-1))) | ((x)>>(w-(y&(w-1))))) 
			Y=ROTL((Y^X),X) + S[2*i+1];    //Y=ROTL((Y^X),X) + S[2*i+1]; 
        }
        Out[j]=X; 
        Out[j+1]=Y; //���� 
    }
}

/**6�����ܺ��� 
  ���ܺ��� 
*/ 
void Decipher(FOURBYTEINT* In,FOURBYTEINT* Out,FOURBYTEINT* S){
    int i=0,j; 
    FOURBYTEINT X,Y; 
    for(j=0;j<(fsize/4+2);j+=2){
        X = In[j]; 
        Y = In[j+1]; 
        for(i=r;i>0;i--){
            Y = ROTR(Y-S[2*i+1],X)^X; //Y = ROTR(Y-S[2*i+1],X)^X;�����ѭ����λ�����  //ROTR(x,y) (((x)>>(y&(w-1))) | ((x)<<(w-(y&(w-1))))) 
            X = ROTR(X-S[2*i],Y)^Y;  // X = ROTR(X-S[2*i],Y)^Y;  
        } 
        Out[j]=X - S[0]; //Out[j]=X - S[0]; 
        Out[j+1]=Y - S[1]; //���� Out[j+1]=Y - S[1];
    }
} 
 
/**7������������
  ������
*/
int main(void){
	int k; 
    FOURBYTEINT ChildKeyS[2*12+2];    //r=12  ����Կ����Ϊ26
    FOURBYTEINT ChildKey1[26];
    BYTE KeyK[16];    //8bit=byte    16=b  ����Կ��16�ֽ�
    FOURBYTEINT Source[NoOfData];
	FOURBYTEINT Dest[NoOfData];    //�����洢���� 
	FOURBYTEINT Data[NoOfData]={0};    //�����洢���ܺ������ 

	InitialKey(KeyK,b);//���ɳ�ʼ��Կ

    generateChildKey(KeyK,ChildKeyS); //���ݳ�ʼ��Կ��������Կ
    
/****************���ļ����м���***************/ 
	char filename[256]={0};
	printf("�����ļ�����:");
	gets(filename);
    FILE *fp=fopen(filename,"rb"); 
	if(!fp){
		printf("can't open\n");
	}
	while(!feof(fp)){
		//fscanf(fp,"%ld",&Source[i]);
		fread(Source,sizeof(FOURBYTEINT),NoOfData,fp);
	}
	fseek(fp, 0L, SEEK_END);
	fsize=ftell(fp);
	fclose(fp);

    for(k=0;k<26;k++){ //************************************������
        ChildKey1[k]=ChildKeyS[k];//����˴��Զ���򵥵���ֵΪ������Կ������Խ��ܳ�����                    
    }
    /***************���ܹ���***************/
    Encipher(Source,Dest,ChildKey1);    //���� 
	FILE *fwp=fopen("����.docx","wb");
	if(!fwp){
		printf("can't write\n");
	}
	fwrite(Dest, 1, fsize, fwp);
	fclose(fwp);
	printf("���ܳɹ�\n");
	
	/***************���ܹ���***************/
    Decipher(Dest,Data,ChildKey1);    //���� 
    FILE *fdp=fopen("����.docx","wb");
	if(!fdp){
		printf("can't write\n");
	}
	fwrite(Data, 1, fsize, fdp);
	fclose(fdp);
	printf("���ܳɹ�\n");


/****************��������м���****************/ 
    /*printf("������ǰ������:"); 
    for (k=0;k<NoOfData;k++){
		if (k%2==0){
			printf("  ");
		}
        printf("%.8X ",Source[k]); //16������� 
    }
    printf("\n"); 
	//���ܹ��� 
    printf("�����Ժ������:"); 
    for (k=0;k<NoOfData;k++){
		if (k%2==0){
			printf("  ");
		}
        printf("%.8X ",Dest[k]); 
    }
    printf("\n");
	//���ܹ��� 
    printf("�����Ժ������:"); 
    for (k=0;k<NoOfData;k++){
		if (k%2==0){
			printf("  ");
		}
        printf("%.8X ",Data[k]); 
    }
    printf("\n");
	system("pause\n");*/ 
}  
