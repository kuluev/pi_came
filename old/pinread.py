#!/usr/bin/env python

from time import sleep, time           # Allows us to call the sleep function to slow down our loop
import RPi.GPIO as GPIO           # Allows us to call our GPIO pins and names it just GPIO
GPIO.setmode(GPIO.BCM)           # Set's GPIO pins to BCM GPIO numbering

SW_PIN = 17
TX_PIN = 4
#RX_PIN = 4

# rx (white) 2
# tx (green) 3
# sw (black) 5

GPIO.setup(SW_PIN, GPIO.OUT)
GPIO.output(SW_PIN, 0)

GPIO.setup(TX_PIN, GPIO.OUT)
GPIO.output(TX_PIN, 0)
#GPIO.setup(RX_PIN, GPIO.IN)

reading = False
time_limit = 10
cur = False;
prev = False;
prtime = 0.0;

code = [0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,1,0,1,0,1,0,0,0,0,0]

for p in range(6):
  for x in code:
    if x==0:
      GPIO.output(TX_PIN, 0)
      sleep(0.00064)
      GPIO.output(TX_PIN, 1)
      sleep(0.00032)
    else:
      GPIO.output(TX_PIN, 0)
      sleep(0.00032)
      GPIO.output(TX_PIN, 1)
      sleep(0.00064)
  GPIO.output(TX_PIN, 1)
  sleep(0.02)

#while True:
#  if (GPIO.input(RX_PIN) == True):
#    active = True
#
#    while active:
#      cur = GPIO.input(RX_PIN)
#      print(str.format("{} at {:.5f}", cur, 100*(time())))
