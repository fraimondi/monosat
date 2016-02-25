from monosat import *
g= Graph()
e1 = g.addEdge(1,2) 
e2 = g.addEdge(2,3)
e3 = g.addEdge(1,3)
Assert(Not(And(e1,e3)))

dist = g.distance_lt(1,3,2)
Assert(dist)

result = Solve()
print(result)

if result:
    path_by_nodes = g.getPath(dist)
    print("Satisfying path (as a list of nodes): " +str(path_by_nodes))
    path_by_edges = g.getPath(dist,return_edge_lits=True)
    for e in path_by_edges:
        v = e.value()
        assert(v)
     