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
plot 'results.log' u 3:1 w line, 'results.log' u 4:1 w line, 'results.log' u 5:1 w line,  'results.log' u 6:1 w line,  'results.log' u 7:1 w line,  'results.log' u 8:1 w line,  'results.log' u 9:1 w line,  'results.log' u 10:1 w line,  'results.log' u 11:1 w line,  'results.log' u 12:1 w line
pause -1 "Press enter to exit\n"
