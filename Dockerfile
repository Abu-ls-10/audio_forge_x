# Stage 1: Build the frontend
FROM node:18 as frontend-builder
WORKDIR /app/frontend
COPY frontend/ ./
RUN npm install

# Stage 2: Build the backend
FROM python:3.10 as backend-builder
WORKDIR /app/backend
COPY backend/ ./
RUN pip install -r requirements.txt

# Stage 3: Create the final image
FROM ubuntu:20.04
WORKDIR /app

# Install required dependencies
RUN apt-get update && apt-get install -y \
    python3 python3-pip nodejs npm \
    && apt-get clean

# Copy backend and frontend builds
COPY --from=backend-builder /app/backend /app/backend
COPY --from=frontend-builder /app/frontend/dist /app/frontend/dist

# Expose ports for Flask and Vite
EXPOSE 5000 5173

# Start both servers
CMD bash -c "cd /app/backend && python3 app.py & cd /app/frontend/dist && npm run dev"
