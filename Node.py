dictgraph={}

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
        
classtuple=[node("a",{'b','f','g'},{12,14,16}),node("b",{'a','n','l'},{28,19,20})]

def assigndict(localnode):
    dictgraph[localnode.givename()]=[localnode.giveedges(),localnode.giveweight()]

for i in range(len(classtuple)):
    assigndict(classtuple[i])

print(dictgraph['a'])