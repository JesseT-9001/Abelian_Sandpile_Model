#include "sandpile.h"
#include <thread>

// define a function that takes a Sandpile by reference and returns a bool (to indicate if the Sandpile is stable)

bool is_stable(Sandpile &sandpile)
{
    int limit = sandpile.size();

    for (int i = 0; i<limit; i++)
    {
        for (int j=0; j<limit; j++)
        {
            if (sandpile[i][j] >= 4)
            {
                return false;
            }
        }
    }
    return true;

}

void stabilize(Sandpile &sandpile)
{
    int limit = sandpile.size();

    for (int i = 0; i<limit; i++)
    {
        for (int j=0; j<limit; j++)
        {
            if (sandpile[i][j] >= 4)
            {
                sandpile[i][j] -= 4;

                // left check
                if (i-1 >= 0){
                    sandpile[i-1][j] += 1;
                }

                // top check
                if (j-1 >= 0)
                {
                    sandpile[i][j-1] += 1;
                }

                // right check
                if (i+1 < limit)
                {
                    sandpile[i+1][j] += 1;
                }

                // bottom check
                if (j+1 < limit)
                {
                    sandpile[i][j+1] += 1;
                }
            }
        }
    }    
    
}

void stabilize_threaded(Sandpile &sandpile)
{
    int limit = sandpile.size();

    // Chunks must be at least of size 3. Thread count divided by limit dictates the chunk size. 
    int thread_count = 0, chunks = 0;
    for (int i = 4; i>0; i--)
    {
        chunks = limit/i;
        if (chunks > 2)
        {
            thread_count = i;
            break;
        }
    }

    // Used to flatten critical point
    auto flatten = [&](int i, int j)
    {
        sandpile[i][j] -= 4;

        // left check
        if (i-1 >= 0){
            sandpile[i-1][j] += 1;
        }

        // top check
        if (j-1 >= 0)
        {
            sandpile[i][j-1] += 1;
        }

        // right check
        if (i+1 < limit)
        {
            sandpile[i+1][j] += 1;
        }

        // bottom check
        if (j+1 < limit)
        {
            sandpile[i][j+1] += 1;
        }
    };

    // Function for threads to use.
    auto threaded_compute_f = [&](int start_x, int end_x)
    {
        for (int i = start_x; i<end_x; i++)
        {
            for (int j = 0; j<limit; j++)
            {
                if (sandpile[i][j] > 3)
                {
                    flatten(i, j);
                }
            }
        }
    };

    // Goes to the end of each chunk and checks/flattens vector -2 from chunks end. This provides seperation need for the threads to not cause a race condition
    for (int i = 1; i<thread_count; i++)
    {
        for (int j = 0; j<2; j++)
        {
            for (int k = 0; k<limit; k++)
            {
                int x = (i*thread_count-2) + j;
                if (sandpile[x][k] > 3)
                {
                    flatten(x, k);
                }
            }
        }
    }

    // This section creates the threads
    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (int i = 0; i < thread_count; ++i)
    {
        int start_x = i*thread_count;
        int end_x = i*thread_count+chunks;

        // Because we are doing integer division, if we add up the chunks, we may have less covered than the actual size.
        // Solution: last thread takes the rest of the sandpile.
        if (i == thread_count-1){
            threads.emplace_back(std::thread(threaded_compute_f, start_x, limit));
        }
        else
        {
        threads.emplace_back(std::thread(threaded_compute_f, start_x, end_x));
        }
    }

    for (auto &th: threads)
    {
        th.join();
    }
}