#!/usr/bin/env bash
# desc: Run unit tests
# deps: build

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

run_task build
ctest --build-dir build --output-on-failure
