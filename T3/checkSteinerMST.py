import os
import sys
from math import sqrt


class Node:
    def __init__(self, col, row):
        self.col = col
        self.row = row
        self.edges = []
        self.visited = False

    def add_edge(self, node):
        self.edges.append(node)


class MST:
    def __init__(self, max_range):
        self.V = 0
        self.max_range = max_range
        self.nodes = []
        self.edges = []

    def add_node(self, node):
        self.nodes.append(node)
        self.V += 1

    def add_edge(self, node1, node2):
        self.edges.append((node1, node2))

    def get_node(self, col, row):
        # no se puede asumir orden de los nodos
        for node in self.nodes:
            if node.col == col and node.row == row:
                return node
        return None

    def manhattan_distance(self, node1, node2):
        return abs(node1.col - node2.col) + abs(node1.row - node2.row)

    def dfs_iterative(self, node):
        stack = [node]
        cost = 0
        while stack:
            node = stack.pop()
            if not node.visited:
                node.visited = True
                for edge in node.edges:
                    if not edge.visited:
                        stack.append(edge)
                        cost += self.manhattan_distance(node, edge)
        return cost

    def check_valid(self):
        # check if all nodes are connected
        for node in self.nodes:
            if not node.visited:
                return False
        return True


def build_mst(student_output, V, max_range):
    # the file has the following format
    # a int that represents the number of edges
    # for each edge, there are four ints: node_1_row node_1_col node_2_row node_2_col

    with open(student_output, "r") as f:
        mst = MST(max_range)
        line_count = f.readline()
        for i in range(int(line_count)):
            line = f.readline()
            if line == "":
                break
            col1, row1, col2, row2 = map(int, line.split())
            node1 = mst.get_node(col1, row1)
            node2 = mst.get_node(col2, row2)
            if node1 is None:
                node1 = Node(col1, row1)
                mst.add_node(node1)
            if node2 is None:
                node2 = Node(col2, row2)
                mst.add_node(node2)
            node1.add_edge(node2)
            node2.add_edge(node1)
            mst.add_edge(node1, node2)
    return mst


def get_input_nodes(test_file):
    # the file contains a line with a int that represents the max_range, other int with the number of nodes and a final int with a target_cost
    # followed by the nodes in the format: row col
    with open(test_file, "r") as f:
        line = f.readline()
        max_range, V, target_cost = map(int, line.split())
        nodes = []
        for i in range(V):
            line = f.readline()
            col, row = map(int, line.split())
            nodes.append((col, row))
    return max_range, V, target_cost, nodes


def check_contains_original_nodes(nodes, mst):
    for node in nodes:
        if not mst.get_node(node[0], node[1]):
            print(node)
            return False
    return True


def parse_input():
    if len(sys.argv) != 3:
        print("Usage: python3 checkSteinerMST.py <test_file> <student_output>")
        sys.exit(1)

    test_file = sys.argv[1]
    student_output = sys.argv[2]

    return test_file, student_output


def main():
    test_file, student_output = parse_input()
    max_range, V, target_cost, nodes = get_input_nodes(test_file)
    mst = build_mst(student_output, V, max_range)
    cost = mst.dfs_iterative(mst.nodes[0])
    is_valid = mst.check_valid()
    if not is_valid:
        print("The MST is not valid")
        sys.exit(1)
    contains_original_nodes = check_contains_original_nodes(nodes, mst)
    if not contains_original_nodes:
        print("The MST does not contain the original nodes")
        sys.exit(1)
    return cost, target_cost


if __name__ == "__main__":
    cost, target_cost = main()
    print("Cost: {}".format(cost))
    print("Target cost: {}".format(target_cost))
    improvement = (target_cost - cost) / target_cost
    print("Improvement: {}".format(improvement))
    if improvement < 0:
        print("The solution is not correct")
        sys.exit(1)
    print("The solution is correct")
