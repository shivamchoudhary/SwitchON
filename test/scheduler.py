import fifo
import pprint 
import Common

log  = Common.SwitchONlogger('Scheduler')

class Scheduler():


    def __init__(self):

        self.fifo0 = fifo.Fifo('fifo0',2)
        self.fifo0.enqueue('pkt010')
        self.fifo0.enqueue('packet011')
        self.fifo1 = fifo.Fifo('fifo1',1)
        self.fifo1.enqueue('pkt111')
        self.fifo2 = fifo.Fifo('fifo2',1)
        self.fifo2.enqueue('pkt210')
        self.fifo3 = fifo.Fifo('fifo3',1)
        self.fifo3.enqueue('pkt310')
        self.fifo_list = [self.fifo0,self.fifo1,self.fifo2,self.fifo3]
        self.packet_queue = {
                "fifo0":(None,None),
                "fifo1":(None,None),
                "fifo2":(None,None),
                "fifo3":(None,None)
                } 
    def schedule(self):
        counter = 0
        while counter!=5:    
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
            #Stores packets not sent in a Cycle.<fifoname>:(<Packet>,<Out Port>)
            for fifo in self.fifo_list:
                #increment counter only when it sends on crossbar
                packet = fifo.deque()
                if packet==-1:
                    packet,output_port = self.packet_queue[fifo.name]
                    self.packet_queue[fifo.name] = (None,None)
                    input[fifo.name] = (packet,output_port)
                elif packet==-2:
                    packet,output_port = (None,None)
                    input[fifo.name] = (None,None)
                else:
                    output_port = packet[-2:]
                    input[fifo.name] = (packet,output_port) 

                # CrossBar Switch
                if packet:
                    if not(crossbar_output[output_port][0]):
                        crossbar_output[output_port] = (True,packet)
                        counter+=1
                    else:
                        self.packet_queue[fifo.name]  = (packet,output_port)
                        fifo.rd_enable = False
            print "INPUT"
            pprint.pprint(input)
            print "OUTPUT"
            pprint.pprint(crossbar_output)



                
            
def main():
    s = Scheduler()
    s.schedule()

if __name__=="__main__":
    main()
