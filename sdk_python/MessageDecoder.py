# this file is reponsible for decoding the messages it doesnt
# provide any logic it is only a tool not a system


from .Structures import *



class MessageDecoder:
    def __init__(self):
        pass


    def decode_message(self, payload:bytes) -> MessageUDP:
        if len(payload) < 72:
            return None

        index = 0

        message = MessageUDP()


        message.type = payload[index]
        index += 1


        message.mac_address = int.from_bytes(payload[index:index+6], "big")
        index += 6


        raw_name = payload[index:index+64]
        message.device_name = raw_name.split(b'\x00', 1)[0].decode(errors="ignore")
        index += 64


        message.is_encrypted = payload[index]
        index += 1


        content = payload[index:]


        if message.type == MessageTypes.command:
            message.content = self.decode_command(content)

        elif message.type == MessageTypes.information:
            message.content = self.decode_information(content)

        elif message.type == MessageTypes.online:
            message.content = self.decode_online(content)

        return message




    def decode_command(self, payload:bytes):
        pass

    def decode_information(self, payload:bytes):
        pass

    def decode_online(self, payload:bytes):
        if len(payload) < 8:
            return None

        online = Online()
        online.led_number = int.from_bytes(payload[0:8], "big")

        return online

