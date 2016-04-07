import Queue
import packetgen
import Common


class Fifo(object):
    """
    Creates a FIFO with space for 4 entries and provides way to input.
    """

    def __init__(self,name,size,rd_enable=True):
        """
        Initialize a FIFO with given name and size
            name: 
                Specific name of the FIFO.

            size:
                size of the FIFO register.

            rd_enable: 
                Denotes whether the dequed operation was successfully 
                transmitted to the output port.
        """
        log.info("Initializing FIFO %s with Size=%s and rd_enable=%s",name,
                size,rd_enable) 
        self.name = str(name)
        self.size = size
        self.rd_enable = rd_enable # It should be true first time        
        self.fifo = Queue.Queue(self.size)
    
    
    def enqueue(self,data):
        """
        Takes the data and puts in the Queue checks if the Queue is full
            data:
                The data which is to be put in the Queue.
        """
        
        if not self.fifo.full():
            log.debug("Data=%s inserted in Queue",data)
            self.fifo.put(data)
            return True
        else:
            log.warning("Queue is Full!")
            return False
   
    def deque(self):
        """
        Dequeues the element from the FIFO. Checks if enable signal is present.
        """
        if self.rd_enable and not(self.fifo.empty()):
            log.info("Returning extracted Value from FIFO")
            return self.fifo.get()
        else:
            if not self.rd_enable:
                log.debug("Fifo is not in rd_enable state")
            else:
                log.debug("FIFO is empty")
            return False

def main():
    fifo = Fifo('Test',1)
    fifo.enqueue("")
    fifo.deque()


if __name__=="__main__":
    log = Common.SwitchONlogger('root')
    main()
