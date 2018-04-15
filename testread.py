import RPi.GPIO as GPIO
import time
pin = 5
GPIO.setmode(GPIO.BCM)
GPIO.setup(5, GPIO.IN, pull_up_down=GPIO.PUD_DOWN)

while (1):
  print(GPIO.input(5))
  time.sleep(0.1)
