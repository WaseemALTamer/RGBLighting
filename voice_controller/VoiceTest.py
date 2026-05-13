from vosk import Model, KaldiRecognizer
import sounddevice as sd
import RGBLightingPY.MessageBuilder
import queue
import json


commands = [
    "lights on",
    "lights off",
    "red",
    "blue",
    "command",
    "down",
    "up",
    "zero",
    "one",
    "two",
    "three",
    "four",
    "five",
    "six",
    "seven",
    "eight",
    "nine",
    "option",
    "jarvis"
]





# Load model
model = Model("model")
recognizer = KaldiRecognizer(model, 16000, json.dumps(commands))

# Audio queue
q = queue.Queue()

def callback(indata, frames, time, status):
    q.put(bytes(indata))

def main():
    print("Listening... speak into your mic")
    current_brightness = 0
    with sd.RawInputStream(
        samplerate=16000,
        blocksize=800,
        dtype='int16',
        channels=1,
        callback=callback
    ):
        while True:
            data = q.get()

            if recognizer.AcceptWaveform(data):
                result = json.loads(recognizer.Result())
                text:str = result.get("text", "")
                

                if text:
                    content = text.split(" ")
                    print(content)

                    if "jarvis" in content:
                        if "lights" in content:
                            if "on" in content:
                                current_brightness = 0.3
                                MessageManager.set_setting(current_brightness)
                                print(current_brightness)
                                continue
                            if "off" in content:
                                current_brightness = 0
                                MessageManager.set_setting(current_brightness)
                                print(current_brightness)
                                continue
                            if "up" in content:
                                current_brightness += 0.1
                                if current_brightness > 1:
                                    current_brightness = 1
                                MessageManager.set_setting(current_brightness)
                                print(current_brightness)
                                continue
                            if "down" in content:
                                current_brightness -= 0.1
                                if current_brightness < 0:
                                    current_brightness = 0
                                MessageManager.set_setting(current_brightness)
                                print(current_brightness)
                                continue

                            if "option" in content:
                                if "one" in content:
                                    MessageManager.set_setting(1)
                                    MessageManager.set_color([255,128,0] * 150)
                                    current_brightness = 1
                                if "two" in content:
                                    MessageManager.set_setting(0.1, 3)
                                    MessageManager.set_color([255,0,255])
                                    MessageManager.set_sequence(3)
                                    current_brightness = 0.1


                            

if __name__ == "__main__":
    main()