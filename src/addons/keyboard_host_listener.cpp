#include "addons/keyboard_host_listener.h"
#include "drivermanager.h"
#include "storagemanager.h"
#include "class/hid/hid_host.h"

#include "system.h"
#include "gamepad.h"

//#define UART_ENABLE
#ifdef UART_ENABLE
/* UART Driver */
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#define UART_ID uart1
#define BAUD_RATE 115200
#define UART_TX_PIN 4
#define UART_RX_PIN 5
char string_a[100];
#endif

void KeyboardHostListener::setup() {
  const KeyboardHostOptions& keyboardHostOptions = Storage::getInstance().getAddonOptions().keyboardHostOptions;
  const KeyboardMapping& keyboardMapping = keyboardHostOptions.mapping;

  _keyboard_host_mapDpadUp.setMask(GAMEPAD_MASK_UP);
  _keyboard_host_mapDpadDown.setMask(GAMEPAD_MASK_DOWN);
  _keyboard_host_mapDpadLeft.setMask(GAMEPAD_MASK_LEFT);
  _keyboard_host_mapDpadRight.setMask(GAMEPAD_MASK_RIGHT);
  _keyboard_host_mapButtonB1.setMask(GAMEPAD_MASK_B1);
  _keyboard_host_mapButtonB2.setMask(GAMEPAD_MASK_B2);
  _keyboard_host_mapButtonB3.setMask(GAMEPAD_MASK_B3);
  _keyboard_host_mapButtonB4.setMask(GAMEPAD_MASK_B4);
  _keyboard_host_mapButtonL1.setMask(GAMEPAD_MASK_L1);
  _keyboard_host_mapButtonR1.setMask(GAMEPAD_MASK_R1);
  _keyboard_host_mapButtonL2.setMask(GAMEPAD_MASK_L2);
  _keyboard_host_mapButtonR2.setMask(GAMEPAD_MASK_R2);
  _keyboard_host_mapButtonS1.setMask(GAMEPAD_MASK_S1);
  _keyboard_host_mapButtonS2.setMask(GAMEPAD_MASK_S2);
  _keyboard_host_mapButtonL3.setMask(GAMEPAD_MASK_L3);
  _keyboard_host_mapButtonR3.setMask(GAMEPAD_MASK_R3);
  _keyboard_host_mapButtonA1.setMask(GAMEPAD_MASK_A1);
  _keyboard_host_mapButtonA2.setMask(GAMEPAD_MASK_A2);
  _keyboard_host_mapDpadUp.setKey(keyboardMapping.keyDpadUp);
  _keyboard_host_mapDpadDown.setKey(keyboardMapping.keyDpadDown);
  _keyboard_host_mapDpadLeft.setKey(keyboardMapping.keyDpadLeft);
  _keyboard_host_mapDpadRight.setKey(keyboardMapping.keyDpadRight);
  _keyboard_host_mapButtonB1.setKey(keyboardMapping.keyButtonB1);
  _keyboard_host_mapButtonB2.setKey(keyboardMapping.keyButtonB2);
  _keyboard_host_mapButtonR2.setKey(keyboardMapping.keyButtonR2);
  _keyboard_host_mapButtonL2.setKey(keyboardMapping.keyButtonL2);
  _keyboard_host_mapButtonB3.setKey(keyboardMapping.keyButtonB3);
  _keyboard_host_mapButtonB4.setKey(keyboardMapping.keyButtonB4);
  _keyboard_host_mapButtonR1.setKey(keyboardMapping.keyButtonR1);
  _keyboard_host_mapButtonL1.setKey(keyboardMapping.keyButtonL1);
  _keyboard_host_mapButtonS1.setKey(keyboardMapping.keyButtonS1);
  _keyboard_host_mapButtonS2.setKey(keyboardMapping.keyButtonS2);
  _keyboard_host_mapButtonL3.setKey(keyboardMapping.keyButtonL3);
  _keyboard_host_mapButtonR3.setKey(keyboardMapping.keyButtonR3);
  _keyboard_host_mapButtonA1.setKey(keyboardMapping.keyButtonA1);
  _keyboard_host_mapButtonA2.setKey(keyboardMapping.keyButtonA2);
  _keyboard_host_mapButtonA3.setKey(keyboardMapping.keyButtonA3);
  _keyboard_host_mapButtonA4.setKey(keyboardMapping.keyButtonA4);

  mouseLeftMapping = keyboardHostOptions.mouseLeft;
  mouseMiddleMapping = keyboardHostOptions.mouseMiddle;
  mouseRightMapping = keyboardHostOptions.mouseRight;

  _8bitdo24g_host_enabled = false;
  _8bitdo24g_dev_addr = 0;
  _8bitdo24g_instance = 0;

  _keyboard_host_enabled = false;
  _keyboard_dev_addr = 0;
  _keyboard_instance = 0;
  
  _mouse_host_enabled = false;
  _mouse_dev_addr = 0;
  _mouse_instance = 0;

  mouseX = 0;
  mouseY = 0;
  mouseZ = 0;

#ifdef UART_ENABLE
  // Set up our UART with the required speed.
  uart_init(UART_ID, BAUD_RATE);

  // Set the TX and RX pins by using the function select on the GPIO
  // Set datasheet for more information on function select
  gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
  gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

  uart_puts(UART_ID, " Hello, UART!\n");

#endif

}

void KeyboardHostListener::process() {
  Gamepad *gamepad = Storage::getInstance().GetGamepad();
  if (_keyboard_host_enabled || _mouse_host_enabled) {
    gamepad->state.dpad     |= _keyboard_host_state.dpad;
    gamepad->state.buttons  |= _keyboard_host_state.buttons;
    gamepad->state.lx       |= _keyboard_host_state.lx;
    gamepad->state.ly       |= _keyboard_host_state.ly;
    gamepad->state.rx       |= _keyboard_host_state.rx;
    gamepad->state.ry       |= _keyboard_host_state.ry;

    if (!gamepad->hasAnalogTriggers) {
        gamepad->state.lt       |= _keyboard_host_state.lt;
        gamepad->state.rt       |= _keyboard_host_state.rt;
    }
  } else if (_8bitdo24g_host_enabled) {
    gamepad->state.dpad     = _keyboard_host_state.dpad;
    gamepad->state.buttons  = _keyboard_host_state.buttons;
    gamepad->state.lx       = _keyboard_host_state.lx;
    gamepad->state.ly       = _keyboard_host_state.ly;
    gamepad->state.rx       = _keyboard_host_state.rx;
    gamepad->state.ry       = _keyboard_host_state.ry;

    if (!gamepad->hasAnalogTriggers) {
        gamepad->state.lt       = _keyboard_host_state.lt;
        gamepad->state.rt       = _keyboard_host_state.rt;
    }
  }

  gamepad->auxState.sensors.mouse.enabled = _mouse_host_enabled;
  gamepad->auxState.sensors.mouse.active = mouseActive;
  if (_mouse_host_enabled && mouseActive) {
    gamepad->auxState.sensors.mouse.x = mouseX;
    gamepad->auxState.sensors.mouse.y = mouseY;
    gamepad->auxState.sensors.mouse.z = mouseZ;
  }
  mouseActive = false;

#ifdef UART_ENABLE
    uart_puts(UART_ID, "KB Process: ");
    sprintf(string_a, "%08x ", gamepad->state.buttons);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%02x ", gamepad->state.dpad);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", gamepad->state.lx);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", gamepad->state.ly);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", gamepad->state.rx);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", gamepad->state.ry);
    uart_puts(UART_ID, string_a);
    uart_puts(UART_ID, "\n");
#endif
}

void KeyboardHostListener::mount(uint8_t dev_addr, uint8_t instance, uint8_t const* desc_report, uint16_t desc_len) {
    // Interface protocol (hid_interface_protocol_enum_t)
    uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

#ifdef UART_ENABLE
    uart_puts(UART_ID, "Device mounted : ");
    sprintf(string_a, "%02x ", itf_protocol);
    uart_puts(UART_ID, string_a);
    uart_puts(UART_ID, "\n");
#endif
    // tuh_hid_report_received_cb() will be invoked when report is available
    if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
        _keyboard_dev_addr = dev_addr;
        _keyboard_instance = instance;
        _keyboard_host_enabled = true;
    } else if (itf_protocol == HID_ITF_PROTOCOL_MOUSE) {
        _mouse_dev_addr = dev_addr;
        _mouse_instance = instance;
        _mouse_host_enabled = true;
    } else if (itf_protocol == HID_ITF_PROTOCOL_NONE) {
        _8bitdo24g_dev_addr = dev_addr;
        _8bitdo24g_instance = instance;
        _8bitdo24g_host_enabled = true;
    } else {
        return;
    }
}

void KeyboardHostListener::unmount(uint8_t dev_addr) {
#if 0
    uart_puts(UART_ID, "Device unmount\n : ");
#endif

    if ( _keyboard_dev_addr == dev_addr ) {
        _keyboard_host_enabled = false;
        _keyboard_dev_addr = 0;
        _keyboard_instance = 0;
    } else if ( _mouse_dev_addr == dev_addr ) {
        _mouse_host_enabled = false;
        _mouse_dev_addr = 0;
        _mouse_instance = 0;
    } else if ( _8bitdo24g_dev_addr == dev_addr ) {
        _8bitdo24g_host_enabled = false;
        _8bitdo24g_dev_addr = 0;
        _8bitdo24g_instance = 0;
    }
}

void KeyboardHostListener::report_received(uint8_t dev_addr, uint8_t instance, uint8_t const* report, uint16_t len){
#ifdef UART_ENABLE
  uart_puts(UART_ID, "dev_addr: ");
  sprintf(string_a, "%02x ", dev_addr);
  uart_puts(UART_ID, string_a);
  uart_puts(UART_ID, ", instance: ");
  sprintf(string_a, "%02x ", instance);
  uart_puts(UART_ID, string_a);  
  uart_puts(UART_ID, ", report: ");
  for(uint32_t i = 0; i < len; i++)
  {
    sprintf(string_a, "%02x ", report[i]);
    uart_puts(UART_ID, string_a);
  }
  uart_puts(UART_ID, "\n");

#endif


  if (
        ( _keyboard_host_enabled == false || _keyboard_dev_addr != dev_addr || _keyboard_instance != instance )
        &&
        ( _mouse_host_enabled == false || _mouse_dev_addr != dev_addr || _mouse_instance != instance )
        &&
        ( _8bitdo24g_host_enabled == false || _8bitdo24g_dev_addr != dev_addr || _8bitdo24g_instance != instance )
  )
    return; // do nothing if we haven't mounted

  // Interface protocol (hid_interface_protocol_enum_t)
  uint8_t const itf_protocol = tuh_hid_interface_protocol(dev_addr, instance);

  preprocess_report();

  // tuh_hid_report_received_cb() will be invoked when report is available
  if (itf_protocol == HID_ITF_PROTOCOL_NONE)
  {
    process_8bitdo24g_report(dev_addr, report, len);
#if 0
    uart_puts(UART_ID, "process 8bitdo24g\n");
#endif
  } else if (itf_protocol == HID_ITF_PROTOCOL_KEYBOARD) {
    process_kbd_report(dev_addr, (hid_keyboard_report_t const*) report );
#if 0
    uart_puts(UART_ID, "process kbd\n");
#endif
  } else if (itf_protocol == HID_ITF_PROTOCOL_MOUSE) {
    process_mouse_report(dev_addr, (hid_mouse_report_t const*) report );
#if 0
    uart_puts(UART_ID, "process mouse\n");
#endif
  } else {
    return;
  }
}


void KeyboardHostListener::process_kbd_hotkey(void)
{
  /* If A1, S1, S2 are pressed at same time, activate hotkey */
  if((_keyboard_host_state.buttons & _keyboard_host_mapButtonA1.buttonMask) && (_keyboard_host_state.buttons & _keyboard_host_mapButtonS2.buttonMask) && (_keyboard_host_state.buttons & _keyboard_host_mapButtonS1.buttonMask))
  {

    Gamepad * gamepad = Storage::getInstance().GetGamepad();
    InputMode inputMode = gamepad->getOptions().inputMode;

#ifdef UART_ENABLE
    uart_puts(UART_ID, "Hotkey Pressed ");
    sprintf(string_a, "%02x ", inputMode);
    uart_puts(UART_ID, string_a);
#endif

    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonB1.buttonMask) inputMode = INPUT_MODE_XBOXORIGINAL; /* B1 XBOX */
    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonB2.buttonMask) inputMode = INPUT_MODE_PCEMINI; /* B2 PCEMINI */
    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonR2.buttonMask) inputMode = INPUT_MODE_NEOGEO; /* R2 NEOGEO */
    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonL2.buttonMask) inputMode = INPUT_MODE_EGRET; /* L2 EGRETII */
    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonB3.buttonMask) inputMode = INPUT_MODE_PS3; /* B3 PS3 */
    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonB4.buttonMask) inputMode = INPUT_MODE_PS4; /* B4 PS4 */
    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonR1.buttonMask) inputMode = INPUT_MODE_PSCLASSIC; /* R1 PSCLASSIC */
    if(_keyboard_host_state.buttons & _keyboard_host_mapButtonL1.buttonMask) inputMode = INPUT_MODE_MDMINI; /* L1 MDMINI/ASTRO */

#ifdef UART_ENABLE
    sprintf(string_a, "%02x ", inputMode);
    uart_puts(UART_ID, string_a);
    uart_puts(UART_ID, "\n");
#endif

    if (inputMode != gamepad->getOptions().inputMode) {
      // Save the changed input mode
      gamepad->setInputMode(inputMode);
      gamepad->save();
      //uart_puts(UART_ID, "Input mode saved.\n");
      sleep_ms(100);

      System::reboot(System::BootMode::DEFAULT); /* Restart GP2040-CE */
      while(1);
    }
    /* Wait for while */
  }

}


// convert hid keycode to ascii and print via usb device CDC (ignore non-printable)
void KeyboardHostListener::process_8bitdo24g_report(uint8_t dev_addr, uint8_t const* report, uint16_t len)
{
  if((report[0] == 0x30) && (len == 64)) /* 8BitDo 2.4G USB Stick report */
  {
    if(report[4] & 0x10) _keyboard_host_state.buttons |= _keyboard_host_mapButtonA1.buttonMask;
    if(report[4] & 0x01) _keyboard_host_state.buttons |= _keyboard_host_mapButtonS2.buttonMask;
    if(report[4] & 0x02) _keyboard_host_state.buttons |= _keyboard_host_mapButtonS1.buttonMask;
    if(report[3] & 0x04) _keyboard_host_state.buttons |= _keyboard_host_mapButtonB1.buttonMask;
    if(report[3] & 0x08) _keyboard_host_state.buttons |= _keyboard_host_mapButtonB2.buttonMask;
    if(report[3] & 0x01) _keyboard_host_state.buttons |= _keyboard_host_mapButtonB3.buttonMask;
    if(report[3] & 0x02) _keyboard_host_state.buttons |= _keyboard_host_mapButtonB4.buttonMask;
    if(report[3] & 0x40) _keyboard_host_state.buttons |= _keyboard_host_mapButtonR1.buttonMask;
    if(report[5] & 0x40) _keyboard_host_state.buttons |= _keyboard_host_mapButtonL1.buttonMask;
    if(report[3] & 0x80) _keyboard_host_state.buttons |= _keyboard_host_mapButtonR2.buttonMask;
    if(report[5] & 0x80) _keyboard_host_state.buttons |= _keyboard_host_mapButtonL2.buttonMask;
    if(report[4] & 0x04) _keyboard_host_state.buttons |= _keyboard_host_mapButtonR3.buttonMask;
    if(report[4] & 0x08) _keyboard_host_state.buttons |= _keyboard_host_mapButtonL3.buttonMask;

    /* DP mode */
    if(report[5] & 0x02) _keyboard_host_state.dpad |= _keyboard_host_mapDpadUp.buttonMask;
    if(report[5] & 0x01) _keyboard_host_state.dpad |= _keyboard_host_mapDpadDown.buttonMask;
    if(report[5] & 0x08) _keyboard_host_state.dpad |= _keyboard_host_mapDpadLeft.buttonMask;
    if(report[5] & 0x04) _keyboard_host_state.dpad |= _keyboard_host_mapDpadRight.buttonMask;

    /* LS mode */
    if(((report[6] & 0xf0) == 0xf0) && ((report[7] & 0x0f) == 0x0f)) _keyboard_host_state.lx = 0xFFFF;
    if(((report[6] & 0xf0) == 0x00) && ((report[7] & 0x0f) == 0x00)) _keyboard_host_state.lx = 0x0000;
    if(report[8] == 0xff) _keyboard_host_state.ly = 0x0000;
    if(report[8] == 0x00) _keyboard_host_state.ly = 0xFFFF;

    /* RS mode */
    if(((report[9] & 0xf0) == 0xf0) && ((report[10] & 0x0f) == 0x0f)) _keyboard_host_state.rx = 0xFFFF;
    if(((report[9] & 0xf0) == 0x00) && ((report[10] & 0x0f) == 0x00)) _keyboard_host_state.rx = 0x0000;
    if(report[11] == 0xff) _keyboard_host_state.ry = 0x0000;
    if(report[11] == 0x00) _keyboard_host_state.ry = 0xFFFF;


#if 0
    sprintf(string_a, "%08x ", _keyboard_host_state.buttons);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%02x ", _keyboard_host_state.dpad);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", _keyboard_host_state.lx);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", _keyboard_host_state.ly);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", _keyboard_host_state.rx);
    uart_puts(UART_ID, string_a);
    sprintf(string_a, "%04x ", _keyboard_host_state.ry);
    uart_puts(UART_ID, string_a);
    uart_puts(UART_ID, "\n");
#endif

    process_kbd_hotkey();
  }
}

uint8_t KeyboardHostListener::getKeycodeFromModifier(uint8_t modifier) {
	switch (modifier) {
	  case KEYBOARD_MODIFIER_LEFTCTRL   : return HID_KEY_CONTROL_LEFT ;
	  case KEYBOARD_MODIFIER_LEFTSHIFT  : return HID_KEY_SHIFT_LEFT   ;
	  case KEYBOARD_MODIFIER_LEFTALT    : return HID_KEY_ALT_LEFT     ;
	  case KEYBOARD_MODIFIER_LEFTGUI    : return HID_KEY_GUI_LEFT     ;
	  case KEYBOARD_MODIFIER_RIGHTCTRL  : return HID_KEY_CONTROL_RIGHT;
	  case KEYBOARD_MODIFIER_RIGHTSHIFT : return HID_KEY_SHIFT_RIGHT  ;
	  case KEYBOARD_MODIFIER_RIGHTALT   : return HID_KEY_ALT_RIGHT    ;
	  case KEYBOARD_MODIFIER_RIGHTGUI   : return HID_KEY_GUI_RIGHT    ;
	}

	return 0;
}

void KeyboardHostListener::preprocess_report()
{
  uint16_t joystickMid = GAMEPAD_JOYSTICK_MID;
  if ( DriverManager::getInstance().getDriver() != nullptr ) {
    joystickMid = DriverManager::getInstance().getDriver()->GetJoystickMidValue();
  }

  _keyboard_host_state.dpad = 0;
  _keyboard_host_state.buttons = 0;
  _keyboard_host_state.lx = joystickMid;
  _keyboard_host_state.ly = joystickMid;
  _keyboard_host_state.rx = joystickMid;
  _keyboard_host_state.ry = joystickMid;
  _keyboard_host_state.lt = 0;
  _keyboard_host_state.rt = 0;

}

// convert hid keycode to ascii and print via usb device CDC (ignore non-printable)
void KeyboardHostListener::process_kbd_report(uint8_t dev_addr, hid_keyboard_report_t const *report)
{
  // make this 13 instead of 7 to include modifier bitfields from hid_keyboard_modifier_bm_t
  for(uint8_t i=0; i<13; i++)
  {
    uint8_t keycode = 0;
    if (i < 6) {
        // process keycodes normally
        keycode = report->keycode[i];
    } else {
        // keycode modifiers are bitfields, so the old getKeycodeFromModifier switch approach doesn't work
        // keycode = getKeycodeFromModifier(report->modifier);
        // new approach masks the modifier bit to determine which keys are pressed
        keycode = getKeycodeFromModifier(report->modifier & (1 << (i - 6)));
    }
    if ( keycode )
    {
      _keyboard_host_state.dpad |=
            ((keycode == _keyboard_host_mapDpadUp.key)    ? _keyboard_host_mapDpadUp.buttonMask : _keyboard_host_state.dpad)
          | ((keycode == _keyboard_host_mapDpadDown.key)  ? _keyboard_host_mapDpadDown.buttonMask : _keyboard_host_state.dpad)
          | ((keycode == _keyboard_host_mapDpadLeft.key)  ? _keyboard_host_mapDpadLeft.buttonMask  : _keyboard_host_state.dpad)
          | ((keycode == _keyboard_host_mapDpadRight.key) ? _keyboard_host_mapDpadRight.buttonMask : _keyboard_host_state.dpad)
        ;

        _keyboard_host_state.buttons |=
            ((keycode == _keyboard_host_mapButtonB1.key)  ? _keyboard_host_mapButtonB1.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonB2.key)  ? _keyboard_host_mapButtonB2.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonB3.key)  ? _keyboard_host_mapButtonB3.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonB4.key)  ? _keyboard_host_mapButtonB4.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonL1.key)  ? _keyboard_host_mapButtonL1.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonR1.key)  ? _keyboard_host_mapButtonR1.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonL2.key)  ? _keyboard_host_mapButtonL2.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonR2.key)  ? _keyboard_host_mapButtonR2.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonS1.key)  ? _keyboard_host_mapButtonS1.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonS2.key)  ? _keyboard_host_mapButtonS2.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonL3.key)  ? _keyboard_host_mapButtonL3.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonR3.key)  ? _keyboard_host_mapButtonR3.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonA1.key)  ? _keyboard_host_mapButtonA1.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonA2.key)  ? _keyboard_host_mapButtonA2.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonA3.key)  ? _keyboard_host_mapButtonA3.buttonMask  : _keyboard_host_state.buttons)
          | ((keycode == _keyboard_host_mapButtonA4.key)  ? _keyboard_host_mapButtonA4.buttonMask  : _keyboard_host_state.buttons)
        ;
    }
  }
}

void KeyboardHostListener::process_mouse_report(uint8_t dev_addr, hid_mouse_report_t const * report)
{
  //------------- button state  -------------//
  _keyboard_host_state.buttons |=
      (report->buttons & MOUSE_BUTTON_LEFT   ?   mouseLeftMapping : _keyboard_host_state.buttons)
    | (report->buttons & MOUSE_BUTTON_MIDDLE ? mouseMiddleMapping : _keyboard_host_state.buttons)
    | (report->buttons & MOUSE_BUTTON_RIGHT  ?  mouseRightMapping : _keyboard_host_state.buttons)
  ;

  //------------- cursor movement -------------//
  mouseX = report->x;
  mouseY = report->y;
  mouseZ = report->wheel;
  mouseActive = true;
}
