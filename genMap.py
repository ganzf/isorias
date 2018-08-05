import random
minX=-25
maxX=25
minY=-25
maxY=25
minZ=-0.8
maxZ=1
for x in range(minX, maxX):
    for y in range(minY, maxY):
        if (random.uniform(0, 100) < 5):
            print ("[" + str(x) + ", " + str(y) + ", " + str(round(random.uniform(minZ, maxZ), 2)) +"],");
        else:
            print ("[" + str(x) + ", " + str(y) + ", " + "0" +"],");


