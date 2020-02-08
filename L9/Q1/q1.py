import numpy as np 
import pickle 
from heapq import *
from fibheap import *
import matplotlib.pyplot as plot
from matplotlib.colors import *
#    dd

def calculateHeuristicDistance(start, end, choice):
    
    if(choice == 1):
        return (end[0] - start[0]) ** 2 + (end[1] - start[1]) ** 2
    elif (choice == 2):
        return max(abs(end[0]-start[0]), abs(end[1]-start[1]))
    elif (choice == 3):
        return abs(end[0]-start[0]) + abs(end[1]-start[1])


def Astar(pathTemp, begin, end, choice):

    possibleDirections = [(0,1),(0,-1),(1,0),(-1,0),(1,1),(1,-1),(-1,1),(-1,-1)]

    boxesInPath = set()
    entireGrid = {}
    scrG = {begin:0}
    scrF = {begin:calculateHeuristicDistance(begin, end, choice)}
    fibonacciHeap = []

    heappush(fibonacciHeap, (scrF[begin], begin))
    
    while fibonacciHeap:

        rightNow = heappop(fibonacciHeap)[1]

        if rightNow == end:
            pathFinal = []
            while rightNow in entireGrid:
                pathFinal.append(rightNow)
                rightNow = entireGrid[rightNow]
            return pathFinal

        boxesInPath.add(rightNow)
        for i, j in possibleDirections:
            neighbor = rightNow[0] + i, rightNow[1] + j            
            tempSrcG = scrG[rightNow] + calculateHeuristicDistance(rightNow, neighbor, choice)
            if 0 <= neighbor[0] < pathTemp.shape[0]:
                if 0 <= neighbor[1] < pathTemp.shape[1]:                
                    if pathTemp[neighbor[0]][neighbor[1]] == 1:
                        continue
                else:
                    continue
            else:
                continue
            random1 = []
            random3 = []
            if neighbor in boxesInPath and tempSrcG >= scrG.get(neighbor, 0):
                continue
                
            if  tempSrcG < scrG.get(neighbor, 0) or neighbor not in [i[1]for i in fibonacciHeap]:
                entireGrid[neighbor] = rightNow
                scrG[neighbor] = tempSrcG
                scrF[neighbor] = tempSrcG + calculateHeuristicDistance(neighbor, end, choice)
                heappush(fibonacciHeap, (scrF[neighbor], neighbor))
                
    return False

#grid = np.pathTemp([
#   [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
#   [1,1,1,1,1,1,1,1,1,1,1,1,0,1],
#   [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
#   [1,0,1,1,1,1,1,1,1,1,1,1,1,1],
#   [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
#   [1,1,1,1,1,1,1,1,1,1,1,1,0,1],
#   [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
#   [1,0,1,1,1,1,1,1,1,1,1,1,1,1],
#   [0,0,0,0,0,0,0,0,0,0,0,0,0,0],
#   [1,1,1,1,1,1,1,1,1,1,1,1,0,1],
#   [0,0,0,0,0,0,0,0,0,0,0,0,0,0]])
    
inputPickle = open("L9P1_t1.pkl", "rb")
inputFile = pickle.load(inputPickle)
countRows = len(inputFile)
countColumns = len(inputFile[0])
for i in range(countRows):
	for j in range(countColumns):
		inputFile[i][j]=0 if inputFile[i][j] is 1 else 1
inputPickle.close()
grid= np.array(inputFile)

input1 = input("Start coordinate: ")
#startY = int(input())
input2 =input("End coordinates: ")
#finishY = int(input())
print("1. Euclidean Distance")
print("2. Diagonal Distance")
print("3. Manhattan Distance")
choice = int(input("Enter choice: "))
list1 = input1.split()
startY = int(list1[0])
startX = int(list1[1])
list2 = input2.split()
finishY = int(list2[0])
finishX = int(list2[1])
path = Astar(grid, (startX, startY), (finishX, finishY), choice)

countRows, countColumns = np.size(grid, 0), np.size(grid, 1)
image = grid
for row in range(countRows):
    for col in range(countColumns):
        if(np.equal(grid[row, col], 1)):
            image[row, col] = 0
        else:
            image[row, col] = 1
c = 2
for (x, y) in path:
    image[x,y] = c
    # c += 1
image[startX, startY] = 3
image[finishX, finishY] = 4
path.reverse()
path.insert(0, (startX, startY))
print ("Path: " , path)

cmap = ListedColormap(['black', 'white', 'blue', 'green', 'red'])
bounds = [0,1,2,3,4,5]
norm = BoundaryNorm(bounds, cmap.N)
row_labels = range(countRows)
col_labels = range(countColumns)
extent = [0, countRows, 0 , countColumns]
plot.imshow(image, cmap = cmap, norm = norm, origin = "lower", extent = extent)
plot.xticks(range(countColumns), col_labels)
plot.yticks(range(countRows), row_labels)
plot.grid()
plot.show()
