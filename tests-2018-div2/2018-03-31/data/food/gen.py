import math 
import io
import random
import os
def fprint(f,*a):
	at=0
	for i in a:
		f.write(str(i))
		at+=1
		if at!=len(a):
			f.write(' ')
		else:
			f.write('\n')
for t in range(4,6):

	with open("food"+str(t)+".in","w") as f:
		if t==1:
			fprint(f,2)
			fprint(f,1,1)
			fprint(f,10,1)
		elif(t<=3):
			fprint(f,5)
			for i in range(5):
				fprint(f,random.randint(1,10),1)
		elif(t<=6):
			fprint(f,10)
			for i in range(10):
				fprint(f,random.randint(1,1000),random.randint(1,1000))
		elif(t<=8):
			fprint(f,50)
			for i in range(50):
				fprint(f,0,random.randint(1,1e9))
		else:
			fprint(f,50)
			for i in range(50):
				fprint(f,random.randint(1,1e9),random.randint(1,1e9))
	os.system("./food<food"+str(t)+".in>food"+str(t)+".out")
		
