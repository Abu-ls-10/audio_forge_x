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
        this.$emit('update:removeVocals', this.removeVocals); // Emit updated value to parent
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
  }
  
  label {
    color: white;
    margin-bottom: 10px;
  }
  
  .stick-shift-switch {
    width: 50px;
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
    width: 30px;
    height: 30px;
    background-color: #5f27cd;
    border-radius: 50%;
    transition: 0.3s;
  }
  
  .stick-shift.active {
    transform: translateY(220px); /* Moves the switch when active */
    background-color: #ff5f5f; /* Optional: change color when active */
  }
  </style>
  