<template>
  <div class="app">
    <div class="container">
      <FilePanel />
      <div class="sliders">
        <Slider
          label="Volume"
          :min="0"
          :max="50"
          :step="1"
          v-model="volume"
        />
        <Slider
          label="Echo Delay"
          :min="0"
          :max="60000"
          :step="10"
          v-model="echoDelay"
        />
        <Switch v-model="removeVocals" />
        <Slider
          label="Pitch Shift"
          :min="0.1"
          :max="5"
          :step="0.1"
          v-model="pitchShift"
        />
      </div>
    </div>
  </div>
</template>

<script lang="ts">
import FilePanel from './components/FilePanel.vue';
import Slider from './components/Slider.vue';
import Switch from './components/Switch.vue';  // Importing Switch component

export default {
  components: {
    FilePanel,
    Slider,
    Switch,  // Registering Switch component
  },
  data() {
    return {
      volume: 1,
      echoDelay: 1000,
      removeVocals: false,  // Initialize the removeVocals data here
      pitchShift: 1,
    };
  },
};
</script>

<style>
.app {
  background-color: #121212;
  color: white;
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  font-family: 'Arial', sans-serif;
}

.container {
  display: flex;
  justify-content: space-between;
  width: 80%;
}

.sliders {
  display: flex;
  flex-direction: row; /* Change this from column to row */
  justify-content: space-evenly;
  align-items: center;
  width: 80%;
  margin-left: 20px;
}

label {
  color: white;
  margin-bottom: 10px;
}
</style>
