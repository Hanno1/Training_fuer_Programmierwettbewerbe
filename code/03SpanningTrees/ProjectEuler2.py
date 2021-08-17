import csv


class Edge:
    def __init__(self, start, end, weight):
        self.edge = [start, end]
        self.weight = weight


def prim_algorithm(matrix):
    """
    :param matrix: Adjazenslist of the graph
    :return: sum of edges.weight of minimal spanning tree
    """
    # F will consist of every edge (in the minimal   spanning tree)
    # in order of the weight
    F = []
    # W is consists of every node in the minimal spanning tree
    W = [0]
    s = 0
    # initialise List
    for i in range(1, len(matrix[0])):
        if matrix[0][i] != "-":
            edge = Edge(0, i, int(matrix[0][i]))
            added = False
            for ind in range(0, len(F)):
                if edge.weight < F[ind].weight:
                    F.insert(ind, edge)
                    added = True
                    break
            if not added:
                F.append(edge)
    while len(W) < len(matrix[0]):
        for e in F:
            print(e.edge, e.weight)
        # take first edge of F
        int_edge = F[0]
        s += int(int_edge.weight)
        # remove first element
        F.pop(0)

        # add end vertices to W and add weight to sum
        W.append(int_edge.edge[1])

        # remove edges that form a circle
        index = 0
        while True:
            if index == len(F):
                break
            if F[index].edge[1] == int_edge.edge[1]:
                F.pop(index)
            else:
                index += 1

        # add new edges from the new node to F
        for i in range(0, len(matrix[0])):
            if matrix[int_edge.edge[1]][i] != "-" and i not in W:
                edge = Edge(int_edge.edge[1], i, int(matrix[int_edge.edge[1]][i]))
                added = False
                for ind in range(0, len(F)):
                    if edge.weight < F[ind].weight:
                        F.insert(ind, edge)
                        added = True
                        break
                if not added:
                    F.append(edge)
    return s


array = []
total = 0
counter = 1
with open("matrix.txt") as csv_file:
    csv_reader = csv.reader(csv_file, delimiter=',')
    for row in csv_reader:
        for i in range(counter, len(row)):
            if row[i] != "-":
                total += int(row[i])
        counter += 1
        array.append(row)

print(total - prim_algorithm(array))
