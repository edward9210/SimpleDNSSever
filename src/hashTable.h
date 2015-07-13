#include <string.h>
#include <stdio.h>

#define HASHSIZE 100
#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct _hash_node
{
	char *name;
	char *ip;
	struct _hash_node *next;

}HashNode;

static HashNode* hashTable[HASHSIZE];

void initHashTable();
unsigned int hash(char *name);
HashNode* search(char *name);
BOOL add(char *name, char *ip);
BOOL delete(char *name);
void dispalyTable();
void removeAll();
