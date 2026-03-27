#!/bin/bash

echo "Stopping Ollama service..."
sudo systemctl stop ollama 2>/dev/null

echo "Disabling Ollama service..."
sudo systemctl disable ollama 2>/dev/null

echo "Removing Ollama user data and models..."
rm -rf ~/.ollama

echo "Removing system-wide Ollama data..."
sudo rm -rf /var/lib/ollama
sudo rm -rf /usr/share/ollama

echo "Removing Ollama binary..."
sudo rm -f /usr/local/bin/ollama

echo "Removing systemd service..."
sudo rm -f /etc/systemd/system/ollama.service
sudo systemctl daemon-reload

echo "Removing ollama user (if exists)..."
sudo userdel ollama 2>/dev/null

echo "Cleanup complete."

echo "Verifying removal..."
if command -v ollama &> /dev/null
then
echo "Ollama still exists!"
else
echo "Ollama successfully removed."
fi
