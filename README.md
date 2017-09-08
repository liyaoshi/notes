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
 or
	java -jar gerrit.war init --batch -d ~/gerrit_testsite 
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
# Get mac Address and ip Address 
	ifconfig eth0 | grep -o -E '([[:xdigit:]]{1,2}:){5}[[:xdigit:]]{1,2}'
	ifconfig eth0 | grep -oP '(?<=inet addr:)[0-9.]*'
# Generate 1M 0xFF file
	dd if=/dev/zero bs=1024 count=1024 | tr "\000" "\377" > testfile
# Jacinto create android bootimg
	out/host/linux-x86/bin/mkbootimg  --kernel out/target/product/jacinto6evm/kernel --ramdisk out/target/product/jacinto6evm/ramdisk.img --base 0x80000000 --ramdisk_offset 0x01f00000 --output out/target/product/jacinto6evm/boot.img
	make_ext4fs -s -T -1 -S out/target/product/jacinto6evm/root/file_contexts -L system -l 805306368 -a system out/target/product/jacinto6evm/obj/PACKAGING/systemimage_intermediates/system.img out/target/product/jacinto6evm/system out/target/product/jacinto6evm/system
	
# i.MX6 android make boot.img
	out/host/linux-x86/bin/mkbootimg  --kernel out/target/product/sabreauto_6q/kernel 
		--ramdisk out/target/product/sabreauto_6q/ramdisk.img 
		--cmdline "console=ttymxc3,115200 init=/init video=mxcfb0:dev=ldb,bpp=32 video=mxcfb1:off video=mxcfb2:off video=mxcfb3:off vmalloc=320M androidboot.console=ttymxc3 consoleblank=0 androidboot.hardware=freescale cma=384M" 
		--base 0x14000000 --second out/target/product/sabreauto_6q/$DTS_BOARD  
		--output out/target/product/sabreauto_6q/boot.img; \
		out/host/linux-x86/bin/boot_signer 
		/boot out/target/product/sabreauto_6q/boot.img 
		build/target/product/security/verity.pk8 
		build/target/product/security/verity.x509.pem 
		out/target/product/sabreauto_6q/boot.img; 
# VFIO 	
	https://www.kernel.org/doc/Documentation/vfio.txt  
	http://www.fp7-save.eu/papers/EUC2014B.pdf  
	https://www.linux-kvm.org/images/b/b3/01x09b-VFIOandYou-small.pdf  
	http://www.virtualopensystems.com/en/services/vfio-full-gpu-virtualization/  
# KVM on omap5
	http://www.virtualopensystems.com/en/solutions/guides/kvm-svirt-omap5/  
# Open project manager 
	https://opensource.com/business/16/3/top-project-management-tools-2016
