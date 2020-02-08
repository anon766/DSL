import pickle
import networkx as networking
from collections import defaultdict
def depthFirstSearchSeeoff(graphToBeChecked, index, visited, dfsVisited, isCycle):
    if isCycle[0]:
        return
    visited[index] = "Visited"
    for v in graphToBeChecked[index]:
        if visited[v] == "Visited":
            isCycle[0] = True
            return
        if visited[v] == "Not Visited":
            depthFirstSearchSeeoff(graphToBeChecked, v, visited, dfsVisited, isCycle)
    visited[index] = "Finished"     
    dfsVisited.append(index)
def randomfunc1():
    return

def topologicalSort(graphToBeSorted):          
    dfsVisited = []                 
    visited = { index : "Not Visited" for index in graphToBeSorted }
    isCycle = [False]
    for index in graphToBeSorted:
        if visited[index] == "Not Visited":
            depthFirstSearchSeeoff(graphToBeSorted, index, visited, dfsVisited, isCycle)
        if isCycle[0]:
            break
 
    if isCycle[0]:            
        dfsVisited = []                 
 
    dfsVisited.reverse()              
    return dfsVisited    


rawGraph=networking.read_gpickle('L9P2_t1.gpickle')
listOfVertices=set(rawGraph.nodes)
graph=dict()
nameOfVertices=dict()
for node in listOfVertices:
   graph[node]=[]
for edges in rawGraph.edges:
    graph[edges[0]].append(edges[1])

random1=[]
random2 = []
#Uncomment this if u wish to sort the adjacency list
"""for node in rawGraph.nodes:
   graph[node].sort()"""
#print(graph)
#Test graph
"""graph4 = { 0 : [1, 2],
           1 : [3, 4],
           2 : [],
           3 : [],
           4 : [],
           5 : [7, 6],
           6 : [],
           7 : [] }"""
topSortList=topologicalSort(graph)
if(len(topSortList)==0):
    print("Not a DAG")
else:
    print(topSortList)
    #Remove this part if nodes are not integers
    print("Topological Sorting: ")
    for x in topSortList:
        if(x!=topSortList[-1]):
            print("V"+str(x+1)+",",end=" ")
        else:
            print("V"+str(x+1))
