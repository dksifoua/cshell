#!/usr/bin/env bash
# desc: Clean build folder

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

rm -rf build
