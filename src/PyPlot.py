import matplotlib.pyplot as plt

file_name = input()

data = [[] for i in range(2)]

counter = 0;

with open(file_name) as f:
    for line in f:
        data[counter] = [int(x) for x in line.split()]
        counter += 1
        
plt.xlabel('Bucket no.')
plt.ylabel('Bucket size')        
        
plt.plot(data[0], data[1])
#ptl.stem(data[0], data[1])

plt.show()
