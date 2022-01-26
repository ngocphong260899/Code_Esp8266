#include <Arduino.h>
#include <EEPROM.h>
#include <eeprom_data.h>




void rom_init()
{
     EEPROM.begin(512);
}

void rom_commit()
{
    EEPROM.commit();
}