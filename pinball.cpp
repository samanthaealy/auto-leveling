#define DR2 4
#define PWM2 5

const int buttonEasy = 9;
const int buttonMed = 11;
const int buttonHard = 13;

int stateEasy = 0;
int stateMed = 0;
int stateHard = 0;

double Setpoint, roll;

Adafruit_BNO055 bno = Adafruit_BNO055(55);

void setup() {
  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialize the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
  
  pinMode(DR1, OUTPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(DR2, OUTPUT);
  pinMode(PWM2, OUTPUT);
  /* Initialize rotation direction */
  digitalWrite(DR1, HIGH);
  digitalWrite(DR2, LOW);

  pinMode(buttonEasy, INPUT);
  pinMode(buttonMed, INPUT);
  pinMode(buttonHard, INPUT);
  
  Setpoint = 0.0 - 5.6250;
  roll = 0.0 - 3.0;
}

void loop() {
  /* Get a new sensor event */
  sensors_event_t event; 
  bno.getEvent(&event);
  
  /* Display the floating point data */
  //Serial.print("X: ");
  //Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  
  delay(100);

  stateEasy = digitalRead(buttonEasy);
  stateMed = digitalRead(buttonMed);
  stateHard = digitalRead(buttonHard);

  if(stateEasy == HIGH)
  {
    Setpoint = -3.0 - 5.6250;
  }
  else if(stateMed == HIGH)
  {
    Setpoint = -6.0 - 5.6250;
  }
  else if(stateHard == HIGH)
  {
    Setpoint = -9.0 - 5.6250;
  }
  
  if(event.orientation.y < Setpoint)
  {
    digitalWrite(DR1, LOW);
  }
  else
  {
    digitalWrite(DR1, HIGH);
  }
  if(event.orientation.z < roll)
  {
    digitalWrite(DR2, LOW);
  }
  else
  {
    digitalWrite(DR2, HIGH);
  }
  if(abs(event.orientation.y - Setpoint) > 0.5)
  {
    analogWrite(PWM1, 40);
  }
  else
  {
    analogWrite(PWM1, 0);
  }
  
  if(abs(event.orientation.z - roll) > 0.5)
  {
    analogWrite(PWM2, 80);
  }
  else
  {
    analogWrite(PWM2, 0);
  }

}
