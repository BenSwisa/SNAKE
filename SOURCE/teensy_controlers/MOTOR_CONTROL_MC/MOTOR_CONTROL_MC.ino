#define Direction 0  //  0 for pull or 1 for release
#define sinAmp 255.0
#define time_inc  2.0*PI/1000.0
#define MotionUnits_num 12
byte motors_PWM_pin[MotionUnits_num] = {2,3,4,5,6,7,8,9,10,29,30,35};    
byte motors_DIR_pin[MotionUnits_num] = {0,1,11,12,24,25,26,27,28,31,32,33};

int motor_dir, motor_pwm, Motor_num, Dir, Steps, j, i, input1, input2, input3;

void setup() {
  // put your setup code here, to run once:
  for (int i=0; i<MotionUnits_num; i++)
  {
    pinMode(motors_PWM_pin[i], OUTPUT);
    pinMode(motors_DIR_pin[i], OUTPUT);
  }
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
//*************************************************************
//----------------[Manual Control]------------------

Serial.println("Motor number? ");
input1=Serial.available();
while(Serial.available()==input1){
  }
  Motor_num=Serial.parseInt();
  Serial.print(Motor_num);
  Serial.println('\n');
  delay(100);
//---------------- Direction ---------------
  Serial.println("Direction? ");
  Serial.println("0 for pull or 1 for release");
  input2 = Serial.available();
  while(Serial.available()==input2){
  }
    Dir = Serial.parseInt();
    Serial.print(Dir);
    Serial.println('\n');
    delay(100);
//--------------- Steps ------------------
    Serial.println("How many steps? ");
    input3 = Serial.available();
    while(Serial.available()==input3){
      }
      Steps = Serial.parseInt();
      Serial.print(Steps);
      Serial.println('\n');
      delay(100);
      for(j = 0; j < Steps; j++){
        for (float i = 0; i<PI; i+=time_inc){
          motor_pwm = sinAmp * sin(i);
          digitalWrite(motors_DIR_pin[Motor_num-1], Dir);
          analogWrite(motors_PWM_pin[Motor_num-1],  abs(motor_pwm));
    
          Serial.print("Motor: ");
          Serial.print(Dir);
          Serial.print("PWM(");
          Serial.print(motors_PWM_pin[Motor_num-1]);
          Serial.print("): ");
          Serial.print(motor_pwm+1);
          Serial.print(" Dir(");
          Serial.print(motors_DIR_pin[Motor_num-1]);
          Serial.print("): ");
          Serial.println(motor_dir);
          delay(10); // milisec
  }
        }   
}
