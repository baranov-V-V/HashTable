//#include "TXLib.h"

#include "Hash.h"

#include "MyVector.cpp"

const int a_val = 2379;
const int b_val = 32456921;
const int p_val = 1013279;

const int increase_bound = 50;
const int two = 2;

uint64_t HashFunc(char* key) {
    uint64_t hash_val = 0;

    for (int i = 0; key[i] != '\0'; ++i) {
        hash_val += key[i];
    }

    return hash_val;
};

Node NodeConstruct(char* key, char* value) {
  Node node = {};
  node.value = value;
  node.key = key;
  return node;
}

HashTable* ConstructTable(int initial_size, uint64_t (*HashFunc)(char* key)) {
    HashTable* table = (HashTable*) calloc(1, sizeof(HashTable));

    table->size = initial_size;
    table->hash_func = HashFunc;

    table->data = (Vector*) calloc (initial_size, sizeof(Vector));
    for(int i = 0; i < initial_size; ++i) {
        Vector* vector_pointer = table->data + i;
        vector_pointer = ConstructVector(0);
    }

    return table;
}

void Insert(HashTable* table, Node node) {
  uint64_t pos = table->hash_func(node.key) % table->size;

  if (Find(table, node.key) != nullptr) {
    return;
  }

  PushBack(table->data + pos, node);
}

char* Find(HashTable* table, char* key) {
    int pos = table->hash_func(key) % table->size;

    for (size_t i = 0; i < VectorSize(table->data + pos); ++i) {
        Node tmp_node = GetElem(table->data + pos, i);
        if (strcmp(key, tmp_node.key) == 0) {
            return tmp_node.value;
        }
    }

    return nullptr;
}

void Delete(HashTable* table, char* key) {
    int pos = table->hash_func(key) % table->size;

    for (size_t i = 0; i < VectorSize(table->data + pos); ++i) {
        Node tmp_node = GetElem(table->data + pos, i);
        if (strcmp(key, tmp_node.key) == 0) {
            Erase(table->data + pos, i);
        }
    }
};

void MakeAdd(HashTable* table) {
    char* new_key = (char*) calloc (100, sizeof(char));
    char* new_value = (char*) calloc (100, sizeof(char));
    scanf("%s %s", new_key, new_value);

    Insert(table, NodeConstruct(new_key, new_value));
}

void MakeFind(HashTable* table) {
    char* key = (char*) calloc (100, sizeof(char));
    scanf("%s", key);

    char* found_value = Find(table, key);

    if (found_value != nullptr) {
        printf("found value: <%s>\n", found_value);
    } else {
        printf("nothing found for key: <%s>\n", key);
    }

    free(key);
}

void MakeDel(HashTable* table) {
    char* key = (char*) calloc (100, sizeof(char));
    scanf("%s", key);

    Delete(table, key);

    free(key);
}

void MakeTask(HashTable* table) {
    char command = '\0';
    scanf("\n%c ", &command);

    switch (command) {
    case '+':
        MakeAdd(table);
        break;

    case '?':
        MakeFind(table);
        break;

    case '-':
        MakeDel(table);
        break;
  }
}

void DumpTable(HashTable* table) {
    assert(table);
    printf("--TableDump--\n");
    printf("Buckets count: %ld\n", table->size);

    for(int i = 0; i < table->size; ++i) {
        printf("[%d]\n", i);
        for(int j = 0; j < VectorSize(table->data + i); ++j) {
            printf("    key: <%s> value: <%s>\n", GetElem(table->data + i, j).key, GetElem(table->data + i, j).value);
        }
    }
}


