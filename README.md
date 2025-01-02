# AudioForgeX

**AudioForgeX** is a web-based audio processing platform designed to empower users with the ability to mix, edit, and enhance audio files effortlessly. This project combines the power of low-level C programming for high-performance audio processing with the flexibility of modern web technologies.

---

## Table of Contents

1. [Overview](#overview)
2. [Features](#features)
3. [Installation](#installation)
   - [Prerequisites](#prerequisites)
   - [Steps](#steps)
4. [Usage](#usage)
5. [Roadmap](#roadmap)
6. [Technologies Used](#technologies-used)
7. [Project Structure](#project-structure)
8. [Acknowledgements](#acknowledgements)
9. [Contact](#contact)

---

## Overview

**AudioForgeX** is a cutting-edge web-based audio processing platform that empowers users to apply advanced audio transformations with ease. It leverages the power of C for efficient audio processing, Python for seamless integration, and Vue.js with TypeScript for a user-friendly frontend.

This project aims to simplify audio editing by allowing users to upload WAV files, apply effects like echo, vocal removal, and pitch shifting, and download the processed file—all through an interactive web interface. With plans for Docker-based deployment, AudioForgeX promises cross-platform compatibility and ease of setup, making professional-grade audio editing accessible to everyone.

---

## Features

- **Audio Processing with C**:
  - High-performance audio transformations written in C, such as:
    - Removing vocals.
    - Adding echo effects.
    - Volume scaling (amplification).
    - Pitch shifting.
   
  - C code is compiled into `.so` files for Linux compatibility. Windows compatibility requires WSL (Windows Subsystem for Linux) installation.

- **Python Integration**:
  - Python acts as the middleware between the backend logic and the Flask API, leveraging `ctypes` to load and execute C functions dynamically.

- **Frontend with Vue.js and TypeScript**:
  - Intuitive, responsive, and interactive user interface built with Vue.js and TypeScript.
  - Provides file upload/download capabilities and real-time configuration for audio effects.

- **Backend with Flask**:
  - Facilitates communication between the frontend and backend.
  - Processes and returns enhanced audio files.
  - Streamlined integration with C libraries via Python.

- **Docker Compatibility (Coming Soon)**:
  - Simplified deployment through Docker containers for cross-platform usability.

---

## Installation

### Prerequisites

- **Linux OS** (or Windows with WSL)
- **Python 3.10+**
- **npm** (for the frontend)

---

### Steps

1. **Clone the Repository**:
   ```bash
   git clone https://github.com/Abu-ls-10/audio_forge_x.git
   cd audio_forge_x
   ```

2. **Backend Setup**:
   - Navigate to the `backend` directory:
     ```bash
     cd backend
     ```
   - Install Python Dependencies:
     ```bash
     pip install -r requirements.txt
     ```
   - Run Flask Backend:
     ```bash
     python3 app.py
     ```

4. **Frontend Setup**:
   - Navigate to the `frontend` directory:
     ```bash
     cd frontend
     ```
   - Install dependencies:
     ```bash
     npm install vite@latest
     ```
   - Move into main application directory
     ```bash
     cd audioforgex-app
     ```
   - Start the development server:
     ```bash
     npm run dev
     ```

---

## Usage

1. Launch the Flask backend and Vue frontend.
2. Open the web app in your browser (typically at `http://localhost:5173`).
3. Upload a WAV file, configure audio effects, and click "Mix!".
4. Download the processed audio file directly.

---

## Roadmap

- [x] Core audio processing with C.
- [x] Integration of C libraries with Python.
- [x] Flask API for backend communication.
- [x] Frontend UI with Vue.js and TypeScript.
- [ ] Add Docker support for containerized deployment.

---

## Technologies Used

- **C**: High-performance audio processing logic.
- **Python**: Middleware and Flask API.
- **Flask**: Backend framework for communication.
- **Vue.js**: Frontend framework.
- **TypeScript**: Strongly-typed programming for the frontend.
- **Docker** (planned): Simplified deployment and cross-platform compatibility.

---

## Project Structure

```plaintext
audio_forge_x/
│
├── backend/
│   ├── audio_mixing/            # Compiled shared library for all features(.so format)
│   │   ├── addecho
│   │   ├── adjust_tempo
│   │   ├── remvocals
│   │   └── shift_pitch          
│   ├── app.py                   # Flask backend
│   ├── audioforgex.py           # Ctypes logic for CDLLs
│   └── requirements.txt         # Python dependencies
│
├── frontend/
│   ├── public/                  # Static assets
│   ├── src/                     # Vue.js + TypeScript code
│   ├── package.json             # Frontend dependencies
│   └── ...
│
├── Dockerfile (coming soon)
├── README.md                    # Project documentation
└── ...
```

---

## Acknowledgements

Special thanks to all contributors and supporters of the AudioForgeX project.

## Contact

For any questions or feedback please reach out to:
- **GitHub**: [Abu-ls-10](https://github.com/Abu-ls-10) (me)
