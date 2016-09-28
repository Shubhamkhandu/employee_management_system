#include<stdio.h>
#include<string.h>
#include<error.h>
#include<stdlib.h>
typedef struct employee{
	int Id;
	char name[50];
	char gender[7];
	int age;
	char dob[30];
	char address[50];
	int contact;
	long int salary;
}emp;
void get(char *str){
	char ch;
	int i = 0;
	while((ch=getchar()) != '\n'){
		str[i] = ch;
		i++;
	}
	str[i] = '\0';
}
void put(char *str){
	int i = 0;	
	while(str[i] != '\0'){
		putchar(str[i]);
		i++;	
	}
	printf("\t");
}
char fname[] = {"database.txt"};
int display_all(){
	system("clear");		
	int errno;	
	FILE *fp;
	emp t1;
	fp = fopen(fname, "rb");
	if(fp == NULL){		
		perror("open failed: ");
		return errno;
	}
	printf("Id\tName\t\t\tAge\tDOB\t\t\tAddress\t\t\t\t\tContact\n");
	while(1){
		fread(&t1, sizeof(t1), 1, fp);
		if(feof(fp)){
			break;				
		}
		printf("%d\t", t1.Id);
		put(t1.name);
		printf("%d\t", t1.age);
		put(t1.dob);
		put(t1.address);
		printf("%d\n", t1.contact);
	}
	fclose(fp);	
}
/*display all the information of employee */
int append(){
	int errno;
	FILE *fp;
	emp t;
	fp = fopen(fname, "ab");
	if(fp == NULL){	
		perror("open failed: ");
		return errno;	
	}	
	printf("ENTER ID : ");
	scanf("%d", &t.Id);
	getchar();
	printf("Name: ");
	get(t.name);
	printf("Gender: ");
	scanf("%s",t.gender);
	printf("Age: ");
	scanf("%d", &t.age);
	getchar();	
	printf("Date Of Birth : ");
	get(t.dob);
	printf("Address: ");
	get(t.address);
	printf("Contact: ");
	scanf("%d", &t.contact);
	printf("Salary: ");
	scanf("%ld", &t.salary);
	fwrite(&t, sizeof(t), 1, fp);
	fclose(fp);

}
	
	
/* add new content */
void delete(){
}
/* delete the content of employee */
int search(){
	int errno;
	int ch, found = 0, id;
	FILE *fp;
	emp t1;
	fp = fopen(fname, "rb");
	if(fp == NULL){		
		perror("open failed: ");
		return errno;
	}
	system("clear");
	printf("***************************************************************\n\n\n");
	printf("\t\t\t 1. According Id  \n");
	printf("\t\t\t 2. According Name of the employee\n");
	printf("\t\t\t 3. According to age \n");
	printf("\t\t\t 3. According to contact \n");
	printf("\t\t\t 4. exit to main \n");
	printf("choice: ");
	scanf("%d", &ch);
	switch(ch){
		case 1:
			printf("Enter the employee Id : ");
			scanf("%d",&id);
			while(1){
				fread(&t1, sizeof(t1), 1, fp);
				if(feof(fp)){
					break;				
				}
				if(t1.Id == id){
					found = 1;
					printf("ID: %d", t1.Id);
					printf("Name: ");
					puts(t1.name);
					printf("Gender: %s\n", t1.gender);
					printf("Age: %d years", t1.age);
					printf("Date Of Birth : ");
					puts(t1.dob);
					printf("Address: ");
					puts(t1.address);
					printf("Contact: %d", t1.contact);
					printf("Salary: %ld", t1.salary);
				}
				if(found == 0){
					printf("Sorry no data found\n");				
				}			
			}
	}
}
/* search the employee*/
void edit_info(){
}
/* change the info of the employee */
void sort(){
}
/* sort according to conditions */
void list_gender(){
}
/* male and female list */


int main(int argc , char *argv[]){
	system("clear");
	if(argc > 1){
		if(strcmp(argv[1],"-h")==0){
			system("clear");
			printf("********************************Employee Management System*******************************\n\n\n");
			printf("\t\t\t 1. ENTER THE NEW DATA OF EMPLOYEE \n");
			printf("\t\t\t 2. DISPLAY ALL THE INFORMATION OF ALL THE EMPLOYEE\n");
			printf("\t\t\t 3. SEARCH\n");
			printf("\t\t\t 4. SORT ACCORDING TO GIVEN CONDITION\n");
			printf("\t\t\t 5. EDIT INFORMATION OF EXISTING EMPLOYEE\n");
			printf("\t\t\t 6. List of employee\n");
			printf("\t\t\t 7. DELETE DATA OF EMPLOYEE\n");
			printf("\t\t\t 8. EXIT\n\n\n");
		}
	}
	if(argc > 0){
		int ch;
		while(1){
			printf("choice : ");
			scanf("%d", &ch);
			switch(ch){
				case 1:
					append();
					break;
				case 2:
					display_all();
					break;
				case 3:
					search();
					break;
				case 4:
					sort();
					break;
				case 5:
					edit_info();
					break;
				case 6:
					list_gender();
					break;
				case 7:
					delete();
					break;
				case 8:
					exit(0);
					break;
			}
							
		}
	}

	return 0;
}


