/*****************************************************************************
 * Copyright (C) SHUBHAM KHANDELWAL shubhamkhandelwal18@gmail.com
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 *****************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<menu.h>
#include<form.h>
#include<ctype.h>
#include<time.h>
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
	init_pair(5, COLOR_BLUE, COLOR_BLACK);
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
	box(my_win1, 0 , 0);
	set_menu_fore(my_menu,COLOR_PAIR(4) | A_REVERSE);
	set_menu_back(my_menu,COLOR_PAIR(5));
	set_menu_grey(my_menu,COLOR_PAIR(2));
	box(my_win2, 0 , 0);
	
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
						log = create(my_win2,0);
						if(log != 0){
							admin();
							create(my_win2,0);
						}			
						print_home(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"EMPLOYEE LOGIN") == 0 ) {
						log = create(my_win2,1);
						if(log != 0){
							employee(log);
							create(my_win2,1);
						}
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
/************************************************** ADMIN LOGIN **************************************************************/
void admin(){
	WINDOW *my_win1, *my_win2;
	char *choices[] = {
                        "HOME", "LEAVE REQUESTS", "SEARCH", "LOGOUT"
                  };
	int c,ch, x, y,n_choices, i;
	ITEM **my_items;				
	MENU *my_menu;
	my_win1 =newwin(8, 20, 8, 4);	
	box(my_win1, 0 , 0);
	init_pair(18,COLOR_BLACK,COLOR_BLACK);
	wbkgd(my_win1, COLOR_PAIR(18));
	wrefresh(my_win1);
	init_pair(3, COLOR_RED, COLOR_WHITE);

	my_win2 =newwin(30, 110, 8,26);	
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
        set_menu_sub(my_menu, derwin(my_win1,1,80,1,12));
	set_menu_format(my_menu, 7, 1);
	set_menu_mark(my_menu, " * ");

	set_menu_fore(my_menu,COLOR_PAIR(4) | A_REVERSE);
	set_menu_back(my_menu,COLOR_PAIR(5));
	set_menu_grey(my_menu,COLOR_PAIR(2));
	wattron(my_win2 ,COLOR_PAIR(3)| A_BOLD);
	destroy_win(my_win2);
	my_win2 =newwin(20, 125, 15, 10);	// creating a window
	box(my_win2, 0 , 0);	
	wbkgd(my_win2, COLOR_PAIR(2));
	printhome2(my_win2);
		
	wattroff(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	post_menu(my_menu);
	wrefresh(my_win1);
	wrefresh(my_win2);
	menu_driver(my_menu, REQ_FIRST_ITEM);
	while((ch = wgetch(my_win1)) != KEY_F(1)){
		switch(ch){	
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10:
				if(strcmp(item_name(current_item(my_menu)),"HOME") == 0 ) {
					destroy_win(my_win2);
					my_win2 =newwin(20, 125, 15, 10);	// creating a window
					box(my_win2, 0 , 0);	
					wbkgd(my_win2, COLOR_PAIR(2));
					printhome2(my_win2);
				}
				if(strcmp(item_name(current_item(my_menu)),"LEAVE REQUESTS") == 0 ) {
					destroy_win(my_win2);
					my_win2 =newwin(30, 110, 8,26);	// creating a window
					box(my_win2, 0 , 0);	
					wbkgd(my_win2, COLOR_PAIR(2));
					leavereq(my_win2);
					destroy_win(my_win2);
					my_win2 =newwin(20, 125, 15, 10);	// creating a window
					box(my_win2, 0 , 0);	
					wbkgd(my_win2, COLOR_PAIR(2));
					printhome2(my_win2);
				
				}
				else if(strcmp(item_name(current_item(my_menu)),"SEARCH") == 0 ) {
					destroy_win(my_win2);
					search_admin();
					my_win2 =newwin(20, 125, 15, 10);	
					box(my_win2, 0 , 0);	
					wbkgd(my_win2, COLOR_PAIR(2));
					printhome2(my_win2);
				}
				else if(strcmp(item_name(current_item(my_menu)),"LOGOUT") == 0 ) {
					unpost_menu(my_menu);
        				free_menu(my_menu);					
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
/* LEAVE REQUEST CODE */
void leavereq(WINDOW *form1){
	FILE *fp,*fp1;
	char *ch1,ch2[30],*ch3 = "    ",*ch4;
	int i, count = 0, size = 10,l,ch = 0, j = 0, x, y,flag = 0;
	fp = fopen("leave.txt","r");
	leave *t1;
	FIELD **field;
	FORM *form;
	t1 = (leave *)malloc(sizeof(leave)*size);
	while(1){
		fread(&t1[count],sizeof(leave),1,fp);
		if(feof(fp))
			break;
		count++;
		if(count == size) {
			size *= 2;
			t1 = (leave *)realloc(t1, sizeof(leave) * size);
		}
	}
	l = count;
	cbreak();
	keypad(form1, TRUE);
	init_pair(15, COLOR_CYAN, COLOR_WHITE);	
	init_pair(12, COLOR_YELLOW, COLOR_BLACK);
	field = (FIELD**)malloc((count + 1) * sizeof(FIELD*));
	init_pair(30, COLOR_RED, COLOR_GREEN);
	i = 0;
	while(i < count){
		field[i] = new_field(1, 6, 4 + 2 * i, 80, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
		set_field_back(field[i], COLOR_PAIR(30));
		set_field_fore(field[i], COLOR_PAIR(30));
		ch1 = tostring(ch2,t1[i].Id);
		set_field_buffer(field[i], 0, ch1);
		i++;
	}
	field[i] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0,80));
	i = 0;
	post_form(form);
	wrefresh(form1);
	while(i < count) {
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(form1, 4 + 2 * i, 5 , "%d ", t1[i].Id);
		mvwprintw(form1, 4 + 2 * i, 15 , "%s", t1[i].name);		
		wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	box(form1, 0 , 0);
	wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
	mvwprintw(form1,2,45,"LEAVE REQUESTS");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	wrefresh(form1);
	form_driver(form, REQ_FIRST_FIELD);
	while(i = wgetch(form1)){
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else{
			switch(i){
				case KEY_DOWN:
					if(flag == (count-1)){
						form_driver(form, REQ_PREV_FIELD);
						flag--;
						break;
					}
					else{
						form_driver(form, REQ_NEXT_FIELD);
						flag++;
						break;
					}
				case KEY_UP:
					if(flag == 0){
						form_driver(form, REQ_NEXT_FIELD);
						flag++;
						break;
					}
					else{
						form_driver(form, REQ_PREV_FIELD);
						flag--;
						break;
					}
				case 27:
					goto end;
					break;
				case 10:
					if(field[flag] == current_field(form)){
						destroy_win(form1);
						form1 =newwin(35, 110, 8,26);
						box(form1, 0 , 0);
						wbkgd(form1, COLOR_PAIR(2));
						leaveform(form1,field_buffer(field[flag], 0),t1[flag]);
						destroy_win(form1);
						form1 =newwin(30, 110, 8,26);	// creating a window
						box(form1, 0 , 0);	
						wbkgd(form1, COLOR_PAIR(2));
						leavereq(form1);
						destroy_win(form1);
						form1 =newwin(20, 125, 15, 10);	
						box(form1, 0 , 0);	
						wbkgd(form1, COLOR_PAIR(2));
						printhome2(form1);
					}
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
		i++;
	}
	free_field(field[0]);
	free(field);
	box(form1, 0, 0);
	wrefresh(form1);
	free(t1);
	fclose(fp);
}
/* leave confirmation by admin */
void leaveform(WINDOW *form1,char *str,leave t){
	FILE *fp;
	emp t1;
	FIELD **field;
	FORM *form;
	char *ch3, a[10];
	int ch = 0, i = 0, j = 0, x, y, size, flag=0, c = 0;
	char *field_names[] = {"Employee-ID", "NAME","LEAVE TYPE","FROM","TO","DAYS","REASON"};
	fp = fopen("database.txt","r+");
	while( fread(&t1,sizeof(emp),1,fp) ){
		if(t1.Id == t.Id)
			break;
	}
	str = (char *)malloc(sizeof(char) * 31);
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(form1, TRUE);
	init_pair(15, 92, COLOR_WHITE);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	field = (FIELD**)malloc((size + 3) * sizeof(FIELD*));
	while(i < size) {	
		field[i] = new_field(1, 30, 5 + 3 * i, 55, 0, 0);
		field[1] = new_field(1, 30, 5 + 3 * 1, 55, 0, 0);
		field[6] = new_field(3, 30, 5 + 3 * 6, 55, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP|O_EDIT);
		set_field_back(field[i], COLOR_PAIR(12));
		set_field_fore(field[i], COLOR_PAIR(12));	
		i++;
	}
	if(t1.seen == 0){
		field[i] = new_field(1, 10, 28, 40,0, 0);
		field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
		set_field_back(field[i], COLOR_PAIR(7));
		set_field_fore(field[i], COLOR_PAIR(7));
		set_field_buffer(field[i], 0, " ACCEPT ");
		i++;
		field[i] = new_field(1, 10, 28, 52, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
		set_field_back(field[i], COLOR_PAIR(7));
		set_field_fore(field[i], COLOR_PAIR(7));
		set_field_buffer(field[i], 0, " REJECT ");
		field[++i] = NULL;
	}
	else{
		field[i] = NULL;
	}
	ch3 = tostring(a,t.Id);
	set_field_buffer(field[0], 0,ch3);
	set_field_buffer(field[1], 0,t.name);
	set_field_buffer(field[2], 0,t.leave);
	set_field_buffer(field[3], 0,t.from);
	set_field_buffer(field[4], 0,t.to);
	ch3 = tostring(a,t.day);
	set_field_buffer(field[5], 0,ch3);
	set_field_buffer(field[6], 0,t.reason);
	form = new_form(field);
	scale_form(form, &y, &x);
	set_field_back(field[1], COLOR_PAIR(12));
	set_field_fore(field[1], COLOR_PAIR(12));
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0, 80));
	form_driver(form, REQ_FIRST_FIELD);
	post_form(form);
	i = 0;
	if(t1.seen != 0){
		if(t1.request == 0){
			wattron(form1 ,A_BOLD | COLOR_PAIR(15));
			mvwprintw(form1,  28, 40, "LEAVE HAS BEEN REJECTED");
			wattroff(form1 ,A_BOLD | COLOR_PAIR(15));
		}
		else{
			wattron(form1 ,A_BOLD | COLOR_PAIR(15));
			mvwprintw(form1,  28, 40, "LEAVE HAS BEEN ACCEPTED");
			wattroff(form1 ,A_BOLD | COLOR_PAIR(15));
		}
	}
	while(i < size){
		if(i == 3){
			wattron(form1 ,COLOR_PAIR(15));
			mvwprintw(form1,  6 + 3 * i, 55, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}	
		if(i == 2){
			wattron(form1 ,COLOR_PAIR(15));
			mvwprintw(form1,  6 + 3 * i, 44, "(SICK/UNPAID LEAVE/PERSONAL LEAVE/BEREAVEMENT/OTHERS)");
			wattroff(form1 ,COLOR_PAIR(15));
		}	
		if(i == 3||i == 4){
			wattron(form1 ,COLOR_PAIR(15));	
			mvwprintw(form1, 6 + 3 * i, 55, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);	
		mvwprintw(form1,  5 + 3 * i, 25, "%s : ", field_names[i]);
		wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
	mvwprintw(form1,2,50,"LEAVE REQUEST");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	wrefresh(form1);
	form_driver(form, REQ_FIRST_FIELD);	
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
				case 27:
					goto end;
					break;
				case 10:
					if(field[7] == current_field(form)){
						t1.seen = 1;
						t1.request = 1;
						t1.count = t1.count - t.day;
						t1.holidays[t1.counter] = t.day;
						t1.counter++;
						fseek(fp,-sizeof(emp),SEEK_CUR);
						fwrite(&t1,sizeof(emp),1,fp);
						goto end;
						break;
					}
					if(field[8] == current_field(form)){
						t1.seen = 1;
						t1.request = 0;
						fseek(fp,-sizeof(emp),SEEK_CUR);
						fwrite(&t1,sizeof(emp),1,fp);
						goto end;
						break;
					}
					else {
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
					}
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
	fclose(fp);
	return;
}
/* SEARCH */
void search_admin(){
	WINDOW *my_win1, *my_win2,*my_win3;	
	char *choice1[]={"ID","NAME","AGE","EMAIL-ID","CONTACT"};
	int place[]={4,12,38,50,88}; 
	int ch, x, y, c, i = 0, size, flag=0, j = 0;		
	FIELD **field;
	FORM *form;
        char *str;
	str = (char *)malloc(sizeof(char)*21);
	while(j< 20){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	init_pair(3, COLOR_RED, COLOR_WHITE);
	init_pair(20, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	
	my_win2 =newwin(30, 100, 13,30);
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	
	my_win1 =newwin(2, 100, 11, 30);
	wbkgd(my_win1, COLOR_PAIR(2));
	while(i < 5){
		wattron(my_win1,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(my_win1, 0,place[i], "%s", choice1[i]);
		wattroff(my_win1,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	wrefresh(my_win1);
	wrefresh(my_win2);
	my_win3 =newwin(5,25,20,1);
	box(my_win3, 0 , 0);	
	wbkgd(my_win3, COLOR_PAIR(20));	
	wrefresh(my_win3);
	cbreak();
	keypad(my_win3, TRUE);
	field = (FIELD**)malloc(2 * sizeof(FIELD*));
	field[0] = new_field(1, 20, 0, 0, 0, 0);
	field_opts_off(field[0], O_AUTOSKIP);
	set_field_back(field[0], COLOR_PAIR(6));
	set_field_fore(field[0], COLOR_PAIR(6));
	field[1] = NULL;
	wattron(my_win3 ,A_BOLD);
	mvwprintw(my_win3,1,10,"NAME");
	wattroff(my_win3 ,A_BOLD);
	form = new_form(field);
	scale_form(form, &y, &x);
	set_form_win(form, my_win3);
	set_form_sub(form, derwin(my_win3, 1,20, 3, 2));
	post_form(form);
	wrefresh(my_win3);
	form_driver(form, REQ_FIRST_FIELD);
	display1(my_win2);
	while(i = wgetch(my_win3)) {
		if(isprint(i) || (i == ' ') || (i == '\t') ){
			form_driver(form, i);
			form_driver(form, REQ_END_LINE);
			destroy_win(my_win2);
			my_win2 =newwin(30, 100, 13,30);	
			wbkgd(my_win2, COLOR_PAIR(2));
			wrefresh(my_win2);
			compare_admin(my_win2,field_buffer(field[0],0));
		}
		else {
			switch(i) {
				case KEY_LEFT:
					form_driver(form, REQ_PREV_CHAR);
					break;
				case KEY_RIGHT:
					form_driver(form, REQ_NEXT_CHAR);
					break;
				case 27:
					goto end;
					break;
				case KEY_BACKSPACE:
					destroy_win(my_win2);
					my_win2 =newwin(30, 100, 13,30);	
					wbkgd(my_win2, COLOR_PAIR(2));
					wrefresh(my_win2);
					form_driver(form, REQ_DEL_PREV);
					form_driver(form, i);
					form_driver(form, REQ_END_LINE);
					compare_admin(my_win2,field_buffer(field[0],0));
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
	wclear(my_win3);
	i = 0;
	while(i < 1) {
		wmove(my_win3, 3 + 2 * i, 1);
		wclrtoeol(my_win3);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(my_win3, 0, 0);
	wrefresh(my_win3);
	destroy_win(my_win3);
	destroy_win(my_win2);
	destroy_win(my_win1);

}

/* compare function in admin login */
void compare_admin(WINDOW *my_win2,char *str){
	destroy_win(my_win2);
	my_win2 =newwin(30, 100, 13,30);
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	FILE *fp;
	fp = fopen(fname1, "rb");
	emp t1;
	int  j = 0, l = 0,place[]={4,12,38,50,88};
	char *ch1 = space(str),*ch2,ch4[30];
	init_pair(20, COLOR_RED, COLOR_WHITE);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	cbreak();
	keypad(my_win2, TRUE);
	attron(COLOR_PAIR(20) | A_BOLD);
	l = strlen(ch1);
	while(fread(&t1,sizeof(emp),1,fp)){
		if(strncasecmp(t1.fname,ch1,l) == 0){
				wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
				mvwprintw(my_win2, j,place[0],"%d", t1.Id);
				mvwprintw(my_win2, j,place[1],"%s", t1.fname);
				mvwprintw(my_win2, j,(place[1]+strlen(t1.fname)+1) ,"%s", t1.lname);
				mvwprintw(my_win2, j,place[2],"%d", t1.age);
				mvwprintw(my_win2, j,place[3],"%s", t1.email);
				mvwprintw(my_win2, j,place[4] ,"%s", t1.contact);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wrefresh(my_win2);
				j++;
		}
	}
	fclose(fp);
}


/**************************************************** EMPLOYEE LOGIN ******************************************************/
void employee(int key){
	WINDOW *my_win1, *my_win2;
	char *choices[] = {
                        "HOME", "PROFILE", "LEAVE APPLICATION" , "SEARCH","LOGOUT"
                  };
	int ch, x, y;
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i;
	my_win1 =newwin(8, 20, 8, 4);	
	box(my_win1, 0 , 0);
	init_pair(18,COLOR_BLACK,COLOR_BLACK);
	wbkgd(my_win1, COLOR_PAIR(18));
	wrefresh(my_win1);
	init_pair(3, COLOR_RED, COLOR_WHITE);

	my_win2 =newwin(30, 110, 8,26);	
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
        set_menu_sub(my_menu, derwin(my_win1,1,80,1,12));
	set_menu_format(my_menu, 7, 1);
	set_menu_mark(my_menu, " * ");

	set_menu_fore(my_menu,COLOR_PAIR(4) | A_REVERSE);
	set_menu_back(my_menu,COLOR_PAIR(5));
	set_menu_grey(my_menu,COLOR_PAIR(2));
	wattron(my_win2 ,COLOR_PAIR(3)| A_BOLD);
	mvwprintw(my_win2,15,50,"WELCOME");
	destroy_win(my_win2);
	my_win2 =newwin(20, 125, 15, 10);	// creating a window
	box(my_win2, 0 , 0);	
	wbkgd(my_win2, COLOR_PAIR(2));
	printhome2(my_win2);
		
	wattroff(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	post_menu(my_menu);
	wrefresh(my_win1);
	wrefresh(my_win2);
	menu_driver(my_menu, REQ_FIRST_ITEM);
	while((ch = wgetch(my_win1)) != KEY_F(1))
		{       switch(ch)
		        {	
				case KEY_DOWN:
					menu_driver(my_menu, REQ_DOWN_ITEM);
					break;
				case KEY_UP:
					menu_driver(my_menu, REQ_UP_ITEM);
					break;
				case 10:
					if(strcmp(item_name(current_item(my_menu)),"HOME") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);	// creating a window
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
					}
					if(strcmp(item_name(current_item(my_menu)),"PROFILE") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(30, 110, 8,26);	// creating a window
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						profile(my_win2,key);
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);	
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"LEAVE APPLICATION") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);	
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						wrefresh(my_win2);
						app(my_win2,key,0);
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);	
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"SEARCH") == 0 ) {
						destroy_win(my_win2);
						search_employee();
						my_win2 =newwin(20, 125, 15, 10);	
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
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
/* PROFILE OF EMPLOYEE */
void profile(WINDOW *form1,int key){
	FILE *fp;
	emp t;
	fp = fopen(fname1,"r");
	while(fread(&t,sizeof(emp),1,fp)){
		if(t.Id == key)
			break;
	}
	fclose(fp);
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, j = 0, x, y, size; 
	char **ch4,*ch1,*ch2,ch3[30],*str , *field_names[] = {"Employee-ID", "First-Name","Last-Name","D.O.B","Age","Mobile-no.","Email-Id","Joining-Date"};
	str = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(form1, TRUE);
	init_pair(15, COLOR_CYAN, COLOR_WHITE);	
	init_pair(12, COLOR_YELLOW, COLOR_BLACK);
	field = (FIELD**)malloc(2 * sizeof(FIELD*));
	while(i < size) {
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(form1, 5 + 2 * i, 15, "%s : ", field_names[i]);		
		wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	init_pair(30, COLOR_RED, COLOR_GREEN);
	field[0] = new_field(1, 10, 20, 10, 0, 0);
	field_opts_off(field[0], O_AUTOSKIP | O_EDIT);
	set_field_back(field[0], COLOR_PAIR(30));
	set_field_fore(field[0], COLOR_PAIR(30));
	set_field_buffer(field[0], 0, "  EDIT");
	wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
	mvwprintw(form1,3,40,"PROFILE");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	field[1] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0, 80));
					
	ch2 = tostring(ch3,t.Id);
	wattron(form1 ,COLOR_PAIR(12)|A_STANDOUT| A_BOLD);
	mvwprintw(form1, 5 , 50, "      %s      ",ch2);
	mvwprintw(form1, 5 + 2 * 1, 50, "      %s      ",t.fname);
	mvwprintw(form1, 5 + 2 * 2, 50, "      %s      ",t.lname);
	mvwprintw(form1, 5 + 2 * 3, 50, "      %s      ",t.dob);
	ch2 = tostring(ch3,t.age);
	mvwprintw(form1, 5 + 2 * 4, 50, "      %s      ",ch2);
	mvwprintw(form1, 5 + 2 * 5, 50, "      %s      ",t.contact);
	mvwprintw(form1, 5 + 2 * 6, 50, " %s ",t.email);
	mvwprintw(form1, 5 + 2 * 7, 50, "      %s      ",t.join);
	wattroff(form1 ,COLOR_PAIR(12)|A_STANDOUT| A_BOLD);
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
					if(field[0] == current_field(form)) {
						destroy_win(form1);
						form1 =newwin(30, 110, 8,26);	// creating a window
						box(form1, 0 , 0);	
						wbkgd(form1, COLOR_PAIR(2));
						mod2(form1,t);
						destroy_win(form1);
						form1 =newwin(30, 110, 8,26);	// creating a window
						box(form1, 0 , 0);	
						wbkgd(form1, COLOR_PAIR(2));
						profile(form1,key);
							
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
		i++;
	}
	free_field(field[0]);
	free(field);
	box(form1, 0, 0);
	wrefresh(form1);
	destroy_win(form1);
	form1 =newwin(20, 125, 15, 10);	
	box(form1, 0 , 0);	
	wbkgd(form1, COLOR_PAIR(2));
	printhome2(form1);
	return;
}
/* EDIT INFO OF EMPLOYEE BYE EMPLOYEE */
void mod2(WINDOW *form1, emp t){
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, j = 0, x, y, size; 
	char **ch4,*ch1,*ch2,ch3[30],*str , *field_names[] = {"Employee-ID", "First-Name","Last-Name","D.O.B","Age","Mobile-no.","Email-Id","Joining-Date"};
	str = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(form1, TRUE);
	init_pair(15, COLOR_CYAN, COLOR_WHITE);	
	init_pair(12, COLOR_BLACK, COLOR_BLUE);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(form1, 5 + 2 * i, 15, "%s : ", field_names[i]);		
		field[i] = new_field(1, 30, 5 + 2 * i, 0, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP);
		set_field_back(field[i], COLOR_PAIR(12));
		set_field_fore(field[i], COLOR_PAIR(12));
		wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);		
		i++;
	}
	field_opts_off(field[0], O_AUTOSKIP|O_EDIT);
	field_opts_off(field[3], O_AUTOSKIP|O_EDIT);
	field_opts_off(field[7], O_AUTOSKIP|O_EDIT);
	init_pair(30, COLOR_RED, COLOR_GREEN);
	field[i] = new_field(1, 10, 22, 8, 0, 0);
	field_opts_off(field[i], O_AUTOSKIP|O_EDIT);
	set_field_back(field[i], COLOR_PAIR(30));
	set_field_fore(field[i], COLOR_PAIR(30));
	set_field_buffer(field[i], 0, "   DONE");
	wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
	mvwprintw(form1,3,40," EDIT INFO");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	field[++i] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0, 60));				
	ch2 = tostring(ch3,t.Id);
	set_field_buffer(field[0], 0,ch2);
	set_field_buffer(field[1], 0, t.fname);
	set_field_buffer(field[2], 0, t.lname);
	set_field_buffer(field[3], 0, t.dob);
	ch2 = tostring(ch3,t.age);
	set_field_buffer(field[4], 0, ch2);
	set_field_buffer(field[5], 0, t.contact);
	set_field_buffer(field[6], 0, t.email);
	set_field_buffer(field[7], 0, t.join);
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
						modit(form,field,t);
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
						return;
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
/* SEARCH */
void search_employee(){
	WINDOW *my_win1, *my_win2,*my_win3,*my_win4;
	char *choice1[]={"NAME","EMAIL-ID","CONTACT"};
	int place[]={4,40,80}; 
	int ch = 0, x, y, c, i = 0, size, flag=0, j = 0;
	FIELD **field;
	FORM *form;
        char *str;
	str = (char *)malloc(sizeof(char)*21);
	while(j< 20){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	init_pair(3, COLOR_RED, COLOR_WHITE);
	init_pair(20, COLOR_BLACK, COLOR_WHITE);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	my_win2 =newwin(35, 100, 11,30);
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	my_win1 =newwin(2, 100, 9, 30);
	wbkgd(my_win1, COLOR_PAIR(2));
	while(i < 3){
		wattron(my_win1,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(my_win1, 0,place[i], "%s", choice1[i]);
		wattroff(my_win1,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	wrefresh(my_win1);	
	my_win3 =newwin(5,25,20,1);
	box(my_win3, 0 , 0);	
	wbkgd(my_win3, COLOR_PAIR(20));	
	wrefresh(my_win3);
	cbreak();
	keypad(my_win3, TRUE);
	field = (FIELD**)malloc(2 * sizeof(FIELD*));
	field[0] = new_field(1, 20, 0, 0, 0, 0);
	field_opts_off(field[0], O_AUTOSKIP);
	set_field_back(field[0], COLOR_PAIR(6));
	set_field_fore(field[0], COLOR_PAIR(6));
	field[1] = NULL;
	wattron(my_win3 ,A_BOLD);
	mvwprintw(my_win3,1,10,"NAME");
	wattroff(my_win3 ,A_BOLD);
	form = new_form(field);
	scale_form(form, &y, &x);
	set_form_win(form, my_win3);
	set_form_sub(form, derwin(my_win3, 1,20, 3, 2));
	post_form(form);
	wrefresh(my_win3);
	form_driver(form, REQ_FIRST_FIELD);
	display1_employee(my_win2);
	while(i = wgetch(my_win3)) {
		if(isprint(i) || (i == ' ') || (i == '\t') ){
			form_driver(form, i);
			form_driver(form, REQ_END_LINE);
			destroy_win(my_win2);
			my_win2 =newwin(35, 100, 11,30);	
			wbkgd(my_win2, COLOR_PAIR(2));
			wrefresh(my_win2);
			compare_employee(my_win2,field_buffer(field[0],0));
		}
		else {
			switch(i) {
				case KEY_LEFT:
					form_driver(form, REQ_PREV_CHAR);
					break;
				case KEY_RIGHT:
					form_driver(form, REQ_NEXT_CHAR);
					break;
				case 27:
					goto end;
					break;
				case KEY_BACKSPACE:
					destroy_win(my_win2);
					my_win2 =newwin(35, 100, 11,30);	
					wbkgd(my_win2, COLOR_PAIR(2));
					wrefresh(my_win2);
					form_driver(form, REQ_DEL_PREV);
					form_driver(form, i);
					form_driver(form, REQ_END_LINE);
					compare_employee(my_win2,field_buffer(field[0],0));
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
	wclear(my_win3);
	i = 0;
	while(i < 1) {
		wmove(my_win3, 3 + 2 * i, 1);
		wclrtoeol(my_win3);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(my_win3, 0, 0);
	wrefresh(my_win3);
	destroy_win(my_win3);
	destroy_win(my_win2);
	destroy_win(my_win1);

}
/* compare function in employee login */
void compare_employee(WINDOW *my_win2,char *str){
	destroy_win(my_win2);
	my_win2 =newwin(35, 100, 11,30);
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	FILE *fp;
	fp = fopen(fname1, "rb");
	emp t1;
	int  j = 0, l = 0,place[]={4,40,80};;
	char *ch1 = space(str),*ch2,ch4[30];
	init_pair(20, COLOR_RED, COLOR_WHITE);
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	cbreak();
	keypad(my_win2, TRUE);
	attron(COLOR_PAIR(20) | A_BOLD);
	l = strlen(ch1);
	while(fread(&t1,sizeof(emp),1,fp)){
		if(strncasecmp(t1.fname,ch1,l) == 0){
			wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
			mvwprintw(my_win2, j,place[0],"%s", t1.fname);
			mvwprintw(my_win2, j,(place[0]+strlen(t1.fname)+1) ,"%s", t1.lname);
			mvwprintw(my_win2, j,place[1],"%s", t1.email);
			mvwprintw(my_win2, j,place[2] ,"%s", t1.contact);
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wrefresh(my_win2);
			j++;
		}
	}
	fclose(fp);
}
/* display the list */
void display1_employee(WINDOW *my_win2){
	int ch = 0,i = 0, j = 0, l = 0, count = 0, size = 100,n1 = 0,n2 = 30,flag = 0;
	int place[]={4,40,80}; 
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	FILE *fp;
	emp *t1;
	cbreak();
	keypad(my_win2, TRUE);
	t1 = (emp *)malloc(sizeof(emp)*size);
	fp = fopen(fname1, "rb");
	while(1){
		fread(&t1[count],sizeof(emp),1,fp);
		if(feof(fp))
			break;
		count++;
		if(count == size) {
			size *= 2;
			t1 = (emp *)realloc(t1, sizeof(emp) * size);
		}
	}
	l = count;
	if(l < 30){
		j = 0;
		i = 0;
		while(i < l){
			wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
			mvwprintw(my_win2, j,place[0],"%s", t1[i].fname);
			mvwprintw(my_win2, j,(place[0]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
			mvwprintw(my_win2, j,place[1],"%s", t1[i].email);
			mvwprintw(my_win2, j,place[2] ,"%s", t1[i].contact);
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wrefresh(my_win2);
			j++;
			i++;
		}
		free(t1);
		return;
	}
	else{
		i = 0;
		j = 0;
		while(i < 30){
			wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
			mvwprintw(my_win2, j,place[0],"%s", t1[i].fname);
			mvwprintw(my_win2, j,(place[0]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
			mvwprintw(my_win2, j,place[1],"%s", t1[i].email);
			mvwprintw(my_win2, j,place[2] ,"%s", t1[i].contact);			
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wrefresh(my_win2);
			j++;
			i++;
		}
		while(ch = wgetch(my_win2)){
			
			switch(ch){
				flag = 0;
				case KEY_DOWN:case 81:
					destroy_win(my_win2);
					my_win2 =newwin(35, 100, 11,30);
					wbkgd(my_win2, COLOR_PAIR(2));
					cbreak();
					keypad(my_win2, TRUE);		
					n1 = n1 + 30;
					n2 = n2 + 30;
					if(n2 > l){
						flag = n2 - l;						
						n2 = l;
					}
					i = n1;
					j = 0;				
					while(i < n2){
						wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
						mvwprintw(my_win2, j,place[0],"%s", t1[i].fname);
						mvwprintw(my_win2, j,(place[0]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
						mvwprintw(my_win2, j,place[1],"%s", t1[i].email);
						mvwprintw(my_win2, j,place[2] ,"%s", t1[i].contact);
						wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
						wrefresh(my_win2);
						j++;
						i++;
					}
					break;
					
				case KEY_UP:case 73:
					destroy_win(my_win2);
					my_win2 =newwin(35, 100, 11,30);	
					wbkgd(my_win2, COLOR_PAIR(2));	
					cbreak();
					keypad(my_win2, TRUE);
					n1 = n1 - 30;
					if(n1 < 0){
						n1 = 0;
					}
					if(flag == 0){					
						n2 = n2 - 30;
						if(n2 <= 0){
							n2 = 30;
						}
					}
					else
						n2 = n2 - 30;
					if(n2 % 30 != 0)
						n2 = n2 + flag;			
					i = n1;
					j = 0;				
					while(i < n2){
						wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
						mvwprintw(my_win2, j,place[0],"%s", t1[i].fname);
						mvwprintw(my_win2, j,(place[0]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
						mvwprintw(my_win2, j,place[1],"%s", t1[i].email);
						mvwprintw(my_win2, j,place[2] ,"%s", t1[i].contact);
						wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
						wrefresh(my_win2);
						j++;
						i++;
					}
					break;
				case 27:
					goto end;
					break;		
		
			}
		}
	}	
	end:
	fclose(fp);
	free(t1);
	return;	
}

/* LEAVE APPLICATION CALL */
void app(WINDOW *form1, int key,int p){
	FIELD **field;
	FORM *form;
	FILE *fp;
	emp t;
	leave t1;
	int ch = 0, i = 0, x, y, size, flag=0;
	fp = fopen(fname1,"r");
	while(fread(&t,sizeof(emp),1,fp)){
		if(t.Id == key)
			break;
	}
	fclose(fp);
	fp = fopen("leave.txt","r");
	while(fread(&t1,sizeof(t1),1,fp)){
		if(t1.Id == key){
			flag = 1;
			break;
		}
	}
	init_pair(35,COLOR_YELLOW,COLOR_BLACK);
	wattron(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
	wattroff(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	init_pair(7, COLOR_RED, COLOR_GREEN);
	cbreak();
	keypad(form1, TRUE);
	
	field = (FIELD**)malloc( 2 * sizeof(FIELD*));
	
	field[0] = new_field(1, 30, 8, 40, 0, 0);
	field_opts_off(field[0], O_AUTOSKIP);
	set_field_back(field[0], COLOR_PAIR(6));
	set_field_fore(field[0], COLOR_PAIR(6));
	set_field_buffer(field[0], 0, "  NEW LEAVE APLLICATION ");
	field[1] = NULL;
	
	form = new_form(field);
	scale_form(form, &y, &x);
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, x, y, 1, 80));
	post_form(form);
	init_pair(30,COLOR_RED,COLOR_WHITE);
	init_pair(25, COLOR_GREEN, COLOR_RED);
	wattron(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(30));
	mvwprintw(form1,6,40,"LEAVE APPLICATION");
	form_driver(form, REQ_FIRST_FIELD);	
	wattroff(form1 ,A_BOLD);
	wattron(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
	if(flag == 1){
		if((t.seen==1)&&(t.request==1)){
			mvwprintw(form1,11,80," STATUS : LEAVE REQUEST ACCEPTED   ");
		}
		if((t.seen==1)&&(t.request==0)){
			mvwprintw(form1,11,80," STATUS : LEAVE REQUEST REJECTED    ");		
		}
		if(t.seen==0){
			mvwprintw(form1,11,80,"   STATUS : LEAVE IN-REQUEST      ");
		}
		mvwprintw(form1,12,80," TOTAL NUMBER OF HOLIDAYS LEFT: %d ",t.count);
	}
	else{
		mvwprintw(form1,12,80," NUMBER OF HOLIDAYS LEFT : %d ",t.count);
	}
	if( p==1)
		mvwprintw(form1,12,40,"LEAVE REQUESTED SUCCESSFULLY");
	form_driver(form, REQ_FIRST_FIELD);
	wattroff(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
	box(form1, 0 , 0);
	wrefresh(form1);
	while(i = wgetch(form1)){
		if(isprint(i) || (i == ' ') || (i == '\t') )
			form_driver(form, i);
		else {
			switch(i) {
					case KEY_DOWN:
						form_driver(form, REQ_NEXT_FIELD);
						break;
					case KEY_UP:
						form_driver(form, REQ_PREV_FIELD);
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
						if(field[0] == current_field(form)){
							if(t.count == 0){
								wattron(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
								mvwprintw(form1,12,40,"      NOT ENOUGH LEAVE LEFT       ");
								wattroff(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
								form_driver(form, REQ_FIRST_FIELD);
								wrefresh(form1);
								break;
							}
							if(flag == 1){
								if(t.seen == 0){
									wattron(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
									mvwprintw(form1,12,40,"    LEAVE ALREADY IN-REQUEST    ");
									wattroff(form1 ,A_STANDOUT|A_BOLD|COLOR_PAIR(35));
									form_driver(form, REQ_FIRST_FIELD);
									wrefresh(form1);
									break;
								}
								
							}
							delete1(key);
							destroy_win(form1);
							form1 =newwin(35, 110, 8,26);
							box(form1, 0 , 0);
							wbkgd(form1, COLOR_PAIR(2));
							i = leave1(form1,key,t);
							destroy_win(form1);
							form1 =newwin(20, 125, 15, 10);
							box(form1, 0 , 0);
							wbkgd(form1, COLOR_PAIR(2));
							app(form1,key,i);
						}
						else {
							form_driver(form, REQ_NEXT_FIELD);
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
	while(i < 2) {
		wmove(form1, 3 + 2 * i, 1);
		wclrtoeol(form1);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(form1, 0, 0);
	wrefresh(form1);
	
}
/* DELETE THE LEAVE APPLICATION */
void delete1(int key){
	FILE *fp,*fp1;
	char fnam[] = "leave.txt";
	fp = fopen("leave.txt","r+");
	fp1 = fopen("tmp.txt","w");
	leave t1;
	int pt = 0,c = 0;
	while(1){
		fread(&t1,sizeof(leave),1,fp);
		if(feof(fp)){
			if(pt == 0)
				return;
			break;
		}
		if(key == t1.Id){
			c = 1;
			pt = 1;
		}
		else
			fwrite(&t1,sizeof(leave),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove(fnam);
	rename("tmp.txt",fnam);

}

/* LEAVE FORM */
int leave1(WINDOW *form1,int key,emp t){
	FIELD **field;
	FORM *form;
	char *ch3, a[10];
	int ch = 0, i = 0, j = 0, x, y, size, flag=0, c = 0;
	char *str , *field_names[] = {"Employee-ID", "NAME","LEAVE TYPE","FROM","TO","DAYS","REASON"};
	str = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(form1, TRUE);
	init_pair(15, 92, COLOR_WHITE);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {	
		field[i] = new_field(1, 30, 7 + 3 * i, 55, 0, 0);
		field[1] = new_field(1, 30, 7 + 3 * 1, 55, 0, 0);
		field[6] = new_field(3, 30, 7 + 3 * 6, 55, 0, 0);
		field_opts_off(field[i], O_AUTOSKIP);
		set_field_back(field[i], COLOR_PAIR(12));
		set_field_fore(field[i], COLOR_PAIR(12));	
		i++;
	}
	field[i] = new_field(1, 15, 30, 55, 0, 0);
	field_opts_off(field[i], O_AUTOSKIP | O_EDIT);
	set_field_back(field[i], COLOR_PAIR(7));
	set_field_fore(field[i], COLOR_PAIR(7));
	set_field_buffer(field[i], 0, "    REQUEST");
	
	ch3 = tostring(a,key);
	field_opts_off(field[0], O_AUTOSKIP | O_EDIT);
	field_opts_off(field[1], O_AUTOSKIP | O_EDIT);
	set_field_buffer(field[0], 0,ch3);
	char b[strlen(t.fname)+strlen(t.lname)+2];
	strcpy(b,t.fname);
	strcat(b," ");
	strcat(b,t.lname);
	set_field_buffer(field[1], 0, b);
	set_field_back(field[1], COLOR_PAIR(12));
	set_field_fore(field[1], COLOR_PAIR(12));
	field[++i] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0, 80));
	form_driver(form, REQ_FIRST_FIELD);
	post_form(form);
	i = 0;
	while(i < size){
		if(i == 3){
			wattron(form1 ,COLOR_PAIR(15));
			mvwprintw(form1,  8 + 3 * i, 55, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}	
		if(i == 2){
			wattron(form1 ,COLOR_PAIR(15));
			mvwprintw(form1,  8 + 3 * i, 44, "(SICK/UNPAID LEAVE/PERSONAL LEAVE/BEREAVEMENT/OTHERS)");
			wattroff(form1 ,COLOR_PAIR(15));
		}	
		if(i == 3||i == 4){
			wattron(form1 ,COLOR_PAIR(15));	
			mvwprintw(form1, 8 + 3 * i, 55, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);	
		mvwprintw(form1,  7 + 3 * i, 25, "%s : ", field_names[i]);
		wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
	mvwprintw(form1,4,55,"LEAVE APPLICATION");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	wrefresh(form1);
	form_driver(form, REQ_FIRST_FIELD);	
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
						if(field[7] == current_field(form)){
							flag = 0;						
							i = 0;
							while(i < 6){
								if(i == 1){
									i++;
									continue;
								}
								if(strcmp(field_buffer(field[i], 0), str) == 0 ) {
									mvwprintw(form1, 32, 40,"Form cant be empty ");
									flag = 1;
									break;
								}
								i++;
							}
							if(flag == 0){
								c = leaveadd(form,field,t,b);
								if(c == 0){
									mvwprintw(form1,  32, 40," NOTE ENOUGH HOLIDAYS LEFT ");
									break;
								}
								else{
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
									return c;
								}
							}
						}
						else {
							form_driver(form, REQ_NEXT_FIELD);
							form_driver(form, REQ_END_LINE);
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
	return 0;
}
/* LEAVE FORM ADDING TO A FILE */
int leaveadd(FORM *form,FIELD **field,emp t,char *str){
	FILE *fp, *fp1,*tmp;
	fp = fopen("leave.txt","a+");
	tmp = fopen("tmp.txt","w");
	leave t1,t2;
	emp t3;
	int i = 0,len = field_count(form),j = 0,check = 1;
	char **ch;
	char *ch1,fnam[]="leave.txt";
	ch = (char **)malloc(sizeof(char *) * len);
	while(i < len){
		ch[i] = field_buffer(field[i], 0);
		i++;
	}
	ch1 = space(ch[5]);
	j = atoi(ch1);
	if( j > t.count)
		return 0;
	ch1 = space(ch[0]);
	j = atoi(ch1);
	t1.Id = j;
	strcpy(t1.name,str);
	ch1 = space(ch[2]);
	strcpy(t1.leave,ch1);
	ch1 = space(ch[3]);
	strcpy(t1.from,ch1);
	ch1 = space(ch[4]);
	strcpy(t1.to,ch1);
	ch1 = space(ch[5]);
	j = atoi(ch1);
	t1.day = j;
	strcpy(t1.reason,ch[6]);
	t.seen = 0;
	t.request = 0;
	j = 0;
	if( fp == NULL ){
		fwrite(&t1,sizeof(leave),1,tmp);
		rename("tmp.txt",fname1);
		fclose(tmp);
		free(ch);
		return 1;
	}
	else{
		
		while(1){
			fread(&t2, sizeof(leave), 1, fp);
			if(feof(fp)){
				if(j == 0) 
					fwrite(&t1,sizeof(leave),1,tmp);
			break;
			}
			if((t2.Id < t1.Id)&&check == 1){
            			fwrite(&t2,sizeof(leave), 1, tmp);
				if(feof(fp)) {
					fwrite(&t1,sizeof(leave),1,tmp);
					j = 1;
					break;
				}
				
			}
			else if(check == 1) {
				fwrite(&t1,sizeof(leave),1,tmp);
				fwrite(&t2,sizeof(leave), 1, tmp);
				j = 2;
				check = 2;
			}
			else
				fwrite(&t2,sizeof(leave), 1, tmp);
		}
	}
	remove(fnam);
	rename("tmp.txt",fnam);
	fp1 = fopen(fname1,"r+");
	while(fread(&t3,sizeof(emp),1,fp1)){
		if(t3.Id == t.Id)
			break;
	}
	fseek(fp1,-sizeof(emp),SEEK_CUR);
	fwrite(&t,sizeof(emp),1,fp1);
	fclose(fp1);
	fclose(fp);
	fclose(tmp);
	return 1;
}

/************************************************************ MANAGER LOGIN *********************************************/
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
	
	my_win2 =newwin(20, 125, 15, 10);	
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
	printhome2(my_win2);
		
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
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);	// creating a window
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);	
					}
					
					if(strcmp(item_name(current_item(my_menu)),"SEARCH") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						search();
						my_win2 =newwin(20, 125, 15, 10);	// creating a window
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"EDIT") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						modify(my_win2,2);
						my_win2 =newwin(20, 125, 15, 10);	// creating a window
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"DISPLAY") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(40, 140, 11,2);
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						display(my_win2);
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
					}
					else if(strcmp(item_name(current_item(my_menu)),"DELETE") == 0 ) {
						destroy_win(my_win2);
						my_win2 =newwin(20, 125, 15, 10);
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						dele(my_win2,3);
						my_win2 =newwin(20, 125, 15, 10);	// creating a window
						box(my_win2, 0 , 0);	
						wbkgd(my_win2, COLOR_PAIR(2));
						printhome2(my_win2);
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

/*********************************************************** ADD ************************************************/
/* to create add window */
int add(WINDOW *form1){
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, j = 0, x, y, size, flag=0, c = 0;
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
	init_pair(15, COLOR_CYAN, COLOR_WHITE);
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {
		if(i == 0){
			wattron(form1 ,COLOR_PAIR(15));			
			mvwprintw(form1, 5 + 2 * i, 43, "(digist from 0-9)");
			wattroff(form1 ,COLOR_PAIR(15));
		}	
		if(i == 3){
			wattron(form1 ,COLOR_PAIR(15));
			mvwprintw(form1, 8 + 1 * i, 50, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}		
		if(i == 7){
			wattron(form1 ,COLOR_PAIR(15));	
			mvwprintw(form1, 12 + 1 * i, 50, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);	
		mvwprintw(form1, 5 + 2 * i, 15, "%s : ", field_names[i]);
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
	mvwprintw(form1,2,40,"ADD NEW EMPLOYEE");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	field[++i] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0, 60));
	form_driver(form, REQ_FIRST_FIELD);
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
								mvwprintw(form1, 24, 8,"Form cant be empty               ");
								flag = 1;
								break;
							}
							i++;
						}
						if(flag == 0) {
							c = add_file(form, field);
							if(c == 0)
								mvwprintw(form1, 24, 8, "ID ALREADY EXISTS            ");
							else
								mvwprintw(form1, 24, 8, "Employee Added successfully");
							i = 0;
							while( i < size ) 
								set_field_buffer(field[i++], 0, "");
						}
							form_driver(form, REQ_FIRST_FIELD);
					}
					
					else {
						form_driver(form, REQ_NEXT_FIELD);
						form_driver(form, REQ_END_LINE);
					}
					break;
				default:
					getyx(form1, y, x);
					mvwprintw(form1, 24, 8, "Character not allowed         ");
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
	free(str);
}

		
/* To add to a file */
int add_file(FORM *form, FIELD **field){
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
	while(1){
		fread(&t1,sizeof(emp),1,fp);
		if(feof(fp))
			break;
		if(t1.Id == t.Id)
			return 0;
	}
	fclose(fp);
	fp = fopen(fname1, "r+");
	ch1 = space(ch[1]);
	strcpy(t.fname,ch1);
	ch1 = space(ch[2]);
	strcpy(t.lname,ch1);
	ch1 = space(ch[3]);
	strcpy(t.dob,ch1);
	ch1 = space(ch[4]);
	t.age = atoi(ch1);
	ch1 = space(ch[5]);
	strcpy(t.contact,ch1);
	ch1 = space(ch[6]);
	strcpy(t.email,ch1);
	ch1 = space(ch[7]);
	strcpy(t.join,ch1);
	t.count = 45;
	for(i = 0;i < 30;i++)
		t.holidays[i] = 0;
	t.seen = 0;
	t.request = 0;
	t. counter = 0;
	if( fp == NULL ){
		fwrite(&t,sizeof(emp),1,tmp);
		rename("tmp.txt",fname1);
		fclose(tmp);
		free(ch);
		return 1;
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
	return 1;
}

/***************************************************** DISPLAY **********************************************************/

void display(WINDOW  *my_win2){
	int ch = 0,i = 0, j = 0, l = 0, count = 0, size = 100,n1 = 0,n2 = 30,flag = 0;
	char *choice[]={"ID","NAME","DATEOF-BIRTH","AGE","EMAIL-ID","CONTACT","JOIN-DATE"};
	int place[]={4, 10, 35, 55, 65, 105, 120}; 
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	while(i < 7){
		wattron(my_win2,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(my_win2, 1,place[i], "%s", choice[i]);
		wattroff(my_win2,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	FILE *fp;
	emp *t1;
	cbreak();
	keypad(my_win2, TRUE);
	t1 = (emp *)malloc(sizeof(emp)*size);
	fp = fopen(fname1, "rb");
	while(1){
		fread(&t1[count],sizeof(emp),1,fp);
		if(feof(fp))
			break;
		count++;
		if(count == size) {
			size *= 2;
			t1 = (emp *)realloc(t1, sizeof(emp) * size);
		}
	}
	l = count;
	if(l < 30){
		j = 1;
		i = 0;
		while(i < l){
			wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
			mvwprintw(my_win2, j+1,place[0],"%d", t1[i].Id);
			mvwprintw(my_win2, j+1,place[1],"%s", t1[i].fname);
			mvwprintw(my_win2, j+1,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
			mvwprintw(my_win2, j+1,place[2],"%s", t1[i].dob);
			mvwprintw(my_win2, j+1,place[3],"%d", t1[i].age);
			mvwprintw(my_win2, j+1,place[4],"%s", t1[i].email);
			mvwprintw(my_win2, j+1,place[5] ,"%s", t1[i].contact);
			mvwprintw(my_win2, j+1,place[6],"%s", t1[i].join);
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wrefresh(my_win2);
			j++;
			i++;
		}
		free(t1);
		return;
	}
	else{
		i = 0;
		j = 1;
		while(i < 30){
			wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
			mvwprintw(my_win2, j+1,place[0],"%d", t1[i].Id);
			mvwprintw(my_win2, j+1,place[1],"%s", t1[i].fname);
			mvwprintw(my_win2, j+1,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
			mvwprintw(my_win2, j+1,place[2],"%s", t1[i].dob);
			mvwprintw(my_win2, j+1,place[3],"%d", t1[i].age);
			mvwprintw(my_win2, j+1,place[4],"%s", t1[i].email);
			mvwprintw(my_win2, j+1,place[5] ,"%s", t1[i].contact);
			mvwprintw(my_win2, j+1,place[6],"%s", t1[i].join);
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wrefresh(my_win2);
			j++;
			i++;
		}
		while(ch = wgetch(my_win2)){
			
			switch(ch){
				flag = 0;
				case KEY_DOWN:case 81:
					destroy_win(my_win2);
					my_win2 =newwin(40, 140, 11,2);
					box(my_win2, 0 , 0);	
					wbkgd(my_win2, COLOR_PAIR(2));
					cbreak();
					keypad(my_win2, TRUE);
					i = 0;				
					while(i < 7){
						wattron(my_win2,COLOR_PAIR(3) | A_BOLD);
						mvwprintw(my_win2, 1,place[i], "%s", choice[i]);
						wattroff(my_win2,COLOR_PAIR(3) | A_BOLD);
						i++;
					}				
					n1 = n1 + 30;
					n2 = n2 + 30;
					if(n2 > l){
						flag = n2 - l;						
						n2 = l;
					}
					i = n1;
					j = 1;				
					while(i < n2){
						wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
						mvwprintw(my_win2, j+1,place[0],"%d", t1[i].Id);
						mvwprintw(my_win2, j+1,place[1],"%s", t1[i].fname);
						mvwprintw(my_win2, j+1,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
						mvwprintw(my_win2, j+1,place[2],"%s", t1[i].dob);
						mvwprintw(my_win2, j+1,place[3],"%d", t1[i].age);
						mvwprintw(my_win2, j+1,place[4],"%s", t1[i].email);
						mvwprintw(my_win2, j+1,place[5] ,"%s", t1[i].contact);
						mvwprintw(my_win2, j+1,place[6],"%s", t1[i].join);
						wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
						wrefresh(my_win2);
						j++;
						i++;
					}
					break;
					
				case KEY_UP:case 73:
					destroy_win(my_win2);
					my_win2 =newwin(40, 140, 11,2);
					box(my_win2, 0 , 0);	
					wbkgd(my_win2, COLOR_PAIR(2));	
					cbreak();
					keypad(my_win2, TRUE);
					i = 0;				
					while(i < 7){
						wattron(my_win2,COLOR_PAIR(3) | A_BOLD);
						mvwprintw(my_win2, 1,place[i], "%s", choice[i]);
						wattroff(my_win2,COLOR_PAIR(3) | A_BOLD);
						i++;
					}
					
					n1 = n1 - 30;
					if(n1 < 0){
						n1 = 0;
					}
					if(flag == 0){					
						n2 = n2 - 30;
						if(n2 <= 0){
							n2 = 30;
						}
					}
					else
						n2 = n2 - 30;
					if(n2 % 30 != 0)
						n2 = n2 + flag;			
					i = n1;
					j = 1;				
					while(i < n2){
						wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
						mvwprintw(my_win2, j+1,place[0],"%d", t1[i].Id);
						mvwprintw(my_win2, j+1,place[1],"%s", t1[i].fname);
						mvwprintw(my_win2, j+1,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
						mvwprintw(my_win2, j+1,place[2],"%s", t1[i].dob);
						mvwprintw(my_win2, j+1,place[3],"%d", t1[i].age);
						mvwprintw(my_win2, j+1,place[4],"%s", t1[i].email);
						mvwprintw(my_win2, j+1,place[5] ,"%s", t1[i].contact);
						mvwprintw(my_win2, j+1,place[6],"%s", t1[i].join);
						wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
						wrefresh(my_win2);
						j++;
						i++;
					}
					break;
				case 27:
					goto end;
					break;		
		
			}
		}
	}	
	end:
	fclose(fp);
	free(t1);
	return;	
}	

/************************************************************ SEARCH *******************************************************/

void search(){
	WINDOW *my_win1, *my_win2,*my_win3,*my_win4;
	char *choices[] = {
                        "ID-Number", "SEARCH NAME", "SEARCH AGE" , "EXIT"
                  };
	char *choice1[]={"ID","NAME","AGE","EMAIL-ID","CONTACT"};
	int place[]={4,12,38,50,88}; 
	int ch, x, y;
	ITEM **my_items;
	int c;				
	MENU *my_menu;
        WINDOW *my_menu_win;
        int n_choices, i = 0;
	my_win1 =newwin(5, 20, 12, 5);
	init_pair(18,COLOR_BLACK,COLOR_BLACK);
	wbkgd(my_win1, COLOR_PAIR(18));
	wrefresh(my_win1);
	init_pair(3, COLOR_RED, COLOR_WHITE);

	my_win2 =newwin(30, 100, 13,30);
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	my_win3 =newwin(2, 100, 12, 30);
	wbkgd(my_win3, COLOR_PAIR(2));
	while(i < 5){
		wattron(my_win3,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(my_win3, 0,place[i], "%s", choice1[i]);
		wattroff(my_win3,COLOR_PAIR(3) | A_BOLD);
		i++;
	}
	wrefresh(my_win3);
		
	n_choices = ARRAY_SIZE(choices);
        my_items = (ITEM **)calloc(n_choices, sizeof(ITEM *));
        for(i = 0; i < n_choices; ++i) 
                my_items[i] = new_item(choices[i], choices[i]);
	my_items[i]=(ITEM *)NULL;	

	my_menu = new_menu((ITEM **)my_items);

	menu_opts_off(my_menu, O_SHOWDESC);
        keypad(my_win1, TRUE);

	set_menu_win(my_menu, my_win1);
	
	set_menu_format(my_menu, 7, 1);
	set_menu_mark(my_menu, " * ");

	set_menu_fore(my_menu,COLOR_PAIR(4) | A_REVERSE);
	set_menu_back(my_menu,COLOR_PAIR(5));
	set_menu_grey(my_menu,COLOR_PAIR(2));
	post_menu(my_menu);
	wrefresh(my_win1);
	wrefresh(my_win2);
	menu_driver(my_menu, REQ_FIRST_ITEM);
	display1(my_win2);
	while((ch = getch()) != KEY_F(1)){      
		 switch(ch){	
			case KEY_DOWN:
				menu_driver(my_menu, REQ_DOWN_ITEM);
				break;
			case KEY_UP:
				menu_driver(my_menu, REQ_UP_ITEM);
				break;
			case 10:
				if(strcmp(item_name(current_item(my_menu)),"ID-Number") == 0 ) {
					search1(my_win2,0);
				}
				if(strcmp(item_name(current_item(my_menu)),"SEARCH NAME") == 0 ) {
					search1(my_win2,1);
				}
				else if(strcmp(item_name(current_item(my_menu)),"SEARCH AGE") == 0 ) {
					search1(my_win2,2);
				}
				else if(strcmp(item_name(current_item(my_menu)),"EXIT") == 0 ) {
					unpost_menu(my_menu);
        				free_menu(my_menu);						
					destroy_win(my_win2);
					destroy_win(my_win1);
					destroy_win(my_win3);
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

/* searcH */

void search1(WINDOW *my_win2,int key){
	WINDOW *my_win3;
	my_win3 =newwin(5,25,20,1);
	box(my_win3, 0 , 0);
	init_pair(20, COLOR_BLACK, COLOR_WHITE);	
	wbkgd(my_win3, COLOR_PAIR(20));	
	wrefresh(my_win3);
	cbreak();
	keypad(my_win3, TRUE);
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, x, y, size, flag=0, j = 0;
	field = (FIELD**)malloc(2 * sizeof(FIELD*));
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
	
	char *str;
	str = (char *)malloc(sizeof(char)*21);
	while(j< 20){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	field[0] = new_field(1, 20, 0, 0, 0, 0);
	field_opts_off(field[0], O_AUTOSKIP);
	set_field_back(field[0], COLOR_PAIR(6));
	set_field_fore(field[0], COLOR_PAIR(6));
	field[1] = NULL;
	wattron(my_win3 ,A_BOLD);
	if(key == 1)
		mvwprintw(my_win3,1,10,"NAME");
	else if(key == 0)
		mvwprintw(my_win3,1,10,"ID");
	else if(key == 2)
		mvwprintw(my_win3,1,10,"AGE");	
	wattroff(my_win3 ,A_BOLD);
	form = new_form(field);
	scale_form(form, &y, &x);
	set_form_win(form, my_win3);
	set_form_sub(form, derwin(my_win3, 1,20, 3, 2));
	post_form(form);
	wrefresh(my_win3);
	form_driver(form, REQ_FIRST_FIELD);
	destroy_win(my_win2);
	my_win2 =newwin(30, 100, 13,30);
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	display1(my_win2);
	while(i = wgetch(my_win3)) {
		if(isprint(i) || (i == ' ') || (i == '\t') ){
			form_driver(form, i);
			form_driver(form, REQ_END_LINE);
			destroy_win(my_win2);
			my_win2 =newwin(30, 100, 13,30);	
			wbkgd(my_win2, COLOR_PAIR(2));
			wrefresh(my_win2);
			compare(my_win2,field_buffer(field[0],0),key);
		}
		else {
			switch(i) {
				case KEY_LEFT:
					form_driver(form, REQ_PREV_CHAR);
					break;
				case KEY_RIGHT:
					form_driver(form, REQ_NEXT_CHAR);
					break;
				case 27:
					goto end;
					break;
				case KEY_BACKSPACE:
					destroy_win(my_win2);
					my_win2 =newwin(30, 100, 13,30);	
					wbkgd(my_win2, COLOR_PAIR(2));
					wrefresh(my_win2);
					form_driver(form, REQ_DEL_PREV);
					form_driver(form, i);
					form_driver(form, REQ_END_LINE);
					compare(my_win2,field_buffer(field[0],0),key);
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
	wclear(my_win3);
	i = 0;
	while(i < 1) {
		wmove(my_win3, 3 + 2 * i, 1);
		wclrtoeol(my_win3);
		free_field(field[i]);
		i++;
	}
	free(field);
	box(my_win3, 0, 0);
	wrefresh(my_win3);
	destroy_win(my_win3);

}

/* COMPARE FUNCTION */
void compare(WINDOW *my_win2,char *str,int key){
	destroy_win(my_win2);
	my_win2 =newwin(30, 100, 13,30);
	wbkgd(my_win2, COLOR_PAIR(2));
	wrefresh(my_win2);
	FILE *fp;
	emp t1;
	int ch = 0,i = 0, j = 0, l = 0, count = 0, size = 100,n1 = 0,n2 = 30,flag = 0;
	int place[]={4,12,38,50,88};
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	fp = fopen(fname1, "rb");
	cbreak();
	keypad(my_win2, TRUE);
	char *ch1 = space(str),*ch2;
	char ch4[30];
	init_pair(20, COLOR_RED, COLOR_WHITE);
	attron(COLOR_PAIR(20) | A_BOLD);
	l = strlen(ch1);
	while(fread(&t1,sizeof(emp),1,fp)){
		if(key == 1){
			if(strncasecmp(t1.fname,ch1,l) == 0){
				wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
				mvwprintw(my_win2, j,place[0],"%d", t1.Id);
				mvwprintw(my_win2, j,place[1],"%s", t1.fname);
				mvwprintw(my_win2, j,(place[1]+strlen(t1.fname)+1) ,"%s", t1.lname);
				mvwprintw(my_win2, j,place[2],"%d", t1.age);
				mvwprintw(my_win2, j,place[3],"%s", t1.email);
				mvwprintw(my_win2, j,place[4] ,"%s", t1.contact);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wrefresh(my_win2);
				j++;
			}
		}
		if(key == 0){
			ch2 = tostring(ch4,t1.Id);
			if(strncasecmp(ch2,ch1,l) == 0){
				wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
				mvwprintw(my_win2, j,place[0],"%d", t1.Id);
				mvwprintw(my_win2, j,place[1],"%s", t1.fname);
				mvwprintw(my_win2, j,(place[1]+strlen(t1.fname)+1) ,"%s", t1.lname);
				mvwprintw(my_win2, j,place[2],"%d", t1.age);
				mvwprintw(my_win2, j,place[3],"%s", t1.email);
				mvwprintw(my_win2, j,place[4] ,"%s", t1.contact);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wrefresh(my_win2);
				j++;
			}
		}
		if(key == 2){
			ch2 = tostring(ch4,t1.age);
			if(strncasecmp(ch2,ch1,l) == 0){
				wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
				mvwprintw(my_win2, j,place[0],"%d", t1.Id);
				mvwprintw(my_win2, j,place[1],"%s", t1.fname);
				mvwprintw(my_win2, j,(place[1]+strlen(t1.fname)+1) ,"%s", t1.lname);
				mvwprintw(my_win2, j,place[2],"%d", t1.age);
				mvwprintw(my_win2, j,place[3],"%s", t1.email);
				mvwprintw(my_win2, j,place[4] ,"%s", t1.contact);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
				wrefresh(my_win2);
				j++;
			}
		}
	}
	fclose(fp);
}

void display1(WINDOW *my_win2){
	int ch = 0,i = 0, j = 0, l = 0, count = 0, size = 100,n1 = 0,n2 = 30,flag = 0;
	int place[]={4,12,38,50,88}; 
	init_pair(10, COLOR_BLACK, COLOR_WHITE);
	FILE *fp;
	emp *t1;
	cbreak();
	keypad(my_win2, TRUE);
	t1 = (emp *)malloc(sizeof(emp)*size);
	fp = fopen(fname1, "rb");
	while(1){
		fread(&t1[count],sizeof(emp),1,fp);
		if(feof(fp))
			break;
		count++;
		if(count == size) {
			size *= 2;
			t1 = (emp *)realloc(t1, sizeof(emp) * size);
		}
	}
	l = count;
	if(l < 30){
		j = 0;
		i = 0;
		while(i < l){
			wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
			mvwprintw(my_win2, j,place[0],"%d", t1[i].Id);
			mvwprintw(my_win2, j,place[1],"%s", t1[i].fname);
			mvwprintw(my_win2, j,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
			mvwprintw(my_win2, j,place[2],"%d", t1[i].age);
			mvwprintw(my_win2, j,place[3],"%s", t1[i].email);
			mvwprintw(my_win2, j,place[4] ,"%s", t1[i].contact);
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wrefresh(my_win2);
			j++;
			i++;
		}
		free(t1);
		return;
	}
	else{
		i = 0;
		j = 0;
		while(i < 30){
			wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
			mvwprintw(my_win2, j,place[0],"%d", t1[i].Id);
			mvwprintw(my_win2, j,place[1],"%s", t1[i].fname);
			mvwprintw(my_win2, j,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
			mvwprintw(my_win2, j,place[2],"%d", t1[i].age);
			mvwprintw(my_win2, j,place[3],"%s", t1[i].email);
			mvwprintw(my_win2, j,place[4] ,"%s", t1[i].contact);
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
			wrefresh(my_win2);
			j++;
			i++;
		}
		while(ch = wgetch(my_win2)){
			
			switch(ch){
				flag = 0;
				case KEY_DOWN:case 81:
					destroy_win(my_win2);
					my_win2 =newwin(30, 100, 13,30);
					wbkgd(my_win2, COLOR_PAIR(2));
					cbreak();
					keypad(my_win2, TRUE);		
					n1 = n1 + 30;
					n2 = n2 + 30;
					if(n2 > l){
						flag = n2 - l;						
						n2 = l;
					}
					i = n1;
					j = 0;				
					while(i < n2){
						wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
						mvwprintw(my_win2, j,place[0],"%d", t1[i].Id);
						mvwprintw(my_win2, j,place[1],"%s", t1[i].fname);
						mvwprintw(my_win2, j,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
						mvwprintw(my_win2, j,place[2],"%d", t1[i].age);
						mvwprintw(my_win2, j,place[3],"%s", t1[i].email);
						mvwprintw(my_win2, j,place[4] ,"%s", t1[i].contact);
						wrefresh(my_win2);
						j++;
						i++;
					}
					break;
					
				case KEY_UP:case 73:
					destroy_win(my_win2);
					my_win2 =newwin(30, 100, 13,30);	
					wbkgd(my_win2, COLOR_PAIR(2));	
					cbreak();
					keypad(my_win2, TRUE);
					n1 = n1 - 30;
					if(n1 < 0){
						n1 = 0;
					}
					if(flag == 0){					
						n2 = n2 - 30;
						if(n2 <= 0){
							n2 = 30;
						}
					}
					else
						n2 = n2 - 30;
					if(n2 % 30 != 0)
						n2 = n2 + flag;			
					i = n1;
					j = 0;				
					while(i < n2){
						wattron(my_win2,COLOR_PAIR(10) | A_BOLD);
						mvwprintw(my_win2, j,place[0],"%d", t1[i].Id);
						mvwprintw(my_win2, j,place[1],"%s", t1[i].fname);
						mvwprintw(my_win2, j,(place[1]+strlen(t1[i].fname)+1) ,"%s", t1[i].lname);
						mvwprintw(my_win2, j,place[2],"%d", t1[i].age);
						mvwprintw(my_win2, j,place[3],"%s", t1[i].email);
						mvwprintw(my_win2, j,place[4] ,"%s", t1[i].contact);
						wattroff(my_win2,COLOR_PAIR(10) | A_BOLD);
						wrefresh(my_win2);
						j++;
						i++;
					}
					break;
				case 27:
					goto end;
					break;		
		
			}
		}
	}	
	end:
	fclose(fp);
	free(t1);
	return;	
}
/************************************************ MODIFICATION *************************************************/

/* TO CREATE MODIFICATION WINDOW */
void modify(WINDOW *form1,int key){
	FIELD **field;
	FORM *form;
	char *str,*field_names[] = {"ID","FIRST-name", "Last-name"};
	int j = 0,a = 0,ch = 0, i = 0, x, y, size, flag = 0;
	str = (char *)malloc(sizeof(char) * 31);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
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
	if(key == 1)		
		mvwprintw(form1,12,45,"Record not found");
	if(key == 0)		
		mvwprintw(form1,12,40,"Record modified successfully");
	form_driver(form, REQ_FIRST_FIELD);
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
								a = mod(form1,form,field,flag);
								destroy_win(form1);
								form1 =newwin(20, 125, 15, 10);
								box(form1, 0 , 0);	
								wbkgd(form1, COLOR_PAIR(2));
								modify(form1,a);
							}
							form_driver(form, REQ_FIRST_FIELD);
						}
												
						else {
							form_driver(form, REQ_NEXT_FIELD);
							form_driver(form, REQ_END_LINE);
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
	free(str);
	destroy_win(form1);
	form1 =newwin(20, 125, 15, 10);	
	box(form1, 0 , 0);	
	wbkgd(form1, COLOR_PAIR(2));
	printhome2(form1);
	return;
}	
/* TO CREATE FORM */
int mod(WINDOW *form1,FORM *form2, FIELD **field1,int key){
	FIELD **field;
	FORM *form;
	FILE *fp,*tmp;
	emp t,t1;
	fp = fopen(fname1, "r");
	int ch = 0, i = 0, j = 0, x, y, size, flag=0,len = field_count(form2),pt = 0,c = 0;
	char **ch4,*ch1,*ch2,ch3[30],*str , *field_names[] = {"Employee-ID", "First-Name","Last-Name","D.O.B","Age","Mobile-no.","Email-Id","Joining-Date"};
	str = (char *)malloc(sizeof(char) * 31);
	ch4 = (char **)malloc(sizeof(char *) * len);
	while(j< 30){
		str[j] = ' ';
		j++;
	}
	str[j] = '\0';
	size = sizeof(field_names) / sizeof(field_names[0]);
	cbreak();
	keypad(form1, TRUE);
	init_pair(15, COLOR_CYAN, COLOR_WHITE);	
	init_pair(12, COLOR_BLACK, COLOR_YELLOW);
	field = (FIELD**)malloc((size + 2) * sizeof(FIELD*));
	while(i < size) {
		if(i == 0){
			wattron(form1 ,COLOR_PAIR(15));			
			mvwprintw(form1, 5 + 2 * i, 43, "(digist from 0-9)");
			wattroff(form1 ,COLOR_PAIR(15));
		}	
		if(i == 3){
			wattron(form1 ,COLOR_PAIR(15));
			mvwprintw(form1, 8 + 1 * i, 50, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}		
		if(i == 7){
			wattron(form1 ,COLOR_PAIR(15));	
			mvwprintw(form1, 12 + 1 * i, 50, "%s", "(DD/MM/YY)");
			wattroff(form1 ,COLOR_PAIR(15));
		}
		wattron(form1 ,COLOR_PAIR(3) | A_BOLD);
		mvwprintw(form1, 5 + 2 * i, 15, "%s : ", field_names[i]);		
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
	set_field_buffer(field[i], 0, "MODIFY");
	wattron(form1 ,COLOR_PAIR(3) | A_BOLD);		
	mvwprintw(form1,3,40,"MODIFY THE INFO");
	wattroff(form1 ,COLOR_PAIR(3) | A_BOLD);
	field_opts_off(field[0], O_AUTOSKIP | O_EDIT);
	field_opts_off(field[3], O_AUTOSKIP | O_EDIT);
	field_opts_off(field[7], O_AUTOSKIP | O_EDIT);
	field[++i] = NULL;
	form = new_form(field);
	scale_form(form, &y, &x);
	
	set_form_win(form, form1);
	set_form_sub(form, derwin(form1, y, x, 0, 60));
	
	i = 0;
	while(i < len){
		ch4[i] = field_buffer(field1[i], 0);
		i++;
	}
	if(key == 1){
		ch1 = space(ch4[0]);
		while(1){
			fread(&t,sizeof(emp),1,fp);
			if(feof(fp)){
				if(pt != 1){
					free_form(form);
					wclear(form1);
					return 1;
				}	
				break;
			}			
			ch2 = tostring(ch3,t.Id);
			if(strcmp(ch2,ch1) == 0){
				pt = 1;
				set_field_buffer(field[0], 0,ch2);
				set_field_buffer(field[1], 0, t.fname);
				set_field_buffer(field[2], 0, t.lname);
				set_field_buffer(field[3], 0, t.dob);
				ch2 = tostring(ch3,t.age);
				set_field_buffer(field[4], 0, ch2);
				set_field_buffer(field[5], 0, t.contact);
				set_field_buffer(field[6], 0, t.email);
				set_field_buffer(field[7], 0, t.join);
				post_form(form);
				wrefresh(form1);
			}
		}
	}
	else{
		ch1 = space(ch4[1]);
		ch2 = space(ch4[2]);
		while(1){
			fread(&t,sizeof(emp),1,fp);
			if(feof(fp)){
				if(pt != 1){
					free_form(form);
					wclear(form1);
					return 0;
				}	
				break;
			}
			if(strcmp(ch1,t.fname) == 0 && strcmp(ch2,t.lname) == 0){
				pt = 1;				
				ch2 = tostring(ch3,t.Id);
				set_field_buffer(field[0], 0,ch2);
				set_field_buffer(field[1], 0, t.fname);
				set_field_buffer(field[2], 0, t.lname);
				set_field_buffer(field[3], 0, t.dob);
				ch2 = tostring(ch3,t.age);
				set_field_buffer(field[4], 0, ch2);
				set_field_buffer(field[5], 0, t.contact);
				set_field_buffer(field[6], 0, t.email);
				set_field_buffer(field[7], 0, t.join);
				post_form(form);
				wrefresh(form1);
			}
		}
	}
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
								mvwprintw(form1, 23, 10,"Form cant be empty              ");
								flag = 1;
								break;
							}
							i++;
						}
						if(flag == 0) {
							modit(form,field,t);
							free(ch4);
							free(str);
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
							return 0;
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
	return 3;

}
/* ENTER EDIT INFO TO THE FILE */
void modit(FORM *form, FIELD **field, emp t){
	FILE *tmp,*fp;
	tmp = fopen("tmp.txt","w");
	fp = fopen(fname1, "r");
	int  i = 0,len = field_count(form),pt = 0,j = 0,c = 0;
	char **ch;
	emp t1;
	char *ch1,*ch2,ch3[30];
	ch = (char **)malloc(sizeof(char *) * len);
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
	strcpy(t.contact,ch1);
	ch1 = space(ch[6]);
	strcpy(t.email,ch1);
	ch1 = space(ch[7]);
	strcpy(t.join,ch1);
	while(1) {
		fread(&t1,sizeof(emp),1,fp);
		if(feof(fp)) {
			break;	
		}
		if(t.Id == t1.Id) {
			fwrite(&t,sizeof(emp),1,tmp);
		}
		else
			fwrite(&t1,sizeof(emp),1,tmp);
	}
	fclose(fp);
	fclose(tmp);
	remove(fname1);
	rename("tmp.txt",fname1);
	free(ch);
	return;
}	

/**************************************************************** DELETE *************************************************/

/* CREATE DELETE WINDOW */
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
	form_driver(form, REQ_FIRST_FIELD);	
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
										form_driver(form, REQ_FIRST_FIELD);
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
									form_driver(form, REQ_FIRST_FIELD);
									break;
								}
								break;
							}
						}
						else {
							form_driver(form, REQ_NEXT_FIELD);
							form_driver(form, REQ_END_LINE);
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
	free(str);
	free(field);
	box(form1, 0, 0);
	wrefresh(form1);
	destroy_win(form1);
	form1 =newwin(20, 125, 15, 10);	
	box(form1, 0 , 0);	
	wbkgd(form1, COLOR_PAIR(2));
	printhome2(form1);
	return;
}

/* DELETE FROM THE FILE */
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
		free(ch);		
		return c;
	}
	else{
		ch1 = space(ch[1]);
		ch2 = space(ch[2]);
		while(1){
			fread(&t,sizeof(emp),1,fp);
			if(feof(fp)){
				if(pt==0){
					free(ch);					
					return 0;
				}				
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
		free(ch);		
		return c;
	}
}


/********************************************************* BASIC FUNCTIONS *************************************************/

/* PRINT LOGIN PAGE */
int printlogin(WINDOW *form1,int key){
	 
	FIELD **field;
	FORM *form;
	int ch = 0, i = 0, x, y, size, flag=0;
	char *field_names[] = {"LOGIN ID", "PASSWORD"};
	size = sizeof(field_names) / sizeof(field_names[0]);
	init_pair(6, COLOR_BLACK, COLOR_BLUE);
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
	form_driver(form, REQ_FIRST_FIELD);	
	wattroff(form1 ,A_BOLD);
	box(form1,0,0);
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
								flag = i;
								goto end;
								break;
							}
							form_driver(form, REQ_FIRST_FIELD);
						}
						else {
							form_driver(form, REQ_NEXT_FIELD);
							form_driver(form, REQ_END_LINE);
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

/* DESTROY THE WINDOW */
void destroy_win(WINDOW *my_win2){
	wclear(my_win2);
	wbkgd(my_win2,COLOR_PAIR(9));
	wrefresh(my_win2);
	delwin(my_win2);
}

/* PRINTING THE HOME PAGE */ 
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

/* CREATE WINDOW AND CALL LOGIN PAGE */
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


/* PRINT HOME PAGE INSIDE EACH LOGIN */
void printhome2(WINDOW *my_win2){
	int  max = 19,i = 0,j = 0, count = 0, size = 25,l,p,r;
	long int n;
	time_t tt;
	srandom(time(&tt));
	n = random() % max; 
	quote *t;
	t = (quote *)malloc(sizeof(quote)*size);
	FILE *fp;
	fp = fopen("quote1.txt","r");
	while(!feof(fp)) {
		fgets(t[i].a,200,fp);
		fgets(t[i].b,200,fp);
		fgets(t[i].c,200,fp);
		i++;
	}
	l = strlen(t[n].a);
	p = strlen(t[n].b);
	r = strlen(t[n].c);
	wattron(my_win2 ,COLOR_PAIR(3));
	mvwprintw(my_win2,8,(125-l)/2,"%s",t[n].a);
	mvwprintw(my_win2,9,(125-p)/2,"%s",t[n].b);	
	mvwprintw(my_win2,10,(125-r)/2,"%s",t[n].c);	
	wattroff(my_win2 ,COLOR_PAIR(3) | A_BOLD);
	wrefresh(my_win2);
	free(t);
	fclose(fp);
}
