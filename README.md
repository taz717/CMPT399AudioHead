# CMPT399SpeechBot
## Purpose
To set up a Zumo32 using audio inputs to issue commands for
movements and information for reseting position later on

## Libraries used
### Python
time                     https://docs.python.org/3/library/time.html
serial                   https://pyserial.readthedocs.io/en/latest/shortintro.html
speech_recognition       https://pypi.org/project/SpeechRecognition/
### C++/Arduino
Radiohead                https://www.airspayce.com/mikem/arduino/RadioHead/
Zumo32 Standard Library  https://pololu.github.io/zumo-32u4-arduino-library/

## How to run
### Arduino Side
Set up bot according to diagrams

Upload reciever code to Zumo 32

Upload transmitter code to Arduino

### Python Side

pip install serial

pip install SpeechRecognition

Run code

Issue commands
