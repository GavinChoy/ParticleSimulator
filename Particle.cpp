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

        // Radius of particle
        double radius = 0;

        // Whether this particle is an immovable wall
        bool is_wall = false;

    public:

        Particle(double new_m, double new_x, double new_vx, double new_radius, bool new_is_wall){
            /**
            * Construct a Particle object.
            * @param new_m Double of the mass of the particle.
            * @param new_x Double of the initial x-coordinate of the particle.
            * @param new_vx Double of the initial velocity in the x-direction of the particle.
            * @param new_radius Double of the initial x-coordinate of the particle.
            * @param new_is_wall Boolean whether this particle is an immovable wall.
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
            * @return Double The radius of this particle.
            */

            return radius;
        }

        bool get_is_wall(){
            /**
            * @return Boolean Whether this particle is an immovable wall.
            */

            return is_wall;
        }

        void advance(double dt){
            /**
            * Updates the position of this particle with its current velocity.
            * @param dt The size of the time step.
            */

            // new_x = x + vt
            x += vx * dt;
        }

        void set_vx(double new_vx){
            /**
            * Updates the velocity of this particle.
            * @param new_vx Double of the new velocity.
            */

            vx = new_vx;
        }

        double time_to_collision(Particle &other){
            /**
            * Calculates the time until a collision with another particle.
            * Throws an exception if there will never be a collision.
            * @param other Particle which is the other particle.
            * @return Double The time until a collision with the other particle.
            */

            // The relative velocity (closing speed) between the two particles.
            double relative_velocity = vx - other.get_vx();

            // If the particles are closing, calculate the time required
            // Otherwise, the particles will never collide so throw an exception
            if (relative_velocity > 0){
                // Time required = distance between the particle surfaces divided by the closing speed
                return ((other.get_x() - other.get_radius()) - (x + radius)) / relative_velocity;
            } else {
                throw "Particles will not collide.";
            }
        }

        void collide(Particle &other, double e){
            /**
            * Calculates and updates the velocities of the colliding particles.
            * @param other Particle which is the other particle.
            * @param e Double of the coefficient of restitution.
            */

            // If this particle is an unmovable wall
            // Else if the other particle is an unmovable wall
            // Otherwise, the two particles are movable
            if (is_wall){
                other.set_vx(e * (-other.get_vx()));
            } else if (other.get_is_wall()){
                vx *= -e;
            } else {
                // Initial velocities
                double ux = vx;
                double other_ux = other.get_vx();

                vx = ((m * ux) + (other.get_m() * (other_ux + (e * (other_ux - ux))))) / (m + other.get_m());
                other.set_vx(vx + (e * (ux - other_ux)));
            }
        }
};
