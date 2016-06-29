//Code by Hunter Knott and based off of Owen Sobel's Bluetooth 4.0 code
#include<SoftwareSerial.h>


#define in1 7 //L298n Motor Driver pins
#define in2 8
#define in3 12
#define in4 13
#define ena 5
#define enb 6
int command; //Int to store app command state.
int Speed = 100; // 0 - 255.
int Speedsec;
int buttonState = 0;
int lastButtonState = 0;
int Turnradius = 0; //Set the radius of a turn, 0 - 255 Note:the robot will malfunction if this is higher than int Speed.
int brakeTime = 45;
int brkonoff = 1;  //1 for the electronic braking system, 0 for normal
int16_t ax1, ay1, az1;// 定义接收数据类型
int16_t ax2, ay2, az2;// 定义接收数据类型
 int  str1[512];// 定义接收数据类型
 int  str2[512];// 定义接收数据类型
 char cmd1;
 char cmd2;
SoftwareSerial mySerial(3,4);//定义软串口及其引脚
void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(ena, OUTPUT);
  pinMode(enb, OUTPUT);
 // pinMode(LED, OUTPUT); //Set the LED pin.
 mySerial.begin(9600);// 定义软串口波特率
 Serial.begin(9600);// 定义硬串口波特率
  mySerial.listen();// 软串口监听
}

void loop() {
  if (Serial.available() >0  &&  mySerial.available()>0){
   
   cmd1 = mySerial.read();// 软串口数据读取
   Serial.print(ax1);
   cmd2 = Serial.read();// 硬串口数据读取
   // 读取的数据进行判断并且输出控制
   if (cmd1=='F' && cmd2=='F')
    command= 'F';
    else if ( cmd1=='B' && cmd2=='B')
     command='B';
         else if( cmd1=='S' && cmd2=='S')
         command='S';
    if   (cmd1=='L' && cmd2=='L')
      command='L';
      else if (cmd1=='R' && cmd2=='R')
      command='R';
      if   (cmd1=='G' && cmd2=='G')
      command='G';
      else if (cmd1=='I' && cmd2=='I')
      command='I';
     
   
    
   switch (command){
    
      case 'F':
       forward();
        break;
        case 'S':
       Stop();
        break;
      case 'B':
        back();
        break;
      case 'L':
        left();
        break;
      case 'R':
        right();
        break;
      case 'G':
        forwardleft();
        break;
      case 'I':
        forwardright();
        break;
      case 'H':
        backleft();
        break;
      case 'J':
        backright();
        break;
      case '0':
        Speed = 100;
        break;
      case '1':
        Speed = 140;
        break;
      case '2':
        Speed = 153;
        break;
      case '3':
        Speed = 165;
        break;
      case '4':
        Speed = 178;
        break;
      case '5':
        Speed = 191;
        break;
      case '6':
        Speed = 204;
        break;
      case '7':
        Speed = 216;
        break;
      case '8':
        Speed = 229;
        break;
      case '9':
        Speed = 242;
        break;
      case 'q':
        Speed = 255;
        break;
        
    mySerial.print( command);
    }
  }
    Speedsec = Turnradius;
    if (brkonoff == 1) {
      brakeOn();
    } else {
      brakeOff();
    }
  
  }

// 以下是小车运动方向程序
void forward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  analogWrite(ena, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255);
}

void back() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enb, 255);
}

void left() {
 digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 0);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 255);
}

void right() {
 digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  analogWrite(ena, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enb, 0);
}
void forwardleft() {
  analogWrite(in1, Speedsec);
  analogWrite(in3, Speed);
}
void forwardright() {
  analogWrite(in1, Speed);
  analogWrite(in3, Speedsec);
}
void backright() {
  analogWrite(in2, Speed);
  analogWrite(in4, Speedsec);
}
void backleft() {
  analogWrite(in2, Speedsec);
  analogWrite(in4, Speed);
}

void Stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void brakeOn() {
  //Here's the future use: an electronic braking system!
  // read the pushbutton input pin:
  buttonState = command;
  // compare the buttonState to its previous state
  if (buttonState != lastButtonState) {
    // if the state has changed, increment the counter
    if (buttonState == 'S') {
      if (lastButtonState != buttonState) {
        digitalWrite(in1, HIGH);
        digitalWrite(in2, HIGH);
        digitalWrite(in3, HIGH);
        digitalWrite(in4, HIGH);
        delay(brakeTime);
        Stop();
      }
    }
    // save the current state as the last state,
    //for next time through the loop
    lastButtonState = buttonState;
  }
}
void brakeOff() {

}
