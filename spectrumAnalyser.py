import pyaudio
import struct # allows to unpack audio to integers instead of b'
import numpy as np
import matplotlib.pyplot as plt
from scipy.fftpack import fft

CHUNK = 1024 * 4 # 4096 -audio samples per frame ### CAN REDUCE THE MULTIPLICATION VALUE FOR A FASTER REFRESH
FORMAT = pyaudio.paInt16 # signed 16 bit string
CHANELS = 1 # input
RATE = 44100 # samples per second

p = pyaudio.PyAudio()
stream = p.open(
    format=FORMAT,
    channels=CHANELS,
    rate=RATE,
    input=True,
    output=True,
    frames_per_buffer=CHUNK
)

# Initial plot
fig, (ax1, ax2) = plt.subplots(2, figsize=(15, 8))

# var for plotting 
x = np.arange(0, 2 * CHUNK, 2)
x_fft = np.linspace(0, RATE, CHUNK)

#create line obj with random data
line, = ax1.plot(x, np.random.rand(CHUNK), 'r') # y data gets updated in loop so instantiate with random data
line_fft, = ax2.semilogx(x_fft, np.random.rand(CHUNK), '-')

# Format graph
ax1.set_title("Waveform")
ax2.set_title("FFT")

ax1.set_xlabel("Samples")
ax1.set_ylabel("Volume")
ax1.set_ylim(-6000, 6000)
# limit x axis
ax1.set_xlim(0, 2 * CHUNK)
ax2.set_xlim(20, RATE / 2) # 0 just discontinues 
fig.show()

while True:
    data = stream.read(CHUNK)
    data_int = struct.unpack(str(CHUNK) + 'h', data) #signed short 16 bit
    line.set_ydata(data_int)
    y_fft = fft(data_int)
    line_fft.set_ydata(np.abs(y_fft[0:CHUNK]) * 2 / (256 * CHUNK)) # slice chunk to get only first half + RESCALE: multiple by 2 then divide by amplitude of waveform then divide by number of bins/freqs in sepctrum
    fig.canvas.draw()
    fig.canvas.flush_events()

