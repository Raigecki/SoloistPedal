void initWavHeader(char *);

///////////////////////////Global Variables/////////////////////////

char wavHeader[44]; //WAV header

void setup() {
  // put your setup code here, to run once:
  

}

void loop() {
  // put your main code here, to run repeatedly:

}

void initWavHeader(char * wavArr) {

  wavArr[0] = 'R';
  wavArr[1] = 'I';
  wavArr[2] = 'F';
  wavArr[3] = 'F';

  wavArr[8] = 'W';
  wavArr[9] = 'A';
  wavArr[10] = 'V';
  wavArr[11] = 'E';
  wavArr[12] = 'f';
  wavArr[13] = 'm';
  wavArr[14] = 't';
  wavArr[15] = ' ';

  wavArr[16] = 16;
  wavArr[17] = 0;
  wavArr[18] = 0;
  wavArr[19] = 0;
  wavArr[20] = 1;
  wavArr[21] = 0;
  wavArr[22] = 1;
  wavArr[23] = 0;
  
}

