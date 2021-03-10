_University Course Assignment_

# ParticleSimulator

I set myself the following additional goal (devised by me):

I wanted to experiment with both elastic and inelastic collisions so I coded my own simulation for any number of particles. This program calculates the positions and kinetic energies of each particle every time there a collision occurs. Also, there is a global coefficient of restitution for particle to particle and wall to particle collisions.

Instead of the suggested method to record the variables equally spaced in time, I chose this method to save on data storage requirements as the motion is constant between collisions so the positions and energies can be interpolated. Another benefit would be the ability to reanimate at any frame "rate" or time intervals without any loss of information - similarly to lossless data compression. However, a drawback could be the very large number of collisions in the case of chattering resulting in large data requirements - this could be reduced by the limit on the number of collisions to be simulated.

To calculate when the next collision occurs, the time for each pair of adjacent particles to intercept each other is calculated, and the lowest time calculated is used. The program then leap forwards to the time of the collision - this advances all particles to their new positions based on their previous positions and velocities. The colliding particles have their new velocities after collision calculated using the conservation of momentum and the coefficient of restitution. This cycle repeats until the maximum specified time or number of collisions has been reached.

The particles are defined by a Particle class which improves encapsulation; this improves maintainability and reduces programming errors. The use of this class made it very simple to add any number of particles to the simulation (also requires changing the number of particles global constant). In this assessment, I also learnt how to provide a reference to another Particle object in some of the methods within the class which improves code readability and also reduces programming errors.

A shell script runs this program and records the output to a log file. GNUPlot is then utilised to plot the positions of the particles over time, and then the energies of the particles over time.

To make my program more useful, I would need to add in two more dimensions and to allow for different coefficient of restitutions for the walls and the particles; though in two dimensions, one would also need to consider angular motion and friction. Perhaps, the walls and particles could have their separate classes: I could have a Wall subclass a Particle for instance since, in this code, a wall is essentially an immovable particle. Furthermore, the definition of all the walls and particles could have been provided in an input file instead of placing them within main(); this allows the program to be able to simulate various simulations without recompiling. It would also be useful to generate and save the plots as part of the script or the C++ program. Other improvements could include overloading the comparison operators (<, <=, >, >=, == and !=) and providing a hash method for the Particle class - one use would be being able to define the particles in any other and sorting the list by position afterwards.

With the default parameters found in the provided source code, but with a coefficient of restitution of 1, the motion of the particles continue forever without loss of total energy. Please see the following two plots:

![Output plot of the positions using the parameters provided in the source code except for the coefficient of restitution which was 1 in this plot.](/plot_elastic_positions.png)

![Output plot of the kinetic energies using the parameters provided in the source code except for the coefficient of restitution which was 1 in this plot.](/plot_elastic_energies.png)

However, with the coefficient of restitution set to 0.95, the particles slow down over time and their energy decays, as expected. Please see the following two plots:

![Output plot of the positions using the parameters provided in the source code.](/plot_inelastic_positions.png)

![Output plot of the kinetic energies using the parameters provided in the source code.](/plot_inelastic_energies.png)

GitHub repository: https://github.com/GavinChoy/ParticleSimulator

My solution was in four files called ParticleSimulator.cpp, Particle.cpp, run\_plot_simulation.sh and gnuplotter.gnu.
