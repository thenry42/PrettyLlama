#!/bin/bash

# Check if script is run as root
if [ "$(id -u)" -ne 0 ]; then
  echo "Please run this script as root"
  exit 1
fi

# Define variables
EXECUTABLE_NAME="PrettyLlama"
DESKTOP_FILE_NAME="${EXECUTABLE_NAME}.desktop"
LOGO_FILE_NAME="/utils/${EXECUTABLE_NAME}.png"

EXECUTABLE_PATH="/usr/bin/${EXECUTABLE_NAME}"
DESKTOP_FILE_PATH="${HOME}/Desktop/${DESKTOP_FILE_NAME}"
LOGO_PATH="/usr/share/icons/${EXECUTABLE_NAME}"

# Copy executable to /usr/bin
cp "${EXECUTABLE_NAME}" "${EXECUTABLE_PATH}"
chmod +x "${EXECUTABLE_PATH}"

# Copy Logo File
cp "${LOGO_FILE_NAME}" "${LOGO_PATH}"
chmod +x "${LOGO_PATH}"

# Create .desktop file
cat << EOF > "${DESKTOP_FILE_PATH}"
[Desktop Entry]
Name=PrettyLlama
Comment=Simple CLI program to use ollama models in a nice looking way
Exec=${EXECUTABLE_NAME}
Icon=${LOGO_PATH}
Type=Application
EOF

# Make .desktop file executable
chmod +x "${DESKTOP_FILE_PATH}"

echo "Installation complete!"
