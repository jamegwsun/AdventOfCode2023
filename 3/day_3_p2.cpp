#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <map>
#include <vector>

std::vector<int> get_adjacents_for_gear(int gear_idx, std::string line)
{
    std::vector<int> adjacents;
    char c;
    int subtotal = 0;
    int start;
    for (int i = 0; i < line.size(); i++)
    {
        c = line[i];
        // handle number
        if (isdigit(c))
        {
            if (subtotal == 0)
            {
                start = i - 1;
            }
            subtotal = subtotal * 10 + c - '0';
        }

        // handle end of number
        if ((!(isdigit(c)) | i == line.size() - 1) & (subtotal > 0))
        {
            if ((gear_idx >= start) & (gear_idx) <= i)
            {
                adjacents.push_back(subtotal);
            }
            subtotal = 0;
        }
    }
    return adjacents;
}

int main()
{
    std::ifstream f("input.txt");
    std::string line;
    std::string prev_line = "";
    std::string next_line = "";
    int total = 0;

    while (std::getline(f, next_line))
    {
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '*')
            {
                std::vector<int> adjacents = get_adjacents_for_gear(i, prev_line);
                std::vector<int> to_add = get_adjacents_for_gear(i, line);
                adjacents.insert(adjacents.end(), to_add.begin(), to_add.end());
                to_add = get_adjacents_for_gear(i, next_line);
                adjacents.insert(adjacents.end(), to_add.begin(), to_add.end());

                if (adjacents.size() == 2)
                {
                    total += adjacents[0] * adjacents[1];
                }
            }
        }

        prev_line = line;
        line = next_line;
    }
    std::cout << total;
}