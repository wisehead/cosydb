/*******************************************************************************
 *      file name: dbclient.cpp                                               
 *         author: Hui Chen. (c) 18                             
 *           mail: chenhui13@baidu.com                                        
 *   created time: 18/03/23- 3:03                                    
 *  modified time: 18/03/23- 3:03                                    
 *******************************************************************************/
#include <iostream>
#include <stdio.h>
#include <netinet/in.h>    // for sockaddr_in  
#include <sys/types.h>    // for socket  
#include <sys/socket.h>    // for socket  
#include <arpa/inet.h>
#include <stdio.h>        // for printf  
#include <stdlib.h>        // for exit  
#include <string.h>        // for bzero  
#include <unistd.h>  
#include <fcntl.h>
#include <errno.h>
#include <signal.h>       // for signal
#include <time.h>

#define HELLO_WORLD_SERVER_PORT    6666   
#define LENGTH_OF_LISTEN_QUEUE 20 
#define BUFFER_SIZE 1024  
#define FILE_NAME_MAX_SIZE 512  
#define MAX_WAITING_COUNT 86400 
#define IDS_SERVER_NUM 4
#define IP_ADDR_LEN 16
#define RECONNECT_TIME 30
#define MAX_RETRY_COUNT 30
#define MAX_PREFERRED_RETRY_COUNT 10
using namespace std;
int g_retry_count = 0;

int main(int argc, char **argv)  
{  
    //init the log handle
    int input_num = 0;
    int input_flag = 0;

    struct timeval timeout = {15, 0};

    time_t rawtime;
    struct tm * timeinfo;
    char time_buf[128]; 

    time(&rawtime);
    timeinfo = localtime(&rawtime);

    bzero(time_buf, 128);   
    if (time_buf && timeinfo)
    {
        strftime(time_buf, sizeof(time_buf), "%Y%m%d", timeinfo);
    }
    srand(time(NULL));
    char last_ip[16];
    int first_flag = 1;
    char* ip_addr = NULL;

    struct sockaddr_in client_addr;  
    int client_socket = 0;  

    while(1)
    {
        bzero(&client_addr, sizeof(client_addr)); //°ÑÒ»¶ÎÄÚ´æÇøµÄÄÚÈÝÈ«²¿ÉèÖÃÎª0  
        client_addr.sin_family = AF_INET;    //internetÐ­Òé×å  
        client_addr.sin_addr.s_addr = htons(INADDR_ANY);//INADDR_ANY±íÊ¾×Ô¶¯»ñÈ¡±¾»úµØÖ·  
        client_addr.sin_port = htons(0);    //0±íÊ¾ÈÃÏµÍ³×Ô¶¯·ÖÅäÒ»¸ö¿ÕÏÐ¶Ë¿Ú  

        client_socket = socket(AF_INET, SOCK_STREAM, 0);  
        if (client_socket < 0)  
        {  
            printf("Create Socket Failed!\n");  
            exit(1);  
        }  
        //set the timeout value
        setsockopt(client_socket, SOL_SOCKET, SO_RCVTIMEO, 
                (char *)&timeout, sizeof(struct timeval));

        if (bind(client_socket, (struct sockaddr*)&client_addr, sizeof(client_addr)))  
        {  
            printf("Client Bind Port Failed!\n");   
            exit(1);  
        }  
      
        struct sockaddr_in server_addr;  
        bzero(&server_addr, sizeof(server_addr));  
        server_addr.sin_family = AF_INET;  
        const char* ip_addr = "127.0.0.1";
        
        printf("Connecting to IDS server:%s\n", ip_addr);
        if(inet_aton(ip_addr, &server_addr.sin_addr) == 0) 
        {  
            printf("Server IP Address Error!\n");  
            exit(1);  
        }  
        server_addr.sin_port = htons(HELLO_WORLD_SERVER_PORT);  
        socklen_t server_addr_length = sizeof(server_addr);  
        if (connect(client_socket, (struct sockaddr*)&server_addr, server_addr_length) < 0)  
        {  
            printf("Can Not Connect To %s!\n", ip_addr);  
            sleep(RECONNECT_TIME);
            if (g_retry_count++ < MAX_RETRY_COUNT)
            {
                continue;
            }
            exit(1);  
        }  

        g_retry_count = 0;
        socklen_t length = sizeof(client_addr);  
  
        char buffer[BUFFER_SIZE];  
        bzero(buffer, BUFFER_SIZE);  
        length = recv(client_socket, buffer, BUFFER_SIZE, 0);  
        if (length < 0)  
        {  
            printf("Server Recieve Data Failed!\n");  
            break;  
        }  
        char file_name[FILE_NAME_MAX_SIZE + 1];  
        bzero(file_name, FILE_NAME_MAX_SIZE + 1);  
        snprintf(file_name, FILE_NAME_MAX_SIZE, "%s", buffer);
        printf("%s\n", file_name);  

        printf("closing fp and socket.\n");
        close(client_socket);  
        sleep(RECONNECT_TIME);
        //goto retry;
    }  
Exit:
    printf("closing server socket.\n");
    if (client_socket)
    {
        close(client_socket);  
    }
    return 0;  
}  
