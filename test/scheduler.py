import fifo
import packetgen
class Input(object):

    def __init__(self):
        """
        Create Instances of FIFO and put data in them
        """
        fifo1 = fifo.Fifo()
        fifo2 = fifo.Fifo()
        fifo3 = fifo.Fifo()
        fifo4 = fifo.Fifo()
        #Instantiate Packet Generator 
        #TODO change the way FIFO's are instantiated.
        p = packetgen.PacketGenerator()
        for i in range(1,4):
            fifo1.putFifo(p.generatePacket())
            fifo2.putFifo(p.generatePacket())
            fifo3.putFifo(p.generatePacket())
            fifo4.putFifo(p.generatePacket())

        while not (fifo1.fifo.empty()):
            print fifo1.fifo.get(),"FIFO:1"
            print fifo2.fifo.get(),"FIFO:2"
            print fifo3.fifo.get(),"FIFO:3"
            print fifo4.fifo.get(),"FIFO:4"

if __name__=="__main__":
    s = Input()




