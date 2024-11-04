#ifndef EEPROM_ALLOC_H
#define EEPROM_ALLOC_H

enum eeprom_address {
    throtTrigPressed_ = 0,
    throtTrigUnpressed_ = 2,
    regenTrigPressed_ = 4,
    regenTrigUnpressed_ = 6,
    throtPedal1Pressed_ = 8,
    throtPedal1Unpressed_ = 10,
    throtPedal2Pressed_ = 12,
    throtPedal2Unpressed_ = 14,
};

#endif