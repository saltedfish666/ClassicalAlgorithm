/*RC5  C代码实现 
w/r/b=32/12/16 
基本的RC5 3种算法组成，即密钥扩展算法、加密算法和解密算法。故RC5的C语言实现也由以下几个部分构成。 
1、参数的定义 
*/ 

#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <math.h>     

int w=32;//字长 32bit 4字节 
int r=12;//12;//加密轮数12 
int b=16;//主密钥(字节为单位8bit)个数  这里有16个
int t=26;//2*r+2=12*2+2=26 
int c=4; //主密钥个数*8/w = 16*8/32    //4个int，一个int4个字节，一个字节8bit，一共4*4*8=128bit
int fsize;

typedef unsigned long int FOURBYTEINT;//4字节 
typedef unsigned short int TWOBYTEINT;//2字节 
typedef unsigned char BYTE; 

void InitialKey(unsigned char* KeyK,int b); 
void generateChildKey(unsigned char* KeyK,FOURBYTEINT* ChildKeyS); 
void Encipher(FOURBYTEINT* In,FOURBYTEINT* Out,FOURBYTEINT* S); 
void Decipher(FOURBYTEINT* In,FOURBYTEINT* Out,FOURBYTEINT* S); 

#define NoOfData 173000

/**2、循环移位函数 
由于在生成子密钥，加密，解密过程中都要进行循环移位，故要首先定义循环以为函数。 
* 循环左移和右移函数 
* x : 被循环的数 
* y : 将要循环的位数 
*/ 
#define ROTL(x,y) ( ((x)<<(y&(w-1))) | ((x)>>(w-(y&(w-1)))) ) 
#define ROTR(x,y) (((x)>>(y&(w-1))) | ((x)<<(w-(y&(w-1))))) 

/**3、初始密钥产生函数 
生成一个初始的长度为b字节的密钥。 
  产生初始密钥的函数 
*/ 
void InitialKey(unsigned char* KeyK,int b){
    int i,j;
	int intiSeed=3;
    for(i=0;i<b;i++){//初始化
        KeyK[i]=0;
    }
    KeyK[0]=intiSeed;
	printf("初始主密钥(16字节共128位)：%.2lx ",KeyK[0]);
    for(j=1;j<b;j++)//生成 
    {
        KeyK[j] = (BYTE)( (int)pow(3,j)%(255-j) );  //pow(x,y)  x^y: 2^3=8
		printf("%.2X ",KeyK[j]);
        //KeyK[j] = (BYTE) ( ((int)(pow(double(3),j))%(255-j))); 
    } 
	printf("\n");
} 

/**4、密钥扩展函数 
由于需加密r轮，每轮需要两个子密钥，所以需要密钥扩展函数根据初始密钥来扩展出2r+2个子密钥。 
  产生子密钥的函数 
*/ 
void generateChildKey(unsigned char* KeyK,FOURBYTEINT* ChildKeyS){ 
    //const double e = 2.718281828459; 
    //const double Phia = 1.618033988749; 
    int PW = 0xB7E15163;//0xb7e1; 
    int QW = 0x9E3779B9;//0x9e37;//更改 
    int i; 
	int u =w/8;    //u=4; 
	FOURBYTEINT A,B,X,Y; 
    FOURBYTEINT L[4]; //c=16*8/32=4 
	A=B=X=Y=0; 
    //初始化数组S 
    ChildKeyS[0]=PW; 
	printf("\n初始子密钥（没有主密钥的参与）：\n%.8X ", ChildKeyS[0]);
    for (i=1;i<t;i++){   //t=26 
		if(i%13==0)printf("\n");
        ChildKeyS[i]=(ChildKeyS[i-1]+ QW);    //简单的相加产生下一个子密钥 
		printf("%.8X ", ChildKeyS[i]);
    }
	printf("\n");

    //将K数组转换为L数组 
    for(i=0;i<c;i++){	//初始化L数组c=4 
       L[i]=0;
    }
    for (i=b-1;i!=-1; i--){    //转换主密钥数组（16个 单位为8bit）为L数组（8个单位为16bit），数组L每一元素长为16bit，数组K每一元素长为8bit
        L[i/u] = (L[i/u]<<8)+KeyK[i];
    }
	printf("\n把主密钥变换为4字节单位：\n");
    for (i=0;i<c;i++){    //16进制输出改动 
        printf("%.8X ",L[i]); 
    } 
    printf("\n\n"); 

    //产生子密钥，存储在ChildKeyS中 
    for(i=0;i<3*t;i++){    //t=26 
        X = ChildKeyS[A] = ROTL(ChildKeyS[A]+X+Y,3);  
        A = (A+1) % t; 
        Y = L[B] = ROTL(L[B]+X+Y,(X+Y));  
        B = (B+1) % c; 
    } 
	printf("生成的子密钥（初始主密钥参与和初始子密钥也参与）："); 
    for (i=0;i<t;i++){    //16进制输出
		if(i%13==0)printf("\n");
            printf("%.8X ",ChildKeyS[i]);  
    } 
    printf("\n\n"); 
}

/**5、加密函数 
  加密函数 
*/ 
void Encipher(FOURBYTEINT * In,FOURBYTEINT * Out,FOURBYTEINT* S){
    FOURBYTEINT X,Y; //定义两个32位存储器
    int i,j;
    for(j=0;j<(fsize/4+2);j+=2){
        X = In[j]+S[0];    //In[j]+S[0];
        Y = In[j+1]+S[1];    //In[j+1]+S[1];
        for( i=1;i<=r;i++){
			X=ROTL((X^Y),Y) + S[2*i];    // X=ROTL((X^Y),Y) + S[2*i];   异或，循环移位，相加 //ROTL(x,y) (((x)<<(y&(w-1))) | ((x)>>(w-(y&(w-1))))) 
			Y=ROTL((Y^X),X) + S[2*i+1];    //Y=ROTL((Y^X),X) + S[2*i+1]; 
        }
        Out[j]=X; 
        Out[j+1]=Y; //密文 
    }
}

/**6、解密函数 
  解密函数 
*/ 
void Decipher(FOURBYTEINT* In,FOURBYTEINT* Out,FOURBYTEINT* S){
    int i=0,j; 
    FOURBYTEINT X,Y; 
    for(j=0;j<(fsize/4+2);j+=2){
        X = In[j]; 
        Y = In[j+1]; 
        for(i=r;i>0;i--){
            Y = ROTR(Y-S[2*i+1],X)^X; //Y = ROTR(Y-S[2*i+1],X)^X;相减，循环移位，异或  //ROTR(x,y) (((x)>>(y&(w-1))) | ((x)<<(w-(y&(w-1))))) 
            X = ROTR(X-S[2*i],Y)^Y;  // X = ROTR(X-S[2*i],Y)^Y;  
        } 
        Out[j]=X - S[0]; //Out[j]=X - S[0]; 
        Out[j+1]=Y - S[1]; //明文 Out[j+1]=Y - S[1];
    }
} 
 
/**7、主函数测试
  主函数
*/
int main(void){
	int k; 
    FOURBYTEINT ChildKeyS[2*12+2];    //r=12  子密钥个数为26
    FOURBYTEINT ChildKey1[26];
    BYTE KeyK[16];    //8bit=byte    16=b  主密钥共16字节
    FOURBYTEINT Source[NoOfData];
	FOURBYTEINT Dest[NoOfData];    //用来存储密文 
	FOURBYTEINT Data[NoOfData]={0};    //用来存储解密后的密文 

	InitialKey(KeyK,b);//生成初始密钥

    generateChildKey(KeyK,ChildKeyS); //根据初始密钥生成子密钥
    
/****************对文件进行加密***************/ 
	char filename[256]={0};
	printf("输入文件名字:");
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

    for(k=0;k<26;k++){ //************************************有问题
        ChildKey1[k]=ChildKeyS[k];//如果此处自定义简单的数值为加密密钥，则可以解密出密文                    
    }
    /***************加密过程***************/
    Encipher(Source,Dest,ChildKey1);    //加密 
	FILE *fwp=fopen("加密.docx","wb");
	if(!fwp){
		printf("can't write\n");
	}
	fwrite(Dest, 1, fsize, fwp);
	fclose(fwp);
	printf("加密成功\n");
	
	/***************解密过程***************/
    Decipher(Dest,Data,ChildKey1);    //解密 
    FILE *fdp=fopen("解密.docx","wb");
	if(!fdp){
		printf("can't write\n");
	}
	fwrite(Data, 1, fsize, fdp);
	fclose(fdp);
	printf("解密成功\n");


/****************对输入进行加密****************/ 
    /*printf("加密以前的明文:"); 
    for (k=0;k<NoOfData;k++){
		if (k%2==0){
			printf("  ");
		}
        printf("%.8X ",Source[k]); //16进制输出 
    }
    printf("\n"); 
	//加密过程 
    printf("加密以后的密文:"); 
    for (k=0;k<NoOfData;k++){
		if (k%2==0){
			printf("  ");
		}
        printf("%.8X ",Dest[k]); 
    }
    printf("\n");
	//解密过程 
    printf("解密以后的明文:"); 
    for (k=0;k<NoOfData;k++){
		if (k%2==0){
			printf("  ");
		}
        printf("%.8X ",Data[k]); 
    }
    printf("\n");
	system("pause\n");*/ 
}  
