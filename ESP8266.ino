#define TotalSamples 800
int runcount = 0;
unsigned long sampleTime[TotalSamples] = {};
int sensorValue[TotalSamples]={};

const int pin = A0;

float zero = 0;


void setup() {
  Serial.begin(38400);
  zero = calibration();
  analogWriteResolution(10);
  analogWriteFreq(200);
  pinMode(BUILTIN_LED, OUTPUT);
}

float calibration() 
{
  Serial.println("---------------");
  Serial.print("Calibrating...\nOffset:");
  float acc = 0;
  for (int i = 0; i < 1000; i++) {
    acc += analogRead(pin);
  }
  float zero = acc / 1000;
  zero = zero * ( 3.3 / 1023.0);
  Serial.print(zero);
  Serial.println("V");
  Serial.println("Done!");
  Serial.println("---------------");
  return zero;
  
}

float getcurrent()
{
  float sum = 0;
  float voltage = 0;
  float current = 0;
  
  for (int i = 0; i < TotalSamples; i++)
    {
      voltage = sensorValue[i] * (3.3 / 1023.0) - zero;
      current = voltage / 0.185;
      sum += sq(current);
    }
  current = sqrt(sum / TotalSamples);
  return (current);
}

//the loop routine runs over and over forever:
void loop() {
 
  while (runcount < TotalSamples)
  {
    sampleTime[runcount]=micros();
    sensorValue[runcount]=analogRead(A0);
    runcount++;
  }
     
    float ave_sample_rate = 0;
    ave_sample_rate = 1000000.0 / ((sampleTime[TotalSamples - 1] - sampleTime[0]) / 800.0);
    Serial.print(ave_sample_rate);
    Serial.println("Hz");
    
    float currentRMS = getcurrent();
    Serial.print(currentRMS);
    Serial.println("A");

    float power = currentRMS * 220;
    Serial.print(power);
    Serial.println("W");

    digitalWrite(LED_BUILTIN,LOW);
    analogWrite(D1,power / 100 * 1023); // duty cicle 0-100% equals 0-100W
    delay(500);
    digitalWrite(LED_BUILTIN,HIGH);
    runcount = 0;
    zero = calibration();
    
}
