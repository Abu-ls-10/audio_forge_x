from flask import Flask, request, jsonify, send_file
from flask_cors import CORS
import os
from werkzeug.utils import secure_filename
import audioforgex

app = Flask(__name__)
CORS(app)

UPLOAD_FOLDER = 'uploads'
PROCESSED_FOLDER = 'processed'

# Ensure directories exist
os.makedirs(UPLOAD_FOLDER, exist_ok=True)
os.makedirs(PROCESSED_FOLDER, exist_ok=True)

# Flask route to process the file
@app.route('/process_file', methods=['POST'])
def process_file():
    try:
        # Retrieve parameters from the request
        remove_vocals_flag = request.form.get('remVocals', type=int, default=0)
        volume_scale = request.form.get('volumeScale', type=float, default=1.0)
        echo_delay = request.form.get('echoDelay', type=int, default=0)
        pitch_shift = request.form.get('pitchShift', type=float, default=1.0)

        # Check and save uploaded file
        if 'file' not in request.files:
            return jsonify({'error': 'No file uploaded'}), 400

        file = request.files['file']
        if not file.filename.endswith('.wav'):
            return jsonify({'error': 'Invalid file format. Only WAV files are supported.'}), 400

        # Secure the file name and save it
        original_filename = secure_filename(file.filename)
        base_name, ext = os.path.splitext(original_filename)
        input_path = os.path.join(UPLOAD_FOLDER, original_filename)
        file.save(input_path)

        # Convert to canonical form if not already
        if audioforgex.is_canonical(input_path):
            canonical_path = input_path
        else:
            canonical_path = os.path.join(PROCESSED_FOLDER, f"{base_name}_canonical{ext}")
            audioforgex.convert_to_canonical(input_path, canonical_path)

        # Initialize the result path with the base name
        result_filename = base_name

        # Apply processing
        if remove_vocals_flag:
            result_filename += "_rm"
            processed_path = os.path.join(PROCESSED_FOLDER, f"{result_filename}{ext}")
            audioforgex.remove_vocals(canonical_path, processed_path)
            canonical_path = processed_path

        if pitch_shift != 1.0:
            pitch_vals = str(pitch_shift).replace(".", "p")
            result_filename += f"_{pitch_vals}"
            processed_path = os.path.join(PROCESSED_FOLDER, f"{result_filename}{ext}")
            audioforgex.shift_pitch(canonical_path, processed_path, pitch_shift)
            canonical_path = processed_path

        if echo_delay > 0 or volume_scale != 1.0:
            volume_str = str(volume_scale).replace(".", "p")
            result_filename += f"_{volume_str}v_{echo_delay}d"
            processed_path = os.path.join(PROCESSED_FOLDER, f"{result_filename}{ext}")
            audioforgex.add_echo(canonical_path, processed_path, echo_delay, volume_scale)

        # Send the processed file back
        return send_file(processed_path, as_attachment=True)

    except Exception as e:
        return jsonify({'error': str(e)}), 500

if __name__ == '__main__':
    app.run(debug=True)
