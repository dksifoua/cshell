#!/usr/bin/env bash
# desc: Format sources with clang-format

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

clang-format -i src/*.c tests/*.c include/cshell/*.h
