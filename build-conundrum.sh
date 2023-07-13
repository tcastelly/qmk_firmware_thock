#!/bin/bash
set -exo pipefail

docker build -t thock/conundrum .
docker run --rm -v $PWD:/qmk_firmware -v $PWD/.build:/qmk_firmware/.build -it thock/conundrum
docker run --rm -v $PWD:/qmk_firmware -v $PWD/.build:/qmk_firmware/.build -it thock/conundrum make mc2s/rev1:tcy
