import os
import random
K=[2,3,4,5,5,6,7,8,9,9]
for i in range(10):
	ou="line" + str(i + 1) + ".in"
	ans="line" + str(i + 1) + ".out"
	os.system("./gen " + str(K[i]) + " " + str(random.randint(1, 100000)) + " > " + ou)
	os.system("./line < " + ou + " > " + ans)
