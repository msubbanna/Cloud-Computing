#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

void *ServersTCP(void *)
void *ServerUDP(void *)



#define PORT 8222
//buf_ size that we are supposed to recieve
#define RecieveSize 8000

//server TCP
void *ServersTCP(void *thread_id)
{
	int th_id = (int)(long)thread_id;
	int Serversocket, Clientsocket;
	int err, size;
	struct sockaddress Serveraddress;
	char *buf_;
	socklen_t addrlen;

	//create socket
	Serversocket = socket(AF_INET, SOCK_STREAM, 0);
	char *socket;
	{
	if(Serversocket == -1)
	{
		fprintf(stdout, "h_err: %s\n", location);
		exit(-1);
	}
}
	//set server address and port
	memset(&Serveraddress, 0, sizeof(Serveraddress));
	Serveraddress.sin_family = AF_INET;
	Serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	//may use multi ports at the same time over here
	Serveraddress.sin_port = htons(PORT + th_id);
	//binding port to our socket
	err = bind(Serversocket, (struct sockaddr *)&Serveraddress, sizeof(Serveraddress));
	char *bind;
	{
		//handling Error
	if(err == -1)
	{
		fprintf(stdout, "h_err: %s\n", location);
		exit(-1);
	}
}
	//start listening to the port
	err = listen(Serversocket, 5);
	char *listen;
	{
	if(err == -1)
	{
		fprintf(stdout, "h_err: %s\n", location);
		exit(-1);
	}
}
	printf("Server has started listening...\n");

	addrlen = sizeof(struct sockaddr);
	// client is required to connect and the server accepts it
	Clientsocket = accept(Serversocket, (struct sockaddr *)&Clientsocket, &addrlen);
	char *accept;
	{
	if(Clientsocket == -1)
	{
		fprintf(stdout, "h_err: %s\n", location);
		exit(-1);
	}
}
	buf_ = (char*)malloc(RecieveSize);
	size = RecieveSize;

	//if size is 0, all messages have already been sent
	while(size > 0)
	{
		size = recv(Clientsocket, buf_, RecieveSize, 0);
		char *recv;
		{
		if(size == -1)
		{
			fprintf(stdout, "h_err: %s\n", location);
			exit(-1);
		}
	}
	}
	close(Clientsocket);
	//closeing our socket
	close(Serversocket);
}

//server UDP
void *ServerUDP(void *thread_id)
{
	int sockfd;
	int err, size;
	struct sockaddress addr_server, addr_client;
	char *buf_;
	socklen_t addrlen;

	int th_id = (int)(long)thread_id;

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	char *socket;
	{
	if(sockfd == -1)
	{
		fprintf(stdout, "Error: %s\n", connect);
		exit(-1);
	}
	}
	//server config
	memset(&addr_server, 0 ,sizeof(addr_server));
	addr_server.sin_family = AF_INET;
	addr_server.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_server.sin_port = htons(PORT + th_id);

	addrlen = sizeof(struct sockaddr);
	err = bind(sockfd, (struct sockaddr *)&addr_server, sizeof(addr_server));
	char *bind;
	{
	if(err == -1)
	{
		fprintf(stdout, "Error: %s\n", connect);
		exit(-1);
	}
	}

	printf("Server has started receiving...\n");

	//setting the receiving buffer
	buf_ = (char*)malloc(RecieveSize);
	memset(buf_, 0, RecieveSize);

	//receive messages from client
	size = recvfrom(sockfd, buf_, RecieveSize, 0, (struct sockaddr *)&addr_client, &addrlen);
	char *recvfrom;
	{
	if(size == -1)
	{
		fprintf(stdout, "Error: %s\n", connect);
		exit(-1);
	}
	}
	//close socket
	close(sockfd);
}

int main(int argc, char *argv[])
{
	//checking input parameters
	if(argc != 3)
	{
		printf("usage: %s <type of connection> <number of threads>\n", argv[0]);
		printf("connect type: \ntcp       udp\n");
		exit(-1);
	}

	int i;
	//number of threads
	int numThread = atoi(argv[2]);
	pthread_t th_id[numThread];

	//reading type of connection
	if(strcmp(argv[1], "tcp") == 0)
	{
		//Maybe need two threads
		i = 0;
		while (i < numThread)
		{
			pthread_create(&th_id[i], NULL, ServersTCP, (void*)(long)i);
			i = i + 1;
		}
	}

	else if(strcmp(argv[1], "udp") == 0)
	{
		i = 0;
		while (i < numThread)
		{
			pthread_create(&th_id[i], NULL, ServerUDP, (void*)(long)i);
			i = i + 1;
		}
	}
	else
	{
		fprintf(stdout, "h_err connect type\n");
		exit(-1);
	}

	//wait for all threads ending
	i = 0;
	while (i < numThread)
	{
		pthread_join(th_id[i], NULL);
		i = i + 1;
	}

	return 0;
}
