#!/bin/bash

# Check if script is run as root
if [ "$(id -u)" -ne 0 ]; then
  echo "Please run this script as root"
  exit 1
fi

# Define variables (must match those used in install.sh)
EXECUTABLE_NAME="PrettyLlama"
DESKTOP_FILE_NAME="${EXECUTABLE_NAME}.desktop"
LOGO_FILE_NAME="${EXECUTABLE_NAME}.png"

EXECUTABLE_PATH="/usr/bin/${EXECUTABLE_NAME}"
DESKTOP_FILE_PATH="/usr/share/applications/${DESKTOP_FILE_NAME}"
LOGO_PATH="/usr/share/icons/${LOGO_FILE_NAME}"

# Remove executable from /usr/bin
if [ -f "${EXECUTABLE_PATH}" ]; then
  rm "${EXECUTABLE_PATH}"
  echo "Removed ${EXECUTABLE_PATH}"
else
  echo "${EXECUTABLE_PATH} not found, skipping removal"
fi

# Remove desktop file from Desktop
if [ -f "${DESKTOP_FILE_PATH}" ]; then
  rm "${DESKTOP_FILE_PATH}"
  echo "Removed ${DESKTOP_FILE_PATH}"
else
  echo "${DESKTOP_FILE_PATH} not found, skipping removal"
fi

# Remove logo file
if [ -f "${LOGO_PATH}" ]; then
  rm "${LOGO_PATH}"
  echo "Removed ${LOGO_PATH}"
else
  echo "${LOGO_PATH} not found, skipping removal"
fi

# Remove /usr/share/PrettyLlama directory
if test -d "/usr/share/${EXECUTABLE_NAME}"; then
  rm -r -f "/usr/share/${EXECUTABLE_NAME}"
  echo "Removed /usr/share/${EXECUTABLE_NAME}"
else
  echo "/usr/share/PrettyLlama not found, skipping removal"
fi

echo "Uninstallation complete!"
