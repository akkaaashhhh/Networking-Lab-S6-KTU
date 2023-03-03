#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(void)
{
    int socket_desc,client_sock,client_size;
    struct sockaddr_in server_addr,client_addr;
    char server_msg[2000],client_msg[2000];
    
    memset(server_msg,'\0',sizeof(server_msg));
    memset(client_msg,'\0',sizeof(client_msg));
    
    socket_desc=socket(AF_INET,SOCK_STREAM,0);
    
    if(socket_desc<0)
    {
        printf("Error while creating socket\n");
        return -1;
    }
    printf("Socket created succesfully");
    
    server_addr.sin_family=AF_INET;
    server_addr.sin_port=htons(2000);
    server_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
    
    if(bind(socket_desc,(struct sockaddr*)&server_addr,sizeof(server_addr))<0)
    {
        printf("Could not bind to the port\n");
        return -1;
    }
    printf("Done with Binding\n");
    
    if(listen(socket_desc,1)<0)
    {
        printf("Error while listening\n");
        return -1;
    }
    printf("listening for incoming connections\n");
    
    client_size=sizeof(client_addr);
    client_sock=accept(socket_desc,(struct sockaddr*)&client_addr,&client_size);
    if(client_sock<0)
    {
        printf("Can Accept\n");
        return -1;
    }
    printf("Client Connected at IP :%s and port %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
    
    if(recv(client_sock,client_msg,sizeof(client_msg),0)<0)
    {
        printf("Could not connect");
        return -1;
    }
    printf("MSG from client:%s\n",client_msg);
    
    strcpy(server_msg,"This is the servers message");
    
    if(send(client_sock,server_msg,strlen(server_msg),0)<0)
    {
        printf("Cant send");
        return -1;
    }
    close(client_sock);
    close(socket_desc);
    return 0;
}