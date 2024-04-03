# >>=========================================================<<
# ||  ______         _      __            __               __||
# || /_  __/      __(_)____/ /___  __    / /__  ____ _____/ /||
# ||  / / | | /| / / / ___/ __/ / / /_  / / _ \/ __ `/ __  / ||
# || / /  | |/ |/ / (__  ) /_/ /_/ / /_/ /  __/ /_/ / /_/ /  ||
# ||/_/   |__/|__/_/____/\__/\__, /\____/\___/\__,_/\__,_/   ||
# ||                        /____/                           ||
# >>=========================================================<<
#           Tʜɪꜱ ᴘʀᴏᴊᴇᴄᴛ ᴡᴀꜱ ᴅᴇᴠᴇʟᴏᴘᴇᴅ ʙʏ TᴡɪꜱᴛʏJᴇᴀᴅ ツ
#                    ɢɪᴛʜᴜʙ.ᴄᴏᴍ/ᴍᴏᴏɴʟxɪɢʜᴛ
# This code is extra, like a different network sniffing tool. You can ignore it.
from scapy.all import *

def sniffPckt(pkt):
    pkt.show()

def start_sniff():
    scapy_sniff = sniff(prn=sniffPckt, timeout=50, iface="eth0") # stop_filter = lambda x:x.haslayer(ICMP)
    wrpcap('netlogs.pcap', scapy_sniff)

def start_read():
    scapy_cap = rdpcap('netlogs.pcap')
    ip_list = []
    for pckt in scapy_cap:
        if IP in pckt:
            if pckt[IP].src not in ip_list:
                ip_list.append(pckt[IP].src)
        else:
            pckt.show()
    print(ip_list)

print("""
    1: sniff
    2: read
    """)

choice = input(">> ")

if(choice == "1"):
    start_sniff()
elif(choice == "2"):
    start_read()
else:
    print("Please enter a correct option.")
