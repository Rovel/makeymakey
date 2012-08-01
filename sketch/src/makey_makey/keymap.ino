#include <avr/eeprom.h>
extern int keyCodes[NUM_INPUTS];
#define KEY_CODES_ADDR ((void*)1)

void loadKeyMap() {
  // If the eeprom has never been set, it will be 255
  uint8_t hasMap = eeprom_read_byte(0);
  if (hasMap != 255) {
    eeprom_read_block(keyCodes, KEY_CODES_ADDR, NUM_INPUTS * 2);
  }
}

void update_eeprom_byte(uint8_t * addr, uint8_t data) {
  // This avoids unnecessary writing to eeprom, saving its lifespan
  eeprom_read_block(0,0,0);
  if (data != eeprom_read_byte(addr)) {
    eeprom_write_byte(addr, data);
  }
}

void writeKeyMap() {
  eeprom_write_block(keyCodes, KEY_CODES_ADDR, NUM_INPUTS * 2);
  // Flag that we have written a keymap
  // We do this last so that an incomplete keymap is not accidentally read.
  update_eeprom_byte(0, 0);
}