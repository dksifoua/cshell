#!/usr/bin/env bash
# desc: List available tasks

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

echo "Available tasks:"
for script in "${SCRIPT_DIR}"/[!_]*.sh; do
    name="$(basename "${script}" .sh)"
    desc="$(sed -n 's/^# desc: //p' "${script}")"
    printf '  %-10s %s\n' "${name}" "${desc}"
done
