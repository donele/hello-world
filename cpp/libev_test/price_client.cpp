// C++ program to illustrate the client application in the 
// socket programming 
#include <cstring> 
#include <iostream> 
#include <netinet/in.h> 
#include <sys/socket.h> 
#include <unistd.h> 

#define PORT_NO 8080

int main() 
{ 
	// creating socket 
	int clientSocket = socket(AF_INET, SOCK_STREAM, 0); 

	// specifying address 
	sockaddr_in serverAddress; 
	serverAddress.sin_family = AF_INET; 
	serverAddress.sin_port = htons(PORT_NO); 
	serverAddress.sin_addr.s_addr = INADDR_ANY; 

	// sending connection request 
	connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress));

	//const char* message = "Hello, server!"; 
    double price = 0.;
    char buf[16];
    for(int i = 0; i < 30; ++i)
    {
        price += 0.01;
        sprintf(buf, "%.2f", price);
	    send(clientSocket, buf, strlen(buf)+1, 0); 
        sleep(1);
    }

	// closing socket 
	close(clientSocket); 

	return 0; 
}

