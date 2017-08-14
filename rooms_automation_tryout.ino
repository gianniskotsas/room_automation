
#define RELAY1  7  

const int sensorPin=A1;
const int threshold= 100;

int state=HIGH;    //the current state of the OUTPUT pin
int reading;       // current reading drom the INPUT pin
int previous=LOW;  //the previous reading from the INPUT pin

long time= 0; // the last time the OUTPUT pin was toggled
long debounce= 200; // the debounce time, increase if the output flickers

String message; //string that stores the incoming message


void setup()
{    
Serial.begin(9600);
pinMode(RELAY1, OUTPUT);       
pinMode(sensorPin, INPUT);
}

  void loop()
{
  int val = analogRead(sensorPin);    //reads the value of the piezoelectric sensor

if(val>threshold)
{
  reading=HIGH;
}
else
{
  reading=LOW;
}

if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;                // stores the state of the switch and accordingly changes its value
    else
      state = HIGH;

    time = millis();    
  }

  previous=reading;         //stores the previous reading
  
    while(Serial.available())
  {//while there is data available on the serial monitor
    message+=char(Serial.read());//store string from serial command
  }
  if(!Serial.available())          //Bluetooth command lines to open the lights or switch them off
  {
    if(message == "lights on")
    {//if data is available
      Serial.println(message); //show the data 
      digitalWrite(RELAY1, HIGH); 
      message=""; //clear the data
    }
    if(message == "lights off")
    {
      Serial.println(message);
      digitalWrite(RELAY1, LOW);
      message="";
    }
   }

  if (state== HIGH){              //Piezoelectric sensor to open the lights or switch them off, in case there is no BT device available
    digitalWrite(RELAY1, HIGH);
  }
  else
  {
    digitalWrite(RELAY1, LOW);
  }
  
}
