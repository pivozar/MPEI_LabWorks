from graph import Graph, get_way

def main(filename):
    with open(filename, 'r') as f:
        data = f.readlines()
        n, m = (int(i)  for i in data[0].split())
        edges = [[int(v) for v in line.split()] for line in data[1:-1]]
        v1, v2 = (int(i)  for i in data[-1].split())
    g = Graph(n, edges)
    short_way = get_way(g.bfs(v1), v2)
    half_cycle = get_way(g.dfs(v1, short_way), v2)
    bad_edges2 = short_way + half_cycle
    cycle = half_cycle + get_way(g.dfs(v1, bad_edges2), v2)
    print(cycle)
    g.Paint(short_way, cycle)

if __name__ == "__main__":
    main("input.txt")