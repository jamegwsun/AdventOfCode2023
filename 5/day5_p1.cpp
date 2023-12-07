#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int64_t> get_ranges(std::string line)
{
    // I really need a regex refresher
    std::vector<int64_t> numbers;
    int64_t subtotal = -1;
    for (int i = 0; i < line.size(); i++)
    {
        if (isdigit(line[i]))
        {
            if (subtotal == -1)
            {
                subtotal = 0;
            }
            subtotal = subtotal * 10 + line[i] - '0';
        }
        if (line[i] == ' ' | i == line.size() - 1)
        {
            if (subtotal > -1)
            {
                numbers.push_back(subtotal);
                subtotal = -1;
            }
        }
    }
    return numbers;
}

int main()
{
    std::ifstream f("input.txt");
    std::string line;

    std::getline(f, line);
    std::vector<int64_t> numbers;
    std::vector<int64_t> seeds = get_ranges(line); // get seeds form the first line
    std::vector<bool> converted;

    int64_t source;
    int64_t dest;
    int64_t source_cap;

    while (std::getline(f, line))
    {
        // refresh
        if (line == "")
        {
            converted = std::vector<bool>(5, false); // syntax?
        }

        numbers = get_ranges(line);
        // skip non number lines
        if (numbers.size() == 0)
        {
            continue;
        }
        dest = numbers[0];
        source = numbers[1];
        source_cap = numbers[1] + numbers[2];

        for (int i = 0; i < seeds.size(); i++)
        {
            // already converted
            if (converted[i] == true)
            {
                continue;
            }

            if ((seeds[i] >= source) & (seeds[i] < source_cap))
            {
                std::cout << seeds[i] << " -> ";
                converted[i] = true;
                seeds[i] += (dest - source);
                std::cout << seeds[i] << '\n';
            }
        }
    }
    std::cout << *std::min_element(seeds.begin(), seeds.end());
}