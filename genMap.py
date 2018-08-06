import random
import sys

minX=-int(sys.argv[1])
maxX=int(sys.argv[1])
minY=-int(sys.argv[2])
maxY=int(sys.argv[2])
minZ=-int(sys.argv[3])
maxZ=int(sys.argv[3])
for x in range(minX, maxX):
    for y in range(minY, maxY):
        if (random.uniform(0, 100) < 20):
            print ("[" + str(x) + ", " + str(y) + ", " + str(round(random.uniform(minZ, maxZ), 2)) +"],");
        else:
            print ("[" + str(x) + ", " + str(y) + ", " + "0" +"],");


