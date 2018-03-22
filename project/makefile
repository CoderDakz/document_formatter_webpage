all: permissionsA4; $(CC) -Wall db.c -L. -lmysqlclient -o db; chmod -v 0777 db
	
permissionsA4: a4	
	chmod -v 0777 a4
	
a4: main.c liblistio.a
	gcc -g main.c -L. -llistio -lmysqlclient -o a4
	
liblistio.a: liblistio.o
	ar rc liblistio.a liblistio.o
	
liblistio.o: liblistio.c listio.h
	$(CC) -Wall liblistio.c -o liblistio.o -c -g

db: db.c
	$(CC) -Wall db.c -L. -lmysqlclient -o db 

clean: liblistio.o
	rm *.o liblistio.a *.html a4 db

CC = gcc
