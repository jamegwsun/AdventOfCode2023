#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

int main(){
    ifstream file("input.txt");
    string str;
    int tens;
    int digit;
    int line_size;
    int total = 0;
    map<string, int> three_char_map = {
        {"one", 1},
        {"two", 2},
        {"six", 6},
        {"ten", 10}
    };
    map<string, int> four_char_map = {
        {"four", 4},
        {"five", 5},
        {"nine", 9}
    };
    map<string, int> five_char_map = {
        {"three", 3},
        {"seven", 7},
        {"eight", 8}
    };

    while (getline(file, str))
    {
        // reset some states every new line
        digit = 0;
        tens = 0;
        line_size = str.size();

        for (int i = 0; i< line_size; i++){
            // attempt to find digit
            if (isdigit(str[i])) 
            {
                digit = str[i] - '0';
            }
            else if (line_size - i >= 3 & three_char_map.count(str.substr(i, 3)) > 0)
            {
                digit = three_char_map[str.substr(i, 3)];
            }
            else if (line_size - i >= 4 & four_char_map.count(str.substr(i, 4)) > 0)
            {
                digit = four_char_map[str.substr(i, 4)];
            }
            else if (line_size - i >= 5 & five_char_map.count(str.substr(i, 5)) > 0)
            {
                digit = five_char_map[str.substr(i, 5)];
            }
            
            // add digit times 10 the first time it is found
            if (tens == 0 & digit > 0)  
            {
                tens = digit * 10;
            }
        }
        total += (tens + digit);
    }
    cout << total << '\n';
}