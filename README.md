<p align="center">
  <a href="https://gp2040-ce.info">
    <img alt="GP2040-CE" src="https://raw.githubusercontent.com/OpenStickCommunity/Site/main/docs/assets/images/gp2040-ce-logo.png" />
  </a>
</p>

<p align="center">
  Multi-Platform Gamepad Firmware for RP2040 customized by tamanegi_taro
</p>

<p align="center">
  <img src="https://img.shields.io/github/license/OpenStickCommunity/GP2040-CE" />
  <img src="https://img.shields.io/github/actions/workflow/status/OpenStickCommunity/GP2040-CE/cmake.yml" />
  <br />
  <img src="https://img.shields.io/badge/inputlag.science-0.86%20ms-blue" />
  <img src="https://img.shields.io/badge/MiSTer%20latency-0.765%20ms-blue" />
</p>

## This project is 8BitDo Arcade Stick USB Converter based on GP2040-CE.

![GdE4uBRagAAjrmu](https://github.com/user-attachments/assets/8f999c09-cf4b-4efe-b427-e4e0749cce39)

![GdE4uBPbsAAGPY7](https://github.com/user-attachments/assets/d93dedf1-becc-4b35-97bc-2e24a5b67b70)

## How to use
- Connect 8BitDo arcade stick 2.4G USB dongle to 8BitDo Arcade Stick USB Converter.
- Connect 8BitDo Arcade Stick USB Converter to console.
- Set 8BitDo Arcade Stick to Nintendo Switch(S) mode and 2.4G wireless mode.
- For LS/DP/RS switch, make sure to set it as DP for mini console compatibility. You can also use LS/RS for Switch, PSx, and other consoles which utilizes LS/RS.
- For PS4/PS5 compatibility, you will need USB Hub(Experimental) and PS4/5 Authentication USB dongle.

Hotkeys:

- Hold S2 + B3 + B4 5 seconds for Firmware Upgrade mode - Bootsel (Or hold Boot button on RP2040-Zero and connect it to your PC)
- Hold S1 + B3 + B4 5 seconds for Webconfig

To change game mode, Hold Home + S1 + S2 and push button below.

- B1 : XBOX Original
- B2 : PC Engine Mini
- R2 : Neogeo mini
- L2 : EgretII mini
- B3 : PS3
- B4 : PS4
- R1 : PS CLASSIC
- L1 : Megadrive mini / Astrocity mini

![image](https://github.com/user-attachments/assets/06845183-13cd-4b73-b737-164304b0d408)

## Known issue
- Joystick movement will be reflected to OLED animation but button movement will not be reflected to OLED animation. This is issue in Keyboard host add-on so I have reported it to GP2040-CE community. Hope it will be fixed soon.
- After changing game mode, sometimes need to reboot USB converter and 8BitDo arcade stick to get it recognized.

## Parts
- RP2040-Zero * 1
https://ja.aliexpress.com/item/1005007393402333.html
- 1.3" OLED Display Module SH1106 128X64 * 1
https://ja.aliexpress.com/item/1005005967766159.html
- USB A Type Standard Port Female PCB Mount Socket Connector Right Angle 4 Pin
https://ja.aliexpress.com/item/1005004572352605.html
- 1206 SMD PTC Resettable fuse 500MA 0.5A * 1
https://ja.aliexpress.com/item/1005004844581464.html
- 1206 Resistor 22ohm * 2
https://ja.aliexpress.com/item/32996310793.html
- Some wires
- M3 Nylon screws nuts set
	- nuts * 4
	- 6mm screws * 4
	- 6mm/10mm male spacer * 4

https://amzn.asia/d/cy7spRY

![image](https://github.com/user-attachments/assets/bf3f8d46-e889-42cc-a2ff-971c7e933b27)
![image](https://github.com/user-attachments/assets/5368e390-aff6-470b-a425-a2c49e8c6c9d)

- PCB of GP2040-CE USB Converter 2.0

You can order PCB from elecrow - PCB Fab - Regular PCB(Online order)
https://www.elecrow.com/pcb-manufacturing.html?from=nav/

Download gerber/gerber.zip and upload it in elecrow PCB online order website.
Choose your favorite color for your PCB board. Choosing Lead free is optional(Good for your health for extra $2).

![image](https://github.com/user-attachments/assets/587bb9d1-a64b-44cc-9c59-435bd8d2bb5e)
![image](https://github.com/user-attachments/assets/b81fccfb-73cd-471a-a642-94ddcbabce0a)

## Instruction to build USB converter
Connect everything like this. Connect RP2040-Zero and OLED.
![image](https://github.com/user-attachments/assets/4e1ea4ec-117e-4953-947c-8ed4af18fa94)

Connect 2 22ohm registors and resettable fuse
![image](https://github.com/user-attachments/assets/19cc8427-b826-4b32-990f-3c574c0c0219)

Use 4 screws and finish build.
![GdE4uBPbsAAGPY7](https://github.com/user-attachments/assets/d93dedf1-becc-4b35-97bc-2e24a5b67b70)

## How to configure
- Download build/GP2040-CE_0.7.10_WaveshareZero.uf2

- From GP2040-CE Releases, download flash_nuke.uf2 and force_webconfig.uf2
[https://github.com/OpenStickCommunity/GP2040-CE](https://github.com/OpenStickCommunity/GP2040-CE/releases)

- Hold BOOT button on RP2040-Zero and connect converter to your PC

![image](https://github.com/user-attachments/assets/a7470a09-87fc-4a4f-8a5c-6625e546146e)

- RPI-RP2 storage will be recognized(Bootsel mode). Copy flash_nuke.uf2 in RPI-RP2. This will initialize your RP2040 Zero.
- RPI-RP2 storage will open again after initialization is completed. Copy GP2040-CE_0.7.10_WaveshareZero.uf2.
- Once copy is completed, hold BOOT button on RP2040-Zero and reconnect converter to your PC.
- RPI-RP2 storage will open again. Copy force_webconfig.uf2.
- After copy is completed, open web browser in your PC and open http://192.168.7.1

![image](https://github.com/user-attachments/assets/f4345e02-e9cd-413c-9ad9-1b506f4f3db4)

- Open configuration - Pin mapping
- Delete all pin configurations as below and make sure to click save

![image](https://github.com/user-attachments/assets/77f6c4ac-88ac-4161-a6d3-e56ae2a443e5)

- Open configuration - Peripheral settings
- Configure I2C and USB port as below and make sure to click save

![image](https://github.com/user-attachments/assets/9aaf8120-6914-4593-a335-56cf9bb46022)

- Open configuration - Display configuration
- Enable display and make sure to click save

![image](https://github.com/user-attachments/assets/f96755a7-c6b7-4ad2-8962-634b86d1d05a)


- Open configuration - add-on configuration
- Enable Keyboard/Mouse USB Host configuration and make sure to click save

![image](https://github.com/user-attachments/assets/f0e1b5ea-e901-43e2-aefd-481a6b4df219)

- Click Reboot - Controller and configuration is finished!

## **************************************************
## **************************************************
## **************************************************
## **************************************************
## **************************************************

<p>

  GP2040-CE (Community Edition) is a gamepad firmware for the Raspberry Pi Pico and other boards based on the RP2040 microcontrollers that combines multi-platform compatibility, low latency and a rich feature set to provide endless customization possibilities without sacrificing performance.
</p>

<p>
  GP2040-CE is compatible with PC, PS3, PS4, PS5, Nintendo Switch, Xbox One, Steam Deck, MiSTer and Android.
</p>

## Links

[Downloads](https://gp2040-ce.info/downloads) | [Installation](https://gp2040-ce.info/installation) | [Wiring](https://gp2040-ce.info/controller-build/wiring) | [Usage](https://gp2040-ce.info/usage) | [FAQ](https://gp2040-ce.info/faq/faq-general) | [GitHub](https://github.com/OpenStickCommunity/GP2040-CE)

Full documentation can be found at [https://gp2040-ce.info](https://gp2040-ce.info)

## Features

- Select from 13 input modes including X-Input, Nintendo Switch, Playstation 4/5, Xbox One, D-Input, and Keyboard
- Input latency average of 0.76ms in Xinput and 0.91ms for Playstation 5.
- Multiple SOCD cleaning modes - Up Priority (a.k.a. Stickless), Neutral, and Second Input Priority.
- Left and Right stick emulation via D-pad inputs as well as dedicated toggle switches.
- Dual direction via D-pad + LS/RS.
- Reversed input via a button.
- [Turbo and Turbo LED](https://gp2040-ce.info/add-ons/turbo) with selectable speed
- Per-button RGB LED support.
- PWM Player indicator LED support (XInput only).
- Multiple LED profiles support.
- Support for 128x64 monochrome I2C displays - SSD1306, SH1106, and SH1107 compatible.
- Custom startup splash screen and easy image upload via web configuration.
- Support for passive buzzer speaker (3v or 5v).
- [Built-in, embedded web configuration](https://gp2040-ce.info/web-configurator) - No download required!

Visit the [GP2040-CE Usage](https://gp2040-ce.info/usage) page for more details.

## Performance

Input latency is tested using the methodology outlined at [WydD's inputlag.science website](https://inputlag.science/controller/methodology), using the default 1000 Hz (1 ms) polling rate in the firmware. You can read more about the setup we use to conduct latency testing [HERE](https://github.com/OpenStickCommunity/Site/blob/main/latency_testing/README.md) if you are interested in testing for yourself or would just like to know more about the devices used to do the testing.

| Version | Mode         | Poll Rate | Min     | Max     | Avg     | Stdev   | % on time | %1f skip | %2f skip |
| ------- | ------------ | --------- | ------- | ------- | ------- | ------- | --------- | -------- | -------- |
| v0.7.9  | Xinput       | 1 ms      | 0.45 ms | 1.28 ms | 0.76 ms | 0.24 ms | 98.48%    | 1.52%    | 0%       |
| v0.7.9  | Switch       | 1 ms      | 0.41 ms | 1.23 ms | 0.72 ms | 0.24 ms | 98.53%    | 1.47%    | 0%       |
| v0.7.9  | Dinput (PS3) | 1 ms      | 0.44 ms | 1.27 ms | 0.75 ms | 0.24 ms | 98.49%    | 1.51%    | 0%       |
| v0.7.9  | PS4          | 1 ms      | 0.55 ms | 2.26 ms | 0.90 ms | 0.32 ms | 98.21%    | 1.79%    | 0%       |
| v0.7.9  | PS5          | 1 ms      | 0.55 ms | 2.33 ms | 0.91 ms | 0.33 ms | 98.18%    | 1.82%    | 0%       |

Full results can be found in the [GP2040-CE v0.7.9 Firmware Latency Test Results](https://github.com/OpenStickCommunity/Site/raw/main/latency_testing/GP2040-CE_Firmware_Latency_Test_Results_v0.7.9.xlsx) .xlsx Sheet.

Results from v0.7.8 can be found [HERE](https://github.com/OpenStickCommunity/Site/raw/main/latency_testing/GP2040-CE_Firmware_Latency_Test_Results_v0.7.8.xlsx).  Previous results can be found in the `latency_testing` folder.

## Support

If you would like to discuss features, issues or anything else related to GP2040-CE please [create an issue](https://github.com/OpenStickCommunity/GP2040-CE/issues/new) or join the [OpenStick GP2040-CE Discord](https://discord.gg/k2pxhke7q8) support channel.

## Contributing

Want to help improve GP2040-CE? There are a bunch of ways to contribute!

### Community Participation

Have an idea for a cool new feature, or just want to discuss some technical details with the developers? Join the [OpenStick GP2040-CE Discord](https://discord.gg/k2pxhke7q8) server to participate in our active and ever-growing community!

### Pull Requests

Pull requests are welcome and encouraged for enhancements, bug fixes and documentation updates.

Please respect the coding style of the file(s) you are working in, and enforce the use of the `.editorconfig` file when present.

## Acknowledgements

- [FeralAI](https://github.com/FeralAI) for building [GP2040](https://github.com/FeralAI/GP2040) and laying the foundation for this community project
- Ha Thach's excellent [TinyUSB library](https://github.com/hathach/tinyusb) examples
- fluffymadness's [tinyusb-xinput](https://github.com/fluffymadness/tinyusb-xinput) sample
- Kevin Boone's [blog post on using RP2040 flash memory as emulated EEPROM](https://kevinboone.me/picoflash.html)
- [bitbank2](https://github.com/bitbank2) for the [OneBitDisplay](https://github.com/bitbank2/OneBitDisplay) and [BitBang_I2C](https://github.com/bitbank2/BitBang_I2C) libraries, which were ported for use with the Pico SDK
- [arntsonl](https://github.com/arntsonl) for the amazing cleanup and feature additions that brought us to v0.5.0
- [alirin222](https://github.com/alirin222) for the awesome turbo code ([@alirin222](https://twitter.com/alirin222) on Twitter)
- [deeebug](https://github.com/deeebug) for improvements to the web-UI and fixing the PS3 home button issue
- [TheTrain](https://github.com/TheTrainGoes/GP2040-Projects) and [Fortinbra](https://github.com/Fortinbra) for helping keep our community chugging along
- [PassingLink](https://github.com/passinglink/passinglink) for the technical details and code for PS4 implementation
- [Youssef Habchi](https://youssef-habchi.com/) for allowing us to purchase a license to use Road Rage font for the project
- [tamanegitaro](https://github.com/tamanegitaro/) and [alirin222](https://github.com/alirin222) for the basis of the mini/classic controller work
- [Ryzee119](https://github.com/Ryzee119) for the wonderful [ogx360_t4](https://github.com/Ryzee119/ogx360_t4/) and xid_driver library for Original Xbox support
- [Santroller](https://github.com/Santroller/Santroller) and [GIMX](https://github.com/matlo/GIMX) for technical examples of Xbox One authentication using pass-through
