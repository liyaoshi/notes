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

