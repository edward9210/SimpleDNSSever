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
