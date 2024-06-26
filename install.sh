#!/bin/bash

# Check if script is run as root
if [ "$(id -u)" -ne 0 ]; then
  echo "Please run this script as root"
  exit 1
fi

# Define variables
EXECUTABLE_NAME="PrettyLlama"
DESKTOP_FILE_NAME="${EXECUTABLE_NAME}.desktop"
LOGO_FILE_NAME="${EXECUTABLE_NAME}.png"

EXECUTABLE_PATH="/usr/bin/${EXECUTABLE_NAME}"
DESKTOP_FILE_PATH="/usr/share/applications/${DESKTOP_FILE_NAME}"
LOGO_PATH="/usr/share/icons/"

# Copy executable to /usr/bin
cp "${EXECUTABLE_NAME}" "${EXECUTABLE_PATH}"
chmod +x "${EXECUTABLE_PATH}"

# Copy Logo File
cp "./utils/${LOGO_FILE_NAME}" "${LOGO_PATH}"
chmod +x "${LOGO_PATH}/${LOGO_FILE_NAME}"

# Create .desktop file
cat << EOF > "${DESKTOP_FILE_PATH}"
[Desktop Entry]
Name=PrettyLlama
Comment=Simple CLI program to use ollama models in a nice looking way
Exec=gnome-terminal --full-screen -- ${EXECUTABLE_NAME}
Icon=${LOGO_PATH}/${LOGO_FILE_NAME}
Type=Application
EOF

# Make .desktop file executable
chmod +x "${DESKTOP_FILE_PATH}"

# Copy PrettyLlama directory in /usr/share/ to store random files
mkdir "/usr/share/${EXECUTABLE_NAME}"
cp "./utils/WelcomeHeader" "/usr/share/${EXECUTABLE_NAME}/"
cp "./utils/HelpFile" "/usr/share/${EXECUTABLE_NAME}/"
cp "./utils/config.json" "/usr/share/${EXECUTABLE_NAME}/"

# Make json file read and write for all users
chmod 666 "/usr/share/${EXECUTABLE_NAME}/config.json"

echo "Installation complete!"
