#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<menu.h>
#include<form.h>
#include<ctype.h>
#include "password.h"
char *space(char *ch){
	int i = 0;
	char *ch1;
	ch1 = (char *)malloc(sizeof(char)*31);
	while(ch[i] != ' '){
		ch1[i] = ch[i];
		i++;
	}
	ch1[i] = '\0';
	return ch1;
}	
//to check password
int check(char *id, char *pa,int key){
	pass i;
	int l,p;
	system("chmod 777 usernamepass.txt");
	FILE *fp;
	fp = fopen("usernamepass.txt", "r");
	if(fp == NULL){
		printf("file cannot be opened\n");
		exit(0);
	}
	while(1){
		fread(&i,sizeof(pass),1,fp);
		if(feof(fp)){
			break;
		}
		l = strlen(i.ID);
		p = strlen(i.Pass);
		if((strncmp(id,i.ID,l) == 0) && (strncmp(pa,i.Pass,p) == 0)){		
			system("chmod 000 usernamepass.txt");			
			fclose(fp);		
			return 1;
		}
	}	
	system("chmod 000 usernamepass.txt");
	fclose(fp);	
	return 0;
	 
}
//change password function
int change(FORM *form, FIELD **field,int key){
	system("chmod 777 usernamepass.txt");
	FILE *fp = fopen("usernamepass.txt", "r+");
	if(fp == NULL){
		return 0;
	}
	int p, j = 0,len = field_count(form);	
	pass i;
	char **ch,*x,*y,*z;
	ch = (char **)malloc(sizeof(char *) * len);
	while(j < len){
		ch[j] = field_buffer(field[j], 0);
		j++;
	}
	x = space(ch[1]);
	y = space(ch[2]);
	z = space(ch[3]);
	while(1){
		fread(&i,sizeof(pass),1,fp);
		if(feof(fp))
			system("chmod 000 usernamepass.txt");
			return 3;
		p = strlen(i.ID);
		if((strncmp(ch[0],i.ID,p)) == 0) {
			p = strlen(i.Pass);
			if(strncmp(x,i.Pass,p)==0){
				if(strcmp(y, z) == 0) {
					strcpy(i.Pass,y);
					fseek(fp,-sizeof(pass), SEEK_CUR);
            				fwrite(&i,sizeof(pass), 1, fp);
					fclose(fp);
					system("chmod 000 usernamepass.txt");
					return 1;
				}
				else {
					system("chmod 000 usernamepass.txt");
					fclose(fp);
					return 2;
				}
			}
			else {
				system("chmod 000 usernamepass.txt");
				fclose(fp);
				return 0;
			}
		}
	}
}
// new password
int newpass(WINDOW *form1,int key) {
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, x, y, size, flag;
	char *field_names[] = {"ID","OLD PASSWORD", "NEW-PASSWORD","CONFIRM_PASSWORD"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	init_pair(6, COLOR_RED, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	cbreak();
	//noecho();
	keypad(form1, TRUE);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {
		
		field[i] = new_field(1, 30, 7 + 2 * i, 50, 0, 0);
		if(i == 2 || i ==3)		
			field_opts_off(field[i],O_PUBLIC | O_AUTOSKIP);
		else
			field_opts_off(field[i], O_AUTOSKIP);
		set_field_back(field[i], COLOR_PAIR(6));
		set_field_fore(field[i], COLOR_PAIR(6));
		i++;
		wattroff(form1 ,A_BOLD);
	}	
	field[i] = new_field(1, 15, 15, 50, 0, 0);
	field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
	set_field_back(field[i], COLOR_PAIR(7));
	set_field_fore(field[i], COLOR_PAIR(7));
	set_field_buffer(field[i], 0, " CHANGE ");
	i++;	
	field[i] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, x, y, 1, 80));
	post_form(form);
	wattron(form1 ,A_BOLD);
	mvwprintw(form1, 7,30, "%s : ", field_names[0]);
	mvwprintw(form1, 9, 30, "%s : ", field_names[1]);
	mvwprintw(form1, 11, 30, "%s : ", field_names[2]);
	mvwprintw(form1, 13, 30, "%s : ", field_names[3]);
	mvwprintw(form1,5,50,"CHANGE PASSWORD");
	wattroff(form1 ,A_BOLD);
	wrefresh(form1);
	while(i = wgetch(form1)){
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
						form_driver(form, REQ_END_LINE);
						break;
					case KEY_LEFT:
						form_driver(form, REQ_PREV_CHAR);
						break;
					case KEY_RIGHT:
						form_driver(form, REQ_NEXT_CHAR);
						break;
					case 27:
						goto end;
						break;
					case 10:
						if(field[4] == current_field(form)){
							i = change(form,field,key);                                               
							if(i == 0){
								wattron(form1 ,A_BOLD);
								mvwprintw(form1, 16, 40, "%s", "OLD PASSWORD IS WRONG ");
								i = 0;
								while( i < size ) 
									set_field_buffer(field[i++], 0, "");
								wattroff(form1 ,A_BOLD);
							}
							else if(i == 2){
								wattron(form1 ,A_BOLD);
								mvwprintw(form1, 16, 40, "%s", "NEW AND RE_ENTER PASSWORD MISMATCH ");
								i = 0;
								while( i < size ) 
									set_field_buffer(field[i++], 0, "");
								wattroff(form1 ,A_BOLD);
							}		
							else if(i == 3){
								wattron(form1 ,A_BOLD);
								mvwprintw(form1, 16, 40, "%s", "ID NOT FOUND");
								i = 0;
								while( i < size ) 
									set_field_buffer(field[i++], 0, "");
								wattroff(form1 ,A_BOLD);
							}					
							else
								return 1;
							
						}	
					case KEY_BACKSPACE: case 127:
						form_driver(form, REQ_DEL_PREV);
						break;
					case KEY_DC:
						form_driver(form, REQ_DEL_CHAR);
						break;
			}
		}
	}
	end:
	unpost_form(form);
	free_form(form);
	i = 0;
	while(i < size) {
		wmove(form1, 3 + 2 * i, 1);
		wclrtoeol(form1);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(form1, 0, 0);
	wrefresh(form1);
}
