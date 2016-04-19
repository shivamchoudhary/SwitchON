# Adapted from http://www.cse.unt.edu/~tarau/teaching/AnAlgo/Ford%E2%80%93
# Fulkerson%20algorithm.pdf

# class Edge(object):
    # def __init__(self,u,v,w):
        # self.source =u
        # self.sink = v
        # self.capacity = w

    # def __repr__(self):
        # return "%s->%s:%s" %(self.source,self.sink,self.capacity)

# class FlowNetwork(object):
    # def __init__(self):

        # self.adj = {}
        # self.flow = {}

    # def add_vertex(self,vertex):
        # self.adj[vertex] = []

    # def get_edges(self,v):
        # return self.adj[v]

    # def add_edge(self,u,v,w=0):
        # if u==v:
            # raise ValueError("u == v")
        # edge = Edge(u,v,w)
        # redge = Edge(v,u,0)
        # edge.redge = redge
        # redge.redge = edge
        # self.adj[u].append(edge)
        # self.adj[v].append(redge)
        # self.flow[edge] = 0
        # self.flow[redge] = 0

    # def find_path(self,source,sink,path,path_set):
        # if source==sink:
            # return path
        # for edge in self.get_edges(source):
            # residual = edge.capacity - self.flow[edge]
            # if residual > 0 and not (edge,residual) in path_set:
                # path_set.add((edge,residual))
                # result  = self.find_path(edge.sink,sink,path+[(edge,residual)],path_set)
                # if result!=None:
                    # return result

    # def max_flow(self,source,sink):
        # path = self.find_path(source,sink,[],set())
        # while path!=None:
            # flow = min(res for edge,res in path)
            # for edge,res in path:
                # self.flow[edge] +=flow
                # self.flow[edge.redge] -=flow
            # path = self.find_path(source,sink,[],set())
        # return sum(self.flow[edge] for edge in self.get_edges(source))


# def main():
    # g = FlowNetwork()
    # [g.add_vertex(v) for v in "suvt"]
    # g.add_edge('s','u',20)
    # g.add_edge('s','v',0)
    # g.add_edge('o','p',2)
    # g.add_edge('p','r',2)
    # g.add_edge('r','t',3)
    # g.add_edge('q','r',4)
    # g.add_edge('q','t',2)
    # print g.max_flow('s','t')



class Edge(object):
  def __init__(self, u, v, w):
    self.source = u
    self.target = v
    self.capacity = w

  def __repr__(self):
    return "%s->%s:%s" % (self.source, self.target, self.capacity)


class FlowNetwork(object):
  def  __init__(self):
    self.adj = {}
    self.flow = {}

  def AddVertex(self, vertex):
    self.adj[vertex] = []

  def GetEdges(self, v):
    return self.adj[v]

  def AddEdge(self, u, v, w = 0):
    if u == v:
      raise ValueError("u == v")
    edge = Edge(u, v, w)
    redge = Edge(v, u, 0)
    edge.redge = redge
    redge.redge = edge
    self.adj[u].append(edge)
    self.adj[v].append(redge)
    # Intialize all flows to zero
    self.flow[edge] = 0
    self.flow[redge] = 0

  def FindPath(self, source, target, path):
    if source == target:
      return path
    for edge in self.GetEdges(source):
      residual = edge.capacity - self.flow[edge]
      if residual > 0 and not (edge, residual) in path:
        result = self.FindPath(edge.target, target, path + [(edge, residual)])
        if result != None:
          return result

  def MaxFlow(self, source, target):
    path = self.FindPath(source, target, [])
    print 'path after enter MaxFlow: %s' % path
    for key in self.flow:
      print '%s:%s' % (key,self.flow[key])
    print '-' * 20
    while path != None:
      flow = min(res for edge, res in path)
      for edge, res in path:
        self.flow[edge] += flow
        self.flow[edge.redge] -= flow
      for key in self.flow:
        print '%s:%s' % (key,self.flow[key])
      path = self.FindPath(source, target, [])
      print 'path inside of while loop: %s' % path
    for key in self.flow:
      print '%s:%s' % (key,self.flow[key])
    return sum(self.flow[edge] for edge in self.GetEdges(source))


if __name__ == "__main__":
  g = FlowNetwork()
  map(g.AddVertex, ['s', 'o', 'p', 'q', 'r', 't'])
  g.AddEdge('s', 'o', 5)
  g.AddEdge('s', 'p', 3)
  g.AddEdge('o', 'p', 2)
  g.AddEdge('o', 'q', 3)
  g.AddEdge('p', 'r', 4)
  g.AddEdge('r', 't', 3)
  g.AddEdge('q', 'r', 4)
  g.AddEdge('q', 't', 2)
  print g.MaxFlow('s', 't')

# if __name__=="__main__":
    # main()
