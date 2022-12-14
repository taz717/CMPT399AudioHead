import time
import serial
import speech_recognition as sr


def recognize_speech_from_mic(recognizer, microphone):
    """Transcribe speech from recorded from `microphone`.

    Returns a dictionary with three keys:
    "success": a boolean indicating whether or not the API request was
               successful
    "error":   `None` if no error occured, otherwise a string containing
               an error message if the API could not be reached or
               speech was unrecognizable
    "transcription": `None` if speech could not be transcribed,
               otherwise a string containing the transcribed text
    """
    # check that recognizer and microphone arguments are appropriate type
    if not isinstance(recognizer, sr.Recognizer):
        raise TypeError("`recognizer` must be `Recognizer` instance")

    if not isinstance(microphone, sr.Microphone):
        raise TypeError("`microphone` must be `Microphone` instance")

    # adjust the recognizer sensitivity to ambient noise and record audio
    # from the microphone
    with microphone as source:
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source)

    # set up the response object
    response = {"success": True, "error": None, "transcription": None}

    # try recognizing the speech in the recording
    # if a RequestError or UnknownValueError exception is caught,
    #     update the response object accordingly
    try:
        response["transcription"] = recognizer.recognize_google(audio)
    except sr.RequestError:
        # API was unreachable or unresponsive
        response["success"] = False
        response["error"] = "API unavailable"
    except sr.UnknownValueError:
        # speech was unintelligible
        response["error"] = "Unable to recognize speech"

    return response


def interpretCommand(command):
    if command == "f":
        ser.write(b"f")

    elif command == "b":
        ser.write(b"b")

    elif command == "l":
        ser.write(b"l")

    elif command == "r":
        ser.write(b"r")

    elif command == "s":
        ser.write(b"s")

    elif command == "p":
        ser.write(b"p")

    elif command == "x":
        ser.write(b"x")


if __name__ == "__main__":
    # set the list of words, maxnumber of guesses, and prompt limit
    SPEECH_TO_BIN = {
        "forward": "f",
        "forwards": "f",
        "backward": "b",
        "backwards": "b",
        "awkward": "b",
        "left": "l",
        "right": "r",
        "start": "s",
        "stop": "p",
        "reset": "x",
    }
    ser = serial.Serial("COM10", 9600, timeout=1)
    PROMPT_LIMIT = 100
    record = False
    recorded = []

    # create recognizer and mic instances
    recognizer = sr.Recognizer()
    microphone = sr.Microphone()

    # format the instructions string
    instructions = (
        "Try giving the bot commands\n"
        "You have the following commands:\n"
        "forward, backward, left, right\n"
    )

    # show instructions and wait 3 seconds before starting the game
    print(instructions)
    time.sleep(3)

    while True:
        # get the guess from the user
        # if a transcription is returned, break out of the loop and
        #     continue
        # if no transcription returned and API request failed, break
        #     loop and continue
        # if API request succeeded but no transcription was returned,
        #     re-prompt the user to say their guess again. Do this up
        #     to PROMPT_LIMIT times
        for j in range(PROMPT_LIMIT):
            # print("Guess {}. Speak!".format(i + 1))
            print("Talk now!")
            guess = recognize_speech_from_mic(recognizer, microphone)
            if guess["transcription"]:
                break
            if not guess["success"]:
                break
            print("I didn't catch that. What did you say?\n")

        # if there was an error, stop the game
        if guess["error"]:
            print("ERROR: {}".format(guess["error"]))
            break

        # show the user the transcription
        print("You said: {}".format(guess["transcription"]))

        try:
            command = f'{SPEECH_TO_BIN[guess["transcription"]]}'
            interpretCommand(command)

            print(bytes(f'{SPEECH_TO_BIN[guess["transcription"]]}', "utf-8"))
            data = ser.readline()
            print(data)
            time.sleep(5)

        except:
            print("ERROR: Unknown command")
