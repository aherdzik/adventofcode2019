#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

std::vector<long long> programData;
std::vector<int> twoValOpcodes = {1, 2, 5, 6, 7, 8};
std::vector<int> oneValOpcodes = {4, 9};
vector<long long> longToVectorLong(long long command)
{
    string numString = std::to_string(command);
    std::vector<long long> individualDigits;
    std::for_each(numString.begin(), numString.end(), [&individualDigits](char const &c) {
        individualDigits.push_back(c - 48);
    });
    return individualDigits;
}

void resizeIfNumBigger(vector<long long> &mainData, long long size)
{
    try
    {
        if (size + 1 > mainData.size())
        {
            mainData.resize(size + 1);
        }
    }
    catch (const std::exception &e)
    { 
    }
}

long long getValueBasedOnMode(int valNum, vector<long long> &modeDigits, std::vector<long long> &mainData, long long relativeNum, long long programIndex)
{
    if (modeDigits.size() < valNum || modeDigits[valNum - 1] == 0 || modeDigits[valNum - 1] > 2)
    {
        resizeIfNumBigger(programData, programIndex + valNum);
        resizeIfNumBigger(programData, programData[programIndex + valNum]);
        return programData[programData[programIndex + valNum]];
    }
    else if (modeDigits[valNum - 1] == 1)
    {
        resizeIfNumBigger(programData, programIndex + valNum);
        return programData[programIndex + valNum];
    }
    else if (modeDigits[valNum - 1] == 2)
    {
        resizeIfNumBigger(programData, programData[relativeNum] + relativeNum);
        return programData[programData[programIndex + valNum] + relativeNum];
    }
    return -1;
}

void runProgram()
{
    long long programIndex = 0;
    long long relativeIndex = 0;
    while (true)
    {
        long long fullCommandInt = programData[programIndex];
        int opcode = 0;
        vector<long long> parameterModeDigits;
        if (fullCommandInt < 100)
        {
            opcode = fullCommandInt;
        }
        else
        {
            parameterModeDigits = longToVectorLong(fullCommandInt);
            opcode = parameterModeDigits[parameterModeDigits.size() - 1] + (10 * parameterModeDigits[parameterModeDigits.size() - 2]);
            parameterModeDigits.pop_back();
            parameterModeDigits.pop_back();
            std::reverse(parameterModeDigits.begin(), parameterModeDigits.end());
        }

        if (std::find(twoValOpcodes.begin(), twoValOpcodes.end(), opcode) != twoValOpcodes.end())
        {
            long long val1 = getValueBasedOnMode(1, parameterModeDigits, programData, relativeIndex, programIndex);
            long long val2 = getValueBasedOnMode(2, parameterModeDigits, programData, relativeIndex, programIndex);
            resizeIfNumBigger(programData, programIndex + 3);
            resizeIfNumBigger(programData, programData[programIndex + 3]);
            resizeIfNumBigger(programData, programData[programIndex + 3] + relativeIndex);
            long long outputSetValue = parameterModeDigits.size() == 3 && parameterModeDigits[2] == 2 ? programData[programIndex + 3] + relativeIndex : programData[programIndex + 3];
            if (opcode == 1) //add
            {
                programData[outputSetValue] = val1 + val2;
                programIndex += 4;
            }
            else if (opcode == 2) //multiply
            {
                programData[outputSetValue] = val1 * val2;
                programIndex += 4;
            }
            else if (opcode == 5) // Jump if true: Jump to val2 if val1 is nonzero
            {
                if (val1 != 0)
                {
                    programIndex = val2;
                }
                else
                {
                    programIndex += 3;
                }
            }
            else if (opcode == 6) // Jump if false: to val2 if val1 is zero
            {
                if (val1 == 0)
                {
                    programIndex = val2;
                }
                else
                {
                    programIndex += 3;
                }
            }
            else if (opcode == 7) // If val1 is less than val2 then store 1 in 3rd param, otherwise 0
            {
                programData[outputSetValue] = val1 < val2 ? 1 : 0;
                programIndex += 4;
            }
            else if (opcode == 8) // If val1 is equal to val2 then store 1 in 3rd param, otherwise store 0
            {
                programData[outputSetValue] = val1 == val2 ? 1 : 0;
                programIndex += 4;
            }
        }
        else if (std::find(oneValOpcodes.begin(), oneValOpcodes.end(), opcode) != oneValOpcodes.end())
        {
            long long val1 = getValueBasedOnMode(1, parameterModeDigits, programData, relativeIndex, programIndex);
            if (opcode == 4)
            {
                std::cout << "OUTPUT: " << val1 << "\n";
            }
            else if (opcode == 9)
            {
                relativeIndex += val1;
            }
            programIndex += 2;
        }
        else if (opcode == 3) //input
        {
            std::cout << "INPUT REQUIRED: ";
            long long inputVal;
            cin >> inputVal;
            std::cout << "\n";
            if (parameterModeDigits.size() == 1 && parameterModeDigits[0] == 2)
            {
                programData[programData[programIndex + 1] + relativeIndex] = inputVal;
            }
            else
            {
                programData[programData[programIndex + 1]] = inputVal;
            }
            programIndex += 2;
        }
        else
        {
            return;
        }
    }
}

int main()
{
    string line;
    ifstream myfile("day9input.txt");
    if (myfile.is_open())
    {
        string dataString = "";
        if (getline(myfile, line))
        {
            dataString = line;
        }
        myfile.close();
        stringstream ss(dataString);
        while (ss.good())
        {
            string substr;
            getline(ss, substr, ',');
            programData.push_back(std::stoll(substr, 0, 10));
        }

        runProgram();
    }
    long  test  = programData.size();
    std::cout << "TEST COMPLETE\n";
}