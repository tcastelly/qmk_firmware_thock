FROM debian:12

RUN apt-get update && apt-get install --no-install-recommends -y \
    avr-libc \
    avrdude \
    binutils-arm-none-eabi \
    binutils-avr \
    build-essential \
    dfu-programmer \
    dfu-util \
    gcc \
    gcc-arm-none-eabi \
    gcc-avr \
    git \
    libnewlib-arm-none-eabi \
    software-properties-common \
    unzip \
    wget \
    zip \
    python3 \
    python3-pip \
    && rm -rf /var/lib/apt/lists/*

RUN pip install milc --break-system-packages

ENV KEYBOARD=thock/conundrum
ENV KEYMAP=default:uf2

VOLUME /qmk_firmware
WORKDIR /qmk_firmware
COPY . .

CMD make $KEYBOARD:$KEYMAP
