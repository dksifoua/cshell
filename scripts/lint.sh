#!/usr/bin/env bash
# desc: Lint sources with clang-tidy
# deps: configure

set -euo pipefail

source "$(dirname "${BASH_SOURCE[0]}")/_common.sh"

# Homebrew's clang-tidy does not locate the macOS SDK headers on its own.
if [[ "$(uname)" == Darwin ]]; then
    export SDKROOT="${SDKROOT:-$(xcrun --show-sdk-path)}"
fi

run_task configure
clang-tidy -p build src/*.c
