#include <iostream>
#include <fstream>
#include <set>
#include <sstream>
#include <vector>
#include <string>
#include <tuple>

using namespace std;
std::set<std::tuple<int, int>> firstSet;
std::set<std::tuple<int, int>> secondSet;
std::vector<std::tuple<int, int>> firstVector;
std::vector<std::tuple<int, int>> secondVector;

void addDirectionsToSet(int &x, int &y, char direction, int length, bool isFirstSet)
{
    std::vector<std::tuple<int, int>> & vectorToFill = isFirstSet ? firstVector : secondVector;
    std::set<std::tuple<int, int>>& setToUse = isFirstSet ? firstSet : secondSet;
    switch (direction)
    {
    case 'U':
        for (int i = 0; i < length; i++)
        {
            y++;
            setToUse.insert(std::make_tuple(x, y));
            vectorToFill.push_back(std::make_tuple(x, y));
        }
        break;
    case 'D':
        for (int i = 0; i < length; i++)
        {
            y--;
            setToUse.insert(std::make_tuple(x, y));
            vectorToFill.push_back(std::make_tuple(x, y));
        }
        break;
    case 'L':
        for (int i = 0; i < length; i++)
        {
            x--;
            setToUse.insert(std::make_tuple(x, y));
            vectorToFill.push_back(std::make_tuple(x, y));
        }
        break;
    case 'R':
        for (int i = 0; i < length; i++)
        {
            x++;
            setToUse.insert(std::make_tuple(x, y));
            vectorToFill.push_back(std::make_tuple(x, y));
        }
        break;
    default:
        break;
    }
}

int getDistanceForTuple(std::tuple<int, int> currentTuple, std::vector<std::tuple<int, int>>& currentVector)
{
    for(int i=0; i<currentVector.size(); i++)
    {
        if(currentVector[i] == currentTuple)
        {
            return i+1;
        }
    }
    return -1;
}

int main()
{
    string line;
    ifstream myfile("day3input.txt");
    if (myfile.is_open())
    {
        bool firstline = true;
        while (getline(myfile, line))
        {
            stringstream ss(line);
            int x = 0, y = 0;
            while (ss.good())
            {
                string command;
                getline(ss, command, ',');
                char direction = command.at(0);
                command.erase(0, 1);
                int length = std::stoi(command, 0, 10);
                addDirectionsToSet(x, y, direction, length, firstline);
            }
            firstline = false;
        }
        myfile.close();
    }

    std::set<std::tuple<int, int>> finalSet;
    ;
    // Iterate till the end of set
    for (std::set<std::tuple<int, int>>::iterator it = firstSet.begin(); it != firstSet.end(); ++it)
    {
        if(secondSet.find(*it) != secondSet.end())
        {
             finalSet.insert(*it);
        }
    }

    int maxDistance = 99999999;

    for (std::set<std::tuple<int, int>>::iterator it = finalSet.begin(); it != finalSet.end(); ++it)
    {
        std::tuple<int, int> currentTuple = *it;
        int distanceFromCenter= getDistanceForTuple(currentTuple,firstVector) + getDistanceForTuple(currentTuple,secondVector);
        if(distanceFromCenter < maxDistance)
        {
            maxDistance = distanceFromCenter;
        }
    }

    cout << endl;
}