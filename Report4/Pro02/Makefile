#Create Execute File
All: 
	gcc -o execute/Hello source/HelloThread.c
	gcc -o execute/Cancel source/CancelThread.c
	gcc -o execute/Mutex source/SyncThread.c
	gcc -o execute/Signal source/SigThread.c
	gcc -o execute/Attribute source/AttThread.c

#Execute File
Execute:
	execute/Attribute

#Delete File 
Clean:
	rm execute/Hello
	rm execute/Cancel
	rm execute/Mutex
	rm execute/Signal
	rm execute/Attribute

#Test Codes
#-------------------------------------------------------
#execute/Hello
#-------------------------------------------------------
#execute/Cancel 2
#execute/Cancel 3
#-------------------------------------------------------
#execute/Mutex 1 2 3
#-------------------------------------------------------
#execute/Signal 1
