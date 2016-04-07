import random

class PacketGenerator(object):
    
    def __init__(self):
        pass
    
    def generatePacket(self):
        """
        generates a random integer between 0 and 255
        """
        #Generates the integer between 0 and 255 converts to binary with padding
        genint = bin(random.randint(1,255)) 
        return genint[2:].zfill(8) 

if __name__=="__main__":

    p = PacketGenerator()
    for i in range(1,10):
        print p.generatePacket()


