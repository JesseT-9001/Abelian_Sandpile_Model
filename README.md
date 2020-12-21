# Abelian Sandpile Model

## Introduction

The abelian sandpile model is an algorithmic model that abstractly captures the self-organizing behavior of sandpiles flattening into a stable state. In this project, we will be implementing the abelian sandpile model's algorithm steps on a two-dimensional square vector array (sandpile) filled with integers ranging from 0 to n such that n is some arbitrary number greater than 0.

The basic rundown of steps in the algorithm are as follows:
1. Scan the sandpile such that you visit each position in the sandpile exactly once per round.
2. If there is a position that holds a value greater or equal to four, touch the position by subtracting 4 and adding 1 to the left, top, bottom, and right of the position. If one of these positions fall outside the square, that addition is ignored.
3. Repeat steps 1 and 2 until we can scan the entire sandpile without touching any of the positions. Once we can complete a scan without doing any touches, we call this sandpile state stable and end the algorithm returning the results.

## Program Flow

Main can receive one (filename) or two (size, number) arguments, all other numbers of arguments simply return main with nothing being done. Upon receiving one of the two arguments, it decides which way to create a sandpile object. 

If one argument is given then it calls `read_sandpile_file` from make_sandpile.cpp, passing to it a string of type `char*`. From here, we read the file into the program, and using a string buffer, read the file line by line, converting each line into a row into our sandpile. After the file is read into the sandpile it returns the result.

If two arguments are given, we pass the values to `create_sandpile` also located in make_sandpile.cpp. Here we convert the char* values into integers using `stringstream`<sup>1</sup> and then with the resulting ints create a row filled with zeros according to the size (s) given and then a sandpile filled with rows also according to the size (s) given, leaving us with s by s matrix of zeros. We then create a random engine seeded with 1337 and a uniform integer distribution from 0 to s-1. The reason for s-1 is because the uniform integer distribution is upper bound inclusive, meaning it may give us a value s which would be an index outside of our matrix. We then iterate a given number of times and upon each iteration choose a random x and y value to a one to the matrix. Again, once this is complete, we return the resulting sandpile.

Before further processing, we take a snapshot of the initial state by creating an `Animation` object and initializing it to our current sandpile state.

Next, we process the sandpile until it is stable using a while loop breaking only when `is_stable` returns true. 'is_stable' is defined in sandpile.cpp takes a sandpile by reference and applies the Abelian sandpile model algorithm to it.

After `is_stable` returns the result is recorded and the current state of the sandpile is placed inside our `Animation` object. The result is then checked, if it's not true then it'll go again inside the while loop, otherwise, it'll dump the resulting `Animation` object into the `animation` function where python is used to produce the graphic in an HTML format.

## Challenges

I initially created this program multi-threaded. When scanning the sandpile, I used up to 4 threads and made sure the work was split between the threads such that each thread should receive no less than 10 rows along with having sections size/"number of thread", which would minimize the chance of a race condition. I was able to get it working and produce the same looking results as the single-threaded version, however, it didn't pass the tests. I guess that when accessing the sandpile reference it counted as multiple touches or perhaps some artifacts were being returned that I didn't fully understand.

## Improvements

First I'd implement error checking and helpful error messages throughout the code.

Another "improvement" would be making the sandpile environment into a class. This would probably allow us to have multiple sandpiles interacting with one another.

To speed things up slightly, without using multithreading, we can implement a data structure with a hash map to keep track of only the positions with a value of 4 or greater and use those positions to modify the sandpile instead of rescanning the whole thing.

## References

1. Converting Strings to Numbers in C/C++. (2018, September 06). Retrieved December 18, 2020, from https://www.geeksforgeeks.org/converting-strings-numbers-cc/