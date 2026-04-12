#include <util/atomic.h>

//-----------------------------------------------------------------//
// CONSTANTS
//-----------------------------------------------------------------//
#define PWM_MAX 255
#define V_MAX 12.0
#define V2PWM (PWM_MAX / V_MAX)
#define MOTOR_V_MAX 9.0
#define DT 5. //ms 
#define BELT_PITCH 2.032
#define NTEETH 90.0
#define RADS2MMS (BELT_PITCH * NTEETH / 6.28)
#define RED (1.0/45.0)
#define PULSE_PER_ROUND 8.0
#define LENGTH 230.
#define WIDTH 180.

#define KX 5  //---- à compléter ------
#define KY 5  //---- à compléter ------
#define KMOTOR 51.

//-----------------------------------------------------------------//
// STRUCTS
//-----------------------------------------------------------------//
struct Point {
  float x;
  float y;
};

struct Motor {
  // Hardware config (const)
  const int VA, VB, I1, I2, PWM;
  // Runtime state
  volatile int deltaT;
  float v;
  float v_desired;
  float u;
};

struct Robot {
  // State
  float x, y, theta;
  // Desired velocities
  float v_desired;
  float omega_desired;
  // Motors
  Motor right;
  Motor left;
};

//-----------------------------------------------------------------//
// GLOBAL VARIABLES
//-----------------------------------------------------------------//
struct Point target = {.x=0., .y=0.};

struct Robot robot = {
  .x=0., .y=0., .theta=0.,
  .v_desired=0., .omega_desired=0.,
  .right = {.VA=18, .VB=31, .I1=34, .I2=35, .PWM=12},
  .left  = {.VA=19, .VB=38, .I1=37, .I2=36, .PWM=8 },
};

//-----------------------------------------------------------------//
// MOTOR FUNCTIONS
//-----------------------------------------------------------------//
void motor_config(const Motor& m) {
  pinMode(m.VA, INPUT_PULLUP);
  pinMode(m.VB, INPUT_PULLUP);
  pinMode(m.I1, OUTPUT);
  pinMode(m.I2, OUTPUT);
  pinMode(m.PWM, OUTPUT);
}

void motor_setVoltage(float voltage, const Motor& m) {
  if (abs(voltage) < 1.) voltage = 0.;
  if (voltage > 0) {
    digitalWrite(m.I2, LOW);
    digitalWrite(m.I1, HIGH);
  } else {
    digitalWrite(m.I1, LOW);
    digitalWrite(m.I2, HIGH);
  }
  analogWrite(m.PWM, constrain(abs(voltage) * V2PWM, 0, MOTOR_V_MAX * V2PWM));
}

float motor_getSpeed(const Motor& m) {
  int deltaT_temp;
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
    deltaT_temp = m.deltaT;
  }
  Serial.print("--------");
  Serial.println(deltaT_temp);
  if (deltaT_temp <= 0) return 0.;
  
  float freq       = 1000000.0 / deltaT_temp;   // Hz (pulses/s)
  float rad_per_s  = freq * 2 * PI / PULSE_PER_ROUND * RED;  // rad/s en sortie réducteur
  return rad_per_s * RADS2MMS;                  // mm/s
}

//-----------------------------------------------------------------//
// INTERRUPTS
//-----------------------------------------------------------------//
void onRisingEdge_right() {
  static long timePrec = 0;
  long timeCurr = micros();
  robot.right.deltaT = timeCurr - timePrec;
  timePrec = timeCurr;
}

void onRisingEdge_left() {
  static long timePrec = 0;
  long timeCurr = micros();
  robot.left.deltaT = timeCurr - timePrec;
  timePrec = timeCurr;
}

//-----------------------------------------------------------------//
// CONTROL FUNCTIONS
//-----------------------------------------------------------------//
void update_desired_robot_velocities(Robot& robot, const Point& ref) {
  double xt_point = KX * (ref.x - robot.x);
  double yt_point = KY * (ref.y - robot.y);
  robot.v_desired = cos(robot.theta) * xt_point + sin(robot.theta) * yt_point;
  robot.omega_desired = - sin(robot.theta)/LENGTH * xt_point + cos(robot.theta)/LENGTH * yt_point;
}

void update_desired_motors_velocity(Robot& robot) {
	robot.right.v_desired = robot.v_desired + LENGTH * robot.omega_desired;
  robot.left.v_desired = robot.v_desired - LENGTH * robot.omega_desired;
}

void update_motors_command(Robot& robot) {
  double u_r = robot.right.v_desired / KMOTOR;
  double u_l = robot.left.v_desired / KMOTOR;
  robot.right.u = (u_r > 1.3 || u_r < -1.3) ? u_r : 0; 
  robot.left.u = (u_l > 1.3 || u_l < -1.3) ? u_l : 0;
}

//-----------------------------------------------------------------//
// ODOMETRY
//-----------------------------------------------------------------//
void update_robot_state(Robot& robot) {

  double vr_mes = robot.right.v;
  double vl_mes = robot.left.v;
  double v_est = 1/2 * (vr_mes + vl_mes);
  double omega_est = 1/2 / WIDTH * (vr_mes - vl_mes);
  double x_point = v_est * cos(robot.theta);
  double y_point = v_est * sin(robot.theta);
  
  robot.x = x_point * 0.001 * DT + robot.x;
  robot.y = y_point * 0.001 * DT + robot.y;
  robot.theta = omega_est * 0.001 * DT + robot.theta;
}

//-----------------------------------------------------------------//
// ARDUINO
//-----------------------------------------------------------------//
void setup() {
  motor_config(robot.right);
  motor_config(robot.left);
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(robot.right.VA), onRisingEdge_right, RISING);
  attachInterrupt(digitalPinToInterrupt(robot.left.VA),  onRisingEdge_left,  RISING);
  Serial.println("target_x,robot_x,target_y,robot_y,v_right,v_left");
}

void loop() {
  static long iteration = 0;
  iteration++;
  static long timePrec = 0;
  while (millis() - timePrec < DT) {}
  timePrec = millis();

  if (iteration == 500)       { target.x = 150.; target.y = 150.;   }
  
  update_desired_robot_velocities(robot, target);
  Serial.println(robot.right.u);
  Serial.print("v_mes :");
  Serial.println(robot.right.v);
  update_desired_motors_velocity(robot);
  update_motors_command(robot);

  motor_setVoltage(-robot.right.u, robot.right);
  motor_setVoltage( robot.left.u,  robot.left);
  
  robot.right.v = (robot.right.u == 0.) ? 0. : motor_getSpeed(robot.right);
  robot.left.v  = (robot.left.u  == 0.) ? 0. : motor_getSpeed(robot.left);
  update_robot_state(robot);

  // DEBUG
  Serial.print(robot.left.u);      Serial.print(",");
  Serial.print(robot.x);       Serial.print(",");
  Serial.print(target.y);      Serial.print(",");
  Serial.print(robot.y);       Serial.print(",");
  Serial.print(robot.right.v); Serial.print(",");
  Serial.println(robot.left.v);
}
