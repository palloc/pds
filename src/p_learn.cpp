#include <iostream>
#include <string>
#include <assert.h>
#include <unistd.h>
#include <net/if.h>
#include <net/ethernet.h>
#include <netinet/ip.h>

// Number of property
#define PNUM 23
// Calc size of array
#define ARRAY_LEN(Z) (sizeof(Z) / sizeof((Z)[0]))


// Keep packet property
class P_property{
protected:
	int property[PNUM];

public:
	P_property(){
		property[0] = {};
	}

	// Input data
	void Input_data(int value[]){
		// Error transaction
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
class Kmeans : public P_property{
public:
	Kmeans() : P_property(){}
	// Read raw packet
	void ReadPacket(unsigned char *buffer){
		struct ether_header *eth_hdr = (struct ether_header *)buffer;
		std::cout << ntohs(eth_hdr->ether_type) << std::endl;
		switch(ntohs(eth_hdr->ether_type)){

		// ip packet
		case 0:
		{
			struct iphdr *ip_hdr = (struct iphdr *)buffer;
			std::cout << ip_hdr->protocol << std::endl;
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
			break;
		}

		default:
		{
			break;
		}
		}
	}
};
	

int main(int argc, char **argv){
	Kmeans A;
	int sock_raw;
	int saddr_size, data_size;
	struct sockaddr saddr;
	unsigned char *buffer;
	buffer = new unsigned char[65536];

	// Create a raw socket that shall sniff
	sock_raw = socket(PF_PACKET, SOCK_RAW, htons(ETH_P_ALL));
	// Error process
	if(sock_raw < 0){
		std::cout << "Socket error." << std::endl;
		return 1;
	}

	for(int i = 0; i < 1; ++i){
		read(sock_raw, buffer, sizeof(buffer));
		A.ReadPacket(buffer);
	}
	delete[] buffer;
	return 0;
}
