

const int trigPin2 = 11;// TRIGGER FOR tank LEVEL
const int echoPin2 = 12;// ECHO FOR tank LEVEL


const int trigPin3 = 7;// TRIGGER for exit sensor
const int echoPin3 = 6;// ECHO FOR exit sensor

const int trigPin1 = 10;// TRIGGER entry sensor
const int echoPin1 = 9;// ECHO FOR entry sensor

const int buzzer = 8;// buzzer
const int pump_relay= 13; // relay controlling pump

int a=0;
int b=0;
int c=0;
                   
// defines variables

long duration3;// PULSE WIDTH FOR MOTION SENSOR
int distance3;// DISTANCE FOR MOTION SENSING

long duration2;// PULSE WIDTH FOR WATER LEVEL
int distance2;// DISTANCE FOR FOR WATER LEVEL

long duration1;// PULSE WIDTH FOR ENTRY
int distance1;// DISTANCE FOR ENTRY

long start; //variable holding the start time when the pump is put on

//declaring functions;
void checks_entry_sensor(); 
void checks_exit_sensor();
void checks_tank_level();


void setup() {



pinMode(trigPin2, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin2, INPUT); // Sets the echoPin as an Input

pinMode(trigPin1, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin1, INPUT); // Sets the echoPin as an Input

pinMode(trigPin3, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin3, INPUT); // Sets the echoPin as an Input



pinMode(pump_relay, OUTPUT); // 
pinMode(buzzer, OUTPUT); //

digitalWrite(pump_relay, HIGH); // putting off the pump's relay (LOW is for ON and HIGH is for OFF)
digitalWrite(buzzer,LOW); // putting off buzzer

Serial.begin(9600); // Starts the serial communication

}
void loop() {// main code here, runs repeatedly:
  
checks_tank_level();  // this part and the line below checks the tank level before further operation
if (distance2<=30){


  if((a==0)&&(b==0)){
    

  
checks_entry_sensor();  // this part of the program checks if there's an entry 
    if (distance1<=65){   //checks the entry sensor has been crossed
    
    b=1; // this prevents the system from checking if there is an exit from  it because that only happens when b = 0
    start = millis(); // stores the  time because the pump is about to be put on (pump start time)
         if(b==1) {digitalWrite(pump_relay,LOW);// pump is turned on
         while ((a==0)&&(b==1)){
            checks_exit_sensor();///checks if the exit sensor has been crossed
                    
            if((millis() - start > 500) || (distance3<=65)){ //if exit sensor has been crossed or the pump has run for up to 3000 milisecs (3 sec) (present time (millis)-pump start time) the pump will be turned off
                  digitalWrite(pump_relay,HIGH); // pump is turned off
                  if(distance3<=65){ //only when then the exit sensor has been crossed the buzzer makes a beep
                         delay(1000);
                         digitalWrite(buzzer,HIGH);
                         delay(500);
                         digitalWrite(buzzer,LOW);
                         b=0; // b returns to 0 and the system can now check  id theres an entry
                              
                     }
              }
       
          }
        }
    }

    checks_exit_sensor(); // this part of the program checks if there's an exit
    if (distance3<=65){  // checks if the exit sensor has been crossed
     a=1;  // this prevents the system from checking if there is an entry from  it because that only happens when a = 0
    
     while((a==1)&&(b==0)){
        checks_entry_sensor(); //checks if the entry sensor has been crossed
       if(distance1<=65){ // if the entry sensor has been crossed, the buzzer makes a beep
          delay(1000);
          digitalWrite(buzzer,HIGH);
          delay(500);
          digitalWrite(buzzer,LOW);
          a=0; // a returns to 0 and the system can now check  if theres an entry
         
         
         
        }
      }
    }


  
  }
if (distance2>30){  //code for buzzer alarm when low on chemical
  digitalWrite(buzzer, LOW);
  digitalWrite(buzzer, HIGH); 
  delay(200);
  digitalWrite(buzzer, LOW); 
  delay(200);
  digitalWrite(buzzer, HIGH); 
  delay(200);
  digitalWrite(buzzer, LOW); 
  delay(200);

}



}

}
void checks_entry_sensor(){  // this is s function which checks the entry sensor
  digitalWrite(trigPin1, LOW);  
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin1, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin1, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin1, HIGH);
// Calculating the distance
distance1= duration1*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance1: ");
Serial.println(distance1);
//delay(500);
}

void checks_exit_sensor(){ // this is s function which checks the exit sensor
  
digitalWrite(trigPin3, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin3, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin3, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration3 = pulseIn(echoPin3, HIGH);
// Calculating the distance
distance3= duration3*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance3: ");
Serial.println(distance3);
//delay(500);
}

void checks_tank_level(){ // this function checks the tank level
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds
duration2 = pulseIn(echoPin2, HIGH);
// Calculating the distance
distance2= duration2*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance2: ");
Serial.println(distance2);
//delay(500);
}
