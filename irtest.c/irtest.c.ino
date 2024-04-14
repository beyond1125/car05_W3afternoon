int IR_pin[5] = {32, 34, 36, 38, 40};
// left 32, right 40
int IR_val[5] = {0, 0, 0, 0, 0};
// 1 -> on black

int PWMA = 11;
int AIN2 = 3;
int AIN1 = 2;
int BIN1 = 5;
int BIN2 = 6;
int PWMB = 12;

enum Movement{
  FORWARD, LEFT_SMALL, LEFT_BIG, RIGHT_SMALL, RIGHT_BIG
};



void set_speed(int right, int left) {
  if(right >= 0) {
    analogWrite(AIN1, 0);
    analogWrite(AIN2, right);
  } else {
    analogWrite(AIN1, -right);
    analogWrite(AIN2, 0);    
  }

  if(left >= 0) {
    analogWrite(BIN1, 0);
    analogWrite(BIN2, left);
  } else {
    analogWrite(BIN1, -left);
    analogWrite(BIN2, 0);
  }
}

void move(Movement m) {
  if(m == FORWARD) {
    set_speed(100, 100);
  } else if(m == LEFT_SMALL) {
    set_speed(100, 50);
  } else if(m == LEFT_BIG) {
    set_speed(100, 0);
  } else if(m == RIGHT_SMALL) {
    set_speed(50, 100);
  } else{
    set_speed(0, 100);
  }
}


void setup() {
  // put your setup code here, to run once:
  pinMode(32, INPUT);
  pinMode(34, INPUT);
  pinMode(36, INPUT);
  pinMode(38, INPUT);
  pinMode(40, INPUT);

  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);
  
  digitalWrite(PWMA, HIGH);
  digitalWrite(PWMB, HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i = 0 ; i < 5 ; i++) {
    IR_val[i] = digitalRead(IR_pin[i]);
    Serial.print(IR_val[i], " ");  
  }
  Serial.println();

  if(IR_val[2] == 1) {
    move(FORWARD);

  } else {

    if(IR_val[1] == 1)          move(LEFT_SMALL);
    else if(IR_val[3] == 1)     move(RIGHT_SMALL);

    else {

      if(IR_val[0] == 1)        move(LEFT_BIG);
      else if(IR_val[4] == 1)   move(RIGHT_BIG);

      else                      move(FORWARD);
    }
  }


  delay(100);
}
