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

b = []


d_name = '.'
t_name = 'new_b.tex'
if len(sys.argv) > 2:
	d_name = sys.argv[1]
	t_name = sys.argv[2]

for root,dirs,files in sorted(os.walk(d_name,topdown = False)):

	for name in sorted(files):
		if name.find('.dat') >= 0:
			# r_0300_b_0036_T_0040_G_0080.dat
			# 0123456789|123456789|1234567
			bb = float(name[9:13])/1000

			Final_D = []
			Final_C = []
			FinalPD = []
			FinalPC = []
			with open(os.path.join(root, name)) as file:
				for last_line in file:
					nmbs = last_line.split()
					Final_D.append(float(nmbs[1]))
					Final_C.append(float(nmbs[2]))
					FinalPD.append(float(nmbs[3]))
					FinalPC.append(float(nmbs[4]))
#					if int(nmbs[0]) == 10000:
#						break


			b.append(bb)
			D.append( sum(Final_D[-3:])/3 )
			C.append( sum(Final_C[-3:])/3 )
			PC.append( sum(FinalPC[-3:])/3 ) 
			PD.append( sum(FinalPD[-3:])/3 )



ax = plt.subplot(111)
box = ax.get_position()
ax.set_position([box.x0, box.y0 + box.height * 0.2,
                 box.width, box.height * 0.8])
#ax.plot(itr, L, color='#cb4335', marker= '.', label = 'Fixed defector')
ax.plot(b, D, color='red', marker= '.',label = 'D',markersize=2)
ax.plot(b, C, color='blue', marker= '.',label = 'C',markersize=2)
ax.plot(b, PD, color='grey', marker= '.',label = 'PD',markersize=2)
ax.plot(b, PC, color=(250/255,218/255,94/255), marker= '.',label = 'PC',markersize=2)
ax.legend(loc='upper center', bbox_to_anchor=(0.5, -0.2), fancybox=True, shadow=True, ncol=2)

plt.ylim([-0.1,1.1])
plt.xlabel(r'$\beta$')
plt.ylabel('Fractions')
plt.grid(False)

import tikzplotlib

tikzplotlib.save(t_name)