#!/usr/bin/env bash
# desc: Configure cmake build directory

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
