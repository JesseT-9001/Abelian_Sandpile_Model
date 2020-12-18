#include "sandpile.h"

// define a function that takes a Sandpile by reference and returns a bool (to indicate if the Sandpile is stable)

bool is_stable(Sandpile &sandpile)
{
    bool stable = true;
    int limit = sandpile.size();

    for (int i = 0; i<limit; i++)
    {
        for (int j=0; j<limit; j++)
        {
            if (sandpile[i][j] >= 4)
            {
                stable = false;
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
    return stable;

}