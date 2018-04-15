#include <wiringPi.h>
#include <stdio.h>
#include <signal.h>

#define txPin 7
#define swPin 0

const int big_delay   = 640;
const int small_delay = 320;
const int delay_between = 20;

// Returns Nth bit of decimal
short getbit(short code, int n) {
  return (code >> n) & 1;
}

void sendcode(short code, int times, int delay_between) {
  digitalWrite(txPin, LOW);
  digitalWrite(swPin, LOW);
  delay(20);
  // sending code several times
  for (int p = 0; p < times; p++) {
    for (int i = 24; i >= 0; i--) {
      if (getbit(code, i) == 1) {
        // one - big high and small low
//        printf("1");
        digitalWrite(txPin, HIGH);
        delayMicroseconds(big_delay);
        digitalWrite(txPin, LOW);
        delayMicroseconds(small_delay);
      } else {
        // one - small high and big low
//        printf("0");
        digitalWrite(txPin, HIGH);
        delayMicroseconds(small_delay);
        digitalWrite(txPin, LOW);
        delayMicroseconds(big_delay);
      }
    }
    delay(delay_between);
  }
}

void bruteforce(short from, short to, int times, int delay_between) {
  for (short code = from; code <= to; code++) {
    printf("trying %d\n", code);
    sendcode(code, times, delay_between);
    delay(delay_between);
  }
}

int main(int argc, char *argv[]) {
// preparing pins
  wiringPiSetup();
  pinMode(7, OUTPUT);
  pinMode(0, OUTPUT);

  // sending code
  //short code = 19104;
  //sendcode(code, 6);
  bruteforce(0, 19104, 1, 20);
  return 0;
}
