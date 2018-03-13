import java.io.*;
import java.util.*;


public class SharedMemory  {
  // public static final int InputFileLength = 1306122448;
public static final  BigInteger InputFileLength =new BigInteger("10801224480");
   public static final int  chunkCount = 600;
   public static final BigInteger chunkSizee = InputFileLength.divide(BigInteger.valueOf(chunkCount)) ;
   public static final int chunkSize = chunkSizee.intValue();
   public static String chunkFileSize[] = new String [chunkSize];
   static int splitCount = 0;
   static int threadCount = 4;
  
	
	
	public static void main(String[] args){

		Date d=new Date();
    	long t1=d.getTime();
      System.out.println("Diving input file into Chunks");
      	try {
			chunking();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
    	
	System.out.println("Chunking complete, sorting chunks"); 
      	SortingChunk threads[] = new SortingChunk[threadCount];
    
		for(int i = 0; i< threads.length; i++)
		{
			threads[i] = new SortingChunk();
		}
					
		//start threads
		for(int i = 0; i< threads.length; i++)
			{
				threads[i].start();
			}
				
		//Join threads
		for(int i = 0; i< threads.length; i++)
		{
			try {
				threads[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		System.out.println("Sorting of individual files complete, final run ! Merger for output");
		try {
			mergeFiles();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
      	
	Date d2=new Date();
	long t2=d2.getTime(); 
	System.out.println(("Time Taken "+(t2-t1)/1000)+"s"); 
	
	
	
	
	}

	
	private static void chunking() throws IOException {
		// TODO Auto-generated method stub
		BufferedReader buffread = new BufferedReader(new FileReader("/data/raid/input"));	
		String input = buffread.readLine(); 
		while(input != null) 
		{	
			FileWriter writer = new FileWriter(new File("/data/raid" +"/part" +splitCount));
			int i=0;
			while(i < chunkSize)
			{
				writer.write(input);
				writer.write("\n");
				input = buffread.readLine();
				if (input == null)
					break;
				i++;	
			}
			splitCount++;
			writer.close();
		}
		
		buffread.close();
	}

	public static void mergeFiles() throws IOException
	{
		String[] input = new String[splitCount];		
	
		BufferedReader[] buffread = new BufferedReader[splitCount];
		for(int i = 0; i < splitCount; i++)
		{
			buffread[i] = new BufferedReader(new FileReader(new File("/data/raid"+"/part" +i)));			
			input[i] = buffread[i].readLine();
		}
		
		
		BufferedWriter writer = new BufferedWriter(new FileWriter(new File("/data/raid" +"/sortedFile")));		
			
	
		
		
		while(true)
		{
			int index = -1; int i=0; 

		while(i < input.length)
		{
			if(input[i]!= null)
				index=i;
		i++;
		}
			

			if(index == -1) 
				break;
			String smallest = input[index];
			int j =1; 
			while(j < input.length)
			{
				if(input[j] != null)
				{
					if (smallest.compareTo(input[j]) >= 0)
					{
						smallest = input[j];
						index = j;
					}
				}
			j++;
									
			}
			
			writer.write(input[index] + " \n"); //write in output file
			
			
			input[index] = buffread[index].readLine();
			
		}
						
		writer.close(); 
						
		
		for(int i  = 0;i < buffread.length; i++)
		{
			buffread[i].close();
			
		}
	}
		
	



}
