# rDSN.tools.log.monitor
Monitor all critical logs for rDSN applications in cluster

### Problem

Something bad happens in the cluster, and we don't know why.

### Solution

Through the tool API in rDSN, we are able to redirect the critical logs to a centralized log master. 

### Build

```
git clone git@github.com:imzhenyu/rDSN.tools.log.monitor.git
cd rDSN.tools.log.monitor
dsn.run.sh build --type release
dsn.run.sh install
```

You should get two modules generated: ```libdsn.tools.log.monitor.master.so``` and ```libdsn.tools.log.monitor.slave.so``` (or You should get two modules generated: ```dsn.tools.log.monitor.master.dll``` and ```dsn.tools.log.monitor.slave.dll``` on Windows).

### Use

Start a log master node by using the following configuration, say uing port 54333 for receiving remote logs.
```
[modules]
dsn.tools.common
dsn.tools.log.monitor.master

[apps.log.monitor.master]
type = log.monitor.master
ports = 54333
pools = THREAD_POOL_DEFAULT

[core]
tool = nativerun
```

For rDSN applications to be monitored (i.e., log monitor slaves), adding the following configurations.

```
[modules]
dsn.tools.log.monitor.slave

[core]
logging_aspects = log.monitor.slave 

[tools.log.monitor]
master = log-master-hostname:54333
```

Then you should be able to see from the screen of the log master all the critical logs (log-level >= WARNING) from all slaves. 


