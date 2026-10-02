#!/usr/bin/env bash
# desc: Run the build system

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

cmake --build build
