#include <iostream>
#include <string>
#include <assert.h>
#include <unistd.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/ip.h>
#include <netinet/if_ether.h>

// Number of property
#define PNUM 23
// Calc size of array
#define ARRAY_LEN(Z) (sizeof(Z) / sizeof((Z)[0]))


// Keep packet property
class P_property{
protected:
	int property[PNUM];
public:
	P_property(){}

	// Input data
	void Input_data(int *value){
		// Error handling
		if(ARRAY_LEN(value) != PNUM){
			std::cout << "Invalid input length." << std::endl;
			assert(-1);
		}else{
			// Store input data to property
			for(int i = 0; i < ARRAY_LEN(value); ++i){
				property[i] = value[i];
			}
		}
	}
};


// Data, ML_Function
class P_Analytics : public P_property{
public:
	P_Analytics() : P_property(){}

	// Read IPv4 packet
	void ReadIPv4(unsigned char *buffer){
		struct iphdr *ip_hdr = (struct iphdr *)buffer;
		printf("----------- IP -----------\n");
		printf("version=%u\n",ip_hdr -> version);
		printf("ihl=%u\n",ip_hdr -> ihl);
		printf("tos=%x\n",ip_hdr -> tos);
		printf("tot_len=%u\n",ntohs(ip_hdr -> tot_len));
		printf("id=%u\n",ntohs(ip_hdr -> id));
		printf("ttl=%u\n",ip_hdr -> ttl);
		printf("protocol=%u\n",ip_hdr -> protocol);
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

		// ipv6 paceket
		case 34525:
		{
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

	for(int i = 0; i < 1; ++i){
		read(sock_raw, buffer, sizeof(buffer));
		A.ReadPacket(buffer);
	}
	return 0;
}
