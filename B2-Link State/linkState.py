import heapq

class NetworkGraph:
    def __init__(self):
        self.nodes = set()
        self.edges = {}

    def add_node(self, node):
        self.nodes.add(node)
        self.edges[node] = []

    def add_edge(self, node1, node2, cost):
        self.edges[node1].append((node2, cost))
        self.edges[node2].append((node1, cost))

def dijkstra(graph, start):
    distances = {node: float('inf') for node in graph.nodes}
    distances[start] = 0
    visited = set()
    priority_queue = [(0, start)]

    while priority_queue:
        current_distance, current_node = heapq.heappop(priority_queue)

        if current_node in visited:
            continue

        visited.add(current_node)

        for neighbor, weight in graph.edges[current_node]:
            distance = current_distance + weight

            if distance < distances[neighbor]:
                distances[neighbor] = distance
                heapq.heappush(priority_queue, (distance, neighbor))

    return distances

def main():
    network = NetworkGraph()

    # Add nodes to the network
    network.add_node("A")
    network.add_node("B")
    network.add_node("C")
    network.add_node("D")
    network.add_node("E")

    # Add links between nodes
    network.add_edge("A", "B", 1)
    network.add_edge("A", "C", 3)
    network.add_edge("B", "D", 2)
    network.add_edge("C", "D", 1)
    network.add_edge("D","E",4)

    start_node = "A"
    shortest_distances = dijkstra(network, start_node)

    for node, distance in shortest_distances.items():
        print(f"Shortest distance from {start_node} to {node}: {distance}")

main()