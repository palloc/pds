#include <stdio.h> //For standard things
#include <stdlib.h>    //malloc
#include <string.h>    //memset
#include <net/if.h>
#include <net/ethernet.h>

// packet property
typedef struct {
	int duration;
	int protocol_type;
	int service;
	int flag;
	int src_bytes;
	int dst_bytes;
	int land;
	int wrong_fragment;
	int urgent;
	int hot;
	int num_failed_logins;
	int logged_in;
	int num_compromised;
	int root_shell;
	int su_attempted;
	int num_root;
	int num_file_creations;
	int num_shells;
	int num_access_files;
	int num_outbound_cmds;
	int is_host_login;
	int is_guest_login;
	int count;
	int srv_count;
	int serror_rate;
	int srv_serror_rate;
	int rerror_rate;
	int srv_rerror_rate;
	int same_srv_rate;
	int diff_srv_rate;
	int srv_diff_host_rate;
	int dst_host_count;
	int dst_host_srv_count;
	int dst_host_same_srv_rate;
	int dst_host_diff_srv_rate;
	int dst_host_same_src_port_rate;
	int dst_host_srv_diff_host_rate;
	int dst_host_serror_rate;
	int dst_host_srv_serror_rate;
	int dst_host_rerror_rate;
	int dst_host_srv_rerror_rate;
} a_packet;

// print mac address
char *mac_ntoa(u_char *d){
	static char str[18];
	sprintf(str,"%02x:%02x:%02x:%02x:%02x:%02x",d[0],d[1],d[2],d[3],d[4],d[5]);
	return str;
}

// convert decimal to binary
int d_to_b(int decimal){
	int binary = 0;
	int base = 1;

	while(decimal>0){
		binary = binary + ( decimal % 2 ) * base;
		decimal = decimal / 2;
		base = base * 10;
	}
	return binary;
}
	
int main(){
	FILE *fp;
	fp = fopen("log.pcap", "wb");
	int sock_raw;
    int saddr_size , data_size;
	int i=0, j=0;
    struct sockaddr saddr;
	// Make buffer
    unsigned char *buffer = (unsigned char *)malloc(65536);

    //Create a raw socket that shall sniff
    sock_raw = socket(PF_PACKET ,SOCK_RAW ,htons(ETH_P_ALL));
	// Error process
    if(sock_raw < 0){
        printf("Socket Error\n");
        return 1;
    }

	//sniff packet
    while(i < 1){
		i++;
		//Receive a packet
        read(sock_raw, buffer, sizeof(buffer));
		struct ether_header *eth_hdr = (struct ether_header *)buffer;

		switch(ntohs(eth->ether_type)){
		//ip packet
		case ETH_P_IP:
			break;
		//ipv6 packet
		case ETH_P_IPV6:
			break;
		//arp packet
		case ETH_P_ARP:
			break;
		default:
			break;
			
    }

    printf("Finished");
    return 0;
}
 

