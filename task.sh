#!/usr/bin/env bash
# Usage: ./task.sh <task> [args...]
# Run ./task.sh with no task to list available tasks.

set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)/scripts"
TASK="${1:-default}"
shift || true

if [[ "${TASK}" == _* || "${TASK}" == */* || ! -x "${SCRIPT_DIR}/${TASK}.sh" ]]; then
    echo "Unknown task: ${TASK}" >&2
    "${SCRIPT_DIR}/default.sh" >&2
    exit 1
fi

exec "${SCRIPT_DIR}/${TASK}.sh" "$@"
