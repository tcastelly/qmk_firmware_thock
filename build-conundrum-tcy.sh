#!/bin/bash
# Build the thock conundrum 'tcy' keymap, mounting the canonical users/tcy
# (from qmk_userspace) into the container as /qmk_firmware/shared_tcy so the
# thock shares the ONE tapdance.c + tcy.c — no copy, no drift.
set -exo pipefail

SHARED_TCY=/Users/tcy/Documents/dev/workspaces/qmk/qmk_userspace/users/tcy

docker build -t thock/conundrum .

docker run --rm \
    -v "$PWD":/qmk_firmware \
    -v "$PWD/.build":/qmk_firmware/.build \
    -v "$SHARED_TCY":/qmk_firmware/shared_tcy \
    -i thock/conundrum \
    make thock/conundrum:tcy:uf2
