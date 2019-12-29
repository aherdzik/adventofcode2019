#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <tuple>
#include <string>
#include <algorithm>

using namespace std;


vector<int> intToVectorInt(int command)
{
    string numString = std::to_string(command);
    std::vector<int> individualDigits;
    std::for_each(numString.begin(), numString.end(),[&individualDigits](char const & c)
    {
        individualDigits.push_back(c - 48);
    });
    return individualDigits;
}

int runProgram(std::vector<int>& programData, std::vector<int> inputs, std::vector<int>& outputs, int programIndex)
{
    int inputIndex = 0;
    while(true)
    {
        int fullCommandInt = programData[programIndex];
        int opcode= 0;
        vector<int> parameterModeDigits;
        if(fullCommandInt < 100)
        {
            opcode = fullCommandInt;
        }
        else
        {
            parameterModeDigits= intToVectorInt(fullCommandInt);
            opcode = parameterModeDigits[parameterModeDigits.size()-1] + (10 * parameterModeDigits[parameterModeDigits.size()-2]);
            parameterModeDigits.pop_back();
            parameterModeDigits.pop_back();
            std::reverse(parameterModeDigits.begin(),parameterModeDigits.end());  
        }

        switch(opcode)
        {
            int val1, val2;
            case 1: // add (value 1, value 2, output)
                val1 = parameterModeDigits.size()>=1 && parameterModeDigits[0] == 1? programData[programIndex+1] : programData[programData[programIndex+1]];
                val2 = parameterModeDigits.size()>=2 && parameterModeDigits[1] == 1? programData[programIndex+2] : programData[programData[programIndex+2]];
                programData[programData[programIndex+3] ] = val1 + val2;
                programIndex +=4;
            break;
            case 2: // multiply (value 1, value 2, output)
                val1 = parameterModeDigits.size()>=1 && parameterModeDigits[0] == 1? programData[programIndex+1] : programData[programData[programIndex+1]];
                val2 = parameterModeDigits.size()>=2 && parameterModeDigits[1] == 1? programData[programIndex+2] : programData[programData[programIndex+2]];
                programData[programData[programIndex+3] ] = val1 * val2;
                programIndex +=4;
            break;
            case 3: // input (take input and put in the location of val1)
                if(inputIndex <inputs.size())
                {
                    val1 = inputs[inputIndex];
                    inputIndex++;
                }
                else
                {             
                    return programIndex;
                }

                programData[programData[programIndex+1] ] = val1;
                programIndex +=2;
            break;
            case 4: // output (take output location and send it to the user and put in the location of val1)
                val1 = parameterModeDigits.size()>=1 && parameterModeDigits[0] == 1? programData[programIndex+1] : programData[programData[programIndex+1]];
                outputs.push_back(val1);
                programIndex +=2;
            break;
            case 5: // Jump if true: Jump to val2 if val1 is nonzero
                val1 = parameterModeDigits.size()>=1 && parameterModeDigits[0] == 1? programData[programIndex+1] : programData[programData[programIndex+1]];
                val2 = parameterModeDigits.size()>=2 && parameterModeDigits[1] == 1? programData[programIndex+2] : programData[programData[programIndex+2]];
                if(val1 !=0)
                {
                    programIndex = val2;
                }
                else
                {
                    programIndex+=3;
                }
            break;
            case 6: // Jump if false: to val2 if val1 is zero
                val1 = parameterModeDigits.size()>=1 && parameterModeDigits[0] == 1? programData[programIndex+1] : programData[programData[programIndex+1]];
                val2 = parameterModeDigits.size()>=2 && parameterModeDigits[1] == 1? programData[programIndex+2] : programData[programData[programIndex+2]];
                if(val1 ==0)
                {
                    programIndex = val2;
                }
                else
                {
                    programIndex+=3;
                }
            break;
            case 7: // If val1 is less than val2 then store 1 in 3rd param, otherwise 0
                val1 = parameterModeDigits.size()>=1 && parameterModeDigits[0] == 1? programData[programIndex+1] : programData[programData[programIndex+1]];
                val2 = parameterModeDigits.size()>=2 && parameterModeDigits[1] == 1? programData[programIndex+2] : programData[programData[programIndex+2]];
                programData[programData[programIndex+3] ] = val1 < val2? 1 : 0;
                programIndex+=4;
            break;
            case 8: // If val1 is equal to val2 then store 1 in 3rd param, otherwise store 0
                val1 = parameterModeDigits.size()>=1 && parameterModeDigits[0] == 1? programData[programIndex+1] : programData[programData[programIndex+1]];
                val2 = parameterModeDigits.size()>=2 && parameterModeDigits[1] == 1? programData[programIndex+2] : programData[programData[programIndex+2]];
                programData[programData[programIndex+3] ] = val1 == val2? 1 : 0;
                programIndex+=4;
            break;
            case 99: // return
            default:
                return -1;
            break;
        }
    }
}

int main()
{
    string line;
    ifstream myfile("day7input.txt");
    std::vector<int> programData;
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
            programData.push_back( std::stoi(substr,0,10 ));
        }
    }

    int permutationArray [] = {5,6,7,8,9};
    int arrSize = 5;
    std::sort(permutationArray, permutationArray + arrSize);
    int maxOutput = 0;
    do 
    { 
        vector<tuple<vector<int>,int>> programStates;
        tuple<vector<int>,int> defaultState = std::make_tuple (programData,0); 
        for(int i = 0; i< arrSize; i++)
        {
            programStates.push_back(defaultState);
        }
        
        int currentIndex = 0;
        int currentSavedOutput = 0;
        int currentOutput = 0;

        while(true)
        {
            std::vector<int> newInput;
            if(currentIndex <arrSize)
            {
                newInput.push_back(permutationArray[currentIndex % arrSize]);
            }
            newInput.push_back(currentOutput);

            std::vector<int> outputVector;
            std::vector<int> usedData = std::get<0>(programStates[currentIndex % arrSize]);
            int programStartIndex = std::get<1>(programStates[currentIndex % arrSize]);
            if(programStartIndex == -1)
            {
                break;
            }

            int result = runProgram(usedData, newInput, outputVector, programStartIndex); // result = -1 if no more input needed, otherwise last instruction index of program
            programStates[currentIndex % arrSize] = std::make_tuple (usedData,result); // save state
            currentOutput = outputVector[0];

            if(currentIndex % arrSize == arrSize - 1 && currentOutput > currentSavedOutput) // only save output if it is out of Amplifier E
            {
                currentSavedOutput = currentOutput;
            }
            currentIndex++;
        }

        if(currentSavedOutput >maxOutput)
        {
            maxOutput = currentSavedOutput;
        }
    } while (next_permutation(permutationArray, permutationArray + arrSize)); 
            
            
    std::cout << "TEST COMPLETE: "<< maxOutput << "\n";
}