# deej
Deej is a volume mixer. It runs on an arduino. The repo can be found here: https://github.com/omriharel/deej. 

I included a mute button and led light. When deej starts the mute state is recorded, when the button is pressed the mute states toggles. On the toggle it will affect the led light and the value of the mic. If it is muted the mic value will be set to 0 and the led will turn on. If it unmuted the mic value will be 1024 and the led light will turn off. 

## Pre-requisites
- `mic` has to be the last number in the config.yaml

## Schematic
![image](https://user-images.githubusercontent.com/10181188/140986428-fcf6894e-48ae-4b84-94eb-9f153a506d85.png)
