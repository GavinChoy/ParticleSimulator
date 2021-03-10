/**
* Particle Simulator
* Copyright (C) 2021  Gavin Choy
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#include<cmath>
using namespace std;

class Particle{

    private:

        // Mass of particle
        double m = 1;

        // Coordinates of particle
        double x = 0;

        // Velocity of particle
        double vx = 0;

        double radius = 0;

        bool is_wall = false;

    public:

        Particle(double new_m, double new_x, double new_vx, double new_radius, bool new_is_wall){
            /**
            * Construct a Particle object.
            * @param new_m The mass of the particle.
            * @param new_x The initial x-coordinate of the particle.
            * @param new_vx The initial velocity in the x-direction of the particle.
            */

            m = new_m;
            x = new_x;
            vx = new_vx;
            radius = new_radius;
            is_wall = new_is_wall;
        }

        double get_m(){
            /**
            * @return Double The mass of this particle.
            */

            return m;
        }

        double get_x(){
            /**
            * @return Double The x-coordinate of this particle.
            */

            return x;
        }

        double get_vx(){
            /**
            * @return Double The velocity in the x-direction of this particle.
            */

            return vx;
        }

        double get_radius(){
            /**
            * @return
            */

            return radius;
        }

        bool get_is_wall(){
            /**
            * @return
            */

            return is_wall;
        }

        void advance(double dt){
            /**
            * Updates the position of this particle due to the resultant force acting.
            * @param dt The size of the time step.
            */

            // new_x = x + vt
            x += vx * dt;
        }

        void add_vx(double additional_vx){
            vx += additional_vx;
        }

        double time_to_collision(Particle &other){

            double relative_velocity = vx - other.get_vx();

            if (relative_velocity > 0){
                double travel_time = ((other.get_x() - other.get_radius()) - (x + radius)) / relative_velocity;
                return travel_time;
            } else {
                throw "Particles will not collide.";
            }
        }

        void collide(Particle &other){
            double relative_velocity = vx - other.get_vx();
            if (is_wall){
                other.add_vx(2 * relative_velocity);
            } else if (other.get_is_wall()){
                vx -= 2 * relative_velocity;
            } else {
                vx -= 2 * relative_velocity * (1 / m) / ((1 / m) + (1 / other.get_m()));
                other.add_vx(2 * relative_velocity * (1 / other.get_m()) / ((1 / m) + (1 / other.get_m())));
            }
        }
};
