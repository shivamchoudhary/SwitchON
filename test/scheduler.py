import fifo
import pprint 
import Common

log  = Common.SwitchONlogger('Scheduler')

class Scheduler():


    def __init__(self):

        self.fifo0 = fifo.Fifo('fifo0',1)
        self.fifo0.enqueue('pkt010')
        self.fifo1 = fifo.Fifo('fifo1',1)
        self.fifo1.enqueue('pkt111')
        self.fifo2 = fifo.Fifo('fifo2',1)
        self.fifo2.enqueue('pkt210')
        self.fifo3 = fifo.Fifo('fifo3',1)
        self.fifo3.enqueue('pkt300')
        self.fifo_list = [self.fifo0,self.fifo1,self.fifo2,self.fifo3]
    
    def schedule(self):
        #Cross bar output. <Port Number>:(T/F,Packet)
        crossbar_output = {
                "00":(False,None),
                "01":(False,None),
                "10":(False,None),
                "11":(False,None)
                }
        #input keeps track if FIFO:(Packet,Port Number)
        input = {
                "fifo0":(None,None),
                "fifo1":(None,None),
                "fifo2":(None,None),
                "fifo3":(None,None)
                }
        while (self.fifo0.isConsumed() and self.fifo1.isConsumed and 
                self.fifo3.isConsumed() and self.fifo3.isConsumed()):
            
            #Stores packets not sent in a Cycle.<fifoname>:(<Packet>,<Out Port>)
            packet_queue = {
                    "fifo1":(None,None),
                    "fifo2":(None,None),
                    "fifo3":(None,None),
                    "fifo4":(None,None)
                    }
            log.info("Current packet_queue is \n %s",pprint.pformat(packet_queue))
            for fifo in self.fifo_list:
                """
                Iterate over all the FIFO's
                """
                packet = fifo.deque()     #Extract the packet from a FIFO
                if packet:
                    output_port = packet[-2:] # Extract the o/p port number
                else: #rd_enable was not set in previous cycle
                    #Extract the packet from the Waiting Queue.
                    packet,output_port = packet_queue[fifo]

                input[fifo.name] = (packet,output_port)
                # If crossbar is empty put the packet there and make it True
                if not(crossbar_output[output_port][0]):
                    crossbar_output[output_port]=(True,packet)
                    fifo.rd_enable = True #Enable read for next cycle
                else:
                    #port is occupied don't deque from FIFO
                    packet_queue[fifo] = (packet,output_port)
                    fifo.rd_enable=False
                log.debug("Recieved input is %s",pprint.pformat(input))
                log.debug("Corresponding output is %s",pprint.pformat(
                    crossbar_output))

            
         


def main():
    s = Scheduler()
    s.schedule()

if __name__=="__main__":
    main()
