
from .MessageBuilder import MessageBuilder
from .Network import Network
from .Structures import *
from . import Config
import threading
import time

# only one instance of the API is allowed as we connect 
# to a udp socket
class API:
    def __init__(self):
        self.network = Network()
        self.message_builder = MessageBuilder()
        self.message_manager = self.network.message_manager # forward the class


        reciving_thread = threading.Thread(target=self.network.start_receiving)
        reciving_thread.start()


        self.online_devices:list[OnlineDevice] = []

        self.message_manager.on_online_message.append(self.on_online_device)


        

    def on_online_device(self, message:MessageUDP, address:tuple):
        
        online_device = OnlineDevice()
        online_device.address = address
        online_device.message = message
        online_device.name = message.device_name
        online_device.time = time.time()
        
        for i in range(len(self.online_devices)):
            device = self.online_devices[i]
            if device.address == address:
                self.online_devices[i] = online_device
                return

        self.online_devices.append(online_device)


    def get_online_devices(self, time_out=1):
        message = self.message_builder.build_discovery_message()
        self.network.send((Config.BROADCAST, Config.PORT), message.to_bytes())
        time.sleep(time_out)

        return self.online_devices
