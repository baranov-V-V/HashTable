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
First, lets measure working time of each function in my hash table and determine which ones are the most time-consuming. I will be finding translation of every word in a big text for many times so working time will be easy and accurate to measure. To profile my programme i will use GNU gprof. On all the following screenshots with GNU gprof results we don't take into account "_mcount_private_" and "__fentry__" functions because they belong only to the profiler, not the hash table.

Working time of each function compiled with -O0:

<img src="Pictures\Gprof1.1JPG" width="auto" height="auto">

As we can see, the most of the working time take Hash fucntion with working time of 8.2 sec and Find function with working time of 7.83 sec. In total they take more than 95% of all working time of my hash table, so we are going to optimize them.

#### Hash
As we can see from the profile picture above, it takes almoust all of our working time to calculate hash. I will use crc32 intrinsic here.

Look at Crc32Optimized hash function which speed increased from 12.4 sec to 1.3 sec:

<img src="Pictures\Gprof2.JPG" width="auto" height="auto">

The total increase in speed of Crc32 hash function is more than 10 times which is very good. However this acceleration is hardware dependent so it is only available on x86 processors.

#### Find

Now since we optimized the slowest part of our hash table, lets look at function which is the second in speed. After hash is calculated we go down a chain and compare keys in nodes with key to find. In order to make it faster we can store key-strings in avx registers (_m256i_ type in C) (because they can store up to 32 bytes and most of the english words are shorter than 32 symbols). So again we will use intrinsics functions to compare avx registers efficiently.

Results after implementing _m256i_ are not so optimistic. The decrease in speed can be seen clearly. The work time of Find function increased from 2.4 sec to 12.0 sec:

<img src="Pictures\Gprof3.JPG" width="auto" height="auto">

However, lets try to rewrite strcmp function using inline asm. By using this we still don't get increase in speed. Find function nowe works for 3.3 sec instead of 2.4 sec:

<img src="Pictures\Gprof6.JPG" width="auto" height="auto">

So we will leave this Find function as it was before all optimizations.

#### Results
Let look at working time of all functions with -O3 optimization:

<img src="Pictures\Gprof5(-O3).JPG" width="auto" height="auto">

It is still significantly lower than with our opimizations:

<img src="Pictures\Gprof2.JPG" width="auto" height="auto">

Furher optimizations are not useful to implement because we increased performances of all the hash table functions and other function in my program are not related to hash table.

### Conclusion

Using all this optimizations i made a hash table that is 3 times faster than -O3.So It is very efficient and can be implemented is your programmes Text me! 
https://vk.com/baranov_v_v
