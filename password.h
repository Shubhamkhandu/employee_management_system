#ifndef PASSWORD_H
#define PASSWORD_H

typedef struct password{
	char ID[30];
	char Pass[30];
}pass;
char *space(char *ch);
int check(char *id, char *pa,int key);
int change(FORM *form, FIELD **field,int key);
int newpass(WINDOW *form1,int key);

#endif
