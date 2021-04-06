# HashTable
### The main goal of this small research is to find an effective hash function, implement it in my hash table, and optimize it.

### Table of Contents
1. [Preparations](#preparations)  
2. [Testing hash functions](#testing)
3. [Results in testing hash function](#results)
4. [Optimizing hash table](#optimization)
5. [Results in optimizing](#conclusion)
### Preparations 
I have chosen seven different hash functions to test and determine which one will be better for my hash table.\
Here are return values of hash-functions:
1. [returns always 0](#first)
2. [returns ascii-value of first symbol](#second)
3. [returns length of key word](#third)
4. [returns sum of ascii-codes of all charecters in key word](#fourth)
5. [returns combination of 'ror' and 'xor' with ascii-code of each sybmol](#fifth)
6. [returns combination of 'rol' and 'xor' with ascii-code of each sybmol](#sixth)
7. [return value calculated by crc64 algorithm](#seventh)

Realization of all of the hash-fuctions can be found in "srs/TestHashFuncs.cpp".

### Testing
I will use all of this hash functions in a hash table which will perform as a Eng-Rus dictionary. In this hash table collisions will be solved by using chains.
Testing results will be demonstrated in two types of graphs:
1. X-axes represents bucket number in hash table and Y-axes shows the amount of elements in that bucket
2. X-axes shows bucket size and Y-axes shows the total amount of buckets with that size

Second graphs will be more representative for efficient hash funtions, so i will use them in hash funcions 4 to 7. 

* [First function](#first)
* [Second function](#second)
* [Third function](#third)
* [Fourth function](#fourth)
* [Fifth function](#fifth)
* [Sixth function](#sixth)
* [Seventh function](#seventh)

#### First

This function is really bad ~~no comments~~.\
<img src="Pictures\GraphFunc1.JPG" width="640" height="450px">

#### Second

A little better than previous one, but buckets with no. 98-120 are only used so it is not very useful in hash table.\
<img src="Pictures\GraphFunc2.JPG" width="640" height="450px">

<img src="Pictures\GraphFunc2.1.JPG" width="640" height="450px">

#### Third

Now buckets with no. 2-15 are mostly used so it is as useless as second one.\
<img src="Pictures\GraphFunc3.JPG" width="640" height="450px">

<img src="Pictures\GraphFunc3.1.JPG" width="640" height="450px">

#### Fourth

This is already a quite good funtion but average chain size is 20 and there are still many empty buckets.\
<img src="Pictures\HistFunc4.JPG" width="640" height="450px"> <img src="Pictures\GraphFunc4.JPG" width="640" height="450px">

#### Fifth

There are fewer empty bucket than in the previous one but the distribution is rather bad: peaks with more than 30 elems in one bucket appear often. In can be clearly seen in following graph:\
<img src="Pictures\HistFunc5.JPG" width="640" height="450px">

<img src="Pictures\GraphFunc5.JPG" width="640" height="450px">

#### Sixth

Both distribution and number of empty buckets are better than in function with 'ror'. However we can achieve even better results with crc64.\
<img src="Pictures\HistFunc6.JPG" width="640" height="450px">

<img src="Pictures\GraphFunc6.JPG" width="640" height="450px">

#### Seventh

Practically there is no empty buckets the graphs are amazing. It is just crc64.\
<img src="Pictures\HistFunc7.JPG" width="640" height="450px">

<img src="Pictures\GraphFunc7.JPG" width="640" height="450px">

### Results
Crc64 hash function turned out to be the most effective since it has the lowest number of empty buckets, overall distribution is excellent and the average length of chain is rather small, which means hash table will respond very fast.

### Optimization
* [Stating problem](#problem)
* [Optimizing hash function](#Hash)
* [Optimizing find function](#Find)
* [Final optimization results](#Result)

#### Problem
First, lets measure all working time of my hash table. I will be finding translation of every word in a big text for many times so working time will be recogniziby big and easy and accurate to measure. Also, i will measure working time of hash function, function finding word and function to insert (wich constists of find and insert in chain)

Function name | Working time
------------ | -------------
Hash | 1.57 sec
Find | 0.70 sec
All Table | 4.65 sec

Total work time:

<img src="Pictures\ValGrind1.JPG" width="auto" height="auto">

Other process time took functions to read from file and construct dictionary, we don't optimize them since they are not functions of hash table.

#### Hash
As we can see, it takes almoust half of our working time to calculate hash, and 3/4 of all hash-table working time. I will use crc32 intrinsic here.
Also i will make a series of measurements to lower measurement uncertainty.

Muasurement no. | 1 | 2 | 3 | 4 | 5 | Average
----------------|---|---|---|---|---|-------- 
Old hash func | 1.57 sec | 1.63 sec | 1.52 sec | 1.50 sec | 1.54 sec | 1.55 sec 
New hash func | 0.87 sec | 0.81 sec | 0.83 sec | 0.89 sec | 0.80 sec | 0.84 sec
Intrisic func | 0.15 sec | 0.17 sec | 0.18 sec | 0.18 sec | 0.17 sec | 0.17 sec

The increase in speed is almost 10 times which is very good. However this acceleration is hardware dependent so it is only available on x86 processors.

Total work time after all hash func optimizations:

<img src="Pictures\ValGrind2.JPG" width="auto" height="auto">

#### Find

Now since we optimized the slowest part of our hash table, lets look at function which is the second in speed. After hash is calculated we go down a chain and compare keys in nodes with key to find. In order to make it faster we can store key-strings in avx registers (_m256i_ type in C) (because they can store up to 32 bytes and most of the english words are shorter than 32 symbols). So again we will use intrinsics functions to compare avx registers efficiently.

Muasurement no. | 1 | 2 | 3 | 4 | 5 | Average
----------------|---|---|---|---|---|-------- 
Old find | 0.78 sec | 0.80 sec | 0.81 sec | 0.75 sec | 0.78 sec | 0.79 sec 
New find | 0.50 sec | 0.53 sec | 0.47 sec | 0.49 sec | 0.50 sec | 0.51 sec

So the increase in work time in 7/4 times
#### Results
Total work time after find func optimizations:

<img src="Pictures\ValGrind3.JPG" width="auto" height="auto">

By using all of this functions i can get very fast hash table and it is faster than -O3 in 1.45 times.

### Conclusion

Using all this optimizations i made a hash table wich is very efficient and can be implemented is your program. Text me! 
https://vk.com/baranov_v_v
