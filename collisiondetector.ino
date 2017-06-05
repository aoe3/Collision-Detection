// constants definition
//these pins will correspond to states of the vehicle

//vehicle is very close to obstacle, stop immediately
const int redPin = D0;

//vehicle is in range of the obstacle where we would want to slow down
const int greenPin = D1;

//vehicle is far from obstacle
const int bluePin = D2;

//sonarPin checks for obstacles, motorPin gives instructions to motor
const int sonarPin = A0;
const int motorPin = D3;

/**sonarPin is read into sVal, which is converted to sVoltage, which is
translated to centimeters (sonar_cm), and then to inches (sonar_inches).
*/
double sVal = 0;
double sVoltage = 0;
double sonar_cm = 0;
double sonar_inches = 0;

byte incoming_byte;

// The setup() method runs once, when the sketch starts
void setup() {
  // initialize the digital pin as an output:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(motorPin, OUTPUT);
}

// the loop() method runs over and over again,
// as long as the Arduino has power
void loop()
{   /**Read sonarPin to sVal and convert to sVoltage.
    Translate the voltage to cm and then inches.*/
    sVal = analogRead(sonarPin);

    //need to map the highest possible reading of the sonar to 3.3v
    sVoltage = map(sVal, 0.0, 4095.0, 0.0, 3300);

    //convert sVoltage to centimeters and then inches.
    sonar_cm = ((70.0/(sVoltage/1000.0)) - 6.0);
    sonar_inches = (sonar_cm/2.54);

    //Give us a reading of the sonar for record.
    Serial.println(sonar_inches);


    //there is no obstacle detected for at least 2.5 feet.
    if(sonar_inches > 30.0){
      //keep motor running
      analogWrite(motorPin, 240);

      //keep blue pin on
      analogWrite(redPin, 0);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 255);

      //delay half a second until next reading.
      delay(500);

    //obstacle detected between 1 and 2.5 feet.
    } else if ((12.0 < sonar_inches) && (sonar_inches <= 30.0)){

      //slow motor
      analogWrite(motorPin, 180);

      //turn blue pin off and turn on green pin
      analogWrite(redPin, 0);
      analogWrite(greenPin, 255);
      analogWrite(bluePin, 0);

      //delay half a second until next reading.
      delay(500);

    //obstacle detected within a foot of the vehicle
    } else {

      //turn off motor to stop vehicle!
      analogWrite(motorPin,0);

      //turn green pin off and turn on red pin
      analogWrite(redPin, 255);
      analogWrite(greenPin, 0);
      analogWrite(bluePin, 0);

      //delay half a second until next reading.
      delay(500);
    }
}
