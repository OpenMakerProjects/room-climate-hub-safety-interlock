# Wiring and assembly
Use the exact labeled nets in [circuit diagram](circuit-diagram.svg). NodeMCU v2 is a board with its onboard A0 divider; a bare ESP8266 ADC allows only 1.0V and is incompatible without a new divider.
| NodeMCU | Component |
|---|---|
| 3V3 | Analog mic VCC; raw HM-10 VCC |
| A0 | Mic analog OUT, bounded 0–3.3V |
| D5/GPIO14 | HC-SR501 OUT, 3.3V logic |
| D6/GPIO12 | HM-10 TXD |
| D7/GPIO13 | HM-10 RXD |
| D2/GPIO4 | 330Ω then LED anode |
| USB 5V rail | PIR VCC |
| GND | All module grounds and LED cathode |
Power disconnected: wire grounds first, supply rails, signals, then inspect for shorts. Power NodeMCU via USB; split the same regulated USB 5V supply for PIR. Do not connect an external 5V supply to 3V3. Verify microphone OUT stays within the board input rating. Wait at least 60 seconds for PIR warm-up and calibrate its retrigger/delay potentiometers. No actuator is connected.
