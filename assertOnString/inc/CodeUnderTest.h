#pragma once
#include<string>
#include<iostream>
void toUpper(char* inputString)
{
    for(int i = 0; i < strlen(inputString); i++)
    {
        inputString[i] = std::toupper(inputString[i]);
    }
}
