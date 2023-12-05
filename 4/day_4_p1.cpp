#include <fstream>
#include <iostream>
#include <string>
#include <set>

int calculate_score(std::string line)
{
    std::set<int> winners;
    bool start = false;
    bool check_winner = false;
    int total = 0;
    int subtotal = 0;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ':')
        {
            start = true;
        }
        else if (line[i] == '|')
        {
            check_winner = true;
        }
        if (start == false)
        {
            continue;
        }

        if (isdigit(line[i]))
        {
            subtotal = subtotal * 10 + line[i] - '0';
        }

        // end of number
        if ((!(isdigit(line[i])) | i == line.size() - 1) & (subtotal > 0))
        {
            if (check_winner == true)
            {
                if (winners.find(subtotal) != winners.end())
                {
                    std::cout << subtotal << '\n';
                    if (total == 0)
                    {
                        total++;
                    }
                    else
                    {
                        total = total * 2;
                    }
                }
            }
            else
            {
                winners.insert(subtotal);
            }
            subtotal = 0;
        }
    }
    return total;
}

int main()
{
    std::ifstream f("input.txt");
    std::string line;
    int total = 0;

    while (std::getline(f, line))
    {
        total += calculate_score(line);
    }
    std::cout << total;
}