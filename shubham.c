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
char fname[] = {"database.dat"};
void display(){
}
/*display the employee as per the id */
void display_all(){
}
/*display all the information of employee */
void append(){
	FILE *fp;
	emp t;
	fp = fopen(fname, "ab");
	/*if(fp == NULL){
		errnum = ENVIAL;
		perror("ERROR: ");
	}	*/	
	printf("ENTER ID : ");
	scanf("%d", &t.Id);
	printf("Name: ");
	gets(t.name);
	printf("Age: ");
	scanf("%d", &t.age);
	printf("Gender: ");
	scanf("%s",t.gender);
	printf("Date Of Birth : ");
	gets(t.dob);
	printf("Address: ");
	gets(t.address);
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
void search(){
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

	return 0;
}


