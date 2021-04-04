# HashTable
### The main goal of this small research is to find an effective hash function and implement it in my hash table.

#### Table of Contents
1. [Preparations](#preparations)  
2. [Testing](#testing)
2. [Results](#results)

## Preparations 
I have chosen six different hash functions to test and determine which one will be better for my hash table.\
Here are they:
* returns always 0
* returns ascii-value of first symbol
* returns length of key word
* returns sum of ascii-codes of all charecters in key word
* returns combination of 'ror' and 'xor' with ascii-code of each sybmol
* returns combination of 'rol' and 'xor' with ascii-code of each sybmol

Implementation of all of the hash-fuctions can be found in "srs/TestHashFuncs.cpp"

### Testing

### Results

