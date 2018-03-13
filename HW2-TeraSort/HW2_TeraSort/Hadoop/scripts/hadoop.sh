




echo "Downloading and unzipping"
sudo wget http://apache.claz.org/hadoop/common/hadoop-2.8.2/hadoop-2.8.2.tar.gz
sudo tar -zxvf hadoop-2.8.2.tar.gz
sudo rm -rf hadoop-2.8.2.tar.gz


echo "Installing Hadoop"
sudo cd /data/hadoop
sudo mv hadoop-2.8.2 /data/hadoop/

sudo cp /data/hadoop/hadoop-2.8.2/etc/hadoop/mapred-site.xml.template /data/hadoop/hadoop-2.8.2/etc/hadoop/mapred-site.xml


echo "updating bashrc"
sudo cat << bashrc >> ~/.bashrc
#HADOOP VARIABLES START
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
export HADOOP_INSTALL=/data/hadoop
export PATH=$PATH:$HADOOP_INSTALL/bin
export PATH=$PATH:$HADOOP_INSTALL/sbin
export HADOOP_MAPRED_HOME=$HADOOP_INSTALL
export HADOOP_COMMON_HOME=$HADOOP_INSTALL
export HADOOP_HDFS_HOME=$HADOOP_INSTALL
export YARN_HOME=$HADOOP_INSTALL
export HADOOP_COMMON_LIB_NATIVE_DIR=$HADOOP_INSTALL/lib/native
export HADOOP_OPTS="-Djava.library.path=$HADOOP_INSTALL/lib"
export HADOOP_OPTS=-Djava.net.preferIPv4Stack=true
export CONF=/data/hadoop/etc/hadoop


#HADOOP VARIABLES END
bashrc
source ~/.bashrc

echo "updating hadoop-env.sh"
sudo cat << hadoop-env >> /data/hadoop/hadoop-2.8.2/etc/hadoop/hadoop-env.sh
export JAVA_HOME=/usr/lib/jvm/java-8-openjdk-amd64
hadoop-env


echo "updating core-site.xml"
sudo cat > /data/hadoop/hadoop-2.8.2/etc/hadoop/core-site.xml << core-site
<?xml version="1.0" encoding="UTF-8"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
 <property>
<name>fs.default.name</name>
<value>hdfs://localhost:9000</value>
</property>
<property>
<name>hadoop.tmp.dir</name>
<value>/data/tmp/</value>
</property>

</configuration>
core-site

echo "updating hdfs-site.xml"

sudo cat > /data/hadoop/hadoop-2.8.2/etc/hadoop/hdfs-site.xml << hdfs-site
<?xml version="1.0" encoding="UTF-8"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
 <property>
<name>dfs.replication</name>
<value>1</value>
</property>
<property>
<name>dfs.namenode.name.dir</name>
<value>file:/data/hadoop/hadoop_data/hdfs/namenode</value>
</property>
<property>
<name>dfs.datanode.data.dir</name>
<value>file:/data/hadoop/hadoop_data/hdfs/datanode</value>
</property>
<property>
<name>dfs.permissions</name>
<value>false</value>
</property>

</configuration>
hdfs-site

sudo echo "updating yarn-site.xml"
sudo cat > /data/hadoop/hadoop-2.8.2/etc/hadoop/yarn-site.xml << yarn-site
<?xml version="1.0" encoding="UTF-8"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
  <property>
<name>yarn.nodemanager.aux-services</name>
<value>mapreduce_shuffle</value>
</property>
<property>
<name>yarn.nodemanager.aux-services.mapreduce.shuffle.class</name>
<value>org.apache.hadoop.mapred.ShuffleHandler</value>
</property>

</configuration>
yarn-site

echo "updating mapred-site.xml"
sudo cat << mapred-site >> /data/hadoop/hadoop-2.8.2/etc/hadoop/mapred-site.xml 
<?xml version="1.0"?>
<?xml-stylesheet type="text/xsl" href="configuration.xsl"?>
<configuration>
 <property>
    <name>yarn.app.mapreduce.am.resource.mb</name>
    <value>1228</value>
</property>
<property>
    <name>yarn.app.mapreduce.am.command-opts</name>
    <value>-Xmx983m</value>
</property>
<property>
    <name>mapreduce.map.memory.mb</name>
    <value>1228</value>
</property>
<property>
    <name>mapreduce.reduce.memory.mb</name>
    <value>1228</value>
</property>
<property>
    <name>mapreduce.map.java.opts</name>
    <value>-Xmx983m</value>
</property>
<property>
    <name>mapreduce.reduce.java.opts</name>
    <value>-Xmx983m</value>
</property>
<property>
<name>mapred.job.shuffle.input.buffer.percent</name>
<value>0.20</value>
</property>
<property>
<name>mapreduce.cluster.local.dir</name>
<value>/data/tmp/mapred/local</value>
</property>

</configuration>
mapred-site

