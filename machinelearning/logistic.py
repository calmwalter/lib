# this is the practice of logistic function
import math
import numpy
import random
import matplotlib.pyplot as plt
import time

# initial alpha
alpha = 0.001
# initial args in the function
args = [random.random(), random.random()]
# linitial the data used to training
data = []
for i in range(10):
    data.append([random.random()*0.5, 1])
for i in range(10):
    data.append([random.random()*0.5+0.5, 0])

openfile=open("point.txt","w")
openfile.write(str(data))
openfile.close()
def jfunction(data):
    j = 0.0
    l = len(data)
    for i in range(l):
        x = data[i][0]
        y = data[i][1]
        #if math.log2(hfunction(x))!=0 and math.log2(1-hfunction(x))!=0:
        j += y*math.log2(hfunction(x))+(1-y)*math.log2(1-hfunction(x))
        
    return -j/l


def djfunction(data):
    dj = 0.0
    l = len(data)
    for i in range(l):
        x = data[i][0]
        y = data[i][1]
        dj += (hfunction(x)-y)*x

    return dj/l


def djfunction1(data):
    dj = 0.0
    l = len(data)
    for i in range(l):
        x = data[i][0]
        y = data[i][1]
        dj += hfunction(x)-y

    return dj/l


def hfunction(x):
    #print(1.0 / float(1.0 + math.exp(-args[1]*x-args[0])))
    return 1.0 / float(1.0 + math.exp(-args[1]*x-args[0]))


def argsUpdate(data):
    arg0 = args[0]
    arg1 = args[1]
    arg0 -= alpha*djfunction(data)
    arg1 -= alpha*djfunction1(data)
    args[0] = arg0
    args[1] = arg1


def writeargs():
    openfile=open("data.txt","w")
    openfile.write(str(args))
    openfile.close()

currentTime = time.time()
totalSeconds = int(currentTime)
while int(time.time())-totalSeconds<10:
    #print(int(time.time())-totalSeconds)
    print(jfunction(data))
    argsUpdate(data)
    writeargs()

#print(args)
mm = numpy.linspace(0, 1, 1000)
for xy in data:
    plt.scatter(xy[0], xy[1], c='r', s=10, alpha=1)
yy = args[0]+args[1]*mm
plt.plot(mm, yy)
plt.show()
