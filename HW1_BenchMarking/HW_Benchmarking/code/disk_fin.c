# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<string.h>
# include<pthread.h>
# include<sys/types.h>
# include<sys/stat.h>
# include<fcntl.h>
# include<unistd.h>

long disksize ;


// Randomly reading accesss from disk
void *rndread(void *bsize)
{
	int i, r;
	int size = (int)(long)bsize;
	srand((unsigned)time(NULL));

	int fil;
	// opening a test file from our local disk
	fil = open("test.bat", O_RDONLY, 0666);
	if(fil < 0)
	{
		printf("Open file failed!\n");
		printf("Please create the file first!\n");
		exit(0);
	}

	// Randomly choosing file indicator to read our generated test file
	i = disksize;
	while(i>0)
	{
		r = rand()%(disksize / size);
		char *temp = (char*)malloc(sizeof(char) * size);
		// Set the positon of the file stream to the given random offset
		lseek(fil, r * size, SEEK_SET);
		// Reading the blck size of file from the disk
		read(fil, temp, size);
		i = i - size;
		free(temp);
	}

	close(fil);

}

// Sequentially reading the test file from locl disk
void *seqread(void *bsize)
{
	int i;
	int size = (int)(long)bsize;

	// Open file from the disk
	int fil;
	fil = open("test.bat", O_RDONLY, 0666);
	if(fil < 0)
	{
		printf("Open file failed!\n");
		printf("Please create the file first!\n");
		exit(0);
	}


	// Sequentially reading the data from our local disk
	i = disksize;
	while(i>0)
	{
		// Read block size of file from the disk
		char *temp = (char*)malloc(sizeof(char) * size);
		read(fil, temp, size);
		i = i - size;
		free(temp);
	}

	close(fil);

}


// Sequential writing of a file to disk
void *writeread(void *bsize)
{
	int i;
	int size = (int)(long)bsize;

	// creating a test file to local disk
	int fil,fil1;
	fil = open("test.bat", O_CREAT|O_TRUNC|O_WRONLY, 0666);
	if(fil < 0)
	{
		printf("Create test file failed!\n");
		exit(0);
	}

	char *temp = (char*)malloc(sizeof(char) * size);
	memset(temp, 'a', size);
	//randomly write the disk
	i = disksize;
	while(i>0)
	{
		write(fil, temp, size);
		i = i - size;

	}
	free(temp);
	close(fil);

	//read

	fil = open("test.bat", O_RDONLY, 0666);
	// Sequentially reading data from the disk
		i = disksize;
		while(i>0)
		{
			// Read block size of file from the disk
			char *temp = (char*)malloc(sizeof(char) * size);
			read(fil, temp, size);
			i = i - size;
			free(temp);
		}

		close(fil);
	}






int main(int argc, char *argv[])
{

	if(argc != 5)
	{
		printf("Please input right command format:\n");
        	printf("Usage: %s\n", argv[0]);
			printf("Operation: 1-RandomRead, 2-SequentialRead, 3-WriteRead\n");
        	printf("Blocksizes: 1-8B, 2-8KB, 3-8MB, 4-80MB\n");
        	printf("Threads: 1, 2  4, 8\n");
			printf("Total size(GB)\n");
		exit(0);
	}

	// Initialization
	int operation = atoi(argv[1]);
	int size = atoi(argv[2]);
	int threadcount = atoi(argv[3]);
	int dsize = atoi(argv[4]);

	disksize = 1024*1024*1024*dsize;
	float runtime;
	int i,blocksize;
	pthread_t thread[threadcount];
	struct timeval starttime, endtime;


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

	//Start time
	gettimeofday(&starttime, NULL);
	if(operation==1)
		for (i = 0; i < threadcount; i++)
		{
			pthread_create(&thread[i], NULL,rndread, (void*)(long)blocksize);
		}
	else if(operation==2)
		for (i = 0; i < threadcount; i++)
		{
			pthread_create(&thread[i], NULL,seqread, (void*)(long)blocksize);
		}
	else if(operation==3)
		for (i = 0; i < threadcount; i++)
		{
			pthread_create(&thread[i], NULL,writeread, (void*)(long)blocksize);
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


	gettimeofday(&endtime, NULL);


	unsigned long long start, end;
	start = (unsigned long long)starttime.tv_sec * 1000000 + starttime.tv_usec;
	end = (unsigned long long)endtime.tv_sec * 1000000 + endtime.tv_usec;
	runtime = (float)(end - start) / 1000;


	float throughput = (float)threadcount * disksize / runtime * 1000 / 1048576;
	float latency = (float)(runtime*1000)/(disksize*threadcount*8);

	//printf("Run time %.3f ms, %.3f MB/sec\n", runtime, throughput);
	//printf("Latency: %.3f ms/bit\n", latency);
	printf("Disk testing: %s\t, %s\t, %s\t, %s\t", argv[1], argv[2], argv[3], argv[4]);
	printf("disksize: %d GB,threadcount:%d,blockSize:%d bytes  ,Run time: %.3f ms, throughput: %.3f MB/sec, Latency: %f ms/bit\n",disksize,threadcount,blocksize, runtime, throughput,latency);
	return 0;
}
