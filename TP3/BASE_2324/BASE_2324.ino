// PIN Declaration
#define VA 18
#define VB 31
#define I1 34
#define I2 35
#define PWM 12

#define I1_B 37
#define I2_B 36
#define PWM_B 8

// Sampling Time
#define DT 2 // in milliseconds
#define TE (DT*0.001F) // in seconds

volatile long pulse = 0; // position in pulses of the encoder
volatile long  t_ISR_last = 0;
volatile long  t_ISR = 1;
volatile short dir = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //Config pins
  pinMode(VA, INPUT_PULLUP);
  pinMode(VB, INPUT_PULLUP);
  
  pinMode(I1, OUTPUT);
  pinMode(I2, OUTPUT);
  pinMode(PWM, OUTPUT); 
   
  pinMode(I1_B, OUTPUT);
  pinMode(I2_B, OUTPUT);
  pinMode(PWM_B, OUTPUT);

  // Config Interrupts (to catch rising edges of encorder chanel A)
  attachInterrupt(digitalPinToInterrupt(VA), ISR_VA, RISING);

}


void Moteur(float voltage){
  int value_pwm;
  voltage = constrain(voltage,-9.0, 9.0);
  value_pwm = abs(voltage)*255.0/12.0;
  
  if(voltage>0)
  {
    digitalWrite(I2,LOW);
    digitalWrite(I1,HIGH);
    digitalWrite(I1_B,LOW);
    digitalWrite(I2_B,HIGH);
  }else{
    digitalWrite(I1,LOW);
    digitalWrite(I2,HIGH);
    digitalWrite(I2_B,LOW);
    digitalWrite(I1_B,HIGH);
  }
  
  analogWrite(PWM, value_pwm   );
  analogWrite(PWM_B, value_pwm   );
}

void loop() {
  
  static float u=0; // control value in Volts
  static float r=0; // reference value in .???
  
  unsigned long temps=0; //time of the current sample
  static unsigned long temps_prec=0; // time of the last sample
  
  //Wait next sampling time
  temps = millis();
  while( (temps-temps_prec)<DT)
  {
    temps = millis();
  }
  temps_prec = temps;
  
  // Set the reference, currently a pulse of 500 ms 
       if(temps<100) {r=0;}
  else if(temps<600) {r=5;}
  else {r=0;} 

    
  // Set the control value. Can use getSpeed() and getPosition() to get measurements.
  u = r;  

  // Apply the control to the motor
  Moteur(u);

  // Log to serial the 1st second of the experiment
  if (temps <1000){ 
  Serial.print(u);
  Serial.print(" ,");
  Serial.print(getSpeed());
  Serial.print(" ;");
  Serial.println(" ");
  }                   
}



// ISR_VA Interrupt service routine fired in rising edge of encoder chanel A. 
// used to count the number of pulses (position) and the measure the angular velocity.
void ISR_VA(){
  if(digitalRead(VB)){
    pulse++;
    dir = 1;  
  }else{
    pulse--;
    dir = -1;
  }
  t_ISR_last = t_ISR;
  t_ISR = micros();
}

// getSpeed() returns the current angular velocity in pulses/seconds.
float getSpeed(){
  long  t_ISR_last_copy;
  long  t_ISR_copy;
  short dir_copy;
  noInterrupts();
  t_ISR_last_copy =t_ISR_last;
  t_ISR_copy = t_ISR;
  dir_copy = dir;
  interrupts();
  if( t_ISR==t_ISR_last)
    return 0;
  else
    {
      float duration = (t_ISR_copy-t_ISR_last_copy)*1e-6;
      return (1.0/duration)*dir;
    }
}

// getPosition() returns the current angular position in pulses.
long getPosition(){
  long pos;
  noInterrupts();
  pos = pulse; 
  interrupts();
  return pos;
}
