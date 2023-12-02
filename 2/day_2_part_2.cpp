#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main()
{
    ifstream file("input.txt");
    string str;
    int total = 0;
    int colon_idx;
    int count_buffer;
    int sub_total;
    char c;
    string color_buffer;
    string token;

    map<string, int> color_count = {
        {"red", 0},
        {"green", 0},
        {"blue", 0}};

    while (getline(file, str))
    {
        // reset per-line states
        color_buffer = "";
        count_buffer = 0;
        colon_idx = str.find(':');

        // Generalize last entry
        str.push_back(';');

        for (int i = colon_idx + 2; i < str.size(); i++)
        {
            c = str[i];
            if (isdigit(c))
            {
                count_buffer = count_buffer * 10 + (c - '0');
            }
            else if (c == ',' | c == ';')
            {
                if (color_count[color_buffer] < count_buffer)
                {
                    color_count[color_buffer] = count_buffer;
                }
                count_buffer = 0;
                color_buffer = "";
            }
            else if (c != ' ')
            {
                color_buffer.push_back(c);
            }
        }

        total += color_count["red"] * color_count["green"] * color_count["blue"];
        // cout << total << '\n';
        color_count["red"] = 0;
        color_count["green"] = 0;
        color_count["blue"] = 0;
    }
    cout << total << '\n';
}