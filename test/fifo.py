import Queue
import packetgen
import Common

log = Common.SwitchONlogger('root')

class Fifo(object):
    """
    Creates a FIFO with space for 4 entries and provides way to input.
    """

    def __init__(self,name,size,rd_enable=True,wr_enable=True):
        """
        Initialize a FIFO with given name and size
            name: 
                Specific name of the FIFO.

            size:
                size of the FIFO register.

            rd_enable: 
                Denotes whether the dequed operation was successfully 
                transmitted to the output port.

            wr_enable:
                Denotes whether the FIFO is ready to be written.
        """
        log.info("Init FIFO:%s with Size=%s and rd_enable=%s",name,
                size,rd_enable) 
        self.name = str(name)
        self.size = size
        self.counter = 0
        self.rd_enable = rd_enable # It should be true first time
        self.wr_enable = wr_enable
        self.fifo = Queue.Queue(self.size)
         
    
    def enqueue(self,data):
        """
        Takes the data and puts in the Queue checks if the Queue is full
            data:
                The data which is to be put in the Queue.
        """
        #TODO check the length of data being inserted into the Queue 
        if not self.fifo.full() and self.wr_enable:
            log.debug("Data=%s inserted in Queue",data)
            self.fifo.put(str(data)) # Convert to string for manipulations
            self.counter +=1 # Number of packets in queue
            return True
        else:
            if self.fifo.full():
                log.warning("Queue is Full!")
            else:
                log.debug("wr_enable is %s",self.wr_enable)
            return False
   
    def deque(self):
        """
        Dequeues the element from the FIFO. Checks if enable signal is present.
        """
        if self.rd_enable and not(self.fifo.empty()):
            log.info("Returning extracted Value from FIFO:%s",self.name)
            self.counter-=1 # Packet Dequeued decrement the counter.
            return self.fifo.get()
        else:
            if not self.rd_enable:
                log.debug("Fifo is not in rd_enable state")
            else:
                # FIFO is empty 
                log.debug("FIFO is empty")
            return False
    
    def isConsumed(self):
        """
        Returns True if the FIFO is empty else False
        """
        if self.counter==0: #Counter is zero FIFO is empty
            return False
        log.debug("FIFO: %s is empty",self.name)
        return True

def main():
    """
    Driver program to run this system
    """
    fifo = Fifo('Fifo 0',4)
    for i in range(0,10):
        fifo.enqueue(i)
    fifo.rd_enable=False

if __name__=="__main__":
    main()
