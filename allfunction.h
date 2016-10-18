#ifndef ALLFUNCTION_H
#define ALLFUNCTION_H
typedef struct employee{
	int Id;
	char fname[30];
	char lname[30];
	int age;
	char dob[30];
	int contact;
	char join[30];
	char email[30];
}emp;
int del(FORM *form, FIELD **field,int key);
void dele(WINDOW *form1,int key);
int printlogin(WINDOW *form1,int key);
void destroy_win(WINDOW *my_win2);
char *tostring(char str[],int num);
void modify(WINDOW *form1);
void print_home(WINDOW *my_win2);
int create(WINDOW *my_win2,int key);
void display(WINDOW  *my_win2);
void add_file(FORM *form, FIELD **field);
int add(WINDOW *form1);
void manage2();

#endif
