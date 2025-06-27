<template>
  <div class="file-panel">
    <h2>Sample Files</h2>
    <div v-for="filename in sampleFiles" :key="filename" class="file-option" @click="selectFile(filename)">
      {{ filename }}
    </div>
  
    <input type="file" @change="onFileUpload" accept=".wav" />
    
    <!-- Mix button -->
    <button @click="onMixClick" class="mix-button">Mix!</button>
  </div>
</template>

<script lang="ts">
import axios from 'axios';

function generateFileName(selectedFile: File, removeVocals: boolean, volume: number, delay: number, pitchShift: number): string {
    // Initialize the filename with the selected file name
    let fileName = selectedFile.name.replace(/\.[^/.]+$/, '');

    // Apply "_rm" if vocals are to be removed
    if (removeVocals) {
        fileName += "_rm";
    }

    // Add pitch shift "_{a}p{b}"
    const pitchShiftBeforeDecimal = Math.floor(pitchShift);
    const pitchShiftAfterDecimal = Math.round((pitchShift - pitchShiftBeforeDecimal) * 10);
    fileName += `_${pitchShiftBeforeDecimal}p${pitchShiftAfterDecimal}`;

    // Add volume and delay "_{a}p{b}v_{x}d"
    const volumeBeforeDecimal = Math.floor(volume);
    const volumeAfterDecimal = Math.round((volume - volumeBeforeDecimal) * 10);
    fileName += `_${volumeBeforeDecimal}p${volumeAfterDecimal}v_${delay}d`;

    // Return the generated filename
    return fileName += ".wav";
}

export default {
  props: {
    removeVocals: {
      type: Boolean,
      required: true,
    },
    volume: {
      type: Number,
      required: true,
    },
    echoDelay: {
      type: Number,
      required: true,
    },
    pitchShift: {
      type: Number,
      required: true,
    },
  },

  data() {
    return {
      sampleFiles: ['cartoon.wav', 'door.wav', 'audio.wav'],
      selectedFile: null as File | null,
    };
  },
  methods: {
    async selectFile(filename: string) {
      const fileUrl = `http://localhost:5000/sample_audios/${filename}`;
      try {
        // Fetch the file from the URL
        const response = await fetch(fileUrl);

        // Check if the response is OK
        if (!response.ok) {
          throw new Error(`Failed to fetch file: ${response.statusText}`);
        }

        // Convert the response into a Blob
        const blob = await response.blob();

        // Ensure the file is a WAV file
        if (blob.type === 'audio/wav') {
          // Create a File object
          const file = new File([blob], filename, { type: blob.type });

          // Set the selected file
          this.selectedFile = file;
          console.log('File selected:', file.name);
        } else {
          console.error('Selected file is not an audio/wav file');
        }
      } catch (error) {
        console.error('Error selecting file:', error);
      }
    },
    onFileUpload(event: Event) {
      const file = (event.target as HTMLInputElement).files?.[0];
      if (file && file.type === 'audio/wav') {
        // Handle file upload (e.g., send to backend or process)
        this.selectedFile = file;
        console.log('File selected:', file.name);
      } else {
        alert('Please upload a valid WAV file');
      }
    },
    onMixClick() {
      if (this.selectedFile) {
        // Log processing vals
        console.log("Processing values:", this.volume, this.echoDelay, this.removeVocals, this.pitchShift);

        // Prepare the data to send to the backend (removing vocals, volume, echo, pitch, etc.)
        const data = new FormData();
        data.append('file', this.selectedFile);
        data.append('remVocals', this.removeVocals ? '1' : '0'); // Convert Boolean to integer
        data.append('volumeScale', this.volume.toString());
        data.append('echoDelay', this.echoDelay.toString());
        data.append('pitchShift', this.pitchShift.toString());

        // Backend API request
        axios.post('http://localhost:5000/process_file', data, { responseType: 'arraybuffer' })
          .then(response => {
            console.log('File mixed successfully:', response);
            // Optionally handle the processed file (e.g., download or play it)

            // Extract the filename from the Content-Disposition header if available
            const contentDisposition = response.headers['content-disposition'];

            // Log the Content-Disposition header to check if it's present and formatted correctly
            // console.log('Content-Disposition:', contentDisposition);

            let processed_filename = generateFileName(this.selectedFile!, this.removeVocals, this.volume, this.echoDelay, this.pitchShift);
            const filenameMatch = contentDisposition?.match(/filename="([^"]+)"/);
            const filename = filenameMatch ? filenameMatch[1] : processed_filename;

            // Create a URL for the returned blob
            const blob = new Blob([response.data], { type: 'audio/wav' });
            const downloadUrl = URL.createObjectURL(blob);

            // Create a link element, set its href to the blob URL, and trigger a click
            const link = document.createElement('a');
            link.href = downloadUrl;
            link.download = filename; // Use the extracted filename
            document.body.appendChild(link);
            link.click();
            document.body.removeChild(link);

            // Revoke the object URL to free memory
            URL.revokeObjectURL(downloadUrl);
          })
          .catch(error => {
            console.error('Error mixing file:', error);
          });
      } else {
        alert('Please upload a file first');
      }
    }
  },
};
</script>

<style scoped>
.file-panel {
  width: 250px;
  background-color: #222;
  color: white;
  padding: 20px;
  border-radius: 20px;
  font-family: 'Orbitron', 'sans-serif';
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: flex-start;
}

.file-option {
  cursor: pointer;
  padding: 8px;
  margin: 5px;
  background-color: #333;
  border-radius: 5px;
  display: inline-block;
  text-align: center;
  width: calc(100% - 20px); /* Make width smaller than the parent by adjusting the padding */
  box-sizing: border-box;  /* Ensures padding and border are included in width */
}

.file-option:hover {
  background-color: #444;
}

.mix-button {
  margin-top: 30px;
  padding: 12px 25px;
  height: 3em;
  width: 12em;
  background: linear-gradient(135deg, #5f27cd, #4e3cf5, #00f1ff); /* Gradient from purple to cyan */
  color: white;
  border-radius: 12px;
  cursor: pointer;
  font-size: 18px;
  transition: background-color 0.3s ease, transform 0.1s ease;
  display: flex;
  align-items: center;
  justify-content: center;
  font-family: 'Orbitron', 'sans-serif';
  text-align: center;
}

.mix-button:hover {
  background: linear-gradient(135deg, #7e44eb, #00f1ff); /* Slightly lighter purple on hover */
}

.mix-button:active {
  background: linear-gradient(135deg, #4e1ea1, #00f1ff); /* Darker purple when active */
  transform: scale(0.98); /* Slight shrink effect when clicked */
}
</style>
