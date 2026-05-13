# this class will help you build a message before
# you send it over
from .Structures import *
import socket
import uuid



class MessageBuilder:
    def __init__(self):
        self.mac = uuid.getnode()
        self.device_name = socket.gethostname()



    def build_setting_command(self, brightness_value, transition_speed=0.3):
        message = MessageUDP()
        message.type = MessageTypes.command
        message.mac_address = self.mac
        message.device_name = self.device_name
        message.is_encrypted = False

        command = Command()
        command.type = CommandTypes.setting
        command.sequence_number = 0

        command_setting = CommandSetting()
        command_setting.brightness = int(255 * brightness_value)
        command_setting.transition_speed = transition_speed

        command.content = command_setting
        message.content = command

        return message


    def build_rgb_stream_command(self, trasition_duration, starting_led, rgb_list):
        message = MessageUDP()
        message.type = MessageTypes.command
        message.mac_address = self.mac
        message.device_name = self.device_name
        message.is_encrypted = False

        command = Command()
        command.type = CommandTypes.rgb_stream
        command.sequence_number = 0

        rgb_stream = CommandRGBStream()
        rgb_stream.leds_number = int(len(rgb_list) / 3) 
        rgb_stream.starting_led = starting_led
        rgb_stream.transition_duration = trasition_duration
        rgb_stream.stream = list(rgb_list)

        command.content = rgb_stream
        message.content = command

        return message



    def build_sequence_command(self, sequence):
        message = MessageUDP()
        message.type = MessageTypes.command
        message.mac_address = self.mac
        message.device_name = self.device_name
        message.is_encrypted = False

        command = Command()
        command.type = CommandTypes.sequence
        command.sequence_number = 0

        sequence_command = CommandSequence()
        sequence_command.type = sequence

        command.content = sequence_command
        message.content = command

        return message


    def build_discovery_message(self):
        message = MessageUDP()
        message.type = MessageTypes.discovery
        message.mac_address = self.mac
        message.device_name = self.device_name
        message.is_encrypted = False

        return message


