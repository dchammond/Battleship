import numpy as np
import sys

a = np.loadtxt(sys.argv[1], dtype='string_', delimiter=',', skiprows=1)

f = open("sprite_map.h", 'w')

for row in a:
    f.write('#define ' + row[0].decode() + '_XPOS ' + row[1].decode() + '\n')
    f.write('#define ' + row[0].decode() + '_YPOS ' + row[2].decode() + '\n')
    f.write('#define ' + row[0].decode() + '_XSIZE ' + row[3].decode() + '\n')
    f.write('#define ' + row[0].decode() + '_YSIZE ' + row[4].decode() + '\n\n')
f.close()
