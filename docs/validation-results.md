# Validation results

GitHub Actions decoder run 37982017759 on 2026-10-10 IST losslessly decoded 54 text chunks and committed the original PNG to the same automation branch. Full completion gates ran explicitly on that decoded commit: C++17 shared policy tests passed warm-up refusal, stable safe arm, sound/PIR/invalid trip, STOP, rearm and timer wrap; 3 image transport unit tests passed; PNG SHA/CRC/dimensions, SVG, relative links, MIT and credential scans passed.

PlatformIO 6.1.18 espressif8266 4.2.1 nodemcuv2 build succeeded: RAM 28724 / 81920 bytes; flash 272975 / 1044464 bytes. Image: 1286228 bytes, 1536×1024, SHA256 c65063b44d017a1a8e054962bcdad33938e10f97c54337e98d078cb67a76a347. No base64 transport chunks remain.

Physical ESP8266 hardware, microphone calibration, PIR response, actual BLE radio/UART and output timing were not tested. Final push and PR checks must pass on the documented head before merge.
