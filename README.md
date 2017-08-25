# ubuntu 16.04 clone vm from exist image
	virt-clone -o ubuntu16 -n mysql -f /var/lib/libvirt/images/mysql.img 	
# git proxy over socat
user@PowerEdge-T630-78:~$ cat bin/gitproxy  
#!/bin/sh   
_proxy=192.168.1.1  
_proxyport=888  
username=liyaoshi  
password=4rfv3edC  
exec socat STDIO PROXY:$_proxy:$1:$2,proxyport=$_proxyport,proxyauth=$username:$password  
  
user@PowerEdge-T630-78:~$ cat .gitconfig  
[core]  
        gitproxy = gitproxy  

# gerrit install 
 sudo adduser gerrit  
 sudo su gerrit  
 java -jar gerrit.war init -d /home/gerrit/gerrit  
# Apache proxy pass
<VirtualHost 136.18.227.58:8888>  
ProxyRequests Off  
<Proxy *>  
        Order deny,allow  
        Allow from all  
        AuthType Basic  
        AuthName "Restricted Content"  
        AuthUserFile /etc/apache2/.htpasswd  
        Require valid-user  
</Proxy>  
AllowEncodedSlashes on  
ErrorLog ${APACHE_LOG_DIR}/gerrit/error.log  
CustomLog ${APACHE_LOG_DIR}/gerrit/access.log combined  

ProxyPass / http://192.168.18.58:8080/  
ProxyPassReverse / http://192.168.18.58:8080/  
</VirtualHost>  

# bash alias
	export CPUNUMBER=`grep -c processor /proc/cpuinfo`  
	alias m="make -j $CPUNUMBER"  ARCH=arm  
	alias mm="make -j $CPUNUMBER"  
	export INSTALL_MOD_PATH=~/.  
	alias bb="python -m CGIHTTPServer 1234"  
	export DISPLAY=`who |grep ${USER} |tail -n 1 | cut -d\\( -f2 |cut -d\\) -f1`:0  

# Ubuntu 14.04 run ia32 app
	apt-get install  zlib1g:i386  
	apt-get install libstdc++6:i386  
# Markdown syntax site
https://daringfireball.net/projects/markdown/syntax
# ssh no passwd
/home/liyaoshi/authorized_keys
# ubuntu start br0 instead of eth0
	apt-get install bridge-utils    
xhuang10@ubuntu:~$ cat /etc/network/interfaces  
source /etc/network/interfaces.d/*  
auto lo  
iface lo inet loopback  
auto br0  
iface br0 inet static  
bridge_stp off  
bridge_fd 0  
bridge_maxwait 0  
address 192.168.122.4  
netmask 255.255.255.0  
gateway 192.168.122.1  
bridge_ports ens3  

# Python Upload server
	https://github.com/stackp/Droopy/blob/master/droopy

