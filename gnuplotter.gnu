# Particle Simulator
# Copyright (C) 2021  Gavin Choy
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

set key outside
set title "Position of particles over time"
set key title "Particle Key"
set xlabel "Position / m"
set ylabel "Time / s"
plot 'results.log' u 4:1 w line title 'Particle 1', 'results.log' u 6:1 w line title 'Particle 2', 'results.log' u 8:1 w line title 'Particle 3',  'results.log' u 10:1 w line title 'Particle 4',  'results.log' u 12:1 w line title 'Particle 5',  'results.log' u 14:1 w line title 'Particle 6',  'results.log' u 16:1 w line title 'Particle 7',  'results.log' u 18:1 w line title 'Particle 8',  'results.log' u 20:1 w line title 'Particle 9',  'results.log' u 22:1 w line title 'Particle 10'
pause -1 "Press enter to proceed\n"

set key outside
set title "Kinetic energy of particles over time"
set key title "Particle Key"
set xlabel "Time / s"
set ylabel "Kinetic energy / J"
plot 'results.log' u 1:5 w line title 'Particle 1', 'results.log' u 1:7 w line title 'Particle 2', 'results.log' u 1:9 w line title 'Particle 3',  'results.log' u 1:11 w line title 'Particle 4',  'results.log' u 1:13 w line title 'Particle 5',  'results.log' u 1:15 w line title 'Particle 6',  'results.log' u 1:17 w line title 'Particle 7',  'results.log' u 1:19 w line title 'Particle 8',  'results.log' u 1:21 w line title 'Particle 9',  'results.log' u 1:23 w line title 'Particle 10'
pause -1 "Press enter to edit\n"
