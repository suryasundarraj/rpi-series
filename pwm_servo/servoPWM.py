# Following code is tested with Raspberry Pi 3
# Import the Libraries Required
import RPi.GPIO as GPIO
import time

SERVO_PIN = 32

if __name__ == '__main__':
	# Setting the GPIO Mode to BOARD => Pin Count Mapping 
	GPIO.setmode(GPIO.BOARD)

	# Setting the GPIO Mode to BCM => GPIO Mapping 
	# Uncomment below line for to use GPIO number
	# GPIO.setmode(GPIO.BCM)

	# Setting the GPIO 18 as PWM Output 
	GPIO.setup(SERVO_PIN,GPIO.OUT)

	# Disable the warning from the GPIO Library
	GPIO.setwarnings(False)

	# Starting the PWM and setting the initial position of the servo 
	servo = GPIO.PWM(SERVO_PIN,50)
	servo.start(7.5)
	while True:
		try:
			# Changing the Duty Cycle to rotate the motor 
			servo.ChangeDutyCycle(7.5)
			# Sleep for 1 Second 
			time.sleep(1)
			servo.ChangeDutyCycle(12.5)
			time.sleep(1)
			servo.ChangeDutyCycle(2.5)
			time.sleep(1)

		except KeyboardInterrupt:
			servo.stop()
			GPIO.cleanup()
# End of the Script
