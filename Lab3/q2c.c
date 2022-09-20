#include <stdio.h>
#include <string.h>
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

void reversestr(char *str,int a,int b)
 {
 	
   int i,j;
   for(i=a,j=b-1;i<j;i++,j--)
   {
   		char temp=str[i];
   		str[i]=str[j];
   		str[j]=temp;
   }
 
 }
 int checkvowel(char*token,int a,int b)
 {
 	int i;
 	for(i=a;i<=b;i++)
	{
		if(token[i] == 'a' || token[i] == 'e' ||token[i]  == 'i' || token[i]  == 'o' || token[i]  == 'u' || token[i] == 'A' || token[i] == 'E' 	|| token[i] == 'I' || token[i] == 'O' || token[i] == 'U')
		{
			return 1;
		}				
	}
	return 0;
 
 }
 void invert(char *data)
 {
 		int a=0;
 		int b =0;
 		int k=0;
 		int i;
 		for( i=0;i<strlen(data)+1;i++)
 		{
 			
 			if(data[i]!=' ' &&data[i]!='\0')
 			{
				b=i;	
				
			}
			else
			{
				
				if(checkvowel(data,a,b)==0)
				{
					
					reversestr(data,a,b+1);
				}
				a=i+1;
 			}
 		
 		}
 		
 		
 }

int main(void)
{
        int socket_desc;
        struct sockaddr_in server_addr;
        char server_message[2000], client_message[2000];
        
        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Specifying the IP and Port of the server to connect
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        //Now connecting to the server accept() using connect() from client side
        
        if(connect(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
        {
                printf("Connection Failed. Error!!!!!");
                return -1;
        }
        
        printf("Connected\n");
        
        //Get Input from the User
        
        printf("Enter Message: ");
        gets(client_message);                                     //One is that gets() will only get character string data. 
                                                       //		will get only one variable at a time.
																//  reads characters from stdin and loads them into str
        //Send the message to Server
        
        if(send(socket_desc, client_message, strlen(client_message),0) < 0)
        {
                printf("Send Failed. Error!!!!\n");
                return -1;
        }
        
        //Receive the message back from the server
        
        if(recv(socket_desc, server_message, sizeof(server_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        invert(server_message);
        printf("Non Vowels words reversed from Server's Message: %s\n",server_message);
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Closing the Socket
        
        close(socket_desc);
        
        return 0;
}

