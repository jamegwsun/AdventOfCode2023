#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

std::vector<int64_t> get_numbers(std::string line)
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

std::vector<std::pair<int64_t, ino64_t>> get_ranges(std::string line)
{
    // I really need a regex refresher
    std::vector<int64_t> numbers = get_numbers(line);
    std::vector<std::pair<int64_t, ino64_t>> ranges;
    for (int j = 0; j < numbers.size() / 2; j++)
    {
        ranges.push_back({numbers[j * 2], numbers[j * 2] + numbers[j * 2 + 1] - 1});
    }

    return ranges;
}

int main()
{
    std::ifstream f("input.txt");
    std::string line;

    std::getline(f, line);
    std::vector<int64_t> numbers;
    std::vector<std::pair<int64_t, ino64_t>> ranges = get_ranges(line);

    std::vector<std::pair<int64_t, ino64_t>> buffer;
    std::vector<std::pair<int64_t, ino64_t>> converted;

    int64_t dest;
    int64_t src_low;
    int64_t src_upp;
    int64_t convert;

    int64_t seed_low;
    int64_t seed_upp;

    while (std::getline(f, line))
    {
        // In every new category, push the converted buffer back to seeds
        if (line == "")
        {
            ranges.insert(ranges.end(), converted.begin(), converted.end());
            converted.clear();
        }

        numbers = get_numbers(line);
        // skip non number lines
        if (numbers.size() == 0)
        {
            continue;
        }
        dest = numbers[0];
        src_low = numbers[1];
        src_upp = numbers[1] + numbers[2] - 1;

        convert = dest - src_low;

        for (int i = 0; i < ranges.size(); i++)
        {
            seed_low = ranges[i].first;
            seed_upp = ranges[i].second;

            // case 1: complete conversion
            if ((src_low <= seed_low) & (seed_upp <= src_upp))
            {
                converted.push_back({seed_low + convert, seed_upp + convert});
            }
            // case 2: convert only middle, push 3 ranges
            else if ((seed_low < src_low) & (src_upp < seed_upp))
            {
                buffer.push_back({seed_low, src_low - 1});
                converted.push_back({src_low + convert, src_upp + convert});
                buffer.push_back({src_upp + 1, seed_upp});
            }
            // case 3: seed higher
            else if ((seed_low <= src_upp) & (src_upp <= seed_upp))
            {
                converted.push_back({seed_low + convert, src_upp + convert});
                buffer.push_back({src_upp + 1, seed_upp});
            }
            // case 4: src higher
            else if ((src_low <= seed_upp) & (seed_upp <= src_upp))
            {
                buffer.push_back({seed_low, src_low - 1});
                converted.push_back({src_low + convert, seed_upp + convert});
            }
            else
            {
                buffer.push_back({seed_low, seed_upp});
            }
        }
        ranges = buffer;
        buffer.clear();
    }

    ranges.insert(ranges.end(), converted.begin(), converted.end());
    std::vector<int64_t> lowers;
    for (int j = 0; j < ranges.size(); j++)
    {
        lowers.push_back(ranges[j].first);
    }
    std::cout << *std::min_element(lowers.begin(), lowers.end());
}