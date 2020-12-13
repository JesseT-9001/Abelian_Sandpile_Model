#pragma once
#include <fstream>
#include <string>
#include <vector>
#include <fmt/format.h>

std::string serialize(const std::vector<std::vector<std::vector<int>>> &animation)
{
    auto frame_count = animation.size();
    auto size = animation[0].size();
    std::string filename = fmt::format("sandpile_{}.bin", frame_count, size);
    std::ofstream frame_data(filename, std::ios::binary);
    frame_data.write(reinterpret_cast<const char*>(&frame_count), sizeof(int));
    frame_data.write(reinterpret_cast<const char*>(&size), sizeof(int));
    for (auto &frame : animation)
    {
        for (auto &line : frame)
        {
            frame_data.write(reinterpret_cast<const char*>(line.data()), sizeof(int) * size);
        }
    }
    return filename;
}
