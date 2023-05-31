# MSc Dissertation
## _Title: David vs. Goliath -- An Array of Raspberry Pi's as a replacement to Servers_

# License
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](https://opensource.org/licenses/MIT)
Copyright (c) 2023 Suhail-SSRC

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

## Equpiment used

- RaspBerry Pi 4 Model B (8 GB RAM)
- 128 GB SD Card

## Setup

We document the steps on how to setup a Pi:

- Download image - [![Raspberry Pi](https://img.shields.io/badge/-RaspberryPi-C51A4A?style=for-the-badge&logo=Raspberry-Pi)](https://ubuntu.com/raspberry-pi)
- SD Card formatter (Format to start with fresh images) - [![Download](https://img.shields.io/badge/SD%20Formatter-SD-blue)](https://www.sdcard.org/downloads/formatter/)
- BalenaEtcher (To flash the OS) [![BalenaEtcher](https://upload.wikimedia.org/wikipedia/commons/thumb/b/bc/Etcher_%28software%29_logo.svg/120px-Etcher_%28software%29_logo.svg.png)](https://etcher.balena.io/)

## Installation


- After downloading the image and sd formatter, install the latest dependecies
```bash
sudo apt update
sudo apt upgrade
```

- Setting SSH keys and connecting to pi's without passwords - [SSH Pi's](https://danidudas.medium.com/how-to-connect-to-raspberry-pi-via-ssh-without-password-using-ssh-keys-3abd782688a)
- Follow this for more useful information [Click Me](https://www.raspberrypi.com/documentation/computers/remote-access.html#connecting-to-your-raspberry-pi)
