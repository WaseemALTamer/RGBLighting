import struct



class CommandType:

    def to_bytes(self):
        return b""


class CommandTypes:
    setting:int = 1
    rgb_stream:int = 2
    sequence:int = 3


class CommandSetting(CommandType):
    def __init__(self):
        self.brightness:int = None # 1 byte from 0-255
        self.transition_speed:float = None # 8 bytes double in cpp


    def to_bytes(self):
        data = b""

        data += self.brightness.to_bytes(1, "big")
        data += struct.pack(">d", self.transition_speed)

        return data



class SequenceTypes:
    rainbow:int = 1
    breahting:int = 2
    wave:int = 3


class CommandSequence(CommandType):
    def __init__(self):
        self.type:int = None


    def to_bytes(self):
        data = b""
        data += self.type.to_bytes(1, byteorder="big")

        return data


class CommandRGBStream(CommandType):
    def __init__(self):
        #the stream goes like this 

        # RGBRGBRGB...RGB
        # you get the point the RGB does for as many
        # leds as you have

        # each value is a byte 0-255
        # R - red
        # G - green
        # B - blue

        self.leds_number:int = None # 8 bytes
        self.stream:list[int] = None # 3 bytes x number of leds


    def to_bytes(self):
        data = b""

        data += self.leds_number.to_bytes(8, byteorder="big")
        if len(self.stream) > self.leds_number * 3:
            raise ValueError("Invalid RGB stream length")

        data += bytes(self.stream)

        return data


class Command:
    def __init__(self):
        self.type:int = None # 1 byte
        self.sequence_number:int = 0 # 8 bytes
        self.content:CommandType = None # range of bytes

    def to_bytes(self):
        data = b""

        data += self.type.to_bytes(1, byteorder="big")
        data += self.sequence_number.to_bytes(8, byteorder="big")

        if self.content:
            data += self.content.to_bytes()

        return data




class MessageTypes:
    command:int = 1
    information:int = 2



class MessageUDP:
    def __init__(self):
        self.type:int = None # this will contain 1 byte

        self.mac_address:int = None # this will contain 6 bytes
        self.device_name:str = None # this will contain 64 bytes

        self.is_encrypted:int = 0 # 1 byte, any thing above 0 is encreapted 
        self.content:Command = None # range of bytes containing bytes

    
    def to_bytes(self):
        data  = b""
        data += self.type.to_bytes(1, byteorder="big")
        data += self.mac_address.to_bytes(6, byteorder="big")
        data += self.device_name.encode("utf-8")[:64].ljust(64, b"\x00")
        data += self.is_encrypted.to_bytes(1, byteorder="big")
        if self.content:
            data += self.content.to_bytes()

        return data
        






