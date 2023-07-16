# Telegram library

This is library that handles Telegram API and protocol.

> This is a fork of [kenorb's repository](https://github.com/kenorb-contrib/tgl), who has been maintaining [vysheng's repository](https://github.com/vysheng/tgl) after he discontinued public development of this project.

If you're looking for client CLI implementation, check [TG repository](https://github.com/vysheng/tg) instead. 

Current versions:

- `scheme.tl`: Layer 38
- `encrypted_scheme.tl`: Layer 23

## API, Protocol documentation

Documentation for Telegram API is available here: https://core.telegram.org/api

Documentation for MTproto protocol is available here: https://core.telegram.org/mtproto

## Building

Clone this GitHub repository with `--recursive` parameter to clone submodules:

```
git clone --recursive https://github.com/vysheng-telegram-cli/tgl.git && cd tgl
```

Compile with CMake:

```
mkdir build
cd build
cmake ..
cmake --build .
```

