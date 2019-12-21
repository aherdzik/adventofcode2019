#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

std::string::size_type sz; // alias of size_t

long recursedFuelRequirements(long input)
{   
    if(input < 9)
    {
        return 0;
    }

    input /= 3;
    input -= 2;
    return input + recursedFuelRequirements(input);
}

int main()
{
    string line;
    ifstream myfile("day1input.txt");
    if (myfile.is_open())
    {
        long total = 0;
        long curLineLong = 0;
        while (getline(myfile, line))
        {
            curLineLong = std::stol(line, 0, 10);
            total += recursedFuelRequirements(curLineLong);
        }
        myfile.close();
    }
    cout << endl;
}