all: project pss
project: main.o  newpass.o
	cc main.o  newpass.o -lncurses -lmenu -lform -o project
newpass.o: newpass.c password.h allfunction.h 
	cc -c newpass.c
main.o: main.c allfunction.h password.h newpass.o
	cc -c main.c
pss: pss.c
	cc -c pss.c
	cc pss.o -o s
	./s
clean: 
	rm *.o
	
