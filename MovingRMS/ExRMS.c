#include <Arduino.h>
#include <MovingRMS.h>
#include <avr/interrupt.h>
#include <math.h>


MovingRMS mrms;
volatile uint16_t windowLength = 200;
volatile float mrms_sq = 0.0f;
volatile float mrms_sqrt = 220.5f;


float t = 0.0;
float sinWave = 0.0f;

ISR (TIMER1_OVF_vect){        //TIMER1_OVF_vect
  t = (t >= 0.02 - 0.0001) ? 0 : t + 0.0001;
  mrms_sq = MovingRMS_Update(&mrms, sinWave);
}


void setup(){
  cli();//stop interrupts
  //  ------------------------------ timer 1 & Interrupt -------------------------------------------------
  TCNT1 = 0;
  TCCR1A = 0; TCCR1B = 0; // Reset 2 registers
  
  TCCR1A |= (1 << WGM11);
  TCCR1B |= (1 << WGM12)|(1 << WGM13); // select Fast PWM mode select TOP_value freely ICR1                     
  ICR1 = 1599;                // Frequency = 16M / (ICR1 + 1)
  TCCR1B |= (1 << CS10);              // No Prescaling = F_Clock or F_clock/1=16mhz
  TIMSK1 |= (1 << TOIE1);         // Timer1 Overflow Interrupt Enable
  sei();

  Serial.begin(115200);
  MovingRMS_Init(&mrms, windowLength);
}

void loop(){
  sinWave = 325 * sin(2 * PI * 50 * t);
  mrms_sqrt = sqrt(mrms_sq);

  Serial.print("sinWave ");
  Serial.print(sinWave);
  Serial.print("\t");
  Serial.print("mrms ");
  Serial.println(mrms_sqrt);
}