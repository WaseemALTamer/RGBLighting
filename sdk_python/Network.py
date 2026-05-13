from .MessageManager import MessageManager
from . import Config
import socket








class Network:
    def __init__(self):
        
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_BROADCAST, 1)
        self.server_socket.bind((Config.IP, Config.PORT))
        

        self.message_manager = MessageManager() # network will contain its own message Manager

        self.is_receiving = False


    def start_receiving(self):
        """
            this function is a loop run it on another thread
        """
        self.is_receiving = True
        while self.is_receiving:
            try:
                data, addr = self.server_socket.recvfrom(1024)
                self.message_manager.handel_message(data, addr)

            except Exception as e:
                print(f"Receive error: {e}")



    def send(self, address:tuple, payload:bytes):
        try:
            self.server_socket.sendto(payload, address)
        except Exception as e:
            print(e)



    def stop(self):
        self.is_receiving = False
        self.server_socket.close()