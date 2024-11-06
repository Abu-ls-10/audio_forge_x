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
.slider-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  margin: 20px;
}

label {
  color: white;
  margin-bottom: 10px;
}

.slider {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: space-between;
}

.slider-input {
  -webkit-appearance: none;
  width: 10px;
  height: 200px;
  background: #ddd;
  border-radius: 5px;
  outline: none;
  transform: rotate(180deg);
}

.slider-input::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 20px;
  height: 20px;
  background: #5f27cd;
  border-radius: 50%;
  cursor: pointer;
}

.value {
  margin-bottom: 10px;
  color: white;
  font-size: 1.2em;
}
</style>
