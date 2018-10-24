#include <NewPing.h>
#include <Servo.h>

#define TRIGGER_PIN  8  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     7  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
Servo leftBackW;
Servo rightBackW;
Servo rightFrontW;
Servo leftFrontW;


//Front: left wheel is pin 2 and right wheel is pin 3
//Back: left wheel is pin 4 and right wheel is pin 5
//Front wheels were going backward so reversed #s in forward() and backup()
//Front left wheel was working before some wires came unplugged. Need to debug wiring.
//Still need to test ultrasonic and tune wheel speeds.
void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  leftBackW.attach(4);
  leftBackW.write(90);
  rightBackW.attach(5);
  rightBackW.write(90);
  leftFrontW.attach(2);
  leftFrontW.write(90);
  rightFrontW.attach(3);
  rightFrontW.write(90);
}

void stop() {
  leftBackW.write(90);
  rightBackW.write(90);  
  leftFrontW.write(90);
  rightFrontW.write(90);
}

void forward() {
  leftBackW.write(0);
  rightBackW.write(180);
  leftFrontW.write(180);
  rightFrontW.write(0);
}

void backup() {
  leftBackW.write(180);
  rightBackW.write(0);
  leftFrontW.write(0);
  rightFrontW.write(180);
}

void loop() {
  delay(50);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  int distance = uS/US_ROUNDTRIP_CM;
  Serial.print(distance); // Convert ping time to distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
  if (distance < 5) {
    stop();
    delay(1000);
    backup();
    delay(1000);
  } else {
    forward();
  }

}
