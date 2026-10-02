#!/usr/bin/env bash
# desc: Run the build system
# deps: configure

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

run_task configure
cmake --build build
