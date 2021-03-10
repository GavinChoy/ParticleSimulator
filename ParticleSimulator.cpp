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

// The step length for time
double const TIME_INTERVAL = 0.1;

// The maximum number of time steps to simulate
int const MAX_TIME = 20;

// The number of particles to simulate
int const MAX_PARTICLES = 2 + 2;

void run_simulation(Particle particles[]);

int main(){

    // Licence info on program start
    cout << "# " << endl;
    cout << "# " << "Particle Simulator  Copyright (C) 2021  Gavin Choy\n";
    cout << "# " << "This program comes with ABSOLUTELY NO WARRANTY.\n";
    cout << "# " << "This is free software, and you are welcome to redistribute it\n";
    cout << "# " << "under certain conditions.\n\n";

    // Define particles with initial conditions
    Particle wall1(1, 0, 0, 0, true);
    Particle wall2(1, 10, 0, 0, true);

    Particle particle1(1, 1, 5, 0.2, false);
    Particle particle2(1, 4, 2, 0.2, false);

    // Array of particles
    Particle particles[MAX_PARTICLES] = {wall1, particle1, particle2, wall2};

    // Run the simulation and output the positions of each particle into the terminal
    run_simulation(particles);

    return 0;
}

double find_time_to_next_collision(Particle particles[], int &collision_position){

    double time_to_next_collision = 100000000000000000000;

    for (int i=0; i<MAX_PARTICLES-1; i++){
        try{
            double time_to = particles[i].time_to_collision(particles[i+1]);
            if (time_to < time_to_next_collision){
                time_to_next_collision = time_to;
                collision_position = i;
            }
        } catch (const char* msg) {
            ;
        }
    }

    return time_to_next_collision;
}

void run_simulation(Particle particles[]){
    /**
    * Calculates and records the positions of the particles at each point in time.
    * @param particles An array of the Particle class.
    */

    double time = 0;

    int collision_position;

    // Output the initial positions of each particle to the terminal
    // Format: "time particle1_x particle2_x" et cetera
    cout << "# " << "Format: \"time particle1_x particle2_x\" et cetera\n\n";
    cout << time << "\t";
    for (int i = 0; i < MAX_PARTICLES; i++){
        cout << particles[i].get_x() << "\t";
    }
    cout << endl;

    while (time < MAX_TIME){

        double time_to_next_collision = find_time_to_next_collision(particles, collision_position);

        if ((time + time_to_next_collision) < MAX_TIME){
            for (int i=0; i < MAX_PARTICLES; i++){
                particles[i].advance(time_to_next_collision);
            }

            particles[collision_position].collide(particles[collision_position+1]);

            time += time_to_next_collision;

        } else {
            for (int i=0; i < MAX_PARTICLES; i++){
                particles[i].advance(MAX_TIME - time);
            }

            time = MAX_TIME;
        }

        // Output the positions to the terminal
        cout << time << "\t";
        for (int j = 0; j < MAX_PARTICLES; j++){

            cout << particles[j].get_x() << "\t";
        }
        cout << endl;
    }
};

