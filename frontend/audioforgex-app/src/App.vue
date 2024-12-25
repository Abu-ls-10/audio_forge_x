<template>
  <div class="app">
    <!-- Title and description centered at the top -->
    <div class="header">
      <h1>AudioForgeX</h1>
      <p>Transform your audio files with advanced effects and seamless controls.</p>
    </div>

    <!-- Main content -->
    <div class="container">
      <FilePanel
        :removeVocals="removeVocals"
        :volume="volume"
        :echoDelay="echoDelay"
        :pitchShift="pitchShift"
      />
      <div class="sliders">
        <Slider
          label="Volume Scale"
          :min="0.5"
          :max="5"
          :step="0.1"
          v-model="volume"
        />
        <Slider
          label="Echo Delay"
          :min="0"
          :max="12000"
          :step="10"
          v-model="echoDelay"
        />
        <Switch v-model="removeVocals" />
        <Slider
          label="Pitch Shift"
          :min="0.1"
          :max="3"
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
import Switch from './components/Switch.vue';

export default {
  components: {
    FilePanel,
    Slider,
    Switch,
  },
  data() {
    return {
      volume: 1,
      echoDelay: 1000,
      removeVocals: false,
      pitchShift: 1,
    };
  },
};
</script>

<style>
/* App container style */
.app {
  background-color: #121212;
  color: white;
  display: flex;
  flex-direction: column; /* Stack items vertically */
  align-items: center;
  justify-content: flex-start; /* Align items at the top */
  min-height: 100vh;
  font-family: 'Arial', sans-serif;
}

/* Header container for title and description */
.header {
  text-align: center; /* Center the text horizontally */
  margin-top: 20px; /* Add some space from the top */
  margin-bottom: 20px; /* Space between the header and the content */
  font-family: 'Orbitron', 'sans-serif';
  padding: 20px 10px 40px 10px;
}

h1 {
  margin: 0;
  font-size: 50px;
}

p {
  margin: 5px 0 0;
  font-size: 1.2em;
  padding-top: 10px;
}

/* Main content container */
.container {
  display: flex;
  justify-content: space-between;
  width: 80%;
}

/* Sliders container */
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
