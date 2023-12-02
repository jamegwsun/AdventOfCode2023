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
    int color_count;
    int sub_total;
    char c;
    string color;
    string token;
    bool legal;

    map<string, int> limit = {
        {"red", 12},
        {"green", 13},
        {"blue", 14}};

    while (getline(file, str))
    {
        // reset per-line states
        legal = true;
        color = "";
        color_count = 0;
        colon_idx = str.find(':');

        // Edge case where the last entry is illegal
        str.push_back(';');

        for (int i = colon_idx + 2; i < str.size(); i++)
        {
            c = str[i];
            if (isdigit(c))
            {
                color_count = color_count * 10 + (c - '0');
            }
            else if (c == ',' | c == ';')
            {
                if (color_count > limit[color])
                {
                    legal = false;
                }

                color_count = 0;
                color = "";
            }
            else if (c != ' ')
            {
                color.push_back(c);
            }

            if (legal == false)
            {
                break;
            }
        }

        if (legal == true)
        {
            cout << str << '\n';
            sub_total = 0;
            for (int i = 5; i < colon_idx; i++)
            {
                sub_total = sub_total * 10 + str[i] - '0';
            }
            total += sub_total;
        }
    }
    cout << total << '\n';
}