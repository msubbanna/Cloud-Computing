Setup & Execution Process for Hadoop Sort
•	Open terminal
•	Copy the SortHadoop.java file to "hadoop" installation folder in system using cp command
•	Change working directory to ../hadoop/sbin
•	Start hadoop by running ./start-all.sh command
•	Run jps command to ensure hadoop status, assuming it works fine then
•	Compile Hadoop_Sort.java using below command
		./bin/hadoop com.sun.tools.javac.Main HadoopSort.java
•	Create directory in HDFS using command
		e.g.: hdfs dfs -mkdir -p input
•	Copy input file to hdfs using command
		hdfs dfs -put input/filename
•	Run program by using below coomand
		./bin/hadoop jar HadoopSort.jar HadoopSort input output
•	Copy output file by using below command
		hdfs dfs -get output/*
•	Check output file using valsort
----------------------------------------------------------------------------------------------------
