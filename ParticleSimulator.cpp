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

#include <iostream>
#include "Particle.cpp"
using namespace std;

// Coefficient of restitution for particle-particle and wall-particle collisions
double const COEFFICIENT_RESTITUTION = 0.95;

// The maximum time in seconds to simulate
int const MAX_TIME = 20;

// A limit to the number of collisions to simulate
// Prevents infinite loops for when the velocitie differences too small so it appears that the next collision is immediately afterwards.
int const MAX_COLLISIONS = 10000;

// The number of particles to simulate
int const MAX_PARTICLES = 2 + 10;

void run_simulation(Particle particles[]);

int main(){

    // Licence info on program start
    cout << "# " << endl;
    cout << "# " << "Particle Simulator  Copyright (C) 2021  Gavin Choy\n";
    cout << "# " << "This program comes with ABSOLUTELY NO WARRANTY.\n";
    cout << "# " << "This is free software, and you are welcome to redistribute it\n";
    cout << "# " << "under certain conditions.\n\n";

    // Define the walls (the boundaries)
    Particle wall1(1, 0, 0, 0, true);
    Particle wall2(1, 10, 0, 0, true);

    // Define particles with initial conditions
    Particle particle1(1, 1, 5, 0.2, false);
    Particle particle2(4, 2, 2, 0.2, false);
    Particle particle3(1, 3, -2, 0.2, false);
    Particle particle4(1, 4, 2, 0.2, false);
    Particle particle5(100, 5, 0, 0.5, false);
    Particle particle6(1, 6, -4, 0.2, false);
    Particle particle7(5, 7, 2, 0.2, false);
    Particle particle8(1, 8, -5, 0.2, false);
    Particle particle9(2, 9, 2, 0.2, false);
    Particle particle10(1, 9.5, -3, 0.2, false);

    // Array of particles
    Particle particles[MAX_PARTICLES] = {wall1, particle1, particle2, particle3, particle4, particle5, particle6, particle7, particle8, particle9, particle10, wall2};

    // Run the simulation and output the positions of each particle into the terminal
    run_simulation(particles);

    return 0;
}

double find_time_to_next_collision(Particle particles[], int &collision_position){
    /**
    * Calculates when the next collision occurs and identifies the particle to collide.
    * @param particles An array of the Particle class.
    * @param collision_position An integer of the position of the particle. This is updated as this function executes.
    * @return Double The time until the next collision.
    */

    // A large time to start off with
    // Continually reduced until the shortest time is found
    double time_to_next_collision = 100000000000000000000;

    // For all particles, calculate it time to its next collision
    for (int i=0; i<MAX_PARTICLES-1; i++){

        // Particle.time_to_collision throws an exception if the pair of particles will never collide
        try{
            // If the time to the next collision between this particle and the particle on the right is shorter
            // then record this time and update the collision_pposition
            double time_to = particles[i].time_to_collision(particles[i+1]);
            if (time_to < time_to_next_collision){
                time_to_next_collision = time_to;
                collision_position = i;
            }
        } catch (const char* msg) {
            // Do nothing
            ;
        }
    }

    return time_to_next_collision;
}

void run_simulation(Particle particles[]){
    /**
    * Calculates and records the positions and kinetic energies of the particles over time.
    * @param particles An array of the Particle class.
    */

    // The universe time
    double time = 0;
    // The number of collisions simulated
    int collisions = 0;

    // The particle that will collide next
    int collision_position;

    // Output the initial positions and kinetic energies of each particle to the terminal
    // Format: "time particle1_xposition particle1_kinetic_energy particle2_xposition particle2_kinetic_energy" et cetera
    cout << "# " << "Format: \"time particle1_xposition particle1_kinetic_energy particle2_xposition particle2_kinetic_energy\" et cetera\n\n";
    cout << time << "\t";
    for (int i = 0; i < MAX_PARTICLES; i++){
        cout << particles[i].get_x() << "\t" << particles[i].get_kinetic_engergy() << "\t";
    }
    cout << endl;

    // Continuously run until the maximum time or number of collisions are reached
    while ((time < MAX_TIME) && (collisions < MAX_COLLISIONS)){

        // Find the time until the next collision occurs and update the collision_position
        double time_to_next_collision = find_time_to_next_collision(particles, collision_position);

        // If the next collision occurs before the maximum time limit, then leap forwards to that time and collide the two particles
        // Otherwise, calculate the particle paths until the time limit
        if ((time + time_to_next_collision) < MAX_TIME){
            // Leap forwards for all particles
            for (int i=0; i < MAX_PARTICLES; i++){
                particles[i].advance(time_to_next_collision);
            }

            // Calculate the new speeds of the two colliding particles
            particles[collision_position].collide(particles[collision_position+1], COEFFICIENT_RESTITUTION);

            // Update the universe time
            time += time_to_next_collision;

        } else {
            // Leap forwards all particles to the end of time
            for (int i=0; i < MAX_PARTICLES; i++){
                particles[i].advance(MAX_TIME - time);
            }

            time = MAX_TIME;
        }

        // Output the positions and kinetic energies to the terminal
        cout << time << "\t";
        for (int j = 0; j < MAX_PARTICLES; j++){
            cout << particles[j].get_x() << "\t" << particles[j].get_kinetic_engergy() << "\t";
        }
        cout << endl;

        // One collision simulated in one cycle of this loop
        collisions++;
    }
};

