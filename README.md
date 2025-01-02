# AudioForgeX

**AudioForgeX** is a web-based audio processing platform designed to empower users with the ability to mix, edit, and enhance audio files effortlessly. This project combines the power of low-level C programming for high-performance audio processing with the flexibility of modern web technologies.

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
   - **Install Python Dependencies**:
     ```bash
     pip install -r requirements.txt
     ```
   - **Run Flask Backend**:
     ```bash
     python3 app.py
     ```

3. **Frontend Setup**:
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
│   ├── c_code/
│   │   └── libaudio.so           # Compiled shared library (Linux)
│   ├── app.py                   # Flask backend
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

## Contributing

We welcome contributions! Please follow these steps:

1. Fork this repository.
2. Create a new branch:
   ```bash
   git checkout -b feature/your-feature-name
   ```
3. Commit your changes:
   ```bash
   git commit -m "Add your message here"
   ```
4. Push to your branch:
   ```bash
   git push origin feature/your-feature-name
   ```
5. Open a Pull Request.
6. 
---

## Contact

For any questions or issues, please reach out to:

- **Email**: [your-email@example.com](mailto:your-email@example.com)
- **GitHub**: [your-username](https://github.com/your-username)
