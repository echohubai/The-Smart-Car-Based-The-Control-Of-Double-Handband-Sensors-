#include "Wire.h"

#include "I2Cdev.h"
#include "MPU6050.h"
#include "SoftwareSerial.h" 
MPU6050 accelgyro;     //实例化传感器
int16_t ax, ay, az;    //定义原始数据
int16_t gx, gy, gz;
char str[512]; 
void setup() {
    Wire.begin();
    Serial.begin(9600);
    accelgyro.initialize();
}
void loop() {
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);    //获得原始数据
    sprintf(str, "%d,%d,%d,%d,%d,%d", ax, ay, az, gx, gy, gz); 
    //Serial.print(str);
   // Serial.write(byte(10));
    //Serial.print(ax);
    //Serial.print("\t");
    //Serial.print(ay);
      //Serial.print("\t");
   // Serial.print(az);
     // Serial.print("\t");
   if ( ax>6000 && ay>6000){
     Serial.print("G");
   }//前右拐
   if ( ax>6000 && ay<-6000){
     Serial.print("I");
   }// forwardleft
    
      if (ax<6000 && ax>-6000 && ay>-6000 && ay<6000){
       Serial.print("S");
      }//stop
       if (ax<6000 && ax>-6000 && ay<-6000){
       Serial.print("L");
      }//just left
       if (ax<6000 && ax>-6000 && ay>6000){
       Serial.print("R");
      }//just right
      if ( ax>6000 && ay>-6000 && ay <6000){
     Serial.print("F");
   }// just forward 
     if ( ax<-6000 && ay>-6000 && ay <6000){
     Serial.print("B");// just back
   }
    
         
    else if (ax<-6000){
     //Serial.print("B");
    }
}
    

