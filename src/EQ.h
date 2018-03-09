/*
  EQ.h - Library for implementing audio EQ.
  Created by Edwin Ew Jong
  ECE 196
*/
#ifndef EQ_h
#define EQ_h

#include "Arduino.h"
#include <FilterOnePole.h>

class EQ 
{
  private:
    FilterOnePole * filterLine;
    float * ampLine;
    short maxAmp;
    short counter;
    char ctrStart;
    	
  public:
    void andrew(int filterIndex, int amp);
    void setOutAmp(int filterIndex, int freq);
    float inputSignal(float sig);
    void set3Band();
    void set5Band();
};

#endif
