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
        :style="{ background: trackBackground }"
        orientation="vertical"
      />
    </div>
  </div>
</template>

<script lang="ts">
export default {
  props: {
    label: {
      type: String,
      required: true,
    },
    min: {
      type: Number,
      required: true,
    },
    max: {
      type: Number,
      required: true,
    },
    step: {
      type: Number,
      required: true,
    },
    modelValue: {
      type: Number,
      required: true,
    },
  },

  data() {
    return {
      initialValue: this.modelValue, // Store the initial/default value
    };
  },
  computed: {
    trackBackground() {
      const minPercent = ((this.min - this.min) / (this.max - this.min)) * 100;
      // const maxPercent = ((this.max - this.min) / (this.max - this.min)) * 100;
      const initialPercent = ((this.initialValue - this.min) / (this.max - this.min)) * 100;
      const currentPercent = ((this.modelValue - this.min) / (this.max - this.min)) * 100;

      if (this.modelValue >= this.initialValue) {
        // Moving upward from the initial value
        return `linear-gradient(
          to right,
          #333 ${minPercent}%,
          #333 ${initialPercent}%,
          #00f1ff ${initialPercent}%,
          #6a0dad ${currentPercent}%,
          #333 ${currentPercent}%
        )`;
      } else {
        // Moving downward from the initial value
        return `linear-gradient(
          to right,
          #333 ${minPercent}%,
          #333 ${currentPercent}%,
          #6a0dad ${currentPercent}%,
          #00f1ff ${initialPercent}%,
          #333 ${initialPercent}%
        )`;
      }
    },
  },
  methods: {
    onInput(event: Event) {
      const value = (event.target as HTMLInputElement).valueAsNumber;
      this.$emit('update:modelValue', value);
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
  height: 340px;
}

/* Label styling */
label {
  color: white;
  margin-bottom: 10px;
  font-family: 'Orbitron', sans-serif;
  text-align: center;
}

/* Slider styling */
.slider {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  height: 290px;
  width: 68px;
  position: relative;
}

/* Value display above the slider */
.value {
  margin-bottom: 0; /* Remove bottom margin */
  color: white;
  font-size: 0.9em;
  font-family: 'Orbitron', sans-serif;
  text-align: center; /* Center the value */
  position: absolute; /* Allow precise positioning */
  margin: 10px;
  top: 0px; /* Adjust the top value to align correctly */
  /* transform: translateX(-50%); /* Center horizontally relative to slider */
}


/* Main slider track */
.slider-input {
  -webkit-appearance: none;
  width: 220px; /* Track width */
  height: 68px; /* Track height */
  /* border-radius: 50px 10px 10px 50px; */
  outline: none;
  transform: rotate(-90deg); /* Rotate to vertical */
  background: var(--slider-background); /* Use dynamic gradient */
  box-shadow: inset 1px 1px 5px rgba(0, 0, 0, 0.3), inset -1px -1px 5px rgba(255, 255, 255, 0.1);
  position: relative;
  z-index: 2; /* Above background layers */
  transition: background 0.2s ease-in-out; /* Smooth trail update */
}



/* Vertical scale lines on the track for a ruler-like effect */
.slider-input::before {
  content: "";
  position: absolute;
  width: 100%;
  height: 100%;
  background: repeating-linear-gradient(
    to right,
    #666,
    #666 1px,
    transparent 1px,
    transparent 20px
  );
  opacity: 0.6;
  z-index: 1; /* Place this behind the main slider track */
}

/* Thumb styling for a 3D, futuristic look */
.slider-input::-webkit-slider-thumb {
  -webkit-appearance: none;
  appearance: none;
  width: 24px;
  height: 60px;
  background: #5f27cd;
  border-radius: 20px;
  box-shadow: 0px 0px 8px rgba(0, 0, 0, 0.5), inset 0px 2px 3px rgba(255, 255, 255, 0.6);
  cursor: pointer;
  transition: background-color 0.3s, transform 0.2s;
  z-index: 3; /* Ensure this is above the ::before pseudo-element */
}

.slider-input::-webkit-slider-thumb:hover {
  /* background-color: #ff5f5f; /* Match the active color from Switch.vue */
  background-color: #666;
  /* border: 3px solid #5f27cd; */
}

.slider-input::-moz-range-thumb {
  width: 24px;
  height: 60px;
  background: #5f27cd;
  border-radius: 20px;
  box-shadow: 0px 0px 8px rgba(0, 0, 0, 0.5), inset 0px 2px 3px rgba(255, 255, 255, 0.6);
  cursor: pointer;
  transition: background-color 0.3s, transform 0.2s;
  z-index: 3; /* Ensure this is above the ::before pseudo-element */

}

.slider-input::-moz-range-thumb:hover {
  /* background-color: #ff5f5f; */
  background-color: #666;
  /* border: 3px solid #5f27cd; */
}

.slider-input::-ms-thumb {
  width: 24px;
  height: 60px;
  background: #5f27cd;
  border-radius: 20px;
  box-shadow: 0px 0px 8px rgba(0, 0, 0, 0.5), inset 0px 2px 3px rgba(255, 255, 255, 0.6);
  cursor: pointer;
  transition: background-color 0.3s, transform 0.2s;
  z-index: 3; /* Ensure this is above the ::before pseudo-element */

}

.slider-input::-ms-thumb:hover {
  /* background-color: #ff5f5f; */
  background-color: #666;
  /* border: 3px solid #5f27cd; */
}
</style>
