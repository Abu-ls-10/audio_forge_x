<template>
  <div class="slider-container">
    <label>{{ label }}</label>
    <div class="slider">
      <span class="value">{{ modelValue }}</span>
      <input
        type="range"
        :min="min"
        :max="max"
        :step="step"
        :value="modelValue"
        @input="onInput"
        class="slider-input"
        orientation="vertical"
      />
    </div>
  </div>
</template>

<script lang="ts">
export default {
  props: {
    label: String,
    min: Number,
    max: Number,
    step: Number,
    modelValue: Number,
  },
  methods: {
    onInput(event: Event) {
      const value = (event.target as HTMLInputElement).valueAsNumber;
      this.$emit('update:modelValue', value); // Emit the updated value to the parent
    },
  },
};
</script>

<style scoped>
/* Container for alignment and styling */
.slider-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  margin: 20px;
}

/* Label styling */
label {
  color: white;
  margin-bottom: 10px;
  font-family: 'Orbitron', sans-serif;
}

/* Slider styling */
.slider {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 300px;
  position: relative;
}

/* Value display above the slider */
.value {
  margin-bottom: 10px;
  color: white;
  font-size: 1.2em;
  font-family: 'Orbitron', sans-serif;
}

/* Main slider track */
.slider-input {
  -webkit-appearance: none;
  width: 60px;
  height: 290px;
  background: #444;
  border-radius: 50px 50px 10px 10px;
  outline: none;
  transform: rotate(180deg);
  box-shadow: inset 1px 1px 5px rgba(0, 0, 0, 0.3), inset -1px -1px 5px rgba(255, 255, 255, 0.1);
  position: relative;
}

/* Vertical scale lines on the track for a ruler-like effect */
.slider-input::before {
  content: "";
  position: absolute;
  width: 100%;
  height: 100%;
  background: repeating-linear-gradient(
    to bottom,
    #666,
    #666 1px,
    transparent 1px,
    transparent 20px
  );
  opacity: 0.6;
}

/* Thumb styling for a 3D, futuristic look */
.slider-input::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 60px;
  height: 30px;
  background: #5f27cd;
  border: solid 2px #444;
  border-radius: 50%;
  box-shadow: 0px 0px 8px rgba(0, 0, 0, 0.5), inset 0px 2px 3px rgba(255, 255, 255, 0.6);
  cursor: pointer;
  transition: background-color 0.3s, transform 0.2s;
}

.slider-input::-webkit-slider-thumb:hover {
  background-color: #ff5f5f; /* Match the active color from Switch.vue */
}

.slider-input::-moz-range-thumb {
  width: 60px;
  height: 30px;
  background: #5f27cd;
  border: solid 2px #444;
  border-radius: 50%;
  box-shadow: 0px 0px 8px rgba(0, 0, 0, 0.5), inset 0px 2px 3px rgba(255, 255, 255, 0.6);
  cursor: pointer;
  transition: background-color 0.3s, transform 0.2s;
}

.slider-input::-moz-range-thumb:hover {
  background-color: #ff5f5f;
}

.slider-input::-ms-thumb {
  width: 60px;
  height: 30px;
  background: #5f27cd;
  border: solid 2px #444;
  border-radius: 50%;
  box-shadow: 0px 0px 8px rgba(0, 0, 0, 0.5), inset 0px 2px 3px rgba(255, 255, 255, 0.6);
  cursor: pointer;
  transition: background-color 0.3s, transform 0.2s;
}

.slider-input::-ms-thumb:hover {
  background-color: #ff5f5f;
}
</style>
