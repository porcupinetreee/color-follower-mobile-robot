#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1);  
#define left1 3
#define left2 4
#define right1 5
#define right2 6

#define enablea 9
#define enableb 10

signed int x;
signed int y;
signed int z;
signed int w;

float a;
float m;

String str;
char dir = 0;

int el = 0;
int er = 0;

int elp = 0;
int erp = 0;

char getData;

boolean fast = true;
boolean StateA0 = false;
boolean StateA1 = false;
boolean State11 = false;

void process();
void processx();
void processy();
void processz();
void processM();
void processA();

void setup() {

  mySerial.begin(9600);
  mySerial.println("Start...");
  pinMode(left1, OUTPUT);
  pinMode(left2, OUTPUT);
  pinMode(right1, OUTPUT);
  pinMode(right2, OUTPUT);
  pinMode(enablea, OUTPUT);
  pinMode(enableb, OUTPUT);
  Serial.begin(9600);
  Serial.println("Start...");
}


void loop()
{


  while (mySerial.available())
  {

    char getData = mySerial.read();

    if (getData == 'M')
    {
      m = mySerial.parseFloat();

      if (mySerial.read() == '#')
      {
        processM();
      }
    }

    if (getData == 'A')
    {
      a = mySerial.parseFloat();

      if (mySerial.read() == '#')
      {
        processA();
      }
    }

    if (getData == 'x')
    {
      delay(5);
      if (mySerial.read() == '#')
      {
        processx();
      }
    }

    if (getData == 'y')
    {
      delay(5);
      if (mySerial.read() == '#')
      {
        processy();
      }
    }

    if (getData == 'z')
    {
      delay(5);
      if (mySerial.read() == '#')
      {
        processz();
      }
    }

    if (getData == '~') {

      x = mySerial.parseInt();

      if (mySerial.read() == '*') {

        y = mySerial.parseInt();

        if (mySerial.read() == '@') {

          z = mySerial.parseInt();

          if (mySerial.read() == '.') {

            w = mySerial.parseInt();

            if (mySerial.read() == '#') {

              process();
            }
          }
        }
      }
    }


  }

}

void process() {

  Serial.print("x: " + String(x) + ", y: " + String(y) + ", z: " + String(z) + ", w: " + String(w));


  if (fast == false) {
    er = map(y, 0, 255, 0, 255);
  }
  else {
    er = y;
  }
    //left motor control
  if (er >= 0) {
    digitalWrite(left1, HIGH) ;
    digitalWrite(left2, LOW) ;
  }

  else if (er < 0) {
    digitalWrite(left1, LOW) ;
    digitalWrite(left2, HIGH) ;
  }

  erp = abs(er);


  //right motor control:

  if (fast == false) {
    el = map(x, 0, 255, 0, 255);
  }
  else {
    el = x;
  }

  if (el > 0) {
    digitalWrite(right1, LOW) ;
    digitalWrite(right2, HIGH) ;
  }

  else if (el <= 0)  {
    digitalWrite(right1, HIGH) ;
    digitalWrite(right2, LOW) ;
  }

  elp = abs(el);

  analogWrite(enablea, elp);
  analogWrite(enableb, erp);

  Serial.flush();
  mySerial.flush();
}



void processx() {
  Serial.println("Button x! ");
  mySerial.flush();
  fast = true;
}

void processy() {
  Serial.println("Button y! ");
  mySerial.flush();
}

void processz() {
  Serial.println("Button z! ");
  mySerial.flush();
  fast = false;
}

void processM() {
  Serial.print("Received Magnitude: ");
  Serial.println(m);
  mySerial.flush();
}

void processA() {
  Serial.print("Received Angle: ");
  Serial.println(a);
  mySerial.flush();
}
