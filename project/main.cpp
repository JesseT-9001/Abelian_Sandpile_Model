#include <string>
#include <vector>
#include <iostream> // Here for testing purposes. Remove befor submittings.

#include <ruc-sci-comp/animate.hpp>

#include "sandpile.h"
#include "make_sandpile.h"

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        // Make sandpile from file.
        Sandpile sandpile = read_sandpile_file(argv[1]);
    }
    else if (argc == 3)
    {
        // Make sandpile using random generator.
        int s = std::stoi(argv[1]);
        int n = std::stoi(argv[2]);
        Sandpile sandpile = create_sandpile(s, n);

    }
    
    else
    {
        return 1;
    }
}
