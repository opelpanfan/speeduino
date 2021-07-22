#ifndef OPF_CORE
#define OPF_CORE

#include "opf_core.h"

//unsigned boot_count __attribute__((__section__(".noinit")));

void setupBoard()
{
  //USBComposite.setManufacturerString("My Garage");
  //USBComposite.setProductString("My Thingy");
}

void initialiseBoard()
{
  //CAN BUS
  STM32_CAN Can0(_CAN1, DEF);
  STM32_CAN Can1(_CAN2, ALT);

  //STATUS LED
  pinMode(LED_RUNNING, OUTPUT);
  pinMode(LED_WARNING, OUTPUT);
  pinMode(LED_ALERT, OUTPUT);
  pinMode(LED_COMS, OUTPUT);

  //SPI FLASH

  // #define PIN_SERIAL_RX PA10
  // #define PIN_SERIAL_TX PA9
  // #define PIN_SERIAL2_RX PA10
  // #define PIN_SERIAL2_TX PA9
  // #define PIN_SERIAL3_RX PB10
  // #define PIN_SERIAL3_TX PB11

  pinMode(PB12, OUTPUT);
  pinMode(PB13, OUTPUT);
  pinMode(PB14, OUTPUT);
  pinMode(PB15, OUTPUT);

  HardwareSerial Serial1(PA10, PA9);
  Serial1.begin(115200);

#if defined(USE_SPI_EEPROM)

  SPIClass SPI_for_flash(113, 112, 111); //SPI1_MOSI, SPI1_MISO, SPI1_SCK

  SPI_for_flash.setMOSI(113);
  SPI_for_flash.setMISO(112);
  SPI_for_flash.setSCLK(111);
  SPI_for_flash.setSSEL(110);

  EEPROM_Emulation_Config EmulatedEEPROMMconfig{255UL, 4096UL, 31, 0x00100000UL};
  Flash_SPI_Config SPIconfig{USE_SPI_EEPROM, SPI_for_flash};
  SPI_EEPROM_Class EEPROM(EmulatedEEPROMMconfig, SPIconfig);

#define pinIsReserved(pin) (((pin) == PA11) || ((pin) == PA12) || ((pin) == USE_SPI_EEPROM))
#endif
}

void runLoop()
{
  int recval = -1;
  if (Serial.available())
  {
    //recval = Serial.read();
    digitalToggle(LED_COMS);
  }
  // if (recval != -1)
  // {
  //   Serial.write(recval);
  //   Serial1.write(recval);
  //   recval = -1;
  //   //delay(10);
  //   if (Serial1.available())
  //   {
  //     recval = Serial1.read();
  //   }
  //   if (recval != -1)
  //   {
  //     Serial.write(recval);
  //   }    
  // }

  // if ((Serial.available()) > 0)
  // {
  //   digitalToggle(LED_COMS);
  // }

  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_1HZ)) //1 hertz
  {
    digitalToggle(LED_RUNNING);
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_4HZ)) //4 hertz
  {
    digitalToggle(LED_WARNING);
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_10HZ)) //10 hertz
  {
    digitalToggle(LED_ALERT);
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_15HZ)) //15 hertz
  {
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_30HZ)) //30 hertz
  {
    digitalToggle(PB12);
    digitalToggle(PB13);
    digitalToggle(PB14);
    digitalToggle(PB15);
  }
}

#endif
