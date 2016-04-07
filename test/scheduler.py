import fifo
import packetgen

    
class Scheduler(object):
    """
    Generic scheduler which inputs out the packet one by one.
    """


    def __init__(self):
        self.fifo_list  = []
        self.fifo1 = fifo.Fifo('fifo1')
        self.fifo2 = fifo.Fifo('fifo2')
        self.fifo3 = fifo.Fifo('fifo3')
        self.fifo4 = fifo.Fifo('fifo4')
        self.portstatus = {}
        self.portstatus['fifo1'] = True
        self.portstatus['fifo2'] = False
        self.portstatus['fifo3'] = False
        self.portstatus['fifo4'] = False
        self.fifo_list.append(self.fifo1)
        self.fifo_list.append(self.fifo2)
        self.fifo_list.append(self.fifo3)
        self.fifo_list.append(self.fifo4)

    def instantiateFifo(self):
        p = packetgen.PacketGenerator()
        for fifo in self.fifo_list:
            for i in range(0,4):
                fifo.putFifo(p.generatePacket())
    
    def print_contents(self):
        """
        Print the contents of the FIFO's
        """
        for fifo in self.fifo_list:
            while not(fifo.fifo.empty()):
                print fifo.name,fifo.fifo.get()

    def schedule(self):
        """
        Dequeue a packet,check port number,if currently unoccupied send it out
        """
        output_flags = {
                "00":False,
                "01":False,
                "10":False,
                "11":False
                }
        input_packet = {
                "fifo1":None,
                "fifo2":None,
                "fifo3":None,
                "fifo4":None
                }
        output_packet = {
                "00":None,
                "01":None,
                "10":None,
                "11":None
                }
        while not(self.fifo1.fifo.empty() and self.fifo2.fifo.empty() and 
                self.fifo3.fifo.empty() and self.fifo4.fifo.empty()):
            for fifo in self.fifo_list:
                packet = fifo.fifo.get()
                if not(output_flags[element]):
                    # Port Empty put the packet here!!
                    output_flags[packet[-2:]] = True
                    input_packet[fifo.fifo.name] = packet 
                else:
                    print "Collision","Port:",element
            print output_flags
            output_flags = {
                "00":False,
                "01":False,
                "10":False,
                "11":False
                }





if __name__=="__main__":
    # s = Input()
    # s.fifoInstantiate()
    s = Scheduler()
    s.instantiateFifo()
    s.schedule()



