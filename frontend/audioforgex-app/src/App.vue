<template>
  <div class="app-container">
    <!-- Sidebar -->
    <div class="sidebar">
      <h2>Sample Files</h2>
      <div class="file-list">
        <div v-for="(file, index) in sampleFiles" :key="index" class="file-item">
          <button @click="loadFile(file)">{{ file }}</button>
        </div>
      </div>
      <hr />
      <h2>Upload Your WAV</h2>
      <input type="file" @change="handleFileUpload" accept=".wav" />
    </div>

    <!-- Main Section with Sliders -->
    <div class="main-content">
      <div class="slider-container">
        <h3>Volume Scale</h3>
        <vue-slider v-model="volume" :min="0" :max="50" :vertical="true" />
      </div>

      <div class="slider-container">
        <h3>Echo Delay</h3>
        <vue-slider v-model="echoDelay" :min="0" :max="60000" :vertical="true" />
      </div>

      <div class="slider-container">
        <h3>Remove Vocals</h3>
        <label class="switch">
          <input type="checkbox" v-model="removeVocals" />
          <span class="slider round"></span>
        </label>
      </div>

      <div class="slider-container">
        <h3>Pitch Shift</h3>
        <vue-slider v-model="pitchShift" :min="0.1" :max="5" :vertical="true" />
      </div>

      <button @click="processFile">Process</button>
    </div>
  </div>
</template>

<script>
import VueSlider from 'vue-slider-component';

export default {
  components: {
    VueSlider
  },
  data() {
    return {
      sampleFiles: ["cartoon.wav", "audio_sample_2.wav", "audio_sample_3.wav"], // Example samples
      volume: 1, 
      echoDelay: 1000, 
      removeVocals: false, 
      pitchShift: 1, 
      selectedFile: null
    };
  },
  methods: {
    loadFile(file) {
      // Load and process the selected sample file
      this.selectedFile = file;
    },
    handleFileUpload(event) {
      const file = event.target.files[0];
      if (file && file.type === "audio/wav") {
        this.selectedFile = file.name;
      } else {
        alert("Please upload a WAV file.");
      }
    },
    processFile() {
      console.log("Processing file:", this.selectedFile);
      console.log("Volume:", this.volume);
      console.log("Echo Delay:", this.echoDelay);
      console.log("Remove Vocals:", this.removeVocals);
      console.log("Pitch Shift:", this.pitchShift);
      // Call backend API for processing
    }
  }
};
</script>

<style scoped>
.app-container {
  display: flex;
  height: 100vh;
  background-color: #121212;
  color: #fff;
}

.sidebar {
  width: 250px;
  background-color: #1d1d1d;
  padding: 20px;
}

.sidebar h2 {
  color: #8e2de2; /* Sci-fi purple */
}

.file-list {
  margin-top: 10px;
}

.file-item {
  margin: 10px 0;
}

.file-item button {
  background-color: #292b2c;
  color: #fff;
  border: none;
  padding: 10px;
  cursor: pointer;
  transition: background-color 0.3s;
}

.file-item button:hover {
  background-color: #5d5d5d;
}

.main-content {
  display: flex;
  flex-wrap: wrap;
  justify-content: space-evenly;
  align-items: center;
  padding: 20px;
  flex-grow: 1;
}

.slider-container {
  margin: 20px;
  text-align: center;
  color: #fff;
}

.vue-slider {
  height: 200px;
}

h3 {
  margin-bottom: 10px;
}

.switch {
  position: relative;
  display: inline-block;
  width: 34px;
  height: 20px;
}

.switch input {
  opacity: 0;
  width: 0;
  height: 0;
}

.slider {
  position: absolute;
  cursor: pointer;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: #ccc;
  transition: 0.4s;
  border-radius: 50px;
}

.slider:before {
  position: absolute;
  content: "";
  height: 12px;
  width: 12px;
  border-radius: 50px;
  left: 4px;
  bottom: 4px;
  background-color: white;
  transition: 0.4s;
}

input:checked + .slider {
  background-color: #4caf50; /* Green when active */
}

input:checked + .slider:before {
  transform: translateX(14px);
}

button {
  background-color: #8e2de2; /* Sci-fi purple */
  color: #fff;
  padding: 10px 20px;
  border: none;
  cursor: pointer;
  font-size: 18px;
  transition: background-color 0.3s;
}

button:hover {
  background-color: #7a1bc9;
}
</style>
