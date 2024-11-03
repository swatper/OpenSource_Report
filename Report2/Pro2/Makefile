#Execute File
execute/main: library/libstest.a
	gcc -g -o execute/main -I./libaray -L./library source/main.c -ltest
#Libaray File
library/libstest.a: source/Add.o source/Sub.o source/Mul.o source/Div.o
	ar rcs library/libtest.a source/Add.o source/Sub.o source/Mul.o source/Div.o
#Object Files
source/Add.o: source/Add.c
	gcc -o source/Add.o -c source/Add.c
source/Sub.o:  source/Sub.c
	gcc -o source/Sub.o -c source/Sub.c
source/Mul.o: source/Mul.c
	gcc -o source/Mul.o -c source/Mul.c
source/Div.o: source/Div.c
	gcc -o source/Div.o -c source/Div.c
#Execute 
Execute:
	execute/main
#Delete Files 
clean: 
	rm source/Add.o source/Sub.o source/Div.o source/Mul.o library/libtest.a execute/main