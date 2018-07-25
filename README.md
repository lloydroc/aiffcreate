# aiffcreate
simple c project that runs on macOS to create aiff files using the audio framework. Running the code will create an AIFF file with a tone approximately at 440Hz.

# compiling
`make`

# running
`./aiffcreate`

# audio file background

    A good link of the [aiff file format](http://paulbourke.net/dataformats/audio/aiff11.gif)

    - A channel is a discrete track of monophonic audio. A monophonic stream has one channel; a stereo stream has two channels.
    - A sample is single numerical value for a single audio channel in an audio stream.
    - A frame is a collection of time-coincident samples. For instance, a linear PCM stereo sound file has two samples per frame, one for the left channel and one for the right channel.
    - A packet is a collection of one or more contiguous frames. A packet defines the smallest meaningful set of frames for a given audio data format, and is the smallest data unit for which time can be measured. In linear PCM audio, a packet holds a single frame. In compressed formats, it typically holds more; in some formats, the number of frames per packet varies.
    - The sample rate for a stream is the number of frames per second of uncompressed (or, for compressed formats, the equivalent in decompressed) audio.
