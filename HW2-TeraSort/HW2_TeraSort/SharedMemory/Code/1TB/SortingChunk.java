import java.io.*;

public class SortingChunk extends Thread{
	
	
	 public static int partNumber = 0;
		public void run()
		{		
			try
			{	
				while(true)
				{
					int i = getPartNumber();
					if(i >= SharedMemory.splitCount)
						break;
					else
					sortFile("/data/raid" +"/part" +i);
					
				}
				
			}
			catch (IOException e)
			{
				e.printStackTrace();
			}
		}
		
		
		synchronized public static int getPartNumber()
		{
			return partNumber++;
				
		}
			
		
		public static void sortFile(String file) throws IOException
		{
			
			LineNumberReader lineRead= new LineNumberReader(new FileReader(file));
			while (lineRead.readLine()!= null)
			{}
			int lineCount = lineRead.getLineNumber();
			lineRead.close();
					
			
			String[] fileData = new String[lineCount];
			BufferedReader buffread= new BufferedReader(new FileReader(new File(file)));
			String str = buffread.readLine(); 
			int i=0;
			
			while(str != null)
			{
				fileData[i] = str;
				str = buffread.readLine();
				i++;
			}
			buffread.close();
				
			
			sort(fileData, 0 , fileData.length);
				
			
			FileWriter writer = new FileWriter(new File(file));
			for (int j = 0; j < fileData.length; j++)
			{
				writer.write(fileData[j] + "\n");					
			}
				writer.close();
		}


private static void sort(String str[], int off, int len)
	{

		int middle = off + (len >> 1),
		l = off,
		n = off + len - 1;
		middle = median (str, l, middle, n);
		String pilot = str[middle];
		
		
		int left = off;
		int right = off + len - 1;
		while(true)
		{
			while (left <= right && (str[left].compareTo(pilot) < 0))
				left++;
			while (right >= left && (str[right].compareTo(pilot) > 0))
				right--;
			if (left > right)
				break;
			
			int a = left++;int b=right--;
	                
			String temp = str[a];
			str[a] = str[b];
			str[b] = temp;
		} 
			if (right + 1 - off > 1)
			sort (str, off, right + 1 - off);
			if (off + len - left > 1)
			sort (str, left, off + len - left);
	}
		
		
		private static int median(String str[], int a, int b, int c)
		{
					
			if(str[a].compareTo(str[b]) < 0)
			{
				if(str[b].compareTo(str[c]) < 0)
				{
					return b;
				}
				else if(str[a].compareTo(str[c]) < 0)
				{
					return c;
				}
				else return a;
			}
			else
			{
				if(str[b].compareTo(str[c]) > 0)
				{
					return b;
				}
				else if(str[a].compareTo(str[c]) > 0)
				{
					return c;
				}
				else return a;
			}
			
		}
		




}
