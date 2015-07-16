#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <string.h>

#define HEAD_ID 0x1020
#define TAG 0x0100

/**********************************
		       DNS Header
	0			                  16 bits
	-------------------------------
	|			   ID             |
	-------------------------------
	|QR|OPCODE|AA|TC|RD|RA|Z|RCODE|    ----> TAG
	-------------------------------
	|			QDCOUNT			  |
	-------------------------------
	|			ANCOUNT			  |
	-------------------------------
	|			NSCOUNT			  |
	-------------------------------
	|			ARCOUNT			  |
	-------------------------------
***********************************/

typedef struct _DNSHEAD {
	unsigned short id;
	unsigned short tag;
	unsigned short qdcount;
	unsigned short ancount;
	unsigned short nscount;
	unsigned short arcount;
}DnsHead;

/**********************************
			  DNS Query
	0			                  16 bits
	-------------------------------
	|			 QNAME            |    --->length variable
	-------------------------------
	|			 QTYPE            |
	-------------------------------
	|			 QCLASS           |
	-------------------------------			  
***********************************/

typedef struct _DNSQUERY {
	unsigned short qtype;
	unsigned short qclass;
}DnsQuery;

/**********************************
			  DNS Answer
	0			                  16 bits
	-------------------------------
	|			 NAME             |    --->length variable
	-------------------------------
	|			 TYPE             |
	-------------------------------
	|			 CLASS            |
	-------------------------------	
	|            TTL              |
	-------------------------------
	|            RDLENGTH         |	
	-------------------------------
	|            RDATA            |
	-------------------------------	  
***********************************/

typedef struct _DNSANSWER {
	unsigned short type;
	unsigned short cls;
	unsigned short ttl;
	unsigned short rdlen;
	unsigned short rddata;
}DnsAnswer;

void createDNSQuery(char *name, char *buf);
void createDNSAnswer(char *ip, char *buf, char *dnsq);
int chName(char *fname, char *tname);
void printDNSQuery(char *mes, char *name);
