#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void)
{
    int socket_desc;
    struct sockaddr_in server_addr;
    char server_msg[2000],client_msg[2000];
    
    memset(server_msg,'\0',sizeof(server_msg));
    memset(client_msg,'\0',sizeof(client_msg));
    
    socket_desc=socket(AF_INET,SOCK_STREAM,0);
    
    if(socket_desc<0)
    {
        printf("Unable to create socke\n");
        return -1;
    }
    
    printf("Socket created succesfully\n");
    
    server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
            printf("Unable to connect\n");
            return -1;
       }
        printf("Connected with server successfully\n");
        printf("Enter message: ");
        gets(client_msg);
        if(send(socket_desc, client_msg, strlen(client_msg), 0) < 0)
        {
            printf("Unable to send message\n");
            return -1;
        }    
        if(recv(socket_desc, server_msg, sizeof(server_msg), 0) < 0)
        {
            printf("Error while receiving server's msg\n");
            return -1;
    }
    
        printf("Server's response: %s\n",server_msg);
        close(socket_desc);
        return 0;
}

