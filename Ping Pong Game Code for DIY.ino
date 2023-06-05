#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

#define start 13
#define P1U 6
#define P1D 7
#define P2U 8
#define P2D 9
#define piezo 10


byte paddle1[16] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};  
byte player11[8] = {0, 0, 0, 0, 0, 0, 1, 1};              
byte player12[8] = {1, 1, 0, 0, 0, 0, 0, 0};              

byte paddle2[16] = {0, 0, 0, 0, 0, 0, 16, 16, 16, 16, 0, 0, 0, 0, 0, 0};
byte player21[8] = {0, 0, 0, 0, 0, 0, 16, 16};              
byte player22[8] = {16, 16, 0, 0, 0, 0, 0, 0};              

byte ball[16] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0};   
byte ball1[8] = {0, 0, 0, 0, 0, 0, 0, 1};               
byte ball2[8] = {0, 0, 0, 0, 0, 0, 0, 0};               


int x = 0, bounce = 0, v1 = 0, v2 = 0, v3 = 0;
char direction = 'L';
int score1 = 0, score2 = 0;
boolean game = 0;
int a = 0;

void setup() {
  pinMode(P1U, INPUT);      
  pinMode(P1D, INPUT);
  pinMode(P2U, INPUT);
  pinMode(P2D, INPUT);
  pinMode(start, INPUT);
  pinMode(piezo, OUTPUT);   

  piezoSound(50);       
  lcd.begin(16, 2);       
  lcd.clear();          
  lcd.setCursor(2, 0);      
  lcd.print("Arduino UNO");   
  lcd.setCursor(1, 1);
  lcd.print("Ping Pong Game");
  delay(1500);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Developed by:");
  lcd.setCursor(0, 1);
  lcd.print("Group-10");
  delay(3000);
}
void loop() {  
  while (game == 0) {
    for (a; a < 1; a++) {
      for (int i = 0; i < 16; i++) {
        if (6 <= i && i <= 9) {
          paddle1[i] = 1;
          paddle2[i] = 16;
        }

        else {
          paddle1[i] = 0;
          paddle2[i] = 0;
        }

        if (i == 7)ball[i] = 1;
        else ball[i] = 0;
      }
      x = 8;              
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Press start");
      lcd.setCursor(3, 1);
      lcd.print("button   ->");
    }

    
    if (digitalRead(start) == HIGH) {
      lcd.clear();
      lcd.setCursor(5, 0);
      lcd.print("Player");
      lcd.setCursor(0, 1);
      lcd.print("1");
      lcd.setCursor(15, 1);
      lcd.print("2");
      delay(2000);

      for (int i = 3; i > 0; i--) {
        lcd.clear();
        lcd.setCursor(4, 0);
        lcd.print("Be ready!");
        lcd.setCursor(8, 1);
        lcd.print(i);
        if (i == 1)piezoSound(100);
        delay(1000);
      }
      a = 0;
      game = 1;             
    }
    delay(100);
  }

  
  if (digitalRead(P1U) == HIGH) {
    paddle1Up();
    delay(50);
  }
  if (digitalRead(P1D) == HIGH) {
    paddle1Down();
    delay(50);
  } 
  if (digitalRead(P2U) == HIGH) {
    paddle2Up();
    delay(50);
  }  
  if (digitalRead(P2D) == HIGH) {
    paddle2Down();
    delay(50);
  }

  
  for (int i = 0; i <= 7; i++) {
    player11[i] = paddle1[i];
  }

  for (int i = 0, j = 8; i <= 7, j <= 15; i++, j++) {
    player12[i] = paddle1[j];
  }

  
  for (int i = 0; i <= 7; i++) {
    player21[i] = paddle2[i];
  }

  for (int i = 0, j = 8; i <= 7, j <= 15; i++, j++) {
    player22[i] = paddle2[j];
  }

 
  for (int i = 0; i <= 7; i++) {
    ball1[i] = ball[i];
    delay(8);
  }

  for (int i = 0, j = 8; i <= 7, j <= 15; i++, j++) {
    ball2[i] = ball[j];
  }

  
  lcd.createChar(0, player11);
  lcd.createChar(1, player12);
  lcd.createChar(2, player21);
  lcd.createChar(3, player22);
  lcd.createChar(4, ball1);
  lcd.createChar(5, ball2);

  
  lcd.clear();
  lcd.setCursor(0, 0);  
  lcd.print(score1);
  lcd.setCursor(0, 1);  
  lcd.print(score2);

  lcd.setCursor(3, 0);  
  lcd.write(byte(0));
  lcd.setCursor(3, 1);  
  lcd.write(byte(1));
  lcd.setCursor(15, 0); 
  lcd.write(byte(2));
  lcd.setCursor(15, 1); 
  lcd.write(byte(3));
  lcd.setCursor(x, 0);  
  lcd.write(byte(4));
  lcd.setCursor(x, 1);  
  lcd.write(byte(5));

 
  if (x == 3) {
    for (int b = 0; b < 16; b++) {
      if (ball[b] != 0) {
        v1 = ball[b];
        v2 = paddle1[b];
      }
    }

    
    if (v1 == v2) {
      direction = 'R';
      score1 += 1;
      piezoSound(10);
    }

    
    else {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Game over");
      lcd.setCursor(4, 1);
      lcd.print("P2 won!");

      
      for (int i = 0; i < 3; i++) {     
        piezoSound(500);
        delay(500);
      }
      score1 = score2 = 0;
      delay(1000);
      game = 0;
    }
  }

  
  if (x == 15) {
    for (int b = 0; b < 16; b++) {
      if (ball[b] != 0) {
        v1 = ball[b];
        v3 = paddle2[b];
      }
    }

    
    if (v1 == v3) {
      direction = 'L';
      score2 += 1;
      piezoSound(10);
    }

   
    else {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Game over");
      lcd.setCursor(4, 1);
      lcd.print("P1 won!");

      
      for (int i = 0; i < 3; i++) {
        piezoSound(500);
        delay(500);
      }
      score1 = score2 = 0;
      delay(1000);
      game = 0;
    }
  }

  
  if (direction == 'L') {
    for (int b = 0; b < 16; b++)
      if (ball[b] == 16) x -= 1;

    if (bounce == 0)
      ballLeftDown();
    else
      ballLeftUp();
  }

  
  if (direction == 'R') {
    for (int b = 0; b < 16; b++)
      if (ball[b] == 1) x += 1;

    if (bounce == 0)
      ballRightDown();
    else
      ballRightUp();
  }
}


void paddle1Up() {
  if (paddle1[0] != 1) {
    int temp = paddle1[0], i;
    for (i = 0; i < 16; i++)
      paddle1[i] = paddle1[i + 1];
    paddle1[i] = temp;
  }
}


void paddle1Down() {
  if (paddle1[15] != 1) {
    int temp = paddle1[15], i;
    for (i = 15; i > 0; i--)
      paddle1[i] = paddle1[i - 1];
    paddle1[i] = temp;
  }
}


void paddle2Up() {
  if (paddle2[0] != 16) {
    int temp = paddle2[0], i;
    for (i = 0; i < 16; i++)
      paddle2[i] = paddle2[i + 1];
    paddle2[i] = temp;
  }
}


void paddle2Down() {
  if (paddle2[15] != 16) {
    int temp = paddle2[15], i;
    for (i = 15; i > 0; i--)
      paddle2[i] = paddle2[i - 1];
    paddle2[i] = temp;
  }
}


void ballLeftDown() {

  if (ball[15] == 0) {
    int temp = ball[15], i;
    for (i = 15; i > 0; i--)
      ball[i] = ball[i - 1];
    ball[i] = temp;
    ballLeft();
  }
  else {
    bounce = 1;
    piezoSound(10);
  }
}

void ballLeftUp() {

  if (ball[0] == 0) {
    int temp = ball[0], i;
    for (i = 0; i < 15; i++)
      ball[i] = ball[i + 1];
    ball[i] = temp;
    ballLeft();
  }
  else {
    bounce = 0;
    piezoSound(10);
  }
}


void ballRightDown() {

  if (ball[15] == 0) {
    int temp = ball[15], i;
    for (i = 15; i > 0; i--)
      ball[i] = ball[i - 1];
    ball[i] = temp;
    ballRight();
  }
  else {
    bounce = 1;
    piezoSound(10);
  }
}


void ballRightUp() {

  if (ball[0] == 0) {
    int temp = ball[0], i;
    for (i = 0; i < 15; i++)
      ball[i] = ball[i + 1];
    ball[i] = temp;
    ballRight();
  }
  else {
    bounce = 0;
    piezoSound(10);
  }
}


void ballRight() {
  for (int b = 0; b < 16; b++) {
    if (ball[b] != 0) {
      if (ball[b] == 16)ball[b] = 8;
      else if (ball[b] == 8) ball[b] = 4;
      else if (ball[b] == 4) ball[b] = 2;
      else if (ball[b] == 2) ball[b] = 1;
      else if (ball[b] == 1) ball[b] = 16;
    }
  }
}


void ballLeft() {
  for (int b = 0; b < 16; b++) {
    if (ball[b] != 0) {
      if (ball[b] == 1)ball[b] = 2;
      else if (ball[b] == 2) ball[b] = 4;
      else if (ball[b] == 4) ball[b] = 8;
      else if (ball[b] == 8)ball[b] = 16;
      else if (ball[b] == 16)ball[b] = 1;
    }
  }
}


void piezoSound(int d) {
  analogWrite(piezo, 20);
  delay(d);
  analogWrite(piezo, 0);
}
