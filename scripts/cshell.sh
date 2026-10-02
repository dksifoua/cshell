#!/usr/bin/env bash
# desc: Run the cshell program
# deps: build

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

run_task build
exec build/cshell "$@"
