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

<img src="Pictures\Gprof1.1.JPG" width="auto" height="auto">

As we can see, the most of the working time take "Crc32NotOprimized" hash fucntion with working time of 8.2 sec and "Find" function with working time of 7.83 sec. In total they take more than 95% of all working time of my hash table, so we are going to optimize them.

#### Hash
As we can see from the profile picture above, Hash function is the slowest one, so we'll try to speed up it. A good way to make hash calculate faster is using crc32 intrinsic function. One disadvantage of this method of optimizing is that it is hardware based and only works on computers with x86 architecture.

The picture below shows us new working times of functions in hash table. In this test we implemented new hash function based on crc32 intrinsic which is called "Crc32Optimized".
The program is compiled with -O1 so that compiler can inline functions for speed.

<img src="Pictures\Gprof2.1JPG" width="auto" height="auto">

As we can see, the working speed of our hash function decreased from 8.2 sec to 0.8 sec which means that the acceleration is 10 times.

#### Find

Now since we optimized the slowest part of our hash table, lets look at function which is the slowest now. It is find function which can be seen in profile pictures as "Find". In order to speed it up we need to understand how it works. So when we want to find a word we 1)calculate hash of key-word 2)go down a chain which is responsible for that hash value and compare keys in nodes with key to find. 

So by making new inline compare stings function we can achieve greater performances since strcmp is ineffective. 
Firstly, lets rewrite string compare function using inline asm in C in order to make faster because of less memory accesses.

<img src="Pictures\Gprof3.1JPG" width="auto" height="auto">

it gave us slightly better speed: decrease of total work time from 7.4 sec to 5.4 sec. (5.4 sec is the sum of "MyStrCmp" and "Find" functions) 

In order to make it even faster we can store key-strings in avx registers which is _m256i_ type in C. Our key words is less than 32 symbols long so there won't be any problems in storing. So again we will use intrinsics functions to compare avx registers efficiently.

<img src="Pictures\Gprof4.1JPG" width="auto" height="auto">

As we can see now it takes only 3.8 sec instead of 7.4 to find all words. It is the best result that we can get using hard

#### Results
Lets look at working times of all unoptimized functions with -O3 optimization and fully optimized hash table:

<img src="Pictures\Gprof5(-O3).1.JPG" width="auto" height="auto">

As we can see the overall working time of program is 12.1 sec (main function time). 

<img src="Pictures\Gprof4.1.JPG" width="auto" height="auto">

And the total work time of full optimized hash table is 4.8 sec (main function time).

So optimized hash table is 2.5 times faster than an unoptimized table compiled in -O3. Such increase in speed over -O3 can be explained: gcc compiler don't undertstand when to use crc32 intrin function, so we use it as a great advantage.

### Conclusion

Using all this optimizations i made a hash table that is 2.5 times faster than the same unoptimized table compiled with -O3. So It is very efficient and can be implemented is your programmes.\
Text me! 
https://vk.com/baranov_v_v
