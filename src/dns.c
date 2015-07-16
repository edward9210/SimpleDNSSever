#include "dns.h"

void createDNSQuery(char *name, char *buf) {
	DnsHead *dnsh;
	DnsQuery *dnsq;
	char *tmp;
	int lenOfName;

	// init buf
	memset(buf, 0, sizeof(DnsHead));

	// set dns header
	dnsh = (DnsHead *)buf;
	dnsh->id = htons(HEAD_ID);
	dnsh->tag = htons(TAG);
	dnsh->qdcount = htons(1);
	dnsh->ancount = 0;
	dnsh->nscount = 0;
	dnsh->arcount = 0;

	// set dns query
	tmp = (char *)(buf + sizeof(DnsHead));
	lenOfName = chName(name, tmp);
	dnsq = (DnsQuery *)(tmp + lenOfName);
	dnsq->qtype = htons(1);
	dnsq->qclass = htons(1);
}

void createDNSAnswer(char *ip, char *buf, char *dnsq) {

}

int chName(char *fname, char *tname) {
	int i = strlen(fname) - 1;
	int j = 0;
	int k = i + 1;
	tname[i + 2] = 0;
	for (; i >= 0; i--, k--) {
		if (fname[i] == '.') {
			tname[k] = j;
			j = 0;
		}
		else {
			tname[k] = fname[i];
			j++;
		}
	}
	tname[0] = j;
	return strlen(tname) + 1;
}

void printDNSQuery(char *mes, char *name) {
	DnsHead *dnsh = (DnsHead*) mes;
	printf("***************************************\n");
	printf("             DNS Header : \n");
	printf("id : %#x\n", ntohs(dnsh->id));
	printf("tag : %#x\n", ntohs(dnsh->tag));
	printf("qdcount : %d\n", ntohs(dnsh->qdcount));
	printf("ancount : %d\n", ntohs(dnsh->ancount));
	printf("nscount : %d\n", ntohs(dnsh->nscount));
	printf("arcount : %d\n", ntohs(dnsh->arcount));
	for (int j = 0; j < (int)ntohs(dnsh->qdcount); j++) {
		char *ptr = (char *)(mes + sizeof(DnsHead));
		int count = (int) *ptr;
		int pos = 0;
		ptr += 1;
		while (1) {
			for (int i = 0; i < count; i++, pos++, ptr++)
				name[pos] = *ptr;
			name[pos] = '.';
			pos++;
			count = (int) *ptr;
			ptr++;
			if (count == 0)
				break;	
		}
		name[pos - 1] = '\0';
		printf("qname : %s\n", name);
		DnsQuery *dnsq = (DnsQuery*) ptr;
		printf("qtype : %#x\n", ntohs(dnsq->qtype));
		printf("qclass : %#x\n", ntohs(dnsq->qclass));
		// if dns query is not A query, ignore it and return '\0'
		if (ntohs(dnsq->qtype) != 0x1)
			name[0] = '\0';
	}
}
