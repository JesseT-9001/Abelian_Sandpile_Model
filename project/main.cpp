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
        sandpile = create_sandpile(argv[1], argv[2]);
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
    bool result = false;
    while (!result){
        result = is_stable(sandpile);
        steps.emplace_back(sandpile);
    }
    animate(steps);
}
