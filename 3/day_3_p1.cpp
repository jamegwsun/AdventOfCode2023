#include <fstream>
#include <iostream>
#include <string>
#include <set>

std::set<int> get_symbol_indices(std::string line)
{
    char c;
    std::set<int> symbols = {};
    for (int i = 0; i < line.size(); i++)
    {
        c = line[i];
        if (c != '.' & !(isdigit(c)))
        {
            symbols.insert(i);
        }
    }
    return symbols;
}

int get_score_for_gear(std::string line, std::string prev_line, std::string next_line)
{
    std::set<int> symbols = {};
    int total = 0;
    int subtotal = 0;
    bool add_to_total = false;
    char c;
    symbols.merge(get_symbol_indices(next_line));
    symbols.merge(get_symbol_indices(line));
    symbols.merge(get_symbol_indices(prev_line));

    for (int i = 0; i < line.size(); i++)
    {
        c = line[i];
        // handle seeing number
        if (isdigit(c))
        {
            if ((symbols.find(i - 1) != symbols.end()) | (symbols.find(i) != symbols.end()) | (symbols.find(i + 1) != symbols.end()))
            {
                add_to_total = true;
            }
            subtotal = subtotal * 10 + (c - '0');
        }
        // handle stop seeing number
        else if (subtotal > 0)
        {
            if (add_to_total == true)
            {
                total += subtotal;
                std::cout << subtotal << '\n';
            }

            // reset for next number
            subtotal = 0;
            add_to_total = false;
        }
    }

    // explicitly deal with numbers that end at the end of line, meh
    if (add_to_total == true)
    {
        total += subtotal;
        std::cout << subtotal << '\n';
    }

    return total;
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
        total += get_score_for_gear(line, prev_line, next_line);

        prev_line = line;
        line = next_line;
    }
    total += get_score_for_gear(line, prev_line, "");
    std::cout << total;
}