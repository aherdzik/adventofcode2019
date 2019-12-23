#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>

using namespace std;

map<string, string> keyOrbitsValue;

vector<string> getOrbitalChain(string orbiter)
{
    vector<string> toReturn;
    while(keyOrbitsValue.count(orbiter) !=0)
    {
        orbiter = keyOrbitsValue[orbiter];
        toReturn.push_back(orbiter);
    }
    return toReturn;
}

int main()
{
    string line;
    ifstream myfile("day6input.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            stringstream ss(line);
            while (ss.good())
            {
                string orbitee;
                getline(ss, orbitee, ')');
                string orbiter;
                getline(ss, orbiter, '\n');
                keyOrbitsValue.insert(std::pair<string,string>(orbiter, orbitee));
            }
        }
        myfile.close();
    }
    int minChain = 9999999;
    vector<string> youChain = getOrbitalChain("YOU");
    vector<string> sanChain = getOrbitalChain("SAN");
    for(int i= 0; i< youChain.size(); i++ )
    {
        for(int j = 0; j< sanChain.size(); j++)
        {
            if(youChain[i] == sanChain[j])
            {
                int length = i + j;
                if(length < minChain)
                {
                    minChain = length;
                }
            }
        }
    }
    cout << minChain << '\n';
}