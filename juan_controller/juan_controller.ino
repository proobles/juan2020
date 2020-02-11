#include <ServoESP32.h>
#include <PS4Controller.h>
#include <ps4_int.h>

static const int MRPin = A0; // Right motor PWM (speed)
static const int MLPin = A1; // Left motor PWM (speed)
int stop = 92;
Servo rightMotor;
Servo leftMotor;

#define NEUTRAL 93


void receivePacket() {
  int L_mapped, R_mapped;

  int L_bm = PS4.data.analog.stick.ly + PS4.data.analog.stick.lx;
  int R_bm = PS4.data.analog.stick.lx - PS4.data.analog.stick.ly;

  L_mapped = map(L_bm, 191, -191, 44, 142);
  R_mapped = map(R_bm, 191, -191, 44, 142);
  
  if(L_mapped < 97 && L_mapped > 87) L_mapped = stop;
  if(R_mapped < 97 && R_mapped > 87) R_mapped = stop;
  
  leftMotor.write(L_mapped);
  rightMotor.write(R_mapped);
}

void controllerConnect() {
  Serial.println("Connected!.");
  PS4.setLed(255,255,255);
}

void setup() {
  Serial.begin(115200);
  rightMotor.attach(MRPin);
  leftMotor.attach(MLPin);
  //PS4.attach(receivePacket);
  PS4.attachOnConnect(controllerConnect);
  PS4.begin("01:02:03:04:05:66");
}

void loop() {
    if(PS4.isConnected()) {
      receivePacket();

     
    }
}
