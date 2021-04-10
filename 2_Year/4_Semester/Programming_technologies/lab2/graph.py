import networkx as nx
import numpy as np
import matplotlib.pyplot as plt

class Graph:
    def __init__(self, vertices_cnt, edges):
        self.edges_cnt = len(edges)
        self.edges = edges
        self.vertices_cnt = vertices_cnt
        self.matrix = [[0]*vertices_cnt for _ in range(vertices_cnt)]
        for edge in edges:
            self.matrix[edge[0]][edge[1]] = 1
            self.matrix[edge[1]][edge[0]] = 1

    def _dfs(self, u, visited, pred, bad_edges):
        visited[u] = 1
        for v in range(self.vertices_cnt):
            if (self.matrix[u][v] and
                [u, v] not in bad_edges and [v, u] not in bad_edges
                and not visited[v]):
                #print("from {} to {}".format(u, v))
                pred[v] = u
                self._dfs(v, visited, pred, bad_edges)
    
    def dfs(self, u, bad_edges=[]):
        visited = [0] * self.vertices_cnt
        pred = [-1] * self.vertices_cnt
        pred[u] = u
        self._dfs(u, visited, pred, bad_edges)
        return pred

    def bfs(self, u):
        INF = self.edges_cnt * 10
        queue = [u]
        length = [INF] * self.vertices_cnt
        length[u] = -1
        pred = [-1] * self.vertices_cnt
        pred[u] = u
        while queue:
            cur_v = queue.pop(0)
            length[cur_v] = length[pred[cur_v]] + 1
            #print("Vertice No. {} visited".format(cur_v))
            for i in range(self.vertices_cnt):
                if i != cur_v and self.matrix[cur_v][i]:
                    if length[i] < INF and length[cur_v] + 1 < length[i]:
                        length[i] = length[cur_v] + 1
                        pred[i] = cur_v
                    elif length[i] == INF:
                        pred[i] = cur_v
                        queue.append(i)
        return pred
    
    def Paint(self, shortest_way=[], cycle=[]):
        def add_edge(f_item, s_item, graph=None):
            graph.add_edge(f_item, s_item)
            graph.add_edge(s_item, f_item) 
        
        g = nx.Graph()
        def get_color(edge, short, cycle):
            if edge in short or edge[::-1] in short:
                return "red"
            elif edge in cycle or edge[::-1] in cycle:
                return "blue"
            else:
                return "black"
        edge_colors = [get_color(e, shortest_way, cycle) for e in self.edges]
        for i in range(self.vertices_cnt): g.add_node(i)
        for edge in self.edges: add_edge(edge[0], edge[1], g)
        nx.draw(g, 
         node_color='gray',
         node_size=700,
         with_labels=True,
         edge_color = edge_colors)
        plt.show()



def get_way(pred, v):
    res = [[pred[v], v]]
    x = v
    while pred[x] != x:
        x = pred[x]
        edge = [pred[x], x] if pred[x] < x else [x, pred[x]]
        res = [edge] + res
    return res[1:]

if __name__ == "__main__":
    g = Graph(6, [[0, 1], [0, 2], [1, 3], [1, 4], [4, 5]])
    print(g.dfs(5, []))
    print('-' * 65)
    print(g.bfs(5))
    g.Paint()
