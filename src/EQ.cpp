#include FilterOnePole.cpp
#include FIlterTwoPole.cpp

class EQ {

    private:
        FilterOnePole * filterLine;

    set3Band() {

        filterLine = new FilterOnePole[4];

        filterLine[0] lowPass = FilterOnePole(LOWPASS, 50, 0);
        //Bp
        filterLine[1] lowPass1 = FilterOnePole(LOWPASS, 300, 0);
        filterLine[2] highPass1 = FilterOnePole(HIGHPASS, 300, 0);

        filterLine[3] highPass = FilterOnePole(HIGHPASS, 15000, 0);
    }

    set5Band() {

        filterLine = new FilterOnePole[8];

        filterLine[0] lowPass = FilterOnePole(LOWPASS, 50, 0);
        //Bp 1
        filterLine[1] lowPass1 = FilterOnePole(LOWPASS, 300, 0);
        filterLine[2] highPass1 = FilterOnePole(HIGHPASS, 300, 0);
        //Bp 2
        filterLine[3] lowPass2 = FilterOnePole(LOWPASS, 1000, 0);
        filterLine[4] highPass2 = FilterOnePole(HIGHPASS, 1000, 0);
        //Bp 3
        filterLine[5] lowPass3 = FilterOnePole(LOWPASS, 5000, 0);
        filterLine[6] highPass3 = FilterOnePole(HIGHPASS, 5000, 0);

        filterLine[7] highPass = FilterOnePole(HIGHPASS, 15000, 0);
    }

    void setFreq(int filterIndex, int freq) {

        if (lineSize < filterIndex) return;
        
        int lineSize = sizeof(filterLine) / sizeof(filterLine[0]);

        if (filterIndex == 0 || filterIndex == lineSize - 1) {
            filterLine[filterIndex].setFrequency(freq);
        }
        else {
            filterLine[filterIndex << 1 - 1].setFrequency(freq);
            filterLine[filterIndex << 1].setFrequency(freq);
        }
    }
};