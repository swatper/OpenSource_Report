#Execute File
execute/main: library/libstest.a
	gcc -g -o execute/main -I./libaray -L./library source/main.c -ltest
#Libaray File
library/libstest.a: source/Myperror.o
	ar rcs library/libtest.a source/Myperror.o
#Object Files
source/Myperror.o: source/Myperror.c
	gcc -o source/Myperror.o -c source/Myperror.c
#Execute 
Execute:
	execute/main Nothing
#Delete Files 
clean: 
	rm source/Myperror.o library/libtest.a execute/main