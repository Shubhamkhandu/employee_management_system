#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct password{
	char ID[30];
	char Pass[30];
}pass;

int main(){
	pass i;
	FILE *fp;
	fp = fopen("usernamepass.txt", "w");
	if(fp == NULL){
		exit(0);
	}	
	char *a ="abhijeet";
	char *b = "abhijeetcoep";
	strcpy(i.ID,a);
	strcpy(i.Pass,b);
	fwrite(&i,sizeof(pass),1,fp);
	a = "shubham";
	b= "shubham18";
	strcpy(i.ID,a);
	strcpy(i.Pass,b);
	fwrite(&i,sizeof(pass),1,fp);
	 a="narendra";
	 b = "modi123";
	strcpy(i.ID,a);
	strcpy(i.Pass,b);
	fwrite(&i,sizeof(pass),1,fp);
	 a="nehru";
	 b = "nehru123";
	strcpy(i.ID,a);
	strcpy(i.Pass,b);
	fwrite(&i,sizeof(pass),1,fp);
	system("chmod 000 usernamepass.txt");
	fclose(fp);
}
	
	
