#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<menu.h>
#include<form.h>
#include<ctype.h>
#include "password.h"
#include "allfunction.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
char fname1[] = {"database.txt"};
int main(int argc, char* argv[]) {

	WINDOW *my_win1, *my_win2, *mainwin;
	int startx, starty, width, height;
	int ch, x, y,log = 0;
	char text[] = "EMPLOYEE MANAGEMENT SYSTEM", *choices[] = { "HOME", "ADMINISTRATOR", "EMPLOYEE LOGIN" , "EMPLOYEE MANAGEMENT", 										"EXIT"};
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i;
        initscr();			/* ncurses begins*/
	cbreak();			
	noecho();
	keypad(stdscr, TRUE);		/* keyboard activated*/
	initscr();			/* initialize NCurses */
	start_color();	
	init_pair(9,COLOR_BLACK, COLOR_BLACK);
	bkgd(COLOR_PAIR(9));
	init_pair(1, COLOR_WHITE, COLOR_RED);	
	move(1,55);
	attron(A_BOLD |A_STANDOUT|COLOR_PAIR(1));
	addstr(text);
	attroff(A_BOLD |A_STANDOUT|COLOR_PAIR(1));
	refresh();

	height = 10;
	width = 10;
	starty = (LINES - height) / 2;	/* center allignment*/
	startx = (COLS - width) / 2;
	init_pair(2,COLOR_BLACK, COLOR_WHITE);
	attron(A_BOLD);
	my_win1 =newwin(3, 125, 4, 10);		// creating 1st window
	box(my_win1, 0 , 0);
	wbkgd(my_win1, COLOR_PAIR(2));
	wrefresh(my_win1);
	init_pair(3, COLOR_RED, COLOR_WHITE);
	my_win2 =newwin(20, 125, 15, 10);	// creating 2nd window
	box(my_win2, 0 , 0);	
	wbkgd(my_win2, COLOR_PAIR(2));
	wattron(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	mvwprintw(my_win2,7,48,"WELCOME TO EMPLOYEE MANAGEMENT SYSTEM");
	mvwprintw(my_win2,8,55,"FOR SUPPORT AND QUERIES");	
	mvwprintw(my_win2,9,56,"CONTACT : 8237824147");	
	mvwprintw(my_win2,10,48, "EMAIL: shubhamkhandelwal18@gmail.com");	
	wattroff(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	wrefresh(my_win2);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_CYAN, COLOR_BLACK);
	/*items */
        n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i) 
                my_items[i] = new_item(choices[i], choices[i]);
	my_items[i]=(ITEM *)NULL;	
	/*menu */
	my_menu = new_menu((ITEM **)my_items);
	/* Set menu option*/
	menu_opts_off(my_menu, O_SHOWDESC);
        keypad(my_win1, TRUE);
     	/* Set main window and sub window */
        set_menu_win(my_menu, my_win1);
        set_menu_sub(my_menu, derwin(my_win1, 2, 110, 1, 10));
	set_menu_format(my_menu, 1, 6);
	set_menu_mark(my_menu, " * ");
	
	set_menu_fore(my_menu,COLOR_PAIR(4) | A_REVERSE);
	set_menu_back(my_menu,COLOR_PAIR(5));
	set_menu_grey(my_menu,COLOR_PAIR(2));

	
	attron(COLOR_PAIR(5));
	mvprintw(0, 100, "Press <ENTER> to select an option");
	mvprintw(1, 100, "Use Arrow Keys to navigate");
	mvprintw(2, 100,"Double Esc to exit from window");
	attroff(COLOR_PAIR(5));
	refresh();
	/* Post the menu */
	post_menu(my_menu);
	wrefresh(my_win1);
	attroff(A_BOLD);	
	
	while((ch = wgetch(my_win1)) != KEY_F(1))
		{       switch(ch)
		        {	
				case KEY_LEFT:
					menu_driver(my_menu, REQ_LEFT_ITEM);
					break;
				case KEY_RIGHT:
					menu_driver(my_menu, REQ_RIGHT_ITEM);
					break;
				case 10:
					if(strcmp(item_name(current_item(my_menu)),"HOME") == 0 ) {
						print_home(my_win2);						
						
						
					}
					
					if(strcmp(item_name(current_item(my_menu)),"ADMINISTRATOR") == 0 ) {
						create(my_win2,0);
						print_home(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"EMPLOYEE LOGIN") == 0 ) {
						create(my_win2,1);
						print_home(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"EMPLOYEE MANAGEMENT") == 0 ) {
						log = create(my_win2,2);
						if(log == 1){
							manage2();
							create(my_win2,2);
						}
						print_home(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"EXIT") == 0 ) {
						endwin();
						exit(0);
						return 0 ;
					}
					break;
			}
        	        wrefresh(my_win1);
		}	
		
		/* Unpost and free all the memory taken up */
        	unpost_menu(my_menu);
        	free_menu(my_menu);
        	for(i = 0; i < n_choices; ++i)
        	        free_item(my_items[i]);
	
		endwin();
		return 0;
}	

//to modify
void modify(WINDOW *form1){
	FIELD **field;
	FORM *form;
	char *str;
	int j = 0;
	str = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	int ch = 0, i = 0, x, y, size, flag;
	char *field_names[] = {"ID","FIRST-name", "Last-name"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	init_pair(6, COLOR_RED, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	cbreak();
	keypad(form1, TRUE);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {
		
		field[i] = new_field(1, 30, 7 + 2 * i, 50, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP);
		set_field_back(field[i], COLOR_PAIR(6));
		set_field_fore(field[i], COLOR_PAIR(6));
		i++;
		wattroff(form1 ,A_BOLD);
	}
	field[i] = new_field(1, 15, 13, 50, 0, 0);
	field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
	set_field_back(field[i], COLOR_PAIR(7));
	set_field_fore(field[i], COLOR_PAIR(7));
	set_field_buffer(field[i], 0, "MODIFY");
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
	mvwprintw(form1,8,60,"OR");
	mvwprintw(form1,5,50,"MODIFY THE INFO OF EMPLOYEE");
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
						if(field[3] == current_field(form)){
							if(strcmp(field_buffer(field[0], 0), str) == 0&&strcmp(field_buffer(field[1], 0), str) == 0&&strcmp(field_buffer(field[2], 0), str) == 0){
								mvwprintw(form1,14,50,"Enter proper ID or name");
								i = 0;
								while( i < size ) 
								set_field_buffer(field[i++], 0, "");
							}
							else if(strcmp(field_buffer(field[0], 0), str) != 0&&strcmp(field_buffer(field[1], 0), str) != 0&&strcmp(field_buffer(field[2], 0), str) != 0){
								mvwprintw(form1,14,50,"Enter  ID OR NAME      ");
								i = 0;
								while( i < size ) 
								set_field_buffer(field[i++], 0, "");
							}
							else{
								destroy_win(form1);
								form1 =newwin(28, 130, 13,5);
								box(form1, 0 , 0);	
								wbkgd(form1, COLOR_PAIR(2));
								//mod(form1,form,field);
								
							break;
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

	return;
}

// to display the list
void display(WINDOW  *my_win2){
	int i = 0,j = 0,l;
	char *choice[]={"ID","NAME","DATEOF-BIRTH","AGE","EMAIL-ID","CONTACT","JOIN-DATE"};
	int place[]={4, 10, 35, 55, 65, 105, 120}; 
	while(i < 7){
		wattron(my_win2,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(my_win2, 1,place[i], "%s", choice[i]);
		wattroff(my_win2,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	FILE *fp;
	emp t1;
	fp = fopen(fname1, "rb");
	j = 1;
	while(1){
		fread(&t1, sizeof(t1), 1, fp);
		if(feof(fp)){
			break;
		}
		wattron(my_win2,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(my_win2, j+1,place[0],"%d", t1.Id);
		mvwprintw(my_win2, j+1,place[1],"%s", t1.fname);
		mvwprintw(my_win2, j+1,(place[1]+strlen(t1.fname)+1) ,"%s", t1.lname);
		mvwprintw(my_win2, j+1,place[2],"%s", t1.dob);
		mvwprintw(my_win2, j+1,place[3],"%d", t1.age);
		mvwprintw(my_win2, j+1,place[4],"%s", t1.email);
		mvwprintw(my_win2, j+1,place[5] ,"%d", t1.contact);
		mvwprintw(my_win2, j+1,place[6],"%s", t1.join);
		wattroff(my_win2,COLOR_PAIR(3) | A_BOLD);
		wrefresh(my_win2);
		j++;
	}
	fclose(fp);	
}

// to create add employee window

int add(WINDOW *form1){
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, j = 0, x, y, size, flag=0;
	char *str , *field_names[] = {"Employee-ID", "First-Name","Last-Name","D.O.B","Age","Mobile-no.","Email-Id","Joining-Date"};
	str = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(form1, TRUE);
	init_pair(12, COLOR_BLACK, COLOR_BLUE);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
		mvwprintw(form1, 5 + 2 * i, 15, "%s : ", field_names[i]);
		if(i == 3)
			mvwprintw(form1, 7 + 1 * i, 50, "%s", "(DD/MM/YY)");
		if(i == 7)
			mvwprintw(form1, 11 + 1 * i, 50, "%s", "(DD/MM/YY)");
		field[i] = new_field(1, 30, 5 + 2 * i, 0, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP);
		set_field_back(field[i], COLOR_PAIR(12));
		set_field_fore(field[i], COLOR_PAIR(12));
		wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);		
		i++;
	}
	field[i] = new_field(1, 15, 21, 15, 0, 0);
	field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
	set_field_back(field[i], COLOR_PAIR(7));
	set_field_fore(field[i], COLOR_PAIR(7));
	set_field_buffer(field[i], 0, "ADD");
	wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
	mvwprintw(form1,3,40,"ADD NEW EMPLOYEE");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	field[++i] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0, 60));
	
	post_form(form);
	wrefresh(form1);
	while(i = wgetch(form1)) {
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
				case KEY_BACKSPACE: case 127:
					form_driver(form, REQ_DEL_PREV);
					break;
				case KEY_DC:
					form_driver(form, REQ_DEL_CHAR);
					break;
				case 10:
					if(field[8] == current_field(form)) {
						flag = 0;						
						i = 0;
						while(i < 8){
							if(strcmp(field_buffer(field[i], 0), str) == 0 ) {
								mvwprintw(form1, 23, 10,"%s" "Form cant be empty");
								flag = 1;
								break;
							}
							i++;
						}
						if(flag == 0) {
							add_file(form, field);
							mvwprintw(form1, 24, 8, "Employee Added successfully");
							i = 0;
							while( i < size ) 
								set_field_buffer(field[i++], 0, "");
							}
					}
					
					else {
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
					}
					break;
				default:
					getyx(form1, y, x);
					mvwprintw(form1, 24, 8, "Character not allowed");
					wmove(form1, y, x);
					break;
			}
		}
	}
	end:
	unpost_form(form);
	free_form(form);
	wclear(form1);
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

		
// to add to file
void add_file(FORM *form, FIELD **field){
	FILE *fp,*tmp;
	int  i = 0,len = field_count(form),flag = 0,check = 1,j = 0;
	char **ch;
	char *ch1;
	ch = (char **)malloc(sizeof(char *) * len);
	emp t,t1;
	fp = fopen(fname1, "r+");
	tmp = fopen("tmp.txt", "w");
	while(i < len){
		ch[i] = field_buffer(field[i], 0);
		i++;
	}
	ch1 = space(ch[0]);
	t.Id = atoi(ch1);
	ch1 = space(ch[1]);
	strcpy(t.fname,ch1);
	ch1 = space(ch[2]);
	strcpy(t.lname,ch1);
	ch1 = space(ch[3]);
	strcpy(t.dob,ch1);
	ch1 = space(ch[4]);
	t.age = atoi(ch1);
	ch1 = space(ch[5]);
	t.contact = atoi(ch1);
	ch1 = space(ch[6]);
	strcpy(t.email,ch1);
	ch1 = space(ch[7]);
	strcpy(t.join,ch1);
	if( fp == NULL ){
			fwrite(&t,sizeof(emp),1,tmp);
			rename("tmp.txt",fname1);
			fclose(tmp);
			free(ch);
			return;
	}
	else{
		
		while(1){
			fread(&t1, sizeof(emp), 1, fp);
			if(feof(fp)){
				if(j == 0) 
					fwrite(&t,sizeof(emp),1,tmp);
			break;
			}
			if((t1.Id < t.Id)&&check == 1){
            			fwrite(&t1,sizeof(emp), 1, tmp);
				if(feof(fp)) {
					fwrite(&t,sizeof(emp),1,tmp);
					j = 1;
					break;
				}
				
			}
			else if(check == 1) {
				fwrite(&t,sizeof(emp),1,tmp);
				fwrite(&t1,sizeof(emp), 1, tmp);
				j = 2;
				check = 2;
			}
			else
				fwrite(&t1,sizeof(emp), 1, tmp);
		}
	}
	remove(fname1);
	rename("tmp.txt",fname1);
	free(ch);
	fclose(fp);
	fclose(tmp);
}

// manger screen after login
void manage2(){
	WINDOW *my_win1, *my_win2;
	char *choices[] = {
                        "ADD", "DISPLAY", "SEARCH" , "EDIT", "DELETE","LOGOUT"
                  };
	int ch, x, y;
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i;
	my_win1 =newwin(3, 100, 8, 20);	
	box(my_win1, 0 , 0);
	wbkgd(my_win1, COLOR_PAIR(2));
	wrefresh(my_win1);
	init_pair(3, COLOR_RED, COLOR_WHITE);

	my_win2 =newwin(28, 130, 13,5);	
	box(my_win2, 0 , 0);	
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	
	n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i) 
                my_items[i] = new_item(choices[i], choices[i]);
	my_items[i]=(ITEM *)NULL;	

	my_menu = new_menu((ITEM **)my_items);

	menu_opts_off(my_menu, O_SHOWDESC);
        keypad(my_win1, TRUE);

	 set_menu_win(my_menu, my_win1);
        set_menu_sub(my_menu, derwin(my_win1,1,80,1,14));
	set_menu_format(my_menu, 1, 7);
	set_menu_mark(my_menu, " * ");

	set_menu_fore(my_menu,COLOR_PAIR(4) | A_REVERSE);
	set_menu_back(my_menu,COLOR_PAIR(5));
	set_menu_grey(my_menu,COLOR_PAIR(2));
	wattron(my_win2 ,COLOR_PAIR(3)| A_BOLD);
	mvwprintw(my_win2,15,50,"WELCOME");
	wattroff(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	post_menu(my_menu);
	wrefresh(my_win1);
	wrefresh(my_win2);
	while((ch = wgetch(my_win1)) != KEY_F(1))
		{       switch(ch)
		        {	
				case KEY_LEFT:
					menu_driver(my_menu, REQ_LEFT_ITEM);
					break;
				case KEY_RIGHT:
					menu_driver(my_menu, REQ_RIGHT_ITEM);
					break;
				case 10:
					if(strcmp(item_name(current_item(my_menu)),"ADD") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(28, 130, 13,5);	
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));						
						add(my_win2);
					}
					
					if(strcmp(item_name(current_item(my_menu)),"SEARCH") == 0 ) {
					
					}
					else if(strcmp(item_name(current_item(my_menu)),"EDIT") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						modify(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"DISPLAY") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(40, 140, 11,2);
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						display(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"DELETE") == 0 ) {
							destroy_win(my_win2);
							my_win2 =newwin(20, 125, 15, 10);
							box(my_win2, 0 , 0);	
							wbkgd(my_win2, COLOR_PAIR(2));
							dele(my_win2,3);
					}
					else if(strcmp(item_name(current_item(my_menu)),"LOGOUT") == 0 ) {
						unpost_menu(my_menu);
        					free_menu(my_menu);						
						destroy_win(my_win2);
						destroy_win(my_win1);
						return;
					}
					break;
			}
        	        wrefresh(my_win1);
		}	
	
		/* Unpost and free all the memory taken up */
        	unpost_menu(my_menu);
        	free_menu(my_menu);
        	for(i = 0; i < n_choices; ++i)
        	        free_item(my_items[i]);
	
		endwin();	
		return;
}		


///creating delete window
void dele(WINDOW *form1,int key){
	FIELD **field;
	FORM *form;
	int j = 0,c = 0,flag = 0,ch = 0, i = 0, x, y, size;
	char *field_names[] = {"ID","FIRST-name", "Last-name"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	char *str;
	str = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';	

	init_pair(6, COLOR_RED, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	cbreak();
	keypad(form1, TRUE);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {
		
		field[i] = new_field(1, 30, 7 + 2 * i, 50, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP);
		set_field_back(field[i], COLOR_PAIR(6));
		set_field_fore(field[i], COLOR_PAIR(6));
		i++;
		wattroff(form1 ,A_BOLD);
	}
	field[i] = new_field(1, 15, 13, 50, 0, 0);
	field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
	set_field_back(field[i], COLOR_PAIR(7));
	set_field_fore(field[i], COLOR_PAIR(7));
	set_field_buffer(field[i], 0, "DELETE");
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
	mvwprintw(form1,8,60,"OR");
	mvwprintw(form1,5,50,"DELETE THE EMPLOYEE");
	if(key == 1){
		mvwprintw(form1,15,50,"Deleted successfully");
	}
	else if(key == 0){
		mvwprintw(form1,14,50,"DELETE UNSUCCESSFULLY");
	}
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
						if(field[3] == current_field(form)){
							if(strcmp(field_buffer(field[0], 0), str) == 0&&strcmp(field_buffer(field[1], 0), str) == 0&&strcmp(field_buffer(field[2], 0), str) == 0){
								mvwprintw(form1,14,50,"Enter proper ID or name");
								i = 0;
								while( i < size ) 
								set_field_buffer(field[i++], 0, "");
							}
							else if(strcmp(field_buffer(field[0], 0), str) != 0&&strcmp(field_buffer(field[1], 0), str) != 0&&strcmp(field_buffer(field[2], 0), str) != 0){
								mvwprintw(form1,14,50,"Enter  ID OR NAME      ");
								i = 0;
								while( i < size ) 
								set_field_buffer(field[i++], 0, "");
							}
							else{
								destroy_win(form1);
								form1 =newwin(28, 130, 13,5);
								box(form1, 0 , 0);	
								wbkgd(form1, COLOR_PAIR(2));
								if(strcmp(field_buffer(field[0], 0), str) != 0)
									flag =1;
								c = del(form,field,flag);
								if(c == 1){
									destroy_win(form1);
									form1 =newwin(20, 125, 15, 10);
									box(form1, 0 , 0);	
									wbkgd(form1, COLOR_PAIR(2));
									dele(form1,1);
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
									break;
								}
								else{
									destroy_win(form1);
									form1 =newwin(20, 125, 15, 10);
									box(form1, 0 , 0);	
									wbkgd(form1, COLOR_PAIR(2));
									dele(form1,0);
									
									i = 0;
									while( i < size ) 
										set_field_buffer(field[i++], 0, "");
									break;
								}
								break;
							}
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

	return;
}

//delete
int del(FORM *form, FIELD **field,int key){
	FILE *fp,*tmp;
	int  i = 0,len = field_count(form),pt = 0,j = 0,c = 0;
	fp = fopen(fname1, "r");
	tmp = fopen("tmp.txt", "w");
	char **ch;
	char *ch1,*ch2,ch3[30];
	ch = (char **)malloc(sizeof(char *) * len);
	emp t,t1;
	while(i < len){
		ch[i] = field_buffer(field[i], 0);
		i++;
	}
	if(key == 1){
		ch1 = space(ch[0]);
		while(1){
			fread(&t,sizeof(emp),1,fp);
			ch2 = tostring(ch3,t.Id);
			if(feof(fp)){
				if(pt==0)
					return 0;
				break;
			}
			if(strcmp(ch1,ch2) == 0){
				c = 1;
				pt = 1;
			}
			else
				fwrite(&t,sizeof(emp),1,tmp);
		}
		fclose(fp);
		fclose(tmp);
		remove(fname1);
		rename("tmp.txt",fname1);
		return c;
	}
	else{
		ch1 = space(ch[1]);
		ch2 = space(ch[2]);
		while(1){
			fread(&t,sizeof(emp),1,fp);
			if(feof(fp)){
				if(pt==0)
					return 0;
				break;
			}
			if(strcmp(ch1,t.fname) == 0 && strcmp(ch2,t.lname) == 0){
				c = 1;
				pt = 1;
			}
			else
				fwrite(&t,sizeof(emp),1,tmp);
		}
		fclose(fp);
		fclose(tmp);
		remove(fname1);
		rename("tmp.txt",fname1);
		return c;
	}
}

// to printlogin page
int printlogin(WINDOW *form1,int key){
	 
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, x, y, size, flag=0;
	char *field_names[] = {"LOGIN ID", "PASSWORD"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	init_pair(6, COLOR_RED, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	cbreak();
	keypad(form1, TRUE);

	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));

	field[0] = new_field(1, 30, 7, 50, 0, 0);
	field_opts_off(field[0], O_AUTOSKIP);
	set_field_back(field[0], COLOR_PAIR(6));
	set_field_fore(field[0], COLOR_PAIR(6));

	field[1] = new_field(1, 30, 9 , 50, 0, 0);
	field_opts_off(field[1], O_PUBLIC | O_AUTOSKIP);
	set_field_back(field[1], COLOR_PAIR(6));
	set_field_fore(field[1], COLOR_PAIR(6));
	
	field[2] = new_field(1, 15, 11, 50, 0, 0);
	field_opts_off(field[2], O_AUTOSKIP | O_EDIT);
	set_field_back(field[2], COLOR_PAIR(7));
	set_field_fore(field[2], COLOR_PAIR(7));
	set_field_buffer(field[2], 0, " LOGIN ");
	if(key != 1){
		field[3] = new_field(1, 20, 13, 50, 0, 0);
		field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
		set_field_back(field[3], COLOR_PAIR(7));
		set_field_fore(field[3], COLOR_PAIR(7));
		set_field_buffer(field[3], 0, " Change Password ");
		field[4] = NULL;
	}
	else
		field[3] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, x, y, 1, 80));
	
	post_form(form);
	wattron(form1 ,A_BOLD);
	if( key == 2)
		mvwprintw(form1,5,50,"MANAGER LOGIN");
	if( key == 0)
		mvwprintw(form1,5,50,"ADMIN LOGIN");
	if( key == 1)
		mvwprintw(form1,5,50,"EMPLOYEE LOGIN");
	mvwprintw(form1, 7, 40, "%s: ", field_names[0]);
	mvwprintw(form1, 9, 40, "%s: ", field_names[1]);
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
						if(field[3] == current_field(form)){
							wattron(form1 ,A_BOLD);
							wattroff(form1 ,A_BOLD);
							unpost_form(form);
							i = newpass(form1,key);
							if(i == 1){
								unpost_form(form);
								printlogin(form1,key);
								break;
							}
						}
						if(field[2] == current_field(form)){
							i = check(field_buffer(field[0], 0),field_buffer(field[1], 0),key);
							if(i == 0){
								form_driver(form, REQ_CLR_FIELD);
								wattron(form1 ,A_BOLD);
								mvwprintw(form1, 14, 40, "%s", "Enter correct ID or Password");
								i = 0;
								while( i < size ) 
									set_field_buffer(field[i++], 0, "");
								wattroff(form1 ,A_BOLD);
							}
							else{
								flag = 1;
								goto end;
								break;
							}
						}
						
						break;	
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
	
	return flag;
}

//destroying the given window
void destroy_win(WINDOW *my_win2){
	wclear(my_win2);
	wbkgd(my_win2,COLOR_PAIR(9));
	wrefresh(my_win2);
	delwin(my_win2);
}
//printing home 
void print_home(WINDOW *my_win2){
	my_win2 =newwin(20, 125, 15, 10);	// creating a window
	box(my_win2, 0 , 0);	
	wbkgd(my_win2, COLOR_PAIR(2));
	wattron(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	mvwprintw(my_win2,7,48,"WELCOME TO EMPLOYEE MANAGEMENT SYSTEM");
	mvwprintw(my_win2,8,55,"FOR SUPPORT AND QUERIES");	
	mvwprintw(my_win2,9,56,"CONTACT : 8237824147");	
	mvwprintw(my_win2,10,48, "EMAIL: shubhamkhandelwal18@gmail.com");	
	wattroff(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	wrefresh(my_win2);
}
//creating the window and login program
int create(WINDOW *my_win2,int key){
	int i=0;	
	my_win2 =newwin(20, 125, 15, 10);	//  creating window
	box(my_win2, 0 , 0);	
	wbkgd(my_win2, COLOR_PAIR(2));	
	wrefresh(my_win2);						
	i = printlogin(my_win2,key);
	wclear(my_win2);
	wbkgd(my_win2,COLOR_PAIR(9));
	wrefresh(my_win2);
	delwin(my_win2);
	return i;
}		
//integer to string
char *tostring(char str[],int num){
	int i, rem, len = 0, n;
	n = num;
	while (n != 0){
		len++;
		n /= 10;
	}
	for (i = 0; i < len; i++){
		rem = num % 10;
		num = num / 10;
		str[len - (i + 1)] = rem + '0';
	}
	str[len] = '\0';
	return str;
}



