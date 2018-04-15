#!/usr/bin/env python

from time import sleep, time           # Allows us to call the sleep function to slow down our loop
import RPi.GPIO as GPIO           # Allows us to call our GPIO pins and names it just GPIO
GPIO.setmode(GPIO.BCM)           # Set's GPIO pins to BCM GPIO numbering

SW_PIN = 4
TX_PIN = 17
RX_PIN = 27

# rx 2 - 17
# tx 3 - 4
# sw 5 - 27

GPIO.setup(SW_PIN, GPIO.OUT)
GPIO.output(SW_PIN, 0)

GPIO.setup(TX_PIN, GPIO.OUT)
GPIO.setup(RX_PIN, GPIO.IN)
reading = False
# Start a loop that never ends
while True:
  if (GPIO.input(RX_PIN) == True): # Physically read the pin now
    active = True
    st = time()
    while active:
      print(str(bool(GPIO.input(RX_PIN))))
