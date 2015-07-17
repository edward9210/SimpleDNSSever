/************************************************************
**  Copyright (C) 2015-2016, XXX Co. Ltd.
**  All rights reserved.
**
**  FileName: dns.h
**  Description: the header file of dns.c
**  Author: Guocheng Wu
**  Date: 2015.7.17
**  Others: None  
***********************************************************/
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HEAD_ID 0x1020
#define QUERY_TAG 0x0100
#define ANSWER_TAG 0x8180
#define ANSWER_NAME 0xC00C

/**********************************************************
		                DNS Header
	0			                                    16 bits
	+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      ID                       |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |QR|   Opcode  |AA|TC|RD|RA|   Z    |   RCODE   |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    QDCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ANCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    NSCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                    ARCOUNT                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+

**********************************************************/

typedef struct _DNS_HEAD {
	unsigned short id;
	unsigned short tag;
	unsigned short qdcount;
	unsigned short ancount;
	unsigned short nscount;
	unsigned short arcount;
}DnsHead;

/**********************************************************
			             DNS Query
	0			                                    16 bits
	+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                     QNAME                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QTYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     QCLASS                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+		  

**********************************************************/

typedef struct _DNS_QUERY {
	unsigned short qtype;
	unsigned short qclass;
}DnsQuery;

/**********************************************************
			             DNS Answer
	0			                                    16 bits
	+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                                               |
    /                                               /
    /                      NAME                     /
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TYPE                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                     CLASS                     |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                      TTL                      |
    |                                               |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+
    |                   RDLENGTH                    |
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--|
    /                     RDATA                     /
    /                                               /
    +--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+ 

**********************************************************/

typedef struct __attribute__((packed)) _DNS_ANSWER {
	unsigned short name;
	unsigned short type;
	unsigned short cls;
	unsigned int ttl;
	unsigned short rdlen;
	unsigned int rddata;
}DnsAnswer;

/***********************************************************************/
//  Function: createDNSQuery
//  Description: create a dns query packet.
//  Param: 
//          name, char*, [IN], the name of the server you want to query.
//          buf, char*, [OUT], the buffer for dns query packet.
//  Return: void
/***********************************************************************/
void createDNSQuery(char *name, char *buf);

/***********************************************************************/
//  Function: createDNSAnswer
//  Description: create a dns response packet.
//  Param: 
//          ip, char*, [IN], the ip address.
//          buf, char*, [OUT], the buffer for dns response packet.
//          dnsOriginQuery, char*, [IN], the origin dns query packet.      
//  Return: void
/***********************************************************************/
void createDNSAnswer(char *ip, char *buf, char *dnsOriginQuery);

/***********************************************************************/
//  Function: chName
//  Description: build a domain name represented as a sequence of labels
//  Param: 
//          fname, char*, [IN], the origin string
//          tname, char*, [OUT], the domain name represented as a sequence 
//                              of labels
//  Return: the length of the tname
/***********************************************************************/
int chName(char *fname, char *tname);

/***********************************************************************/
//  Function: printDNSQuery
//  Description: parse and print the dns query packet 
//  Param: 
//          mes, char*, [IN], the origin dns query packet.
//          name, char*, [OUT], the name which dns query packet contains.
//  Return: void
/***********************************************************************/
void printDNSQuery(char *mes, char *name);
