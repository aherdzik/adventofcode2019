#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

bool hasTwoAdjacentDigits;

int vectorIntToInt (std::vector<int> individualDigits)
{
    std::stringstream ss;
    std::for_each(individualDigits.begin(), individualDigits.end(),[&ss](int i)
    {
        ss << std::to_string(i);
    });

    return stoi(ss.str());
}

bool hasTwoSameAdjacentDigits(std::vector<int> individualDigits)
{
    for(int i=0 ; i<individualDigits.size() -1; i++)
    {
        if(individualDigits[i] == individualDigits[i+1])
        {
            if(i+1 == individualDigits.size() -1)
            {
                return true; // if the last 2 digits match, we're good
            }
            else if(individualDigits[i+1] == individualDigits[i+2]) // the block is no good, find where the next digit that isn't the same is
            {
                int iter = i+2;
                while(iter < individualDigits.size() -1 && individualDigits[iter] == individualDigits[iter+1])
                {
                    iter++;
                }
                i = iter;
            }
            else 
            {
                return true; // we found 2 (and only 2) adjacent digits
            }
        }
    }
    return false;
}

std::vector<int> intToVectorOfNextAscendingNumber(int& currentNumber)
{   
    string numString = std::to_string(currentNumber);
    std::vector<int> individualDigits;
    std::for_each(numString.begin(), numString.end(),[&individualDigits](char const & c)
    {
        individualDigits.push_back(c - 48);
    });

    for(int i=0 ; i <individualDigits.size() -1; i++)
    {
        if(individualDigits[i] > individualDigits[i+1])
        {
            for(int j = i+1; j < individualDigits.size(); j++)
            {
                individualDigits[j] = individualDigits[i];
            }
            break;
        }
    }

    return individualDigits;
}

int main()
{
    int numPasswords = 0;
    int currentNumber = 265275;
    int endingNumber = 781584;
    while(currentNumber < endingNumber)
    {
        std::vector<int> individualDigits = intToVectorOfNextAscendingNumber(currentNumber);
        bool twoSameAdjacentDigits = hasTwoSameAdjacentDigits(individualDigits);
        currentNumber = vectorIntToInt(individualDigits);
        if(currentNumber < endingNumber && twoSameAdjacentDigits)
        {
            numPasswords++;
        }
        currentNumber++;
    }

    cout << numPasswords;
}