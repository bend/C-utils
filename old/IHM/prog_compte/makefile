all: ihm_compte_V2.o save.o new_month.o consult.o
	gcc $(pkg-config --libs --cflags gtk+-2.0) ihm_compte_V2.1.o save.o
	new_month.o consult.o -o compte
ihm_compte_V2.o:
	gcc  $(pkg-config --libs --cflags gtk+-2.0) -c ihm_compte_V2.1.c -Wall
new_month.o:
	gcc  $(pkg-config --libs --cflags gtk+-2.0) -c new_month.h -Wall
save.o:
	gcc  $(pkg-config --libs --cflags gtk+-2.0) -c save.h -Wall
consult.o:
	gcc  $(pkg-config --libs --cflags gtk+-2.0) -c consult.h -Wall



