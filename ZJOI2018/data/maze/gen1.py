import random
A = []
for m in range(2,7):
	for K in range(1, 11):
		A.append([m,K])
print(len(A))
for i in range(len(A)):
	print(str(A[i][0]) + " " +str(A[i][1]))
