import sys

class Node:
    def __init__(self, pos, col):
        self.pos = pos
        self.col = col
        self.edges = []
        self.visited = False

class Graph:
    def __init__(self):
        self.nodes = []
        self.edges = []

    def add_node(self, pos, col):
        node = Node(pos, col)
        self.nodes.append(node)
        return node

    def clear_visited(self):
        for node in self.nodes:
            node.visited = False

    def add_edge(self, node1, node2):
        for edge in node1.edges:
            if edge.pos == node2.pos:
                return
        self.edges.append((node1, node2))
        node1.edges.append(node2)
        node2.edges.append(node1)

    def dfs(self, node, not_color):
        node.visited = True
        for edge in node.edges:
            if not edge.visited and edge.col != not_color:
                self.dfs(edge, not_color)

    def iterative_dfs_with_cost(self, node):
        stack = [node]
        cost = 0
        while len(stack) > 0:
            current = stack.pop()
            if current.visited == False:
                current.visited = True
                for edge in current.edges:
                    if not edge.visited:
                        stack.append(edge)
                        cost += abs(current.pos - edge.pos)
        return cost

    def iterative_dfs(self, node, not_color):
        stack = [node]
        while len(stack) > 0:
            current = stack.pop()
            if current.col != not_color:
                current.visited = True
                for edge in current.edges:
                    if not edge.visited and edge.col != not_color:
                        stack.append(edge)

    def find_first_node_without_color(self, color):
        for node in self.nodes:
            if node.col != color:
                return node
        return None

    def check_graph(self, not_color):
        for node in self.nodes:
            if node.col != not_color:
                if node.visited == False:
                    print(f"Error: node {node.pos} {node.col} not visited")
        return True

    def binary_search_nodes(self, pos):
        low = 0
        high = len(self.nodes) - 1
        while low <= high:
            mid = (low + high) // 2
            if self.nodes[mid].pos == pos:
                return self.nodes[mid]
            elif self.nodes[mid].pos > pos:
                high = mid - 1
            else:
                low = mid + 1
        return None    

    def brute_search_node(self, pos):
        for node in self.nodes:
            if node.pos == pos:
                return node
        return None

def build_graph_nodes(graph, file_name):
    with open(file_name) as f:
        amount_nodes = int(f.readline())
        for i in range(amount_nodes):
                line = f.readline()
                if line:
                    pos, col = int(line.split(' ')[0]), line.split(' ')[1].strip('\n')
                    graph.add_node(pos, col)

def build_graph_edges(graph, file_name):
    with open(file_name) as f:
        amount_edges = int(f.readline())
        for i in range(amount_edges):
            line = f.readline()
            if line != "":
                pos_x, col_x, pos_y, col_y = int(line.split(' ')[0]), line.split(' ')[1], int(line.split(' ')[2]), line.split(' ')[3].strip('\n')
                node_x = graph.binary_search_nodes(pos_x)
                node_y = graph.binary_search_nodes(pos_y)
                if not node_x or not node_y:
                    node_x = graph.brute_search_node(pos_x)
                    node_y = graph.brute_search_node(pos_y)
                if not node_x or not node_y:
                    print("Node not on original")
                    sys.exit(1)
                colors_equal_x = node_x.col == col_x.strip().lower()
                colors_equal_y = node_y.col == col_y.strip().lower()
                color_equal = colors_equal_x and colors_equal_y
                if node_x and node_y and color_equal:
                    graph.add_edge(node_x, node_y)
                else:
                    print("Error: Node not found")
                    sys.exit(1)

def main():
    graph = Graph()
    check_params()
    build_graph_nodes(graph, sys.argv[1])
    build_graph_edges(graph, sys.argv[2])
    node = graph.find_first_node_without_color('r')
    graph.iterative_dfs(node, "r")
    if graph.check_graph("r"):
        print("Blue-Green is connected")
    else:
        print("Blue-Green is not connected")
        sys.exit(1)

    graph.clear_visited()

    node = graph.find_first_node_without_color('b')
    graph.iterative_dfs(node, "b")
    if graph.check_graph("b"):
        print("Red-Green is connected")
    else:
        print("Red-Green is not connected")
        sys.exit(1)
    
    graph.clear_visited()
    node = graph.find_first_node_without_color('x')
    cost = graph.iterative_dfs_with_cost(node)

    print(f"Cost: {cost}")
    return
    


def check_params():
    if len(sys.argv) < 3:
        print("Usage: python check_lights.py <input_file> <output_file>")
        sys.exit(1)

if __name__ == "__main__":
    check_params()
    main()