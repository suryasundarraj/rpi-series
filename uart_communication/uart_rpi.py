#Sending the data thorugh UART 
#UART PINOUT
#Rx -> GPIO15
#Tx -> GPIO14

# get the GPIO Library
import RPi.GPIO as GPIO
import serial
import time

#Open named port 
ser = serial.Serial ("/dev/ttyAMA0")    

# the input buttons
up = 7
down = 8

#Setting up the GPIO Pins
GPIO.setwarnings(False)
GPIO.setmode(GPIO.BCM)
GPIO.cleanup()

#Setting up the Button Inputs
GPIO.setup(up, GPIO.IN)
GPIO.setup(down, GPIO.IN)

#Set baud rate to 9600
ser.baudrate = 9600                     

g_button_1_pressed = 0
g_button_1_flag = 0
g_button_1_released = 0
g_button_2_pressed = 0
g_button_2_released = 0
g_button_2_flag = 0
led_1_flag = 0
led_2_flag = 0

while True:
    #Handling the Button Debounce 
    if GPIO.input(up):
        if g_button_1_pressed < 600:
            g_button_1_pressed += 1
            if g_button_1_pressed >= 500 and g_button_1_flag == 1:
                g_button_1_flag = 0
                g_button_1_released = 0
                #Controlling the LED 1
                if(led_1_flag == 0):
                	ser.write("11")
                	led_1_flag = 1
                else:
                	ser.write("10")
                	led_1_flag = 0
    else:
        if g_button_1_released < 600:
            g_button_1_released += 1
            if g_button_1_released >= 500 and g_button_1_flag == 0:
                g_button_1_pressed = 0
                g_button_1_flag = 1

    if GPIO.input(down):
        if g_button_2_pressed < 600:
            g_button_2_pressed += 1
            if g_button_2_pressed >= 500 and g_button_2_flag == 1:
                g_button_2_flag = 0
                g_button_2_released = 0
                #Controlling LED 2
                if(led_2_flag == 0):
                	ser.write("21")
                	led_2_flag = 1
                else:
                	ser.write("20")
                	led_2_flag = 0
    else:
        if g_button_2_released < 600:
            g_button_2_released += 1
            if g_button_2_released >= 500 and g_button_2_flag == 0:
                g_button_2_pressed = 0
                g_button_2_flag = 1
#Close the Serial Connection
ser.close()        

#End of the Script