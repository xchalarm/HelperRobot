#include <Arduino.h>
#include <motor_esp.h>
#include <ps5Controller.h>
#include <ESP32Servo.h>


#define ena_motor_right 32
#define ina_motor_right 33
#define inb_motor_right 25
#define ena_motor_left 26
#define ina_motor_left 27
#define inb_motor_left 14

//define motor
Motor motor_right(20000, 8, 0, 1, ena_motor_right, ina_motor_right, inb_motor_right);
Motor motor_left(20000, 8, 1, 1, ena_motor_left, ina_motor_left, inb_motor_left);

Servo base;
Servo a1;
Servo a2;
Servo a3;
Servo a4;
Servo efx;

//define function
void move();
void arm_task();
void debug_controller();

//define global varieable
int max_speed = 255;
float speed_ly = 1 ;
float speed_rx = 1 ;
int ps5_LStickX ; 
int ps5_LStickY ;
int ps5_RStickX ;
int ps5_RStickY ;

int base_value = 0;
int a1_value = 0;
int a2_value = 0;
int a3_value = 0;
int a4_value = 0;
int efx_value = 60;



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
  base.attach(4);
  a1.attach(16);
  a2.attach(17);
  a3.attach(3);
  a4.attach(15);
  efx.attach(2);
}
 
void loop() {
  if(ps5.isConnected() == true){
    debug_controller();
    move();
    arm_task();
    delay(50);
  }
  // put your main code here, to run repeatedly:
}

//lx=joystick left x 
void arm_task(){
  int index_value = 5 ;
  if(ps5.Right() && base_value < 180)base_value += index_value;
  if(ps5.Left() && base_value > 0) base_value -= index_value;
  if(ps5.Up() && a1_value < 180)a1_value +=  index_value;  
  if(ps5.Down()&& a1_value > 0)a1_value -= index_value;  
  if(ps5.Square()&& a2_value < 180)a2_value += index_value;  
  if(ps5.Circle()&& a2_value > 0)a2_value -= index_value; 
  if(ps5.Triangle()&& a3_value < 180)a3_value += index_value;  
  if(ps5.Cross()&& a3_value > 0)a3_value -= index_value; 
  if(ps5.L1()&& a4_value < 180)a4_value += index_value;  
  if(ps5.L2()&& a4_value > 0)a4_value -= index_value; 
  if(ps5.R1()&& efx_value < 180)efx_value +=  index_value;  
  if(ps5.R2()&& efx_value > 0)efx_value -= index_value; 


  Serial.println("Base : "+ String(base_value));
  Serial.println("joint1 : "+ String(a1_value));
  Serial.println("Joint2 : "+ String(a2_value));
  Serial.println("Joint3: "+ String(a3_value));
  Serial.println("Joint4: "+ String(a4_value));
  Serial.println("End effector: "+ String(efx_value));

  base.write(base_value);
  a1.write(a1_value);
  a2.write(a2_value);
  a3.write(a3_value);
  a4.write(a4_value);
  efx.write(efx_value);

}



void move(){
  // float lx=ps5_LStickX/128.0;
  float ly=ps5_LStickY/128.0 * speed_ly;
  float rx=ps5_RStickX/128.0 * speed_rx;
  float d=max(abs(ly)+abs(rx),float(1));
  float motor_right_speed = (ly+rx)/d * max_speed ;
  float motor_left_speed = (ly-rx)/d * max_speed ;

  Serial.printf("motor_right_speed %f\n", motor_right_speed);
  Serial.printf("motor_left_speed %f\n", motor_left_speed);
  Serial.println();

  motor_right.spin(motor_right_speed);
  motor_left.spin(motor_left_speed);

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

