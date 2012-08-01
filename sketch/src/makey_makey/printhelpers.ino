#include <avr/pgmspace.h>
#include "keynames.h"
#include "pinnames.h"

char buffer[30];

char *keyNameForIndex(int i) {
  strcpy_P(buffer, (char*)pgm_read_word(&(keyNames[i * 2 + 1]))); 
  return buffer;
}

int keyCodeForIndex(int i) {
  return (int)keyNames[i * 2];
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
  strcpy_P(pinbuffer, (char*)pgm_read_word(&(pinNames[pinnumber])));
  return pinbuffer;
}

void typeString(char *string) {
  int i = 0;
  while (string[i]) {
    Keyboard.press(string[i]);
    Keyboard.release(string[i]);
  }
}

void typeStringLn(char *string) {
  typeString(string);
  Keyboard.press(KEY_RETURN);
  Keyboard.release(KEY_RETURN);
}
