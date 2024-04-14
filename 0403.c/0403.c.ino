int IR_pin[5] = {32, 34, 36, 38, 40};
// left 32, right 40
int IR_val[5] = {0, 0, 0, 0, 0};
// 1 -> on black
int weight[5] = {-2, -1, 0, 1, 2};
// left < --- > right

const int L_SPEED = 150;
const int R_SPEED = 150;  
int turn_idx = 0;
bool in_block = false;


enum Movement {
  L, R, U, F
};

Movement movement_list[1000] = {L, L, L, L, L, L};

double dot(int arr1[5], int arr2[5]) {
  double ret = 0;
  for(int i = 0 ; i < 5 ; i++) ret += arr1[i] * arr2[i];
  return ret;
}

int PWMA = 11;
int AIN2 = 3;
int AIN1 = 2;
int BIN1 = 5;
int BIN2 = 6;
int PWMB = 12;



void set_speed(int left, int right) {

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

void tracking(double score) {
  if(score == 0) {
    set_speed(L_SPEED, R_SPEED);
  } else if(score < 0) {
    set_speed(L_SPEED*(1+score/1.2), R_SPEED);
  } else {
    set_speed(L_SPEED, R_SPEED*(1-score/1.2));
  }
  return;
} 

void turn(Movement movement) {
  if(movement == L) {
    set_speed(-L_SPEED, R_SPEED);
    delay(300);
  } else if(movement == R) {
    set_speed(L_SPEED, -R_SPEED); 
    delay(300); 
  }
  
  while(digitalRead(IR_pin[0]) == 0 && digitalRead(IR_pin[1]) == 0 && digitalRead(IR_pin[2]) == 0 && digitalRead(IR_pin[3]) == 0 &&  digitalRead(IR_pin[4]) == 0) {
    if(movement == L) {
      set_speed(-L_SPEED, R_SPEED);
    } else if(movement == R) {
      set_speed(L_SPEED, -R_SPEED);  
    } else if(movement == F) {
      return;
    } else if(movement == U) {
      turn(L);
      turn(L);
    } else {
      set_speed(0, 0);
    }
  }
}

void back() {
  
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

  Serial.begin(74880);
  
  digitalWrite(PWMA, HIGH);
  digitalWrite(PWMB, HIGH);

}

void loop() {
  // put your main code here, to run repeatedly:
  
  int sum = 0;
  double score = 0;
  for(int i = 0 ; i < 5 ; i++) {
    IR_val[i] = digitalRead(IR_pin[i]);
    sum += IR_val[i];
  }


  if(in_block) {

    if(sum != 5) {
      // turn(movement_list[turn_idx++]);
      delay(200);
      turn(B); 
      // set_speed(0, 0);
      in_block = false;
    }

  } else if(sum == 5) {
    in_block = true;
    set_speed(L_SPEED, R_SPEED);
  } else {
    if(sum == 0)  score = 0;
    else  score = dot(IR_val, weight)/sum;
    Serial.println(score);
    tracking(score);
  }
  
 
}