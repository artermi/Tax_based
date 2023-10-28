import sys
import os
import numpy as np
import matplotlib.pyplot as plt
from collections import defaultdict
from matplotlib import rc

D = []
C = []
PD = []
PC = []

t = []


f_name = '.'
t_name = 'new_b.tex'
if len(sys.argv) > 2:
	f_name = sys.argv[1]
	t_name = sys.argv[2]


	with open(f_name) as file:
		to_be_break = False
		break_number = 0
		for line in file:
			nmbs = line.split()
			if (not to_be_break) and (float(nmbs[1]) == 1.0 or float(nmbs[2]) == 1.0 or float(nmbs[3]) == 1.0 or float(nmbs[4]) == 1.0) :
				break_number = ( int(int(nmbs[0]) / 500) + 1) * (500)
				to_be_break = True

			t.append(int(nmbs[0]))
			D.append(float(nmbs[1]))
			C.append(float(nmbs[2]))
			PD.append(float(nmbs[3]))
			PC.append(float(nmbs[4]))

			if to_be_break and int(nmbs[0]) == break_number:
				break

else:
	os.exit()


ax = plt.subplot(111)
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * 0.8])
#ax.plot(itr, L, color='#cb4335', marker= '.', label = 'Fixed defector')
ax.plot(t, D, color='red', marker= '.',label = 'D',markersize=2)
ax.plot(t, C, color='blue', marker= '.',label = 'C',markersize=2)
ax.plot(t, PD, color='grey', marker= '.',label = 'PD',markersize=2)
ax.plot(t, PC, color=(250/255,218/255,94/255), marker= '.',label = 'PC',markersize=2)
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.2), fancybox=True, shadow=True, ncol=2)

plt.ylim([-0.1,1.1])
plt.xlabel('Iteration')
plt.ylabel('Fractions')
plt.grid(False)

import tikzplotlib

tikzplotlib.save(t_name)