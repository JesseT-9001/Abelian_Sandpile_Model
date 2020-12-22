#include <string>
#include <vector>

#include <ruc-sci-comp/animate.hpp>

#include "sandpile.h"
#include "make_sandpile.h"

void run_simulation(Sandpile &sandpile);

int main(int argc, char **argv)
{
    Sandpile sandpile;

    if (argc == 2)
    {
        // Make sandpile from file.
        sandpile = read_sandpile_file(argv[1]);
    }
    else if (argc == 3)
    {
        // Make sandpile using random generator.
        int s = std::stoi(argv[1]);
        int n = std::stoi(argv[2]);
        sandpile = create_sandpile(s, n);
    }
    else
    {
        return 0;
    }
    
    run_simulation(sandpile);
}

void run_simulation(Sandpile &sandpile)
{
    Animation steps(1,sandpile);
    while (!is_stable(sandpile)){
        // stabilize(sandpile);
        stabilize_threaded(sandpile);
        steps.emplace_back(sandpile);
    }
    animate(steps);
}
