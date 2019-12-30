#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>

using namespace std;

int main()
{
    string line;
    ifstream myfile("day8input.txt");
    const int width = 25, height = 6;

    vector<vector<int>> results;
    if (myfile.is_open())
    {
        if (getline(myfile, line))
        {
            int numLayers = line.size() / (width * height);
            for (int i = 0; i < numLayers; i++)
            {
                for (int j = 0; j < height; j++)
                {
                    if (i == 0) // front layer, create array
                    {
                        results.push_back(vector<int>());
                    }
                    for (int k = 0; k < width; k++)
                    {
                        int intVal = (line[(i * height * width) + (j * width) + k]) - 48;
                        if (i == 0) //front layer, create array
                        {
                            results[j].push_back(intVal);
                        }
                        else if (results[j][k] == 2 && intVal != 2)
                        {
                            results[j][k] = intVal;
                        }
                    }
                }
            }
        }
        myfile.close();

        for (vector<vector<int>>::iterator it = results.begin(); it < results.end(); it++)
        {
            vector<int> currentRow = *it;
            for (vector<int>::iterator it2 = currentRow.begin(); it2 < currentRow.end(); it2++)
            {
                int currentDigit = *it2;
                if(currentDigit == 1)
                {
                    cout << "X";
                }
                else
                {
                    cout << " ";
                }
            }
            cout << "\n";
        }
    }
}