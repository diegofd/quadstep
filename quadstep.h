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

#ifndef __QUADSTEP_H__
#define __QUADSTEP_H__

class Quadstep {

  public:
    Quadstep(int stp_pin,
             int dir_pin,
             int enable1_pin,
             int enable2_pin,
             int enable3_pin,
             int enable4_pin);

    void step_motor1(int steps);
    void step_motor2(int steps);
    void step_motor3(int steps);
    void step_motor4(int steps);  
  private:

    int stp_pin;
    int dir_pin;
    int enable1_pin;
    int enable2_pin;
    int enable3_pin;
    int enable4_pin;
    int pulse_width;
    
    void step_motor(int enable_pin,
                    int steps);
    void step();
};


#endif // __QUADSTEP_H__
