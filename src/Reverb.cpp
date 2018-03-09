#include <cmath>
#include <Reverb>

#define SAMPLERATE 38500 //Hz

//delay ratios for each wall relative to input
#define WASDDELAY 0.8
#define TOPDELAY 0.9
#define BOTDELAY 0.7
#define CORDELAY 1

//decay ratios for each wall relative to input
#define WASDDECAY 0.4
#define TOPDECAY 0.2
#define BOTDECAY 0.5
#define CORDECAY 0.2

    void DelayLine::setDelayLine(unsigned short dTime, unsigned char in_decay) {
        delayTime = dTime;
        decay = in_decay;
        delaySamples = (int)((float)delayMilliseconds * 38.5f);
    }

    unsigned short DelayLine::input(unsigned short * inSig) {
        bufferIndex = inSig;
    }
    //set the first two delay lines for the short echo
    void Reverb::initReverb() {

        multipleDelay[0].setDelayLine(29, 50);
        multipleDelay[1].setDelayLine(41, 50);
    } 

    void Reverb::setDelayTime(unsigned short delTime) {

        multipleDelay[2].setDelaytime(delTime * WASDDELAY + 3);
        multipleDelay[3].setDelaytime(delTime * WASDDELAY - 3);
        multipleDelay[4].setDelaytime(delTime * WASDDELAY + 2);
        multipleDelay[5].setDelaytime(delTime * WASDDELAY - 2);
        multipleDelay[6].setDelaytime(delTime * TOPDECLY);
        multipleDelay[7].setDelaytime(delTime * BOTDECLY);
        multipleDelay[8].setDelaytime(delTime * CORDECLY);
    }

    void Reverb::setDelayLevel(unsigned char delLevel) {
        if (delLevel > 100) delLevel = 100;

        multipleDelay[2].setDelayLevel(delLevel * WASDDECAY);
        multipleDelay[3].setDelayLevel(delLevel * WASDDECAY);
        multipleDelay[4].setDelayLevel(delLevel * WASDDECAY);
        multipleDelay[5].setDelayLevel(delLevel * WASDDECAY);
        multipleDelay[6].setDelayLevel(delLevel * TOPDECAY);
        multipleDelay[7].setDelayLevel(delLevel * BOTDECAY);
        multipleDelay[8].setDelayLevel(delLevel * CORDECAY);
    }

    unsigned short DelayLine::input(unsigned short inSig) {
        unsigned short out = 0;
        for (int = 0; i < 9; i++) {
            out += multipleDelay[i].input
        }
    }
}