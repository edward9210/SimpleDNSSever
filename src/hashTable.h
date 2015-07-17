/************************************************************
**  Copyright (C) 2015-2016, XXX Co. Ltd.
**  All rights reserved.
**
**  FileName: hashTable.h
**  Description: the header file of hasTable
**  Author: Guocheng Wu
**  Date: 2015.7.17
**  Others: None  
***********************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define HASHSIZE 100
#define BOOL int
#define TRUE 1
#define FALSE 0

typedef struct _HASH_NODE
{
	char *name;
	char *ip;
	struct _HASH_NODE *next;

}HashNode;

static HashNode* hashTable[HASHSIZE];

/*************************************************/
//	Function: initHashTable 
//	Description: init the hash table
//	Param: void
//	Return: void
/*************************************************/
void initHashTable();

/*************************************************/
//	Function: hash
//	Description: calculate the hash value of the 
//				 given name
//	Param: 
//			name, char*, [IN], a string of name 
//	Return: the hash value of the name
/*************************************************/
unsigned int hash(char *name);

/*************************************************/
//	Function: search
//	Description: search the name whether it is in
//				the hash table or not
//	Param: 
//			name, char*, [IN], a string of name 
//	Return: the pointer of a HashNode if exists
/*************************************************/
HashNode* search(char *name);

/*************************************************/
//	Function: add
//	Description: add the pair (name --> ip) into the
//				hash table.
//	Param: 
//			name, char*, [IN], a string of name 
//			ip, char*, [IN], a string of IP
//	Return: BOOL
/*************************************************/
BOOL add(char *name, char *ip);

/*************************************************/
//	Function: delete
//	Description: delete the name in the hash table.
//	Param: 
//			name, char*, [IN], a string of name 
//	Return: BOOL
/*************************************************/
BOOL delete(char *name);

/*************************************************/
//	Function: displayTable
//	Description: display hash table
//	Param: void
//	Return: void
/*************************************************/
void dispalyTable();

/*************************************************/
//	Function: removeAll
//	Description: remove all data in the hash table.
//	Param: void
//	Return: void
/*************************************************/
void removeAll();
