# HashTable
### The main goal of this small research is to find an effective hash function and implement it in my hash table.

#### Table of Contents
1. [Preparations](#preparations)  
2. [Testing](#testing)
3. [Results](#results)
### Preparations 
I have chosen six different hash functions to test and determine which one will be better for my hash table.\
Here are return values of hash-functions:
1. returns always 0
2. returns ascii-value of first symbol
3. returns length of key word
4. returns sum of ascii-codes of all charecters in key word
5. returns combination of 'ror' and 'xor' with ascii-code of each sybmol
6. returns combination of 'rol' and 'xor' with ascii-code of each sybmol

Realization of all of the hash-fuctions can be found in "srs/TestHashFuncs.cpp".

### Testing
I will use all of this hash functions in a hash table which will perform as a Eng-Rus dictionary. In this hash table collisions will be solved by using chains.
Testing results will be demonstrated in two types of graphs:
1. X-axes represents bucket number in hash table and Y-axes shows the amount of elements in that bucket
2. X-axes shows bucket size and Y-axes shows the total amount of buckets with that size

Second graphs will be more representative for efficient hash funtions, so i will use them in hash funcions from 4 to 6. 

* [First](#first)
* [Second](#second)
* [Third](#third)
* [Fourth](#fourth)
* [Fifth](#fifth)
* [Sixth](#sixth)
* [Conclusion](#conclusion)

#### First

<img src="Pictures\GraphFunc1.JPG" width="auto" height="auto">

#### Second Function

<img src="Pictures\GraphFunc2.JPG" width="auto" height="auto">

#### Third

<img src="Pictures\GraphFunc3.JPG" width="auto" height="auto">

#### Fourth

<img src="Pictures\HistFunc4.JPG" width="auto" height="auto">

<img src="Pictures\GraphFunc4.JPG" width="auto" height="auto">

#### Fifth

<img src="Pictures\HistFunc5.JPG" width="auto" height="auto">

<img src="Pictures\GraphFunc5.JPG" width="auto" height="auto">

#### Sixth

<img src="Pictures\HistFunc6.JPG" width="auto" height="auto">

<img src="Pictures\GraphFunc6.JPG" width="auto" height="auto">

#### Conclusion


### Results
The 6th hash function turned out to be the most effective since it has the lowest number of buckets without elements and overall distribution is close to normal and the average length of chain is rather small, which means hash table will respond faster to queries.
