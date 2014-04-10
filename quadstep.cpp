/*
    Quadstepper driver for Arduino
    Copyright (C) 2012 Diego Fernandez Duran <diego@goedi.net>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Inspired on code from
    Aaron Weiss, SparkFun electronics 2011
    John Miller, johnjamesmiller.com 2012
*/


#include "quadstep.h" 

#include <Arduino.h>

Quadstep::Quadstep(int stp_pin,
                   int dir_pin,
                   int enable1_pin,
                   int enable2_pin,
                   int enable3_pin,
                   int enable4_pin)
{
 
  this->stp_pin = stp_pin;
  this->dir_pin = dir_pin;
  this->enable1_pin = enable1_pin;
  this->enable2_pin = enable2_pin;
  this->enable3_pin = enable3_pin;
  this->enable4_pin = enable4_pin;

  // Set pin modes
  pinMode(stp_pin, OUTPUT);
  pinMode(dir_pin, OUTPUT);
  pinMode(enable1_pin, OUTPUT);
  pinMode(enable2_pin, OUTPUT);
  pinMode(enable3_pin, OUTPUT);
  pinMode(enable4_pin, OUTPUT);

  // Set everything low
  digitalWrite(stp_pin, LOW);
  digitalWrite(dir_pin, LOW);
  digitalWrite(enable1_pin, HIGH);
  digitalWrite(enable2_pin, HIGH);
  digitalWrite(enable3_pin, HIGH);
  digitalWrite(enable4_pin, HIGH);

  // pulse_width = STEPMIN + (torque * 260) / step_size;
  pulse_width = 800 + (5 * 260) / 1;
  //pulse_width = 2000;

  Serial.println("Quadstep created");
  Serial.print(" Motor 1: ");Serial.println(enable1_pin);
  Serial.print(" Motor 2: ");Serial.println(enable2_pin);
  Serial.print(" Motor 3: ");Serial.println(enable3_pin);
  Serial.print(" Motor 4: ");Serial.println(enable4_pin);
  Serial.print(" Dir    : ");Serial.println(stp_pin);
  Serial.print(" Step   : ");Serial.println(dir_pin);
}

void Quadstep::step_motor1(int steps)
{
	step_motor(enable1_pin, steps);
}

void Quadstep::step_motor2(int steps)
{
        step_motor(enable2_pin, steps);
}

void Quadstep::step_motor3(int steps)
{
        step_motor(enable3_pin, steps);
}

void Quadstep::step_motor4(int steps)
{
        step_motor(enable4_pin, steps);
}

void Quadstep::step_motor(int enable_pin,
                          int steps)
{

  // select direction
  if (steps > 0) {
    digitalWrite(dir_pin, HIGH);
  } else {
    digitalWrite(dir_pin, LOW);
  }
  steps = abs(steps);
 
  // low on enable pin enables motor
  digitalWrite(enable_pin, LOW);
 
  for(int i=0; i<steps; i++) {
    Serial.print(enable_pin); Serial.print(":"); Serial.println(i);
    step();
  }

  digitalWrite(enable_pin, HIGH);
}

void Quadstep::step()
{
  // low to high transition moves one step
  digitalWrite(stp_pin, HIGH);
  delayMicroseconds(pulse_width);
  digitalWrite(stp_pin, LOW);
  delayMicroseconds(pulse_width);
}

