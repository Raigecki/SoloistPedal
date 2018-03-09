#ifndef Reverb_h
#define Reverb_h

class Reverb {   
    private:
        class DelayLine {
            char * bufferIndex;
            unsigned short delayTime; // in milliseconds
            int delaySamples;
            unsigned char decay;

            void setDelayLine(unsigned short dTime, char in_decay); 
            unsigned short input(unsigned short inSig);

        };

        /*
         * 0, 1 default short delay
         * 2 = front, 3 = back, 4 = left, 5 = right
         * 6 = left, 7 = right, 8 = corner
         */
        DelayLine multipleDelay[9]; 

    public:
        void initReverb(); 
        void setDelayTime(unsigned short delTime); // 0 - 255 * 4
        void setDelayLevel(unsigned char delLevel); // 0 - 100
        unsigned short input(unsigned short inSig);

};

#endif