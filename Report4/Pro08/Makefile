#Create Execute File
#GTK 컴파일은 make로 안돼서 명령어를 직접 실행
All: 
	gcc -o execute/GTK source/GTK.c $(pkg-config --cflags --libs gtk+-3.0)

#Execute File
Execute:
	execute/GTK

#Delete File 
Clean:
	rm execute/GTK

#Test Codes
#-----------------------------------------------------------------------
#gcc -o execute/GTK source/GTK.c $(pkg-config --cflags --libs gtk+-3.0)
#-----------------------------------------------------------------------
#