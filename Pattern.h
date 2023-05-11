#ifndef _PATTERN_H
#define _PATTERN_H
#include <string>
#include <ctype.h>
#include <math.h>
using namespace std;

struct Pattern
{
    string pattern;
    int noOfWords;
    int Start;
    int End;
    
    Pattern()
    {
        noOfWords=5;
    }
    
    int sum0fLetters(int index)
    {
        if(pattern[index]==' ')
          {
            return 0;
          }
          else
          {
            return (tolower(pattern[index])-0)*(pow(10,4)) + sum0fLetters(index+1);
          }
    }
    
    
};

#endif //_PATTERN_H

