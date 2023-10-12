#include <AccelStepper.h>

AccelStepper stepperX(AccelStepper::DRIVER, 2, 5);  // X-axis stepper motor
AccelStepper stepperY(AccelStepper::DRIVER, 3, 6);  // Y-axis stepper motor

int stepsPerRevolution = 200;      // 스테퍼 모터 당 스텝 수 (모터에 따라 조절)
int delayBetweenMovements = 2000;  // 이동 간 딜레이 시간 (ms)

const int EN = 8;  //모터 드라이버 관련 핀번호. 안 건드려도 됨

// 초기 위치 (영점) 설정
int initialXPosition = 0;
int initialYPosition = 0;

// 엔드 스톱 스위치 관련 핀 설정
const int endStopXPin = 9;   // X 축 엔드 스톱 스위치 핀 번호
const int endStopYPin = 10;  // Y 축 엔드 스톱 스위치 핀 번호

// here is setup. by seungbum kim
void setup() {
  pinMode(EN, OUTPUT);
  digitalWrite(EN, LOW);  //LOW 상태로 유지해야함

  pinMode(endStopXPin, INPUT_PULLUP);  // X 축 엔드 스톱 스위치를 풀업 입력 모드로 설정
  pinMode(endStopYPin, INPUT_PULLUP);  // Y 축 엔드 스톱 스위치를 풀업 입력 모드로 설정

  stepperX.setMaxSpeed(1000);     // X축 스테퍼 모터 최대 속도 설정
  stepperX.setAcceleration(500);  // X축 스테퍼 모터 가속도 설정

  stepperY.setMaxSpeed(1000);     // Y축 스테퍼 모터 최대 속도 설정
  stepperY.setAcceleration(500);  // Y축 스테퍼 모터 가속도 설정

  // 초기 위치로 이동 (영점 설정)
  moveToInitialPosition();
  delay(2000);
}

void loop() {
  // X와 Y 축을 각각 다른 거리만큼 이동
  moveXDistance(-100, 0);   // X 축은 100 mm만큼 이동
  moveYDistance(100, 0);  // Y 축은 -100 mm만큼 이동
  delay(delayBetweenMovements);

  // X와 Y 축을 각각 다른 거리만큼 이동
  moveXDistance(100, 0);  // X 축은 -100 mm만큼 이동
  moveYDistance(100, 0);   // Y 축은 100 mm만큼 이동
  delay(delayBetweenMovements);

  moveXYDistance(50, 50, 0);
  moveXYDistance(-50, -50, 0);
  delay(delayBetweenMovements);
}

void moveToInitialPosition() {
  // 엔드 스톱 스위치까지 이동
  while (!digitalRead(endStopXPin)) {
    stepperX.move(-1 / 0.04);
    stepperY.move(-1 / 0.04);
    stepperX.run();
    stepperY.run();
  }
  while (!digitalRead(endStopYPin)) {
    stepperX.move(-1 / 0.04);
    stepperY.move(1 / 0.04);
    stepperX.run();
    stepperY.run();
  }

  // 초기 위치로 설정
  stepperX.setCurrentPosition(0);
  stepperY.setCurrentPosition(0);
}

void moveXDistance(int distance, int stepDelay) {
  stepperX.move(distance / 0.04);  // X 모터 회전
  stepperY.move(distance / 0.04);  // Y 모터 회전

  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    stepperX.run();
    stepperY.run();
    delayMicroseconds(stepDelay);
  }
}

void moveYDistance(int distance, int stepDelay) {
  stepperX.move(distance / 0.04);         // X 모터 회전
  stepperY.move((distance * -1) / 0.04);  // Y 모터 회전

  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    stepperX.run();
    stepperY.run();
    delayMicroseconds(stepDelay);
  }
}

void moveXYDistance(int distanceX, int distanceY, int stepDelay) {
  stepperX.move(distanceX / 0.04);  // X 모터 회전
  stepperY.move(distanceY / 0.04);  // Y 모터 회전

  while (stepperX.distanceToGo() != 0 || stepperY.distanceToGo() != 0) {
    stepperX.run();
    stepperY.run();
    delayMicroseconds(stepDelay);
  }
}
