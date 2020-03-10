#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(unsigned char *s,unsigned int i,unsigned int j){
	unsigned char temp=s[i];
	s[i]=s[j];
	s[j]=temp;
} 

/*KSA*/
void rc4_init(unsigned char *S,unsigned char *key,unsigned int key_length){
	int i=0,j=0;
	char k[256]={0}; 
	for(i=0;i<256;i++){
		S[i]=i;
		k[i]=key[i%key_length]; 
	}
	for(i=0;i<256;i++){
		j=(j+k[i]+S[i])%256;
		swap(S,i,j);
	}
}

/*PRGA*/
unsigned char rc4_crypt(unsigned char *S,unsigned char *data,unsigned int data_length){
	int i=0,j=0,t=0;
	unsigned int k;
	for(k=0;k<data_length;k++){
		i=(i+1)%256;
		j=(j+S[i])%256;
		swap(S,i,j);
		t=(S[i]+S[j])%256;
		data[k]^=S[t];
	}
}

int main() {
	int i; 
	unsigned char S[256];    //S经初始化后成为密钥流 
	unsigned char key[256]={"secret"};  //密钥 
	unsigned char data[256]="inmethetigersniffstherose";  //明文数据 
	//将明文数组改为键盘输入 
	/*unsigned char data[12000];
	gets(data); */
	
	unsigned int data_length=strlen(data);  //明文长度 
	printf("key: %s\n", key);
    printf("data: %s\n\n", data);
    
//加密过程 
	rc4_init(S,key,strlen(key));  //初始化密钥流 
	//输出密钥流 
	/*for(i=0;i<256;i++){
		printf("%d ",S[i]);
	}
	printf("\n");*/
	rc4_crypt(S,data,data_length);    //加密 
	printf("encode: %s\n\n", data);
	
// 解密过程
	rc4_init(S,key,strlen(key)); 
	rc4_crypt(S,data,data_length);
	printf("decode: %s\n", data);
	system("pause");
}  

