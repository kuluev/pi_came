#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define txPin 7
#define swPin 0

const int big_delay   = 640;
const int small_delay = 320;

// Returns Nth bit of decimal
short getbit(short code, int n) {
  return (code >> n) & 1;
}

void sendcode(short code, int times, int delay_between) {
  // sending code several times
  digitalWrite(swPin, HIGH);
  for (int p = 0; p < times; p++) {
    for (int i = 24; i >= 0; i--) {
      if (getbit(code, i) == 1) {
        // one - big high and small low
        digitalWrite(txPin, HIGH);
        delayMicroseconds(big_delay);
        digitalWrite(txPin, LOW);
        delayMicroseconds(small_delay);
      } else {
        // one - small high and big low
        digitalWrite(txPin, HIGH);
        delayMicroseconds(small_delay);
        digitalWrite(txPin, LOW);
        delayMicroseconds(big_delay);
      }
    }
    digitalWrite(swPin, LOW);
    delay(delay_between);
  }
}

void bruteforce(short from, short to, int times, int delay_between) {
  for (short code = from; code <= to; code++) {
    printf("%d\n", code);
    sendcode(code, times, delay_between);
  }
}

int main(int argc, char *argv[]) {
  // preparing pins
  wiringPiSetup();
  pinMode(txPin, OUTPUT);
  pinMode(swPin, OUTPUT);

  short from = 0;
  short to   = 30000;
  int delay_between = 20;
  int times = 4;
  int c;

  opterr = 0;
  while ((c = getopt(argc, argv, "f:t:m:d:")) != -1)
    switch (c) {
    case 'f':
      from = atoi(optarg);
      break;
    case 't':
      to = atoi(optarg);
      break;
    case 'm':
      delay_between = atoi(optarg);
      break;
    case 'd':
      delay_between = atoi(optarg);
      break;
    default:
      abort ();
    }
  digitalWrite(swPin, LOW);
  digitalWrite(txPin, LOW);
  bruteforce(from, to, times, delay_between);
  return 0;
}
