#!/bin/bash

# install_ncursesw.sh

set -e

echo "Detecting Linux distro"

if [ -f /etc/debian_version ]; then
    echo "Detected Debian/Ubuntu distro."
    echo "Updating packages"
    sudo apt update
    echo "Installing"
    sudo apt install -y libncursesw5 libncursesw5-dev

elif [ -f /etc/redhat-release ]; then
    echo "Detected RedHat/Fedora/CentOS distro"
    echo "Installing"
    sudo dnf install -y ncurses ncurses-devel

elif [ -f /etc/arch-release ]; then
    echo "Detected Arch Linux distro"
    echo "Installing"
    sudo pacman -Sy --noconfirm ncurses

else
    echo "Distro not automatically detected"
    echo "Manual install of ncursesw is needed"
    exit 1
fi

echo "Installation completed successfully"
