from scipy.io.wavfile import read
import numpy as np
import pyaudio
import wave

# Purposefully keeping these up here because I don't want ppl modifying them
FORMAT = pyaudio.paInt16
CHANNELS = 1
RATE = 48000
CHUNK = 512
RECORD_SECONDS = 5


class CrossCorrelator:
    def __init__(self):
        self.audio = pyaudio.PyAudio()

        # programatically get the left/right indexes, assumes left was plugged in first
        self.indexes = []

        info = audio.get_host_api_info_by_index(0)
        numdevices = info.get("deviceCount")

        for i in range(0, numdevices):
            # check all devices with a nonzero number of channels and keywords in their name
            if (
                self.audio.get_device_info_by_host_api_device_index(0, i).get(
                    "maxInputChannels"
                )
            ) and (
                "USB Composite Device: Audio"
                in self.audio.get_device_info_by_host_api_device_index(0, i).get("name")
            ):
                self.indexes.append(i)

        if len(self.indexes) != 2:
            raise SystemExit("Incorrect number of microphones, I exit")

    def cross_correlate(self):
        # start recording
        left_stream = self.audio.open(
            format=FORMAT,
            channels=CHANNELS,
            rate=RATE,
            input=True,
            frames_per_buffer=CHUNK,
            input_device_index=self.indexes[0],
        )

        right_stream = self.audio.open(
            format=FORMAT,
            channels=CHANNELS,
            rate=RATE,
            input=True,
            frames_per_buffer=CHUNK,
            input_device_index=self.indexes[1],
        )

        left_frames = []
        right_frames = []

        for i in range(0, int(RATE / CHUNK * RECORD_SECONDS)):
            # It overflows, hopefully just ignoring it is fine
            left_data = left_stream.read(CHUNK, exception_on_overflow=False)
            right_data = right_stream.read(CHUNK, exception_on_overflow=False)
            left_frames.append(left_data)
            right_frames.append(right_data)

        # stop recording
        left_stream.stop_stream()
        right_stream.stop_stream()
        left_stream.close()
        right_stream.close()
        self.audio.terminate()

        # create the output files
        waveFile = wave.open("left.wav", "wb")
        waveFile.setnchannels(CHANNELS)
        waveFile.setsampwidth(self.audio.get_sample_size(FORMAT))
        waveFile.setframerate(RATE)
        waveFile.writeframes(b"".join(left_frames))
        waveFile.close()

        waveFile = wave.open("right.wav", "wb")
        waveFile.setnchannels(CHANNELS)
        waveFile.setsampwidth(self.audio.get_sample_size(FORMAT))
        waveFile.setframerate(RATE)
        waveFile.writeframes(b"".join(right_frames))
        waveFile.close()

        # read in that data
        sampling_rate, left = read("left.wav")
        _, right = read("right.wav")

        # run correlation
        corr = np.fft.ifft(
            np.fft.fft(left, len(left) + len(right))
            * np.fft.fft(right[::-1], len(right) + len(right))
        )

        # determine direction
        max = np.argmax(corr)
        adjusted_max = max - (len(corr) / 2)
        delay = adjusted_max * (1 / sampling_rate)

        if delay < 0:
            return b"LEFT"
        else:
            return b"RIGHT"
