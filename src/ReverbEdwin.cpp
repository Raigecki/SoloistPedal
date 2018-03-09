#include <cmath>

#define SAMPLERATE = 38500 //Hz

class Reverb {

    class delayLine {
        char * buffer;
        int delayTime; // in milliseconds
        int delaySamples = 
        (int)((float)delayMilliseconds * 44.1f); // assumes 44100 Hz sample rate
        char decay;
        for (int i = 0; i < buffer.length - delaySamples; i++) {   
        // WARNING: overflow potential
        buffer[i + delaySamples] += (short)((float)buffer[i] * decay);
        }

        void setDelayLine(int dTime, char in_decay) {

            buffer = new char
        }
    }

}