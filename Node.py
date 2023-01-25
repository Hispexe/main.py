class node:
    def __init__(self, name, edges, weight):
        self.name=name
        self.edges=edges
        self.weight=weight
    def givename(self):
        return(self.name)
    def giveedges(self):
        return(self.edges)
    def giveweight(self):
        return(self.weight)

dictpathgraph={}
dictweightgraph={}
classtuple=[node("a",{'b','c'},{12,14}),node("b",{'a','c'},{12,19}),node("c",{'a','b'},{14,19}),node("d",{'a','c'},{14,19}),node("f",{'d','b'},{14,19})] # A list of data to be made into a dictionary entry

def assignpathdict(localnode):
    dictpathgraph[localnode.givename()]=localnode.giveedges()

def assignweightdict(localnode):
    dictweightgraph[localnode.givename()]=localnode.giveweight()

"""
def findNode(startnode,endnode,path=None):
    data=dictpathgraph
    if path==None:
        path=[]
    path=path+[startnode]
    if startnode==endnode:
        return path
    if startnode not in data:
        return None
    for i in data[startnode]:
        if i not in path:
            ext_path = findNode(i,endnode,path)
            if ext_path:
                return ext_path
    return None
"""

def findAllPaths(startnode,endnode,path=[]):
    path=path+[startnode]
    if startnode==endnode:
        return[path]
    if startnode not in dictpathgraph:
        return[]
    paths=[]
    for vertex in dictpathgraph[startnode]:
        if vertex not in path:
            ext_path=findAllPaths(vertex,endnode,path)
            for ex in ext_path:
                paths.append(ex)
    return paths

"""
def calCost(paths):
    costs=[]
    for i in range(len(paths)):
        cost=0
        total= len(paths[i])
        for b in range(total):
            cost+=dictweightgraph[dictpathgraph[b+1]]
        costs.append(cost)
    return costs
"""
         
for i in range(len(classtuple)):
    assignpathdict(classtuple[i])
    assignweightdict(classtuple[i])

allthepaths = findAllPaths("d","a")
print(allthepaths)
# print(calCost(allthepaths))
# print(dictpathgraph)
