# arduino-collectd
CollectD implementation for arduino

#### Minimal collectd installation
Simplest way to test it, install collectd server on any ubuntu (including raspberry):


`apt-get install collectd`


Minimal /etc/collectd/collectd.conf configuration


**(Replace 10.255.255.1 by your internal ip, or if you have DHCP and host is not exposed to internet, use 0.0.0.0**


```
LoadPlugin csv
LoadPlugin network
<Plugin csv>
	DataDir "/var/lib/collectd/csv"
</Plugin>
<Plugin network>
	Listen "10.255.255.1" "25826"
</Plugin>
```