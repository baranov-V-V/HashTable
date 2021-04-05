#pragma once

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <sys\stat.h>

struct Node {
  char* value;
  char* key;
};

typedef Node Type_t;

struct Vector {
    size_t size;
    size_t capacity;
    Type_t* data;
};

struct HashTable {
  Vector* data;

  size_t size;

  uint64_t (*hash_func)(char* value);
};

struct Text {
    char* text;
    Node* dict;

    size_t length;
    size_t lines_count;
};

const int initial_size = 883;
const int MAX_INT_LEN = 6;

uint64_t HashFunc(char* value);
Node NodeConstruct(char* key, char* value);
HashTable* ConstructTable(int initial_size, uint64_t (*HashFunc)(char* key));
void Insert(HashTable* table, Node node);
char* Find(HashTable* table, char* key);
void Delete(HashTable* table, int value);
void MakeAdd(HashTable* table);
void MakeFind(HashTable* table);
void MakeTask(HashTable* table);
void DumpTable(HashTable* table);
void DestructTable(HashTable* table);
