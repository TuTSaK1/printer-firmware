int X_SPEED = 0;
int Y_SPEED = 0;
int Z_SPEED = 100;

double rad = 0;

int X_DIR = A1;        // X        
int X_STEP = A0;       //  
int Y_DIR = A7;        // Y
int Y_STEP = A6;       // 
int Z1_DIR = 28;      // E0
int Z1_STEP = 26;     //
int Z2_DIR = 34;      // E1
int Z2_STEP = 36;     //
int X_EN = 38;
int Y_EN = A2;
int Z1_EN = 24;
int Z2_EN = 30; 

unsigned long x_last_time;
unsigned long y_last_time;
unsigned long z_last_time;
unsigned long time_current;

int x_state;
int y_state;
int z_state;
int x_direction;
int y_direction;
int z_direction;

int stepsPerRevolution = 30000;
int stepsInThisRevolution;

int z_height;
int z_pos;

double x_speed, y_speed;

enum axis {
  X,
  Y,
  Z
};

void setup() {
  Serial.begin(9600);
  pinMode(X_DIR, OUTPUT);
  digitalWrite(X_DIR, LOW);
  pinMode(X_STEP, OUTPUT);
  digitalWrite(X_STEP, LOW);
  pinMode(Y_DIR, OUTPUT);
  digitalWrite(Y_DIR, LOW);
  pinMode(Y_STEP, OUTPUT);
  digitalWrite(Y_STEP, LOW);
  pinMode(Z1_DIR, OUTPUT);
  digitalWrite(Z1_DIR, LOW);
  pinMode(Z1_STEP, OUTPUT);
  digitalWrite(Z1_STEP, LOW);
  pinMode(Z2_DIR, OUTPUT);
  digitalWrite(Z2_DIR, LOW);
  pinMode(Z2_STEP, OUTPUT);
  digitalWrite(Z2_STEP, LOW);
  pinMode(X_EN, OUTPUT);
  digitalWrite(X_EN, LOW);
  pinMode(Y_EN, OUTPUT);
  digitalWrite(Y_EN, LOW);
  pinMode(Z1_EN, OUTPUT);
  digitalWrite(Z1_EN, LOW);
  pinMode(Z2_EN, OUTPUT);
  digitalWrite(Z2_EN, LOW);
  x_last_time = micros();
  y_last_time = micros();
  z_last_time = micros();
  x_state = LOW;
  y_state = LOW;
  z_state = LOW;
  z_height = 25600;
  x_speed = 0;
  y_speed = 0;
}

void turnAll(int angle) {
  rad = (PI * angle) / 180;
  //x_speed = sin(rad) * X_SPEED;
  //y_speed = -cos(rad) * Y_SPEED;
  
  turnMotor(X);
  turnMotor(Y);
  
}

void turnMotor(int axis) {
   time_current = micros();
   switch (axis) {
     case X:
       if (x_speed < 0) {
         x_direction = LOW;
       }
       else {
         x_direction = HIGH;        
       }
       if (time_current > x_last_time + x_speed) {
         x_state = HIGH - x_state;
         x_last_time = micros();
         stepsInThisRevolution++;
       }
       digitalWrite(X_STEP, x_state);     
       digitalWrite(X_DIR, x_direction); 
       break;
     case Y:
       if (y_speed < 0) {
         y_direction = LOW;
       }
       else {
        y_direction = HIGH;
       }
       if (time_current > y_last_time + y_speed) {
         y_state = HIGH - y_state;
         y_last_time = micros();
       }
       digitalWrite(Y_STEP, y_state);     
       digitalWrite(Y_DIR, y_direction); 
       break;
     case Z:
       if (z_pos >= z_height || z_pos <= 0) {
         z_direction = HIGH - z_direction; 
       }
       if (time_current > z_last_time + Z_SPEED) {
         z_state = HIGH - z_state;
         z_last_time = micros();
         if (z_direction > 0) {
           z_pos++;
         }
         else {
           z_pos--;
         }
       }
       digitalWrite(Z1_STEP, z_state);     
       digitalWrite(Z1_DIR, z_direction);
       digitalWrite(Z2_STEP, z_state);     
       digitalWrite(Z2_DIR, z_direction);
       break;
     default:
       break;
   }
}

void loop() {
<<<<<<< HEAD
  while (stepsInThisRevolution < stepsPerRevolution) {
    double angle = 360 * ((double)stepsInThisRevolution / (double)stepsPerRevolution);
=======
  while (stepsInThisRevolution < stepsPerRevolution) {ls
  cd
    double angle = 360 * (stepsInThisRevolution / stepsPerRevolution);
>>>>>>> b6e34fc4156dd8c0cc5e5c0ed8cb2b8beafa35e3
    turnAll(angle);
  }
  stepsInThisRevolution = 0;
}
