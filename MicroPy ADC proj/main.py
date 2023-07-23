from machine import ADC
from machine import Pin
from machine import PWM
import sys
import rp_adc_server as adcDev


#Poner el pin 16 en 1
led = Pin(16, Pin.OUT)
led.value(1)

#configurar la señal pwm en el pin 17
pwm = PWM(Pin(17))          # create a PWM object on a pin
pwm.freq(100000)
pwm.duty_u16(int(65535 * 0.5))

#Capturar el valor en el ADC
#bytearray
'''sensor = ADC(26)
while True:
    a = sensor.read_u16()    
    sys.stdout.buffer.write(a.to_bytes(2,'big')) #  little '''  

adcDev.adc_dma_init()
while True:       
    sys.stdout.buffer.write(adcDev.adc_capture())     