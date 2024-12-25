import os
import wave
import numpy as np
from ctypes import CDLL, c_char_p, c_int, c_float
from scipy.io import wavfile
from scipy.signal import resample

# Base directory containing the subdirectories for shared libraries
base_dir = os.path.dirname(__file__)

# Load shared libraries with their full paths
remvocals_lib = CDLL(os.path.join(base_dir, 'audio_mixing', 'remvocals', 'remvocals.so'))
addecho_lib = CDLL(os.path.join(base_dir, 'audio_mixing', 'addecho', 'addecho.so'))
shiftpitch_lib = CDLL(os.path.join(base_dir, 'audio_mixing', 'shift_pitch', 'shift_pitch.so'))

# Wrapper functions using ctypes
def add_echo(input_file, output_file, delay, volume_scale=1.0):
    """Wrapper for addecho C program."""
    addecho_lib.add_echo.argtypes = [c_char_p, c_char_p, c_int, c_float]
    addecho_lib.add_echo.restype = c_int
    result = addecho_lib.add_echo(input_file.encode('utf-8'), 
                                  output_file.encode('utf-8'), 
                                  delay, 
                                  float(volume_scale))
    if result != 0:
        raise RuntimeError("Error adding echo to the file.")


def remove_vocals(input_file, output_file):
    """Wrapper for remvocals C program."""
    remvocals_lib.remove_vocals.argtypes = [c_char_p, c_char_p]
    remvocals_lib.remove_vocals.restype = c_int
    result = remvocals_lib.remove_vocals(input_file.encode('utf-8'), output_file.encode('utf-8'))
    if result != 0:
        raise RuntimeError("Error removing vocals from the file.")

def shift_pitch(input_file, output_file, pitch_factor=1.0):
    """Wrapper for shift_pitch C program."""
    shiftpitch_lib.shift_pitch.argtypes = [c_char_p, c_char_p, c_float]
    shiftpitch_lib.shift_pitch.restype = c_int
    result = shiftpitch_lib.shift_pitch(input_file.encode('utf-8'), output_file.encode('utf-8'), pitch_factor)
    if result != 0:
        raise RuntimeError("Error shifting pitch of the file.")

def is_canonical(file_path):
    """
    Checks if the given WAV file is in canonical form.
    Canonical form criteria:
    - PCM format (uncompressed)
    - 16-bit sample depth
    - Sample rate of 44100 Hz
    - Mono or Stereo (1 or 2 channels)

    :param file_path: Path to the WAV file
    :return: True if the file is in canonical form, otherwise False
    """
    try:
        with wave.open(file_path, 'rb') as wav_file:
            # Check audio format
            if wav_file.getcomptype() != 'NONE':  # PCM WAV files have 'NONE' as compression type
                return False
            
            # Check bit depth (sample width)
            if wav_file.getsampwidth() != 2:  # 2 bytes = 16 bits
                return False
            
            # Check sample rate
            if wav_file.getframerate() != 44100:
                return False
            
            # Check number of channels
            if wav_file.getnchannels() not in (1, 2):  # Mono or Stereo
                return False
            
        return True
    except wave.Error as e:
        print(f"Error reading WAV file: {e}")
        return False


def convert_to_canonical(input_path, output_path, target_rate=44100):
    """
    Converts a non-canonical WAV file to canonical form.
    Canonical form:
    - PCM format
    - 16-bit sample depth
    - Sample rate of 44100 Hz
    - Mono or Stereo (preserves original number of channels)

    :param input_path: Path to the input WAV file
    :param output_path: Path to save the canonical WAV file
    :param target_rate: Desired sample rate (default 44100 Hz)
    """
    try:
        # Read the input WAV file
        rate, data = wavfile.read(input_path)
        original_dtype = data.dtype
        
        # Ensure the data is in the correct range for processing
        if data.dtype not in [np.int16, np.int32, np.float32]:
            raise ValueError("Unsupported WAV data type.")
        
        # Resample if the sample rate is not target_rate
        if rate != target_rate:
            num_samples = int(len(data) * target_rate / rate)
            data = resample(data, num_samples).astype(np.int16)

        # Convert to 16-bit if necessary
        if original_dtype != np.int16:
            if data.dtype == np.float32:  # Scale float32 to int16
                data = (data * 32767).astype(np.int16)
            else:  # Ensure other types are converted safely
                data = data.astype(np.int16)

        # Write the canonical WAV file
        wavfile.write(output_path, target_rate, data)
        print(f"File converted to canonical form and saved as {output_path}")
    except Exception as e:
        print(f"Error converting file: {e}")

# Example usage
if __name__ == "__main__":
    input_file = "backend/audios/audio.wav"
    file_name = os.path.splitext(os.path.basename(input_file))[0]
    output_file = "backend/audios/" + file_name + "_canonical.wav"

    # Check if the input file is canonical
    if is_canonical(input_file):
        print("The file is already in canonical form.")
    else:
        print("The file is not in canonical form. Converting...")
        convert_to_canonical(input_file, output_file)
