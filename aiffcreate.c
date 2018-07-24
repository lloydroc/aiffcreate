#include <string.h>
#include <math.h>
#include "CoreAudio/CoreAudio.h"
#include "CoreAudio/CoreAudioTypes.h"
#include "AudioToolbox/AudioToolbox.h"
#include "AudioToolbox/AudioFile.h"

CFURLRef MakeUrl(const char *cstr);
void CheckError(OSStatus res);

AudioStreamBasicDescription asbd;

AudioFileID audioFile;
OSStatus res;

void CheckError(OSStatus result) {
  if (result == noErr) return;
  switch(result) {
    case kAudioFileUnspecifiedError:
      printf("kAudioFileUnspecifiedError");
      break;
    case kAudioFileUnsupportedFileTypeError:
      printf("kAudioFileUnsupportedFileTypeError");
      break;
    case kAudioFileUnsupportedDataFormatError:
      printf("kAudioFileUnsupportedDataFormatError");
      break;
    case kAudioFileUnsupportedPropertyError:
      printf("kAudioFileUnsupportedPropertyError");
      break;
    case kAudioFileBadPropertySizeError:
      printf("kAudioFileBadPropertySizeError");
      break;
    case kAudioFilePermissionsError:
      printf("kAudioFilePermissionsError");
      break;
    case kAudioFileNotOptimizedError:
      printf("kAudioFileNotOptimizedError");
      break;
    case kAudioFileInvalidChunkError:
      printf("kAudioFileInvalidChunkError");
      break;
    case kAudioFileDoesNotAllow64BitDataSizeError:
      printf("kAudioFileDoesNotAllow64BitDataSizeError");
      break;
    case kAudioFileInvalidPacketOffsetError:
      printf("kAudioFileInvalidPacketOffsetError");
      break;
    case kAudioFileInvalidFileError:
      printf("kAudioFileInvalidFileError");
      break;
    case kAudioFileOperationNotSupportedError:
      printf("kAudioFileOperationNotSupportedError");
      break;
    case kAudioFileNotOpenError:
      printf("kAudioFileNotOpenError");
      break;
    case kAudioFileEndOfFileError:
      printf("kAudioFileEndOfFileError");
      break;
    case kAudioFilePositionError:
      printf("kAudioFilePositionError");
      break;
    case kAudioFileFileNotFoundError:
      printf("kAudioFileFileNotFoundError");
      break;
    default:
      printf("unknown error");
      break;
  }
  exit(result);
}

CFURLRef MakeUrl(const char *cstr) {
  CFStringRef path = CFStringCreateWithCString(0, cstr, kCFStringEncodingUTF8);
  CFURLRef url = CFURLCreateWithFileSystemPath(NULL, path, 0, false);
  CFRelease(path);
  return url;
}

int main() {
  double sampleRate = 44100.0;
  double duration = 10.0;
  long nSamples = (long)(sampleRate * duration);

  memset(&asbd, 0, sizeof(asbd));
  // Format struct for 1 channel, 16 bit PCM audio
  asbd.mSampleRate = sampleRate;
  asbd.mFormatID = kAudioFormatLinearPCM;
  asbd.mFormatFlags = kAudioFormatFlagIsBigEndian | kAudioFormatFlagIsSignedInteger;
  asbd.mBitsPerChannel = 16;
  asbd.mChannelsPerFrame = 1;
  asbd.mFramesPerPacket = 1;
  asbd.mBytesPerFrame = 2;
  asbd.mBytesPerPacket = 2;

  CFURLRef url = MakeUrl("hello.aiff");
  res = AudioFileCreateWithURL(url, kAudioFileAIFFType, &asbd,
      kAudioFileFlags_EraseFile, &audioFile);

  CheckError(res);

  UInt32 numBytes = 2;
  int freq = 100;
  for (int i=0; i<nSamples; i++) {
    int x = (i % freq);
    double angle = 2.0*3.1459*x/freq;
    double s = 32767*sin(angle);
    SInt16 sample = (SInt16) s;
    sample = OSSwapHostToBigInt16(sample);
    res = AudioFileWriteBytes(audioFile, false, i*2, &numBytes, &sample);
    CheckError(res);
  }

  res = AudioFileClose(audioFile);
  CheckError(res);

  exit(0);
}
