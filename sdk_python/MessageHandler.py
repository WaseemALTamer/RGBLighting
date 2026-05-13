# this file is responsible  for  handling  the  message it self
# it will simply decode it with the help of the message decoder
# then it will provide functions that you can subscribe to



from .MessageDecoder import MessageDecoder
from .Structures import *
import socket
import uuid




class MessageHandler:
    def __init__(self):
        self.on_information:list[callable] = []

        self.message_decoder = MessageDecoder()


    def handel_message(self, payload:bytes, address:tuple):

        message = self.message_decoder.decode_message(payload)
        
        

        print(message.__dict__)
        print(message.content.__dict__)

        return 




"""

client_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

server_address = ('192.168.1.29', 39394)


def set_setting(value, transition_speed = 0.3):
    mac = uuid.getnode()

    message = MessageUDP()
    message.type = MessageTypes.command
    message.mac_address = mac
    message.device_name = socket.gethostname()
    message.is_encrypted = False

    command = Command()
    command.type = CommandTypes.setting
    command.sequence_number = 3003



    command_setting = CommandSetting()
    command_setting.brightness = int(255 * value)
    command_setting.transition_speed = transition_speed


    command.content = command_setting 
    message.content = command

    client_socket.sendto(message.to_bytes(), server_address)


def set_color(rgb_list):
    mac = uuid.getnode()


    message = MessageUDP()
    message.type = MessageTypes.command
    message.mac_address = mac
    message.device_name = socket.gethostname()
    message.is_encrypted = False

    command = Command()
    command.type = CommandTypes.rgb_stream
    command.sequence_number = 3004

    rgb_stream = CommandRGBStream()

    rgb_stream.leds_number = int(len(rgb_list) / 3) 


    rgb_stream.stream = list(rgb_list)

    command.content = rgb_stream
    message.content = command

    client_socket.sendto(message.to_bytes(), server_address)


def set_sequence(sequence):
    mac = uuid.getnode()


    message = MessageUDP()
    message.type = MessageTypes.command
    message.mac_address = mac
    message.device_name = socket.gethostname()
    message.is_encrypted = False

    command = Command()
    command.type = CommandTypes.sequence
    command.sequence_number = 3004

    sequence_command = CommandSequence()

    sequence_command.type = sequence

    command.content = sequence_command
    message.content = command

    client_socket.sendto(message.to_bytes(), server_address)

"""