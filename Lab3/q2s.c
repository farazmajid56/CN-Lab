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
		if(token[i] == 'a' || token[i] == 'e' ||token[i]  == 'i' || token[i]  == 'o' || token[i]  == 'u' || token[i] == 'A' || token[i] == 'E' 							|| token[i] == 'I' || token[i] == 'O' || token[i] == 'U')
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
				if(checkvowel(data,a,b)==1)
				{
					reversestr(data,a,b+1);
				}
				a=i+1;
 			}
 		
 		}
 		//printf("%s\n",data);
 		
 		
 }
int main(void)
{	
		
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;         //SERVER ADDR will have all the server address
        char server_message[2000], client_message[2000];                 // Sending values from the server and receive from the server we need this

        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));     // Set all bits of the padding field//
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;               /* Address family = Internet */
        server_addr.sin_port = htons(2000);               // Set port number, using htons function to use proper byte order */
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");    /* Set IP address to localhost */
		
		
		
		// BINDING FUNCTION
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)    // Bind the address struct to the socket.  /
	                            	//bind() passes file descriptor, the address structure,and the length of the address structure
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)                               //This listen() call tells the socket to listen to the incoming connections.
     // The listen() function places all incoming connection into a "backlog queue" until accept() call accepts the connection.
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
        while(1)
        {
        client_size = sizeof(client_addr);
		
		
		
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);          // heree particular client k liye new socket create kr rhaa ha
        
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
        
        printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
		       //inet_ntoa() function converts the Internet host address in, given in network byte order, to a string in IPv4 dotted-decimal notation
        
        //Receive the message from the client
        
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        printf("Client's Message: %s\n",client_message);
        invert(client_message);
        printf("Vowels words reversed from Client Message: %s\n",client_message);
        
        //Send the message back to client
        
        strcpy(server_message, client_message);
        
        if (send(client_sock, server_message, strlen(client_message),0)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
              
        //Closing the Socket
         close(client_sock);
        }
       
        close(socket_desc);
        return 0;       
}

