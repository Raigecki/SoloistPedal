// defines for setting and clearing register bits
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define BUFFSIZE 100

/////////////////////////////////////MIC/////////////////////////////////////
int micPin = A0;
int speakerPin = 9;
short micRead;
short outSig;

///////////////////////////////////SD Card///////////////////////////////////

short inBuffer1[BUFFSIZE];   int inBuffCtr1;   int currIn;
short inBuffer2[BUFFSIZE];   int inBuffCtr2; 
short outBuffer1[BUFFSIZE];  int outBuffCtr1;  int currOut;
short outBuffer2[BUFFSIZE];  int outBuffCtr2;

void setup() {
  // put your setup code here, to run once:
  
  // set prescale to 16
  sbi(ADCSRA,ADPS2) ;
  cbi(ADCSRA,ADPS1) ;
  cbi(ADCSRA,ADPS0) ;

   
  ////////////////////////////////////MIC//////////////////////////////////
  pinMode(micPin, INPUT);
  Serial.begin(9600);

  inBuffCtr1 = 0;
  inBuffCtr2 = 0; 
  outBuffCtr1 = 0;
  outBuffCtr2 = 0;
  currIn = 1;
  currOut = 1;

  pinMode(speakerPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

  //////////////////////////////////MIC///////////////////////////////////
  micRead = analogRead(micPin);
  Serial.print(micRead);
  Serial.print("\n");

  ///////////////////////////////SPEAKERS////////////////////////////////
  outSig = micRead >> 2 - 1;
  if (outSig < 0) outSig = 0; //We don't want to deal with - #
  int mappedSig = map(outSig, 0, 1023, 0, 5);
  digitalWrite(speakerPin, mappedSig);
}


void fillInBuffer(short inSig) {

  if (currIn == 1) {
    inBuffer1[inBuffCtr1] = inSig; //insert signal inside buffer
    if (inBuffCtr1 == (BUFFSIZE - 1)) {
      inBuffCtr1 = 0; //reset the counter when full
      currIn = 2;     //select next buffer when full
    }
  }
  else if (currIn == 2) {
    inBuffer2[inBuffCtr2] = inSig;
    if (inBuffCtr2 == (BUFFSIZE - 1)) {
      inBuffCtr2 = 0; //reset the counter when full
      currIn = 1;     //select next buffer when full
    }
  }
}

void fillOutBuffer(short * outSigArr) {

  for (int i = 0; i < BUFFSIZE; i++) {
    if (currOut == 1) {
      outBuffer1[i] = outSigArr[i];
    }
    else if (currOut == 2) {
      outBuffer2[i] = outSigArr[i];
    }
  }
  if (currOut == 1) currOut = 2;
  else currOut = 1;
  }

