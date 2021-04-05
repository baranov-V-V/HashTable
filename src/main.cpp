#include "Hash.h"

#include "HashFuncs.cpp"
#include "HashTable.cpp"
#include "TestHashFuncs.cpp"

int main() {
    HashTable* table = ConstructFromFile("dict.txt", HashFunc7);

    DumpBucketSizes(table, "BucketSizesFunc7.csv");
    DumpBucketGraph(table, "BucketGraphFunc7.txt");

    DestructTable(table);

    return 0;
}
