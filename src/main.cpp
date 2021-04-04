#include "Hash.h"

#include "HashFuncs.cpp"
#include "HashTable.cpp"
#include "TestHashFuncs.cpp"

int main() {
    HashTable* table = ConstructFromFile("dict.txt", HashFunc6);

    for (int i = 0; i < 5; ++i) {
        MakeTask(table);
    }

    //DumpBucketSizes(table, "BucketSizesFunc6.csv");
    //DumpBucketGraph(table, "BucketGraphFunc6.txt");

    //system("PyPlot.py");
    //system("PlotBucketSizes.py");
    //int query_count = 0;
    //scanf("%d", &query_count);

    //for (int i = 0; i < query_count; ++i) {
      //  MakeTask(table);
    //}

    return 0;
}
