<template>
    <div class="file-panel">
      <h2>Sample Files</h2>
      <ul>
        <li v-for="file in sampleFiles" :key="file">{{ file }}</li>
      </ul>
  
      <input type="file" @change="onFileUpload" accept=".wav" />
    </div>
  </template>
  
  <script lang="ts">
  export default {
    data() {
      return {
        sampleFiles: ['cartoon.wav', 'adventure.wav', 'music.wav'],
      };
    },
    methods: {
      onFileUpload(event: Event) {
        const file = (event.target as HTMLInputElement).files?.[0];
        if (file && file.type === 'audio/wav') {
          // Handle file upload (e.g., send to backend or process)
          console.log('File selected:', file.name);
        } else {
          alert('Please upload a valid WAV file');
        }
      },
    },
  };
  </script>
  
  <style scoped>
  .file-panel {
    width: 250px;
    background-color: #222;
    color: white;
    padding: 20px;
    border-radius: 10px;
  }
  </style>
  