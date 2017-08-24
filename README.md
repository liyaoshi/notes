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
export DISPLAY=`who |grep ${USER} |tail -n 1 | cut -d\( -f2 |cut -d\) -f1`:0  

