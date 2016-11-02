#ifndef ALLFUNCTION_H
#define ALLFUNCTION_H
typedef struct employee{
	int Id;
	char fname[30];
	char lname[30];
	int age;
	char dob[30];
	char contact[12];
	char join[30];
	char email[30];
	int count;
	int seen;
	int holidays[45];
	int request;
	int counter;
}emp;

typedef struct leave{
	int Id;
	char name[60];
	char leave[60];
	char from[10];
	char to[10];
	int day;
	char reason[100];
}leave;

typedef struct quote{
	char a[200];
	char b[200];
	char c[200];
}quote;

/* admin functions */
void admin();
void leavereq(WINDOW *form1);
void leaveform(WINDOW *form1,char *str,leave t);
void search_admin();
void compare_admin(WINDOW *my_win2,char *str);

/* employee functin */
void employee(int key);
void profile(WINDOW *form1,int key);
void mod2(WINDOW *form1, emp t);
void search_employee();
void display1_employee(WINDOW *my_win2);
void compare_employee(WINDOW *my_win2,char *str);
void app(WINDOW *form1, int key,int p);
void delete1(int key);
int leave1(WINDOW *form1,int key,emp t);
int leaveadd(FORM *form,FIELD **field,emp t,char *str);

/* manager function */
void manage2();
int add(WINDOW *form1);
int add_file(FORM *form, FIELD **field);
void display(WINDOW  *my_win2);
void search();
void search1(WINDOW *my_win2,int key);
void compare(WINDOW *my_win2,char *str,int key);
void display1(WINDOW *my_win2);
void modify(WINDOW *form1,int key);
int mod(WINDOW *form1,FORM *form2, FIELD **field1,int key);
void modit(FORM *form, FIELD **field, emp t);
void dele(WINDOW *form1,int key);
int del(FORM *form, FIELD **field,int key);

/* extra functions */
int printlogin(WINDOW *form1,int key);
int create(WINDOW *my_win2,int key);
void destroy_win(WINDOW *my_win2);
void print_home(WINDOW *my_win2);
void printhome2(WINDOW *my_win2);
#endif
