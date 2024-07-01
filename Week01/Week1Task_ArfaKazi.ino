// C++ code
//
// Importing the Servo Library
#include <Servo.h>
Servo myservo;  // create servo object to control a servo

// Initialize LED pins
int leds[3] = {2,3,4};

// Initialise Ultrasonic Pins 
const int trigPin = 10;
const int echoPin = 9;
long duration;
int distance;



void setup()
{
  // Set LED pins as OUTPUT
  for (int led : leds) {
  	pinMode(led, OUTPUT);
  }
  
  // servo
  myservo.attach(5);  // attaches the servo on pin 5 to the servo object
  
  // Ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  Serial.begin(9600); // Initialize serial communication
}




void loop()
{
  //Reading the value of Ultrasonic Sensor
  digitalWrite(trigPin, LOW);		   // Clears the trigPin
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);		   // Sets the trigPin on HIGH state for 10 micro seconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);   // Reads the echoPin, returns the sound wave travel time in microseconds
  distance = duration * 0.034 / 2;	   // Calculating the distance
  
  Serial.print("Distance: ");          // Prints the distance on the Serial Monitor
  Serial.println(distance);
  
  // Control the servo motor based on distance
  if (distance >= 25 && distance <= 100) {
    int angle = map(distance, 25, 100, 0, 180);
    myservo.write(angle);
  }else if (distance < 25) {
    myservo.write(0);
  } else {
    myservo.write(180);
  }
  
  (distance < 100)? digitalWrite(leds[0], HIGH):digitalWrite(leds[0], LOW); 
  (distance < 60)? digitalWrite(leds[1], HIGH):digitalWrite(leds[1], LOW); 
  (distance < 25)? digitalWrite(leds[2], HIGH):digitalWrite(leds[2], LOW); 
  
  delay(100); 
}