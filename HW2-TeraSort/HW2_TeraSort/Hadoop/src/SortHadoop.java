import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class SortHadoop
{

	// this is the mapper class 
	public static class MyMapper
		extends Mapper<Object, Text, Text, Text>
	{
		private Text Key;
		private Text Value;
		public void map(Object key, Text value, Context context) 
			throws IOException, InterruptedException
		{
			StringTokenizer itr = new StringTokenizer(value.toString());
			Key = new Text(value.toString().substring(0,10));	
			Value = new Text(value.toString().substring(10));
			context.write(Key, Value);
		}
	}
	//the reducer class 
	
	public static class MyReducer extends Reducer<Text,Text,Text,Text>
	{
		private Text strLine = new Text();
		private Text strNewValue = new Text();
		public void reduce(Text Key, Text Value, Context context) 
			throws IOException, InterruptedException
		{
			strLine.set(Key.toString() + Value.toString());
			strNewValue.set("");
			context.write(strLine, strNewValue);
		}
	}
	

	//main function
	public static void main(String[] args) throws Exception
	{
		
		Configuration conf = new Configuration();           // initialize Configuration object
		conf.set("mapred.textoutputformat.separator", "");

		
		Job job = Job.getInstance(conf, "Hadoop Sort");        //define job class
		
		job.setJarByClass(HadoopSort.class); //define mapper class
		
		job.setMapperClass(MyMapper.class);   // define mapper
		
		job.setCombinerClass(MyReducer.class);
		
		job.setReducerClass(MyReducer.class);
		
		job.setOutputKeyClass(Text.class);    // set outputkey
		
		job.setOutputValueClass(Text.class);
		
		job.setMapOutputKeyClass(Text.class); // set mapoutput
		
		job.setMapOutputValueClass(Text.class);
		
		FileInputFormat.addInputPath(job, new Path(args[0]));
		
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		
		System.exit(job.waitForCompletion(true) ? 0 : 1);
	}
	/

}