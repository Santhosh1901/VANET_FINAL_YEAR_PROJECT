// Speed_Sensor 

float REV = 0;
int RPM_VALUE;
int PREVIOUS = 0;
int TIME;

void INTERRUPT()
{
  REV++;
}
 
void setup() 
{
  Serial.begin(9600);
  attachInterrupt(1,INTERRUPT, RISING);
}

void loop() 
{
  delay(1000);
  detachInterrupt(0);
  TIME = millis() - PREVIOUS;
  RPM_VALUE = (REV/TIME) * 60000;
  PREVIOUS = millis();
  REV = 0;
  int velocity = 0.1885 * RPM_VALUE * 0.025;     //Vehicle speed = 0.1885 * Wheel RPM * diameter of the tire.  (in Km/hr)
  Serial.println(velocity);
  attachInterrupt(1, INTERRUPT, RISING); 
}
