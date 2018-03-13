val input = sc.textFile("hdfs://ec2-18-220-240-122.us-east-2.compute.amazonaws.com:9000/data/input/128gb")
val output = input.map(x=> (x.substring(0,10),x.substring(10,x.length))).sortByKey(true, 1).map(x => x._1.toString + x._2.toString + "\r")
output.saveAsTextFile("hdfs://ec2-18-220-240-122.us-east-2.compute.amazonaws.com:9000/data/output")