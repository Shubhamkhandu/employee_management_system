shubham khandelwal
111508066
employee management system
-> home
-> admin
-> employee
-> manager
for now only manager login is working
-> 3 managers 
   id = abhijeet
   passowrd = abhijeetcoep
   id = shubham
   password = shubham18
   id = narendra
   password = modi123
   password can be change
   password file is secured by modification of permission
   after login
            -> add employee
            -> display
            -> edit
            -> delete
            -> search
            -> logout
   of which only 
   add , display , delete is working
   -> leave application will be handeld
   -> sorting of the database will be taken care
   -> employee login
            -> id = id number 
            -> password = last name
            -> after login this will happen
                  -> info display
                  -> leave application request
                  ->edit
    ->admin login
              -> display 
              -> remove manager or employee
     functions discriptions
     ->allfunction.h
            ->del(FORM *form, FIELD **field,int key)          delete the employee from list
            ->void dele(WINDOW *form1,int key);                create delete window
            ->int printlogin(WINDOW *form1,int key);            create login window
            ->void destroy_win(WINDOW *my_win2);              destroy the window given in argument
            ->char *tostring(char str[],int num);             convert int to string
            ->void modify(WINDOW *form1);                     MODIFY THE LIST
            ->void print_home(WINDOW *my_win2);               print the home page
            ->int create(WINDOW *my_win2,int key);             create new window
            ->void display(WINDOW  *my_win2);                  display the list
            ->void add_file(FORM *form, FIELD **field);         create add to employee window
            ->int add(WINDOW *form1);                           add data of employee to lisat
            ->void manage2();                                   after login manager
         ->password.h   
            ->char *space(char *ch);                             removes space from buffer
            ->int check(char *id, char *pa,int key);             checks password
            ->int change(FORM *form, FIELD **field,int key);      change password
            ->int newpass(WINDOW *form1,int key);                 new password window
