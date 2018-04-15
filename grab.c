#include <wiringPi.h>
#include <stdio.h>
#include <time.h>
#define rxPin 21
#define MAX_DELTA 200

volatile static long lastCode = 0;
volatile unsigned long prevtime;
volatile unsigned int lolen, hilen, state;
volatile static short cameCounter = 0;
volatile static long cameCode = 0;

int CheckValue(unsigned int base, unsigned int value) {
  return ((value == base) || ((value > base) && ((value - base) < MAX_DELTA)) ||
          ((value < base) && ((base - value) < MAX_DELTA)));
}

void grab() {
  state = digitalRead(rxPin);
  if (state == LOW)
    lolen = micros() - prevtime;
  else
    hilen = micros() - prevtime;
  prevtime = micros();

  if (state == HIGH) {
    if (CheckValue(320, hilen) && CheckValue(640, lolen)) { // valid 1
      printf("1");
      cameCode = (cameCode << 1) | 1;
      cameCounter++;
    } else if (CheckValue(640, hilen) && CheckValue(320, lolen)) { // valid 0
      printf("0");
      cameCode = (cameCode << 1) | 0;
      cameCounter++;
    }
  } else if (cameCounter >= 12 && (lolen > 1000 || hilen > 1000)) {
    cameCode = (cameCode << 1) | 0;
    printf("0 = %d; lolen = %d; hilen = %d", cameCounter, lolen, hilen);
    lastCode = cameCode;
    cameCounter = 0;
    cameCode = 0;
  }
}

int main() {
  wiringPiSetup();
  pinMode(rxPin, INPUT);
  wiringPiISR(rxPin, INT_EDGE_BOTH, &grab);
  while (1) {
    if (lastCode > 0) {
      printf(" %ld\n", lastCode);
      lastCode = 0;
    }
  }
  return 0;
}

