int XY_SPEED = 200;
int Z_SPEED = 100;

int X_DIR = A1;        // X        
int X_STEP = A0;       //  
int Y_DIR = A7;        // Y
int Y_STEP = A6;       // 
int Z1_DIR = 28;      // E0
int Z1_STEP = 26;     //
int Z2_DIR = 34;      // E1
int Z2_STEP = 36;     //

unsigned long x_last_time;
unsigned long y_last_time;
unsigned long z_last_time;
unsigned long time;

int x_state;
int y_state;
int z_state;
int x_direction;
int y_direction;
int z_direction;

int stepsPerRevolution;
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
  x_last_time = micros();
  y_last_time = micros();
  z_last_time = micros();
  x_state = LOW;
  y_state = LOW;
  z_state = LOW;
  z_height = 25600;
  stepsPerRevolution = 19200;
  x_speed = 0;
  y_speed = 0;
}

void turnAll(int angle) {
  double rad = (PI * angle) / 180;
  x_speed = sin(rad) * XY_SPEED;
  y_speed = -cos(rad) * XY_SPEED;
  
  turnMotor(X);
  turnMotor(Y);
  turnMotor(X);
  
}

void turnMotor(int axis) {
   time = micros();
   switch (axis) {
     case X:
       x_direction = HIGH;
       if (x_speed < 0) {
         x_direction = LOW;
       }
       if (x_last_time > time + x_speed) {
         x_state = HIGH - x_state;
         x_last_time = micros();
         stepsInThisRevolution++;
       }
       digitalWrite(X_STEP, x_state);     
       digitalWrite(X_DIR, x_direction); 
       break;
     case Y:
       y_direction = HIGH;
       if (y_speed < 0) {
         y_direction = LOW;
       }
       if (y_last_time > time + y_speed) {
         y_state = HIGH - y_state;
         y_last_time = micros();
       }
       digitalWrite(X_STEP, y_state);     
       digitalWrite(X_DIR, y_direction); 
       break;
     case Z:
       if (z_pos >= z_height && z_pos <= 0) {
         z_direction = HIGH - z_direction; 
       }
       if (z_last_time > time + Z_SPEED) {
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
  while (stepsInThisRevolution < stepsPerRevolution) {
    double angle = 360 * (stepsInThisRevolution / stepsPerRevolution);
    turnAll(angle);
  }
  stepsInThisRevolution = 0;
}
