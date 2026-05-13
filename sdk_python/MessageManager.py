# this file is responsible  for  handling  the  message it self
# it will simply decode it with the help of the message decoder
# then it will provide functions that you can subscribe to



from .MessageDecoder import MessageDecoder
from .Structures import *
import uuid




class MessageManager:
    def __init__(self):
        self.on_information:list[callable] = []
        self.message_decoder = MessageDecoder()

        self.mac = uuid.getnode()


        # add your function inside to be excauted when specific messages
        # are recieved, 

        self.on_online_message = []



    def handel_message(self, payload:bytes, address:tuple):
        message = self.message_decoder.decode_message(payload)

        if not message:
            return 
        
        if message.mac_address == self.mac:
            # filter own device messages
            return
        

        if message.type == MessageTypes.online:
            self.trigger_event(message, address, self.on_online_message) # trigger the callback

        

    


    def trigger_event(self,
                      message:MessageUDP, 
                      address:tuple, 
                      callbacks):
        
        for callback in callbacks:
            callback(message, address)
        
