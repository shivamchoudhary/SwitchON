import Queue
import packetgen
class Fifo(object):

    def __init__(self):

        self.size = 4
        self.fifo = Queue.Queue(self.size)

    def putFifo(self,data):
        """
        Takes the data and puts in the Queue
        """
        if not self.fifo.full():
            self.fifo.put(data)
            return True
        else:
            print "FIFO is Full"
            return False


if __name__=="__main__":
    fifo = Fifo()
    p = packetgen.PacketGenerator()
    for i in range(0,10):
        fifo.putFifo(p.generatePacket())
