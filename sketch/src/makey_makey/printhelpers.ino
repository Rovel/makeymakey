#include <avr/pgmspace.h>
#include "keynames.h"
#include "pinnames.h"

char buffer[30];

char *keyNameForIndex(int i) {
  memcpy_P (buffer, (void*)(pgm_read_word(&allKeyNamesFunny[0]) + KEY_NAME_LENGTH * i), KEY_NAME_LENGTH);
  buffer[KEY_NAME_LENGTH] = 0;
  return buffer;
}

int keyCodeForIndex(int i) {
  return (int) keyNames[i * 2];
}

int indexForCode(int code) {
  for (int i = 0; i < NUM_ALL_KEYS; i++) {
    if (keyCodeForIndex(i) == code) {
      return i;
    }  
  }
  return -1;
}

char *keyNameForCode(int code) {
  int i = indexForCode(code);
  if (i >= 0) {
     return keyNameForIndex(i);
  }
  return "NONE";
}

char pinbuffer[30];

char *pinName(int pinnumber) {
  memcpy_P (pinbuffer, (void*)(pgm_read_word(&pin_funny[0]) + PIN_NAME_LENGTH*pinnumber), PIN_NAME_LENGTH);
  pinbuffer[PIN_NAME_LENGTH] = 0;
  return pinbuffer;
}

void typeString(char *string) {
  Serial.print(string);
  while(*string) {
    Keyboard.press(*string);
    cycleLEDs();
    delay(10);
    Keyboard.release(*string);
    string++;
  }
}

void typeStringLn(char *string) {
  typeString(string);
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}
