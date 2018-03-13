#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <pthread.h>

unsigned long no_operations = 50000000;
int threadcount;

//operation for integer calculations
void* opr_int(void* arg)
{   
    int a=1, b=2, c=3,d=4,e=5,f=6,g=7,h=8,i=9,j=10,k=11,l=12,m=13,n=14,o=15,p=16,q=17,r=18,s=19,t=20;  
    unsigned long count;
    for(count=0; count<no_operations/threadcount; count++)
    {
        a=a+b;
        b=b+c;
        c=c+d;
        d=d+e;
       /** e=e+f;
        f=f+g;
        g=g+h;
        h=h+i;
        i=i+j;
        j=j+k;
        k=l-k;
        l=m-l;
        m=n-m;
        n=o-n;
        o=p-o;
        p=q-p;
        q=r-q;
        r=s-r;
        s=t-s;
        t=t+a; **/
    }
    return NULL;
}

//operations for float benchmark
void* opr_float(void* arg)
{  
	float a=1.0,b=2.0,c=3.0,d=4.0,e=5.0,f=6.0,g=7.0,h=8.0,i=9.0,j=10.0,k=11.0,l=12.0,m=13.0,n=14.0,o=15.0,p=16.0,q=17.0,r=18.0,s=19.0,t=20.0; 
	unsigned long count;
    for(count=0; count<no_operations/threadcount; count++)
    {
		a=a+b;
        b=b+c;
        c=c+d;
        d=d+e;
       /** e=e+f;
        f=f+g;
        g=g+h;
        h=h+i;
        i=i+j;
        j=j+k;
        k=l-k;
        l=m-l;
        m=n-m;
        n=o-n;
        o=p-o;
        p=q-p;
        q=r-q;
        r=s-r;
        s=t-s;
        t=t+a; **/
    }
    
    return NULL;
}


int main(int argc, char** argv)
{
   	struct timeval tv;
    long long start, stop;
    double sec;
	threadcount = 1;	
	int operation =1;
	int i;
	//input from console
	if(argc != 3)
	{
		printf("Please input right command format:\n");
        printf("Program: %s\n", argv[0]);
		printf("Processor speed: 1 for GIOP,2 for GFLOP\n");
		printf("ThreadCount: 1, 2,4,8 Threads\n");		

		exit(0);
	}
       
	operation = atoi(argv[1]);
	threadcount = atoi(argv[2]);
	    
    pthread_t p[threadcount]; 
   //calculating GIOPS
 if (operation ==1) {
	 
    gettimeofday(&tv, NULL);
    start = tv.tv_sec*1000000LL + tv.tv_usec;
	
    for(i=0; i<threadcount; i++)
    {
       pthread_create(&p[i], NULL, opr_int, NULL);
    }
   
    for(i=0; i<threadcount; i++)
    {
        pthread_join(p[i], NULL);
    }
	gettimeofday(&tv, NULL);
    stop = tv.tv_sec*1000000LL + tv.tv_usec;
    sec = (stop-start)/1000000.0;
    printf("Time taken for operations for GIOPS: %lf\n", sec);
    printf("%lf GIOPS\n", (no_operations*4.*threadcount)/(sec*100000000.)*2); 
 }
 //calculating GFLOPS
 if(operation==2){
    
    gettimeofday(&tv, NULL);
    start = tv.tv_sec*1000000LL + tv.tv_usec;

    for(i=0; i<threadcount; i++)
    {
       pthread_create(&p[i], NULL, opr_float, NULL);
    }
  
    for(i=0; i<threadcount; i++)
    {
        pthread_join(p[i], NULL);
    }
	gettimeofday(&tv, NULL);
    stop = tv.tv_sec*1000000LL + tv.tv_usec;
    sec = (stop-start)/1000000.0;
    printf("Time taken for operations for GLOPS: %lf\n", sec);
    printf("%lf GFLOPS\n", (no_operations*4.*threadcount)/(sec*100000000.)*2);  
    
 }
    return 0;
}