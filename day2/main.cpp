#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

std::vector<int> originalProgramData;


void runProgram(std::vector<int> programData, int param1, int param2)
{
    int programIndex = 0;
    int currentCommand = programData[programIndex];
    programData[1] = param1;
    programData[2] = param2;
    while(currentCommand != 99)
    {
        int val1;
        int val2;
        switch(currentCommand)
        {
            case 1: // add (value 1, value 2, output)
                val1 = programData[programData[programIndex+1] ];
                val2 = programData[programData[programIndex+2] ];
                programData[programData[programIndex+3] ] = val1 + val2;
                programIndex +=4;
            break;
            case 2: // add (value 1, value 2, output)
                val1 = programData[programData[programIndex+1] ];
                val2 = programData[programData[programIndex+2] ];
                programData[programData[programIndex+3] ] = val1 * val2;
                programIndex +=4;
            break;
            case 99: // return
            default:
                programIndex = programIndex;
            break;
        }
        currentCommand = programData[programIndex];
    }

    if(programData[0] == 19690720)
    {
        programIndex = programIndex;
    }
}

int main()
{
    string line;
    ifstream myfile("day2input.txt");
    if (myfile.is_open())
    {
        string dataString = "";
        if(getline(myfile, line))
        {
            dataString = line;
        }
        myfile.close();
        stringstream ss(dataString);
        while( ss.good() )
        {
            string substr;
            getline( ss, substr, ',' );
            originalProgramData.push_back( std::stoi(substr,0,10 ));
        }

        for(int i = 0; i<100; i++)
        {
            for(int j = 0; j<100; j++)
            {
                runProgram(originalProgramData, i, j);
            }
        }
    }
    cout << endl;
}