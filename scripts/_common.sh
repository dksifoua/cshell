#!/usr/bin/env bash
# Shared helper

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT_DIR="$(cd "${SCRIPT_DIR}/.." && pwd)"

cd "${PROJECT_ROOT_DIR}"

run_task() {
    local task="$1"
    "${SCRIPT_DIR}/${task}.sh"
}
