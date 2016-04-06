import random

class PacketGenerator(object):
    
    def __init__(self):
        pass
    
    def generatePacket(self):
        """
        generates a random integer between 0 and 255
        """
        return '{0:8b}'.format(random.randint(0,255))
        




if __name__=="__main__":

    p = PacketGenerator()
    for i in range(1,10):
        print p.generatePacket()[-2:]


