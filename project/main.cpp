#include <string>
#include <vector>
#include <iostream> // Here for testing purposes. Remove befor submittings.

#include <ruc-sci-comp/animate.hpp>

#include "sandpile.h"
#include "make_sandpile.h"

void run_simulation(Sandpile &sandpile);

int main(int argc, char **argv)
{
    if (argc == 2)
    {
        // Make sandpile from file.
        Sandpile sandpile = read_sandpile_file(argv[1]);
        run_simulation(sandpile);
    }
    else if (argc == 3)
    {
        // Make sandpile using random generator.
        int s = std::stoi(argv[1]);
        int n = std::stoi(argv[2]);
        Sandpile sandpile = create_sandpile(s, n);
        run_simulation(sandpile);
    }
}

void run_simulation(Sandpile &sandpile)
{
    Animation steps(1,sandpile);
    bool result = false;
    while (result==false){
        result = is_stable(sandpile);
        steps.emplace_back(sandpile);
    }
    animate(steps);
}
