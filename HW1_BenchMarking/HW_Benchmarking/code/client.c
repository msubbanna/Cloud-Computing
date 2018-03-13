#include <errno.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>


//port number
#define PORT 8222
//buffer size to be sent
#define SizetoSend_ 8000
#define SizetoSendSMALL 600000

int lps = 16;
//handle error
//void Handle_err(int return_value, char *location)
/*int return_value;
char *location;
{
	if(return_value == -1)
	{
		fprintf(stdout, "Error: %s\n", location);
		exit(-1);
	}
}*/
//Struct to store parameters
typedef struct Info
{
	int thread_num; //thread_num
	int pack_size; //pack_size

} data;

//client TCP
void *C_TCP(void *arg)
{
	struct sockaddr_in addr_ser;
	char *buffer;
	int sockfd, err, i;
	int SendBuffer, thread_num;
	data *pInfo;
	pInfo = (data *)arg;
	SendBuffer = pInfo->pack_size;
	thread_num = pInfo->thread_num;

	//create socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	//int sockfd;
	char *socket;
{
	if(sockfd == -1)
	{
		fprintf(stdout, "Error: %s\n", socket);
		exit(-1);
	}
}

	//set TCP packet size according to the packet size
	setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (const char*)&SendBuffer, sizeof(int));

	//set server's address and port
	memset(&addr_ser, 0, sizeof(addr_ser));
	addr_ser.sin_family = AF_INET;
	addr_ser.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	addr_ser.sin_port = htons(PORT + thread_num);
	//connect to the server
	err = connect(sockfd, (struct sockaddr *)&addr_ser, sizeof(addr_ser));
	//int err;
	char *connect;
{
	if(err == -1)
	{
		fprintf(stdout, "Error: %s\n", connect);
		exit(-1);
	}
}

	//send messages to the server
	for(i = 0; i < (lps); i++)
	{
		buffer = (char*)malloc(SizetoSend_);
		memset(buffer, 'a', SizetoSend_);

		send(sockfd, buffer, SizetoSend_, 0);
	}

	//close socket
	close(sockfd);
}

int Buffer_Size(char *block)
{
	int buffersize;

	if(strcmp(block, "1b") == 0)
	{
		buffersize = 1;
	}
	else if(strcmp(block, "1kb") == 0)
	{
		buffersize = 1024;
	}
	else if(strcmp(block, "64kb") == 0)
	{

		buffersize = 65507;

	}
	else
	{
		printf("The packet size is wrong!");
	}
	return buffersize;
}

//client UDP
void *Cli_UDP(void *arg)
{
	int sockfd;
	struct sockaddr_in addr_ser;
	char *buffer;
	socklen_t addrlen;

	int SendBuffer, thread_id;
	data *pInfo;
	pInfo = (data *)arg;
	SendBuffer = pInfo->pack_size;
	thread_id = pInfo->thread_num;

	//create socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		//int sockfd;
	char *socket;
{
	if(sockfd == -1)
	{
		fprintf(stdout, "Error: %s\n", socket);
		exit(-1);
	}
}

	//set server's address and port
	memset(&addr_ser, 0, sizeof(addr_ser));
	addr_ser.sin_family = AF_INET;
	addr_ser.sin_addr.s_addr = htonl(INADDR_ANY);
	addr_ser.sin_port = htons(PORT + thread_id);

	addrlen = sizeof(addr_ser);

	int SizetoSend;
	int size;

	//start send messages to server
	int i;
	i = 0;
	while(i < 9)
	{
		SizetoSend = SendBuffer > 1 ? SizetoSend_ : SizetoSendSMALL;
		buffer = (char*)malloc(SizetoSend);
		memset(buffer, 'a', SizetoSend);
		size = SizetoSend;
		int sendsize;

		//until all the buffers have been sent
		while(size > 0)
		{

			//packet size is specified at here, cause UDP uses datagram
			sendsize = sendto(sockfd, buffer, SendBuffer, 0, (struct sockaddr *)&addr_ser, addrlen);
			size -= SendBuffer;
			if(size == -1)
			{
				printf("Error: sendto: %s\n", strerror(errno));
				exit(-1);
			}
		}
		i = i + 1;
	}

	//close socket
	close(sockfd);
}


int main(int argc, char *argv[])
{
	//check input socket
	if(argc != 4)
	{
		printf("usage: %s <connect type> <packet size> <num of thread>\n", argv[0]);
		printf("connect type: \ntcp    udp\n");
		printf("packet size: 1b  1kb  64kb\n");
		exit(-1);
	}

	int SendBuffer, i;
	//number of threads
	int numThread = atoi(argv[3]);
	pthread_t thread_id[numThread];
	char *block = argv[2];
	SendBuffer = Buffer_Size(block);

	//parameter structure passed in pthread
	data d[2];
	d[0].pack_size = SendBuffer;
	d[1].pack_size = SendBuffer;
	//variables to count the time
	struct timeval etstart, etstop;
	unsigned long long start, stop;

	//start time
	gettimeofday(&etstart, NULL);

	//TCP
	if(strcmp(argv[1], "tcp") == 0)
	{
		//run several clients at the same time
		i = 0;
		while (i < numThread)
		{
			d[i].thread_num = i;
			pthread_create(&thread_id[i], NULL, C_TCP, &d[i]);
			i = i + 1;
		}
	}
	//UDP
	else if(strcmp(argv[1], "udp") == 0)
	{
		//run several clients at the same time
		i = 0;
		lps = lps /numThread;
 		while(i < numThread)
		{
			d[i].thread_num = i;
			pthread_create(&thread_id[i], NULL, Cli_UDP, &d[i]);
			i = i + 1;
		}

	}
	else
	{
		printf("Error connect type\n");
		exit(-1);
	}

	//wait until all the threads end
	i = 0;

	while(i < numThread)
	{
		pthread_join(thread_id[i], NULL);
		i = i + 1;
	}

	//end time
	gettimeofday(&etstop, NULL);
	start = (unsigned long long)etstart.tv_sec * 1000000 + etstart.tv_usec;
	stop = (unsigned long long)etstop.tv_sec * 1000000 + etstop.tv_usec;

	int tempSize = (SendBuffer > 1 || argv[1] == "tcp") ? SizetoSend_ : SizetoSendSMALL;
	float running_time = (float)(stop - start) / 1000;
	float through_put = (float)numThread * tempSize * lps * 8 * numThread / running_time * 1000 / 1e6;
	float latency = (float)(running_time * 1000)/(tempSize * lps * numThread * 8);

	printf("Run time is: %.3f ms, throughput: %.3f Mbits/sec, latency :%f ms/bit\n", running_time, through_put, latency);

	return 0;
}
