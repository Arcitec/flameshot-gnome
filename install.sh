#!/usr/bin/env bash

# Copyright (C) 2024 Arcitec
# SPDX-License-Identifier: GPL-2.0-or-later

set -e

# Set current working dir to the script directory.
cd -- "$(dirname -- "${BASH_SOURCE[0]}")"

_ACTION="install"
while getopts ":iu" option; do
    case "${option}" in
    i)
        _ACTION="install"
        ;;
    u)
        _ACTION="uninstall"
        ;;
    *)
        echo "Usage: $0 [-i] [-u]"
        echo
        echo "Options:"
        echo " -i  Install (default if no options provided)."
        echo " -u  Uninstall."
        exit 1
        ;;
    esac
done

BINARY_NAME="flameshot-gnome"

if [[ "${_ACTION}" == "install" ]]; then
    echo "Installing Flameshot-GNOME..."
    set -x

    # Rebuild the binary.
    mkdir -p build
    gcc "src/${BINARY_NAME}.c" -o "build/${BINARY_NAME}"

    # Use the system-wide "local administrator-installed binaries" location.
    sudo install -D -t "/usr/local/bin" -m "u=rwx,go=rx,a-s" "build/${BINARY_NAME}"
elif [[ "${_ACTION}" == "uninstall" ]]; then
    echo "Removing Flameshot-GNOME..."
    set -x

    # Remove the installed binary from disk.
    sudo find "/usr/local/bin" -maxdepth 1 -name "${BINARY_NAME}" -print -delete
fi

set +x
echo "Process complete: \"${_ACTION}\"."
