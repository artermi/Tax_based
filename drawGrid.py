import os
import numpy as np
import scipy.misc as smp
from PIL import Image

# Create a 1024x1024x3 array of 8 bit unsigned integers


for root,dirs,files in sorted(os.walk('.',topdown = False)):
	for name in sorted(files):
		if 'i' not in name:
			continue
		info = []
		with open(os.path.join(root, name),"rb") as file:
			count = 0
			while True:
				c = file.read(1)
				if not c:
					break
				info.append(int(c))
				count +=1
		print(len(info))
		pixsize = 1
		row = int(len(info) ** .5 + 0.0000001)
		data = np.zeros( (pixsize * row,pixsize * row,3), dtype=np.uint8 ) #
		for ind, typ in enumerate(info):
			x,y = int(ind / row),int(ind % row)
			x*= pixsize
			y*= pixsize

			if typ == 0:
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [255, 0, 0]
			if typ == 1:
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [0, 0, 255]
			if typ == 2:
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [128,128,128]
			if typ == 3:
				for i in range(pixsize):
					for j in range(pixsize):
						data[x+i,y+j] = [255,255,0]

				
		image = Image.fromarray(data)
		print(name.split('.')[0])
		image.save(name.split('.')[0] + '.png')                      # View in default viewer
