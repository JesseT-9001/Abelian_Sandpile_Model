#pragma once

#include <vector>

using Row = std::vector<int>;
using Sandpile = std::vector<Row>;
using Animation = std::vector<Sandpile>;

// forward declare a function that takes a Sandpile by reference and returns a bool (to indicate if the Sandpile is stable)
