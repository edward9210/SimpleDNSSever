/************************************************************
**  Copyright (C) 2015-2016, XXX Co. Ltd.
**  All rights reserved.
**
**  FileName: hashTable.c
**  Description: the implementation of hasTable
**  Author: Guocheng Wu
**  Date: 2015.7.17
**  Others: None  
***********************************************************/
#include "hashTable.h"

void initHashTable() 
{
	for(int i = 0; i < HASHSIZE; i++)
	{
		hashTable[i] = NULL;
	}
}

unsigned int hash(char *name) 
{
	unsigned int hashValue = 0;
	for (; *name != '\0'; name++)
	{
		hashValue += *name;
	}
	return hashValue % HASHSIZE;
}

HashNode* search(char *name) 
{
	unsigned int hashValue = hash(name);
	HashNode* ptr = hashTable[hashValue];
	while (ptr) 
	{
		if (strcmp(name, ptr->name) == 0)
			return ptr;
		ptr = ptr->next;
	}
	return NULL;
}

BOOL add(char *name, char *ip) 
{
	// if name exist, cannot modify
	HashNode* ptr;
	ptr = search(name);
	if (ptr)
		return FALSE;

	// else, calculate the hash value
	unsigned int hashValue = hash(name);
	ptr = hashTable[hashValue];
	HashNode* tmp = (HashNode*)malloc(sizeof(HashNode));
	tmp->name = (char*)malloc(sizeof(char)  * (strlen(name) + 1));
	tmp->ip = (char*)malloc(sizeof(char)  * (strlen(ip) + 1));
	strcpy(tmp->name, name);
	tmp->name[strlen(name)] = '\0';
	strcpy(tmp->ip, ip);
	tmp->ip[strlen(ip)] = '\0';
	tmp->next = NULL;
	if (ptr == NULL) 
	{
		hashTable[hashValue] = tmp;
	}
	else 
	{
		while (ptr->next) 
		{
			ptr = ptr->next;
		}
		ptr->next = tmp;
	}
	return TRUE;
}

BOOL delete(char *name) 
{
	unsigned int hashValue = hash(name);
	HashNode* ptr = hashTable[hashValue];
	HashNode* pre = NULL;
	while (ptr) 
	{
		if (strcmp(ptr->name, name) == 0) 
		{
			if (pre == NULL) 
			{
				hashTable[hashValue] = ptr->next;
			}
			else 
			{
				pre->next = ptr->next;
			}
			free(ptr);
			ptr = NULL;
			return TRUE;
		}
		pre = ptr;
		ptr =  ptr->next;
	}
	return FALSE;
}

void dispalyTable() 
{
	HashNode* ptr;
	for (int i = 0; i < HASHSIZE; i++) 
	{
		printf("[%d] : ", i);
		ptr = hashTable[i];
		while (ptr) 
		{
			printf("{%s-->%s}, ", ptr->name, ptr->ip);
			ptr = ptr->next;
		}
		printf("\n");
	}
}

void removeAll() 
{
	HashNode *ptr, *tmp;
	for (int i = 0; i < HASHSIZE; i++) 
	{
		if (hashTable[i] != NULL) 
		{
			ptr = hashTable[i];
			while (ptr) 
			{
				tmp = ptr->next;
				free(ptr);
				ptr = tmp;
			}
			hashTable[i] = NULL;
		}
	}
}