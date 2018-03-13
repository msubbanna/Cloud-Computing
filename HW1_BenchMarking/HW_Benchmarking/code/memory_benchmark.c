#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
//defining the total memory size to 1 GB
long long totalsize = 1024*1024*1024;
int threadcount; // count of number of threads

//function to perform the read and write function in memory
void *readwrite(void *bsize)
{	
	int i;
	int size = (int)(long)bsize;
	char *mem1 = (char*)malloc(sizeof(char) * totalsize);
	char *mem2 = (char*)malloc(sizeof(char) * size);

	for(i = 0; i < (totalsize/size)/threadcount; i++)
	{		

		memcpy(mem2, mem1 + (i * size), size);
	}
	free(mem1);
	free(mem2);	
}

//function to perform the sequential write in memory
void *seqwrite(void *bsize)
{
	
	int i;
	int size = (int)(long)bsize;
	char *mem = (char*)malloc(sizeof(char) * totalsize);
	for(i = 0; i < (totalsize/size)/threadcount; i++)
	{		
		memset(mem+(i*size), 1, size);
	}
	free(mem);
			
}

 //function to perform the random write
void *ranwrite(void *bsize)
{
	int i, ran;
	int size = (int)(long)bsize;
	char *mem = (char*)malloc(sizeof(char) * totalsize);
	
	srand((unsigned)time(NULL));
	for(i = 0; i < (totalsize/size)/threadcount; i++)
	{
		ran = rand()%((totalsize/size)/threadcount);
		memset(mem+ran, 1, size);
	}
	free(mem);
}


int main(int argc, char* argv[]){
	threadcount =1;
	// Users inputs
	if(argc != 4)
	{
		printf("Please input right command format:\n");
        	printf("Usage: %s\n", argv[0]);
        	printf("Operation: 1 for ReadWrite,2 for Sequential Write, 3 for Random Write\n");
        	printf("Block size: 1-8B, 2-8KB,3-8MB,4-80MB\n");
        	printf("Threadcount: 1, 2,4,8 Threads\n");
		exit(0);
	}

     
	int operation = atoi(argv[1]);
	int size = atoi(argv[2]);
	 threadcount = atoi(argv[3]);
	//initialization
	int i;
	int blocksize;
	pthread_t thread[threadcount];
	struct timeval starttime, endtime;
	float runtime;
	//set the blocksize
	if(size == 1)
	{
		blocksize = 8;
	}
	else if(size==2)
	{
		blocksize = (8*1024);
	}
	else if(size==3)
	{
		blocksize = (8*1024*1024);
	}
	else if(size==4)
	{
		blocksize = (80*1024*1024);
	}
	else 
	{		
		blocksize = 83886080;
	}

	// get the start time
	gettimeofday(&starttime, NULL);
	
	
		if(operation==1)
		for (i = 0; i < threadcount; i++)
		{
			pthread_create(&thread[i], NULL,readwrite, (void*)(long)blocksize);
		}	
	else if(operation==2)
		for (i = 0; i < threadcount; i++)
		{
			pthread_create(&thread[i], NULL,seqwrite, (void*)(long)blocksize);
		}
	else if(operation==3)
		for (i = 0; i < threadcount; i++)
		{
			pthread_create(&thread[i], NULL,ranwrite, (void*)(long)blocksize);
		}	
		else
		{
		printf("Error\n");
		exit(0);
		}	

	for (i = 0; i < threadcount; i++)
	{
		pthread_join(thread[i], NULL);
	}
	
	// get the end time
	gettimeofday(&endtime, NULL);
	

	// fetching the total runtime
	unsigned long long start,end;
	start = (unsigned long long)starttime.tv_sec * 1000000 + starttime.tv_usec;
	end = (unsigned long long)endtime.tv_sec * 1000000 + endtime.tv_usec;
	runtime = (float)(end - start) / 1000;
	//calculating throughput and latency
	float throughput,latency;
	if (size == 1)
	{
		latency = (float)(runtime*1000)/(totalsize*threadcount*8);
	
	}
	else{
		throughput = (float)threadcount * totalsize / runtime * 1000 / (1024*1024); 
	}
	
	//Results print 
	printf("Memory benchmark: %s\t, %s\t, %s\t", argv[1], argv[2], argv[3]);
	if (size ==1){printf("Run time: %.3f ms, Latency: %f ms/bit\n",runtime,latency);}
	else
		{printf("Run time: %.3f ms,Throughput: %.3f MB/sec \n",runtime,throughput);}
	return 0;

}
