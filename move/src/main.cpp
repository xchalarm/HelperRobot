#include <Arduino.h>
#include <motor_esp.h>
#include <ps5Controller.h>

#define ena_motor_right 32
#define ina_motor_right 33
#define inb_motor_right 25
#define ena_motor_left 26
#define ina_motor_left 14
#define inb_motor_left 27

//define motor
Motor motor_right(20000, 8, 0, 1, ena_motor_right, ina_motor_right, inb_motor_right);
Motor motor_left(20000, 8, 1, 1, ena_motor_left, ina_motor_left, inb_motor_left);

//define function
void move();
void debug_controller();

//define global varieable
int max_speed = 255;
float speed_ly = 1 ;
float speed_rx = 1 ;
int ps5_LStickX ; 
int ps5_LStickY ;
int ps5_RStickX ;
int ps5_RStickY ;






void setup() {
  /*motor_right.spin(200);
  motor_left.spin(200);
  delay(6000);
  motor_right.spin(0);
  motor_left.spin(0);
  delay(300);*/

  Serial.begin(115200);
  ps5.begin("90:b6:85:21:1a:b0"); //replace with MAC address of your controller
  Serial.println("Ready.");
}
 
void loop() {
  if(ps5.isConnected() == true){

    debug_controller();
    move();
    delay(300);
  }
  // put your main code here, to run repeatedly:
}

//lx=joystick left x 

void move(){
  // float lx=ps5_LStickX/128.0;
  float ly=ps5_LStickY/128.0 * speed_ly;
  float rx=ps5_RStickX/128.0 * speed_rx;
  float d=max(abs(ly)+abs(rx),float(1));
  float motor_right_speed = (ly-rx)/d * max_speed ;
  float motor_left_speed = (ly+rx)/d * max_speed ;

  Serial.printf("motor_right_speed %f\n", motor_right_speed);
  Serial.printf("motor_left_speed %f\n", motor_left_speed);
  Serial.println();

  // motor_right.spin(motor_right_speed);
  // motor_left.spin(motor_left_speed);

}
void debug_controller(){

  ps5_LStickX = abs(ps5.LStickX())<8 ? 0 : ps5.LStickX();
  Serial.printf("Left Stick x at %d\n", ps5_LStickX);

  ps5_LStickY = abs(ps5.LStickY())<8 ? 0 : ps5.LStickY();
  Serial.printf("Left Stick y at %d\n", ps5_LStickY);

  ps5_RStickX = abs(ps5.RStickX())<8 ? 0 : ps5.RStickX();
  Serial.printf("Right Stick x at %d\n", ps5_RStickX);

  ps5_RStickY = abs(ps5.RStickY())<8 ? 0 : ps5.RStickY();
  Serial.printf("Right Stick y at %d\n", ps5_RStickY);

  Serial.println();
}

