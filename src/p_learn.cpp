#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
#include <unistd.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>

#define PNUM           23
#define OIP_PROTO      0
#define OIP_TTL        1
#define OIP_TLEN       2
#define OIP_TOS        3
#define OIP_FRAGOFF    4
#define OIP_ID         5
#define OTCP_SPORT     6
#define OTCP_DPORT     7
#define OTCP_SEQ       8
#define OTCP_ACKSEQ    9
#define OTCP_DOFF      10
#define OTCP_CWR       11
#define OTCP_ECE       12
#define OTCP_URG       13
#define OTCP_ACK       14
#define OTCP_PSH       15
#define OTCP_RST       16
#define OTCP_SYN       17
#define OTCP_FIN       18
#define OTCP_WINDOW    19
#define OTCP_CHECK     20
#define OTCP_RES1      21
#define OTCP_RES2      22


// Calc size of array
#define ARRAY_LEN(Z) (sizeof(Z) / sizeof((Z)[0]))


// Hold property array
class P_Property{
protected:
	int property[PNUM];
public:
	// Input data
	void InputData(int i, int value){
		// Store input data to property
		property[i] = value;
	}
};


// Data, ML_Function
class P_Analytics : public P_Property{
public:
	P_Analytics() : P_Property(){}

	// Read TCP packet
	void ReadTCP(unsigned char *buffer){
		struct tcphdr *tcp_hdr = (struct tcphdr *)buffer;
		printf("----------- TCP ----------\n");
		printf("src port = %u\n",ntohs(tcp_hdr -> source));
		printf("dst port = %u\n",ntohs(tcp_hdr -> dest));
		InputData()
	}
		
	// Read IPv4 packet
	void ReadIPv4(unsigned char *buffer){
		struct iphdr *ip_hdr = (struct iphdr *)buffer;
		printf("----------- IP -----------\n");
		InputData(OIP_PROTO, ip_hdr -> protocol);
		InputData(OIP_TTL, ip_hdr -> ttl);
		InputData(OIP_TLEN, ntohs(ip_hdr -> tot_len));
		InputData(OIP_TOS, ip_hdr -> tos);
		InputData(OIP_FRAGOFF, ip_hdr -> frag_off);
		InputData(OIP_ID, ntohs(ip_hdr -> id));

		switch (ip_hdr -> protocol){
		case 6:
		{
			ReadTCP(buffer + sizeof(struct iphdr));
			break;
		}
		default:
		{
			break;
		}
		}
	}

	// Read arp packet  
	void ReadARP(unsigned char *buffer){
		struct ether_arp *arp_hdr = (struct ether_arp *)buffer;
		printf("----------- ARP ----------\n");
		printf("arp_hrd=%u\n",ntohs(arp_hdr -> arp_hrd));
		printf("arp_pro=%u\n",ntohs(arp_hdr -> arp_pro));
		printf("arp_hln=%u\n",arp_hdr -> arp_hln);
		printf("arp_pln=%u\n",arp_hdr -> arp_pln);
		printf("arp_op=%u\n",ntohs(arp_hdr -> arp_op));
	}

	// Read raw packet
	void ReadPacket(unsigned char *buffer){
		struct ether_header *eth_hdr = (struct ether_header *)buffer;
		switch(ntohs(eth_hdr->ether_type)){
		// ip packet
		case 2048:
		{
			ReadIPv4(buffer + sizeof(struct ether_header));
			break;
		}
		// ARP packet
		case 2054:
		{
			ReadARP(buffer + sizeof(struct ether_header));
			break;
		}
		default:
		{
			std::cout << "none." << std::endl;
			break;
		}
		}
	}
};


int main(int argc, char **argv){
	P_Analytics A;
	int sock_raw;
	int saddr_size, data_size;
	struct sockaddr saddr;
	unsigned char buffer[65535];

	// Create a raw socket that shall sniff
	sock_raw = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));

	// Error handling
	if(sock_raw < 0){
		std::cout << "Socket error." << std::endl << "Must be sudoers." << std::endl;
		assert(-1);
	}

	// Main loop
	for(int i = 0; i < 1; ++i){
		read(sock_raw, buffer, sizeof(buffer));
		A.ReadPacket(buffer);
	}
	return 0;
}
