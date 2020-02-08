import networkx as nx

g = nx.read_gml('L8_P1_sample.gml')
#g = nx.Graph()
#g.add_node(1)
#g.add_node(2)
#g.add_node(3)
#g.add_node(4)
#g.add_edge(1, 2, weight = 2)
#g.add_edge(2, 3, weight = 2)
#g.add_edge(3, 4, weight = 1)
#g.add_edge(4, 1, weight = 4)
f = nx.betweenness_centrality(g, k = None, normalized = False, weight = 'weight', endpoints = False)
print (f)
