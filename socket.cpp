#include<iostream>
#include<winsock2.h>
#pragma comment(lib, "ws2_32.lib")

#define PORT 9090 //server port 
#define BUFFER_SIZE 124

int main()
{
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int addrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE] = {0};

    //initialize winsock
    if(WSAStartup(MAKEWORD(2,2), &wsaData) != 0)
    {
        std::cerr<<"WSAStartup failed\n";
        return 1;
    }

    //tcp socket 
    //descriptor = socket(protofamily,type,protocol)
    //connection oriented stream transfer-SOCK_STREAM
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocket == INVALID_SOCKET)
    {
        std::cerr<<"Socket creation failed\n";
        WSACleanup();
        return 1;
    }

    /*struct sockaddr_in
    {
        u_char sin_len;
        u_char sin_family;
        u_short sin_port;
        struct sin_addr sin_addr -ip address
        char sin_zero[8];
    }*/

   //configure server address 
   serverAddr.sin_family = AF_INET;
   serverAddr.sin_addr.s_addr = INADDR_ANY; //to allow the server to operate on a multihomed host
   serverAddr.sin_port = htons(PORT);

   //Binding socket : bind(socket,localaddr,addrlen)
   if(bind(serverSocket,(struct sockaddr*)&serverAddr,sizeof(serverAddr)) == SOCKET_ERROR)
   {
    std::cerr<<"Bind failed\n";
    closesocket(serverSocket);
    WSACleanup();
    return 1;
   }

   //LISTEN : listen(socket,queuesize)
   if(listen(serverSocket, 3) == SOCKET_ERROR)
   {
        std::cerr<<"Listen failed!\n";
        closesocket(serverSocket);
        WSACleanup();
        return 1;
   }

   std::cout<<"Server listenening on port "<<PORT<<"....\n";

   //ACCEPT incoming connections : newsock = accept(socket,caddress,caddrlen)

   while(true)
   {
        clientSocket = accept(serverSocket,(struct sockaddr*)&clientAddr, &addrLen);
        if(clientSocket == INVALID_SOCKET)
        {
            std::cerr<<"Accept failed!\n";
            continue;
        }
   

    //READ HTTP requests 
    /* recv(socket,buffer,length,flags) 
    */

        recv(clientSocket, buffer, BUFFER_SIZE, 0);
        std::cout<<"Recieved Request: \n"<<buffer<<std::endl;

        //HTTP response:

        std::string httpResponse = 
        "HTTP/1.1 200 OK\r\n"
                "Content-Type: text/html\r\n"
                "Content-Length: 13\r\n"
                "\r\n"
                "Connection: close\r\n"
                "sup bitches!";

        //send HTTP response 
        //send(socket,data,length,flags)
        send(clientSocket, httpResponse.c_str(), httpResponse.length(), 0);

        //close client socket
        closesocket(clientSocket);
   }

    //cleanup
    closesocket(serverSocket);
    WSACleanup();
    return 0;

}