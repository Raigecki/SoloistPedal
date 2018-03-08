	#include<EQ.h>
		//EQ::EQ() {
		//}
		
	    // Made a void function
		void EQ::set3Band() {
	
	        filterLine = new FilterOnePole[4];
	        ampLine = new float[4];
	
	        filterLine[0] = FilterOnePole(LOWPASS, 50, 0);
	        //Bp
	        filterLine[1] = FilterOnePole(LOWPASS, 300, 0);
	        filterLine[2] = FilterOnePole(HIGHPASS, 300, 0);
	
	        filterLine[3] = FilterOnePole(HIGHPASS, 15000, 0);
		}
	
		// Made a void function
	    void EQ::set5Band() {
	
	        filterLine = new FilterOnePole[8];
	        ampLine = new float[8];
	
			filterLine[0] = FilterOnePole(LOWPASS, 50, 0);
	        //Bp 1
	        filterLine[1] = FilterOnePole(LOWPASS, 300, 0);
	        filterLine[2] = FilterOnePole(HIGHPASS, 300, 0);
	        //Bp 2
	        filterLine[3] = FilterOnePole(LOWPASS, 1000, 0);
	        filterLine[4] = FilterOnePole(HIGHPASS, 1000, 0);
	        //Bp 3
	        filterLine[5] = FilterOnePole(LOWPASS, 5000, 0);
	        filterLine[6] = FilterOnePole(HIGHPASS, 5000, 0);
	
	        filterLine[7] = FilterOnePole(HIGHPASS, 15000, 0);
	    }
	
	    void EQ::setOutAmp(int filterIndex, int amp) {   
	        // if (lineSize < filterIndex) return; - moved below lineSize declaration
	        int lineSize = sizeof(ampLine) / sizeof(ampLine[0]);
			if (lineSize < filterIndex) return;
	
	        if (filterIndex == 0 || filterIndex == lineSize - 1) {
	            ampLine[filterIndex] = amp;
	        }
	        else {
	            ampLine[filterIndex << 1 - 1] = amp;
	            ampLine[filterIndex << 1] = amp;
	        }
	    }
	
	    void EQ::andrew(int filterIndex, int freq) {
	    	// if (lineSize < filterIndex) return; - moved below lineSize declaration
	        int lineSize = sizeof(filterLine) / sizeof(int);
	        
	        if (lineSize < filterIndex) return;
	
	        if (filterIndex == 0 || filterIndex == lineSize - 1) {
	            filterLine[filterIndex].setFrequency(freq);
	        }
	        else {
	            filterLine[filterIndex << 1 - 1].setFrequency(freq);
	            filterLine[filterIndex << 1].setFrequency(freq);
	        }
	    }
	    

	
	    float EQ::inputSignal(float sig) {
	        
	        int lineSize = sizeof(filterLine) / sizeof(int);
	        float out = 0;
	
	        for (int i = 0; i < lineSize; i++ ) {          
	                out += filterLine[i].input(sig) * (ampLine[i] / 100);
	        }
	        return out;
	    }

