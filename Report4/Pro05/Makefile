#Create Execute File
All: 
	gcc -o execute/TClient source/TCPClient.c
	gcc -o execute/TServer source/TCPServer.c
	gcc -o execute/UClient source/UDPClient.c
	gcc -o execute/UServer source/UDPServer.c

#Execute File
Execute:
	execute/UServer &
	execute/UClient 127.0.0.1 "This Message from Client"

#Delete File 
Clean:
	rm execute/TClient
	rm execute/TServer 
	rm execute/UClient
	rm execute/UServer 

#Test Codes
#-------------------------------------------------------
#execute/TServer &
#execute/TClient 127.0.0.1 "This Message from Client"
#-------------------------------------------------------
#execute/Cancel 2
#execute/Cancel 3
#-------------------------------------------------------
#execute/Mutex 1 2 3
#-------------------------------------------------------
#execute/Signal 1
