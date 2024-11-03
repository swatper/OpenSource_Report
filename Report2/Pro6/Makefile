#Execute File
execute/main: library/libstest.a
	gcc -g -o execute/main -I./libaray -L./library source/main.c -ltest
#Libaray File
library/libstest.a: source/Myassert.o
	ar rcs library/libtest.a source/Myassert.o
#Object Files
source/Myassert.o: source/Myassert.c
	gcc -o source/Myassert.o -c source/Myassert.c
#Execute 
Execute1:
	execute/main 73
Execute2:
	execute/main 10000
#Delete Files 
clean: 
	rm source/Myassert.o library/libtest.a execute/main