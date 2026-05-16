#!/usr/bin/env bash
set -euo pipefail

ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
BINARY="$BUILD_DIR/cpp_microservice_template"

if ! command -v cmake >/dev/null 2>&1; then
  echo "Error: 'cmake' is not installed or not in PATH."
  echo "Install it, then rerun this script."
  echo "Ubuntu/Debian: sudo apt update && sudo apt install -y cmake build-essential"
  exit 1
fi

if ! cmake -S "$ROOT_DIR" -B "$BUILD_DIR"; then
  echo
  echo "CMake configure failed."
  echo "If the error says Drogon was not found, install it:"
  echo "Ubuntu/Debian: sudo apt update && sudo apt install -y libdrogon-dev"
  echo "Then rerun: ./start.sh"
  exit 1
fi
cmake --build "$BUILD_DIR" -j

cp "$ROOT_DIR/config/config.json" "$BUILD_DIR/config.json"

exec "$BINARY"
