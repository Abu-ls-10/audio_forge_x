<template>
    <div class="switch-container">
      <label>Remove Vocals</label>
      <div class="stick-shift-switch" @click="toggleVocals">
        <div :class="{'stick-shift': true, 'active': removeVocals}"></div>
      </div>
    </div>
  </template>
  
  <script lang="ts">
  export default {
    data() {
      return {
        removeVocals: false, // Tracks whether vocals are removed or not
      };
    },
    methods: {
      toggleVocals() {
        this.removeVocals = !this.removeVocals; // Toggle the state
        this.$emit('update:modelValue', this.removeVocals); // Emit updated value to parent
      },
    },
  };
  </script>
  
  <style scoped>
  .switch-container {
    display: flex;
    flex-direction: column;
    align-items: center;
    margin: 20px;
    height: 340px;
  }
  
  label {
    color: white;
    margin-bottom: 10px;
    font-family: 'Orbitron', sans-serif;
    text-align: center;
  }
  
  .stick-shift-switch {
    width: 58px;
    height: 250px; /* Increased the height for a vertical design */
    background-color: #333;
    border-radius: 50px;
    display: flex;
    align-items:start;
    justify-content: center;
    padding: 20px 5px 20px 5px;
    cursor: pointer;
  }
  
  .stick-shift {
    width: 32px;
    height: 32px;
    background-color: #666;
    box-shadow: 0px 0px 8px rgba(0, 0, 0, 0.5), inset 0px 2px 3px rgba(255, 255, 255, 0.6);
    border-radius: 50%;
    transition: 0.3s;
  }
  
  .stick-shift.active {
    transform: translateY(220px); /* Moves the switch when active */
    background-color: #5f27cd; /* Optional: change color when active */
  }
  </style>
  