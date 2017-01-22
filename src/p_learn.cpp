#include <iostream>
#include <string>
#include <assert.h>
#include <net/if.h>
#include <net/ethernet.h>



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
			for(i = 0; i < ARRAY_LEN(value); ++i){
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
		switch(ntohs(eth_hdr->ether_type)){
		// ip packet
		case ETH_P_IP:
			break;
		// ipv6 paceket
		case ETH_P_IPV6:
			break;
		// ARP packet
		case ETH_P_ARP:
			break;
	}


};
	

int main(int argc, char **argv){
	P_property A;
	
	cout << A.property[0] << endl;
	A.Test();
	cout << A.property[0] << endl;
}
