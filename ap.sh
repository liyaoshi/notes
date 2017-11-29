#!/bin/sh
> /tmp/ap.conf
echo "network={" > /tmp/ap.conf
echo '    ssid="N331-huang-AP"' >> /tmp/ap.conf
echo '    mode=2' >> /tmp/ap.conf
echo '    key_mgmt=WPA-PSK' >> /tmp/ap.conf
echo '    psk="1234567890"' >> /tmp/ap.conf
echo '    frequency=5745' >> /tmp/ap.conf
echo '}' >> /tmp/ap.conf

ifconfig wlan0 192.168.100.99
killall -9 wpa_supplicant
wpa_supplicant -Dnl80211 -iwlan0 -c /tmp/ap.conf -B
killall -9 udhcpd
udhcpd -I 192.168.100.99 
echo 1 > /proc/sys/net/ipv4/ip_forward
iptables -t nat -A POSTROUTING -s 192.168.100/24 -o eth0 -j MASQUERADE
