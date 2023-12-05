#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <map>

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
                    total++;
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
    std::map<int, int> cards;

    int i = 0;
    int max;
    while (std::getline(f, line))
    {
        cards[i] = 1;
        i++;
        max = i;
    }

    int score;
    i = 0;
    std::ifstream f2("input.txt");
    while (std::getline(f2, line))
    {
        score = calculate_score(line);
        for (int j = 1; j <= score; j++)
        {
            cards[i + j] = cards[i + j] + cards[i];
        }
        std::cout << i << " " << cards[i] << "\n";
        i++;
    }

    int total = 0;
    for (int k = 0; k < max; k++)
    {
        total = total + cards[k];
    }
    std::cout << total;
}