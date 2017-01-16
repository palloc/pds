#include<stdio.h> //For standard things
#include<stdlib.h>    //malloc
#include<string.h>    //memset
#include<netinet/ip_icmp.h>   //Provides declarations for icmp header
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<sys/socket.h>
#include<arpa/inet.h>
 

typedef struct {
	int duration;
	int ip_proto;
	int service;
	int src_bytes;
	int dst_bytes;
	int flag;
	int land;
	int wrong_fragment;
	int urgent;

	int hot;
	int num_failed_logins;
} a_packet;

int main()
{
	int sock_raw;
    int saddr_size , data_size;
	int i=0, j=0;

    struct sockaddr saddr;
    struct in_addr in;

	// Make buffer
    unsigned char *buffer = (unsigned char *)malloc(65536);

    //Create a raw socket that shall sniff
    sock_raw = socket(AF_INET , SOCK_RAW , IPPROTO_TCP);

    if(sock_raw < 0)
    {
        printf("Socket Error\n");
        return 1;
    }

	//sniff packet
    while(i<10)
    {
		j=0;
		i++;
        saddr_size = sizeof saddr;
        //Receive a packet
        data_size = recvfrom(sock_raw, buffer, 65536, 0, &saddr, &saddr_size);
		struct iphdr *ip_hdr = (struct iphdr*)buffer;
		for(j; j < 1000; ++j){
			printf("%d", *(buffer+j));
		}
		printf("\n");
    }
    printf("Finished");
    return 0;
}
 

