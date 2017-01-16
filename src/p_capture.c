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
 

