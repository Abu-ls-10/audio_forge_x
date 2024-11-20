<template>
  <div class="file-panel">
    <h2>Sample Files</h2>
    <ul>
      <li v-for="file in sampleFiles" :key="file">{{ file }}</li>
    </ul>
  
    <input type="file" @change="onFileUpload" accept=".wav" />
    
    <!-- Mix button -->
    <button @click="onMixClick" class="mix-button">Mix!</button>
  </div>
</template>

<script lang="ts">
export default {
  props: {
    removeVocals: Boolean,
    volume: Number,
    echoDelay: Number,
    pitchShift: Number,
  },
  data() {
    return {
      sampleFiles: ['cartoon.wav', 'adventure.wav', 'music.wav'],
      selectedFile: null,
    };
  },
  methods: {
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
        // Prepare the data to send to the backend
        const data = {
          remvocals: this.removeVocals,
          volumeScale: this.volume,
          echoDelay: this.echoDelay,
          pitchShift: this.pitchShift,
        };

        // Example backend API call
        this.$axios.post('your-backend-endpoint', data)
          .then(response => {
            console.log('File mixed successfully:', response);
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
