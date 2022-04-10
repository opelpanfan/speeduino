#ifndef OPF_CORE
#define OPF_CORE

#include "opf_core.h"

#ifdef USE_I2C_BARO
TwoWire LPS_dev(PIN_WIRE_SDA, PIN_WIRE_SCL);
LPS22HHSensor LPS_Sensor(&LPS_dev, LPS22HH_I2C_ADD_L);
#endif //USE_I2C_BARO

#ifdef USE_DBW_IFX9201

HardwareTimer Timer10(TIM10);
IFX9201 IFX9201_HBridge = IFX9201( );

#endif //USE_DBW_IFX9201

void setupBoard()
{
  resetPins();
  setPins();
  configPage2.pinMapping = 60;

  STM32_CAN Can0(_CAN1, DEF);
  STM32_CAN Can1(_CAN2, DEF);

  //STATUS LED
  pinMode(LED_RUNNING, OUTPUT);
  digitalWrite(LED_RUNNING, LOW);
  pinMode(LED_WARNING, OUTPUT);
  digitalWrite(LED_WARNING, LOW);
  pinMode(LED_ALERT, OUTPUT);
  digitalWrite(LED_ALERT, LOW);
  pinMode(LED_COMS, OUTPUT);
  digitalWrite(LED_COMS, LOW);
  #ifdef USE_SPI_EEPROM
    EEPROM.begin(SPI_for_flash, PIN_SPI_SS);
  #endif
  #ifdef USE_I2C_BARO
    LPS_dev.begin();
    LPS_Sensor.begin();
    LPS_Sensor.Enable();
  #endif //USE_I2C_BARO

  #ifdef USE_DBW_IFX9201
    // Timer10.setMode(1, TIMER_OUTPUT_COMPARE_PWM1, DIS_PIN);  //DBW PWM output fixed to PB8/
    // Timer10.setOverflow(20000, HERTZ_FORMAT);
    // Timer10.setCaptureCompare(1, 0, RESOLUTION_12B_COMPARE_FORMAT);
    // Timer10.resume();
    //IFX9201_HBridge.begin( DIR_PIN, STP_PIN, DIS_PIN );

    //IFX9201_HBridge.forwards( 50 );       // Same as forwards( )
    //IFX9201_HBridge.stop( );
    //IFX9201_HBridge.backwards( 50 );
    //IFX9201_HBridge.stop( );

    // TIM_TypeDef *Instance = (TIM_TypeDef *)pinmap_peripheral(digitalPinToPinName(DIS_PIN), PinMap_PWM);
    // uint32_t channel = STM_PIN_CHANNEL(pinmap_function(digitalPinToPinName(DIS_PIN), PinMap_PWM));
    //Timer10->setPWM(channel, DIS_PIN, 10, 50, dbwScheduleInterrupt);

    //DBWMotor.begin();
    //DBWMotor.setSpeed(100);
  #endif //USE_DBW_IFX9201

  initialiseAll();
  
  Can0.begin();
  Can0.setBaudRate(500000);
  Can0.enableFIFO();
  
  Can1.begin();
  Can1.setBaudRate(500000);
  Can1.enableFIFO();
}

#ifdef USE_DBW_IFX9201
void dbwScheduleInterrupt(){
  digitalToggle(LED_WARNING);
}
#endif //USE_DBW_IFX9201


void setPins()
{
//******************************************
  //******** Trigger CONNECTIONS ***************
  //******************************************

  pinTrigger = PE2; //106
  //pinTrigger2 = PE3;  //107
  //pinTrigger3 = PE4;  //104
  //pinVSS = PE5;       //105

  //******************************************
  //******** ANALOG CONNECTIONS ***************
  //******************************************

  pinBat = PA0;  //A12
  pinCLT = PA3;  //A7
  pinTPS = PA2;  //A9
  pinIAT = PA4;  //A8
  pinO2 = PC1;   //A13
  //pinO2_2 = PC2; //A14
  //pinBaro = PC5; //A1
  pinMAP = PA5;   //A5
  pinOilPressure = PA1;  //A0
  //pinSpareTemp1 = PC4; //OIL TEMP
  //pinSpareTemp2 =;
  //pinFuelPressure = PC4; //A2
  //pinFuel = PC4; //A2

  //******************************************
  //******** INJECTOR CONNECTIONS ***************
  //******************************************

  //pinInjector8 = PD11; //9
  //pinInjector7 = PD12; //8
  //pinInjector6 = PD11; //7
  //pinInjector5 = PD10; //6
  //pinInjector4 = PD12;  //5
  //pinInjector3 = PG5;//PF14;  //4
  pinInjector2 = PD13; //71
  pinInjector1 = PF13; //70

  //******************************************
  //******** COIL CONNECTIONS ***************
  //******************************************

  pinCoil1 = PG0; //59
  pinCoil2 = PF15; //58
  //pinCoil3 = PE13; //61
  //pinCoil4 = PE12; //60
  //pinCoil5 = PE11; //63
  //pinCoil6 = PF15; //68
  //pinCoil7 = PG0;  //69
  //pinCoil8 = PG1;  //66

  //******************************************
  //******** OTHER CONNECTIONS ***************
  //******************************************

  //pinTachOut = PG5;    //10
  pinIdle1 = PD11;      //11
  //pinIdle2 = PG2;       //12
  pinBoost = PD12;       //13
  //pinStepperDir = PG4;  //14
  //pinStepperStep = PG5; //15
  pinFuelPump = PG7;    //16
  pinFan = PG6;         //17
  //pinLaunch = PF5;      
}

void resetPins()
{
  pinInjector1 = BOARD_MAX_IO_PINS - 1;
  pinInjector2 = BOARD_MAX_IO_PINS - 1;
  pinInjector3 = BOARD_MAX_IO_PINS - 1;
  pinInjector4 = BOARD_MAX_IO_PINS - 1;
  pinInjector5 = BOARD_MAX_IO_PINS - 1;
  pinInjector6 = BOARD_MAX_IO_PINS - 1;
  pinInjector7 = BOARD_MAX_IO_PINS - 1;
  pinInjector8 = BOARD_MAX_IO_PINS - 1;
  injectorOutputControl = 0;
  pinCoil1 = BOARD_MAX_IO_PINS - 1;
  pinCoil2 = BOARD_MAX_IO_PINS - 1;
  pinCoil3 = BOARD_MAX_IO_PINS - 1;
  pinCoil4 = BOARD_MAX_IO_PINS - 1;
  pinCoil5 = BOARD_MAX_IO_PINS - 1;
  pinCoil6 = BOARD_MAX_IO_PINS - 1;
  pinCoil7 = BOARD_MAX_IO_PINS - 1;
  pinCoil8 = BOARD_MAX_IO_PINS - 1;
  ignitionOutputControl = 0;
  pinTrigger = BOARD_MAX_IO_PINS - 1;
  pinTrigger2 = BOARD_MAX_IO_PINS - 1;
  pinTrigger3 = BOARD_MAX_IO_PINS - 1;
  pinTPS = BOARD_MAX_IO_PINS - 1;
  pinMAP = BOARD_MAX_IO_PINS - 1;
  pinEMAP = BOARD_MAX_IO_PINS - 1;
  pinMAP2 = BOARD_MAX_IO_PINS - 1;
  pinIAT = BOARD_MAX_IO_PINS - 1;
  pinCLT = BOARD_MAX_IO_PINS - 1;
  pinO2 = BOARD_MAX_IO_PINS - 1;
  pinO2_2 = BOARD_MAX_IO_PINS - 1;
  pinBat = BOARD_MAX_IO_PINS - 1;
  pinDisplayReset = BOARD_MAX_IO_PINS - 1;
  pinTachOut = BOARD_MAX_IO_PINS - 1;
  pinFuelPump = BOARD_MAX_IO_PINS - 1;
  pinIdle1 = BOARD_MAX_IO_PINS - 1;
  pinIdle2 = BOARD_MAX_IO_PINS - 1;
  pinIdleUp = BOARD_MAX_IO_PINS - 1;
  pinIdleUpOutput = BOARD_MAX_IO_PINS - 1;
  pinCTPS = BOARD_MAX_IO_PINS - 1;
  pinFuel2Input = BOARD_MAX_IO_PINS - 1;
  pinSpark2Input = BOARD_MAX_IO_PINS - 1;
  pinSpareTemp1 = BOARD_MAX_IO_PINS - 1;
  pinSpareTemp2 = BOARD_MAX_IO_PINS - 1;
  pinSpareOut1 = BOARD_MAX_IO_PINS - 1;
  pinSpareOut2 = BOARD_MAX_IO_PINS - 1;
  pinSpareOut3 = BOARD_MAX_IO_PINS - 1;
  pinSpareOut4 = BOARD_MAX_IO_PINS - 1;
  pinSpareOut5 = BOARD_MAX_IO_PINS - 1;
  pinSpareOut6 = BOARD_MAX_IO_PINS - 1;
  pinSpareHOut1 = BOARD_MAX_IO_PINS - 1;
  pinSpareHOut2 = BOARD_MAX_IO_PINS - 1;
  pinSpareLOut1 = BOARD_MAX_IO_PINS - 1;
  pinSpareLOut2 = BOARD_MAX_IO_PINS - 1;
  pinSpareLOut3 = BOARD_MAX_IO_PINS - 1;
  pinSpareLOut4 = BOARD_MAX_IO_PINS - 1;
  pinSpareLOut5 = BOARD_MAX_IO_PINS - 1;
  pinBoost = BOARD_MAX_IO_PINS - 1;
  pinVVT_1 = BOARD_MAX_IO_PINS - 1;
  pinVVT_2 = BOARD_MAX_IO_PINS - 1;
  pinFan = BOARD_MAX_IO_PINS - 1;
  pinStepperDir = BOARD_MAX_IO_PINS - 1;
  pinStepperStep = BOARD_MAX_IO_PINS - 1;
  pinStepperEnable = BOARD_MAX_IO_PINS - 1;
  pinLaunch = BOARD_MAX_IO_PINS - 1;
  pinIgnBypass = BOARD_MAX_IO_PINS - 1;
  pinFlex = BOARD_MAX_IO_PINS - 1;
  pinVSS = BOARD_MAX_IO_PINS - 1;
  pinBaro = BOARD_MAX_IO_PINS - 1;
  pinResetControl = BOARD_MAX_IO_PINS - 1;
  pinFuelPressure = BOARD_MAX_IO_PINS - 1;
  pinOilPressure = BOARD_MAX_IO_PINS - 1;
  pinWMIEmpty = BOARD_MAX_IO_PINS - 1;
  pinWMIIndicator = BOARD_MAX_IO_PINS - 1;
  pinWMIEnabled = BOARD_MAX_IO_PINS - 1;
  pinMC33810_1_CS = BOARD_MAX_IO_PINS - 1;
  pinMC33810_2_CS = BOARD_MAX_IO_PINS - 1;
}

void runLoop()
{
  if ((Serial.available()) > 0)
  {
    digitalToggle(LED_COMS);
  }
  else
  {
    digitalWrite(LED_COMS, LOW);
  }

#ifdef USE_CAN_DASH
  dash_generic(&Can1);
#endif
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_1HZ)) // 1 hertz
  {
#ifdef USE_I2C_BARO
    float pressure;
    float temperature;
    LPS_Sensor.GetPressure(&pressure);
    LPS_Sensor.GetTemperature(&temperature);
    currentStatus.fuelTemp = temperature;
    currentStatus.baro = pressure / 10.0f;
#endif
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_4HZ)) // 4 hertz
  {
    digitalWrite(LED_ALERT, currentStatus.engineProtectStatus);
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_10HZ)) // 10 hertz
  {
    digitalToggle(LED_RUNNING);
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_15HZ)) // 15 hertz
  {
  }
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_30HZ)) // 30 hertz
  {
  }
}

void dash_generic(STM32_CAN *can)
{
  if (BIT_CHECK(LOOP_TIMER, BIT_TIMER_30HZ))
  {
    // (SensorValue * sensorMultiplier - offset) * DIV
    outMsg.id = 0x5F0;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(currentStatus.RPM);            // ECU_RPM
    outMsg.buf[1] = highByte(currentStatus.RPM);           // ECU_RPM
    outMsg.buf[2] = lowByte(currentStatus.TPS * 10 * 65);  // ECU_TPS
    outMsg.buf[3] = highByte(currentStatus.TPS * 10 * 65); // ECU_TPS
    outMsg.buf[4] = lowByte(0x00);                         // ECU_PPS
    outMsg.buf[5] = highByte(0x00);                        // ECU_PPS
    outMsg.buf[6] = lowByte(currentStatus.vss * 10 * 10);  // ECU_VEH_SPD
    outMsg.buf[7] = highByte(currentStatus.vss * 10 * 10); // ECU_VEH_SPD
    can->write(outMsg);

    outMsg.id = 0x5F1;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);  // ECU_WS_FR
    outMsg.buf[1] = highByte(0x00); // ECU_WS_FR
    outMsg.buf[2] = lowByte(0x00);  // ECU_WS_FL
    outMsg.buf[3] = highByte(0x00); // ECU_WS_FL
    outMsg.buf[4] = lowByte(0x00);  // ECU_WS_RR
    outMsg.buf[5] = highByte(0x00); // ECU_WS_RR
    outMsg.buf[6] = lowByte(0x00);  // ECU_WS_RL
    outMsg.buf[7] = highByte(0x00); // ECU_WS_RL
    can->write(outMsg);

    outMsg.id = 0x5F2;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte((((uint16_t)currentStatus.IAT * 10) - (-450)) * 19);       // ECU_INT_AIR_T
    outMsg.buf[1] = highByte((((uint16_t)currentStatus.IAT * 10) - (-450)) * 19);      // ECU_INT_AIR_T
    outMsg.buf[2] = lowByte((((uint16_t)currentStatus.coolant * 10) - (-450)) * 19);   // ECU_ENG_T
    outMsg.buf[3] = highByte((((uint16_t)currentStatus.coolant * 10) - (-450)) * 19);  // ECU_ENG_T
    outMsg.buf[4] = lowByte((((uint16_t)currentStatus.fuelTemp * 10) - (-450)) * 19);  // ECU_FUEL_T
    outMsg.buf[5] = highByte((((uint16_t)currentStatus.fuelTemp * 10) - (-450)) * 19); // ECU_FUEL_T
    outMsg.buf[6] = lowByte(0x00);                                                     // ECU_OIL_T
    outMsg.buf[7] = highByte(0x00);                                                    // ECU_OIL_T
    can->write(outMsg);
    
    delay(1);

    outMsg.id = 0x5F3;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(((uint16_t)currentStatus.MAP * 10) * 10);                          // ECU_MAN_AIR_P in kPa to mBar need * 10
    outMsg.buf[1] = highByte(((uint16_t)currentStatus.MAP * 10) * 10);                         // ECU_MAN_AIR_P in kPa to mBar need * 10
    outMsg.buf[2] = lowByte(((uint16_t)currentStatus.baro * 10) * 10);                         // ECU_BARO in kPa to mBar need * 10
    outMsg.buf[3] = highByte(((uint16_t)currentStatus.baro * 10) * 10);                        // ECU_BARO in kPa to mBar need * 10
    outMsg.buf[4] = lowByte(((uint16_t)(currentStatus.oilPressure * 0.0689476f * 10) * 100));  // ECU_OIL_P PSI to BAR * 6.89476f
    outMsg.buf[5] = highByte(((uint16_t)(currentStatus.oilPressure * 0.0689476f * 10) * 100)); // ECU_OIL_P PSI to BAR * 6.89476f
    outMsg.buf[6] = lowByte(((uint16_t)(currentStatus.fuelPressure * 0.0689476f * 10) * 2));   // ECU_FUEL_P PSI to BAR * 0.0689476f
    outMsg.buf[7] = highByte(((uint16_t)(currentStatus.fuelPressure * 0.0689476f * 10) * 2));  // ECU_FUEL_P PSI to BAR * 0.0689476f
    can->write(outMsg);

    outMsg.id = 0x5F4;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte((currentStatus.MAP - currentStatus.baro) * 10 * 10);  // ECU_BOOST in mBar
    outMsg.buf[1] = highByte((currentStatus.MAP - currentStatus.baro) * 10 * 10); // ECU_BOOST in mBar
    outMsg.buf[2] = lowByte(currentStatus.battery10 * 32 * 10);                   // ECU_V_BATT
    outMsg.buf[3] = highByte(currentStatus.battery10 * 32 * 10);                  // ECU_V_BATT
    outMsg.buf[4] = lowByte(0x00);                                                // ECU_FUEL_USE
    outMsg.buf[5] = highByte(0x00);                                               // ECU_FUEL_USE
    outMsg.buf[6] = lowByte((int16_t)currentStatus.gear);                         // ECU_GEAR
    outMsg.buf[7] = highByte((int16_t)currentStatus.gear);                        // ECU_GEAR
    can->write(outMsg);

    outMsg.id = 0x5F5;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);  // ECU_SHIFT_FLAG
    outMsg.buf[1] = highByte(0x00); // ECU_SHIFT_FLAG
    outMsg.buf[2] = lowByte(0x00);  // ECU_GEAR_TIME
    outMsg.buf[3] = highByte(0x00); // ECU_GEAR_TIME
    outMsg.buf[4] = lowByte(0x00);  // ECU_THRT_VOLT
    outMsg.buf[5] = highByte(0x00); // ECU_THRT_VOLT
    outMsg.buf[6] = lowByte(0x00);  // ECU_FUEL_LEV
    outMsg.buf[7] = highByte(0x00); // ECU_FUEL_LEV
    can->write(outMsg);
    
    delay(1);

    outMsg.id = 0x5F6;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte((uint16_t)((currentStatus.O2 / 14.7f * 100) * 2));    // ECU_LAMBDA1
    outMsg.buf[1] = highByte((uint16_t)((currentStatus.O2 / 14.7f * 100) * 2));   // ECU_LAMBDA1
    outMsg.buf[2] = lowByte((uint16_t)((currentStatus.O2_2 / 14.7f * 100) * 2));  // ECU_LAMBDA2
    outMsg.buf[3] = highByte((uint16_t)((currentStatus.O2_2 / 14.7f * 100) * 2)); // ECU_LAMBDA2
    outMsg.buf[4] = lowByte(0x00);                                                // ECU_LAMBDA_T1
    outMsg.buf[5] = highByte(0x00);                                               // ECU_LAMBDA_T1
    outMsg.buf[6] = lowByte(0x00);                                                // ECU_LAMBDA_T2
    outMsg.buf[7] = highByte(0x00);                                               // ECU_LAMBDA_T2
    can->write(outMsg);

    outMsg.id = 0x5F7;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);                                                     // ECU_LAMB1_ERR
    outMsg.buf[1] = highByte(0x00);                                                    // ECU_LAMB1_ERR
    outMsg.buf[2] = lowByte(0x00);                                                     // ECU_LAMB2_ERR
    outMsg.buf[3] = highByte(0x00);                                                    // ECU_LAMB2_ERR
    outMsg.buf[4] = lowByte((uint16_t)((currentStatus.afrTarget / 14.7f * 100) * 2));  // ECU_LAMB1_TARGET
    outMsg.buf[5] = highByte((uint16_t)((currentStatus.afrTarget / 14.7f * 100) * 2)); // ECU_LAMB1_TARGET
    outMsg.buf[6] = lowByte((uint16_t)((currentStatus.afrTarget / 14.7f * 100) * 2));  // ECU_LAMB2_TARGET
    outMsg.buf[7] = highByte((uint16_t)((currentStatus.afrTarget / 14.7f * 100) * 2)); // ECU_LAMB2_TARGET
    can->write(outMsg);

    outMsg.id = 0x5F8;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);  // ECU_STEER_POS
    outMsg.buf[1] = highByte(0x00); // ECU_STEER_POS
    outMsg.buf[2] = lowByte(0x00);  // ECU_STEER_SPD
    outMsg.buf[3] = highByte(0x00); // ECU_STEER_SPD
    outMsg.buf[4] = lowByte(0x00);  // ECU_BRK_P
    outMsg.buf[5] = highByte(0x00); // ECU_BRK_P
    outMsg.buf[6] = lowByte(0x00);  // ECU_CLUCH_P
    outMsg.buf[7] = highByte(0x00); // ECU_CLUCH_P
    can->write(outMsg);

    delay(1);

    outMsg.id = 0x5F9;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);  // ECU_BRK_P_FR
    outMsg.buf[1] = highByte(0x00); // ECU_BRK_P_FR
    outMsg.buf[2] = lowByte(0x00);  // ECU_BRK_P_FL
    outMsg.buf[3] = highByte(0x00); // ECU_BRK_P_FL
    outMsg.buf[4] = lowByte(0x00);  // ECU_BRK_P_RR
    outMsg.buf[5] = highByte(0x00); // ECU_BRK_P_RR
    outMsg.buf[6] = lowByte(0x00);  // ECU_BRK_P_RL
    outMsg.buf[7] = highByte(0x00); // ECU_BRK_P_RL
    can->write(outMsg);

    outMsg.id = 0x5FA;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);  // ECU_ACC_LAT
    outMsg.buf[1] = highByte(0x00); // ECU_ACC_LAT
    outMsg.buf[2] = lowByte(0x00);  // ECU_ACC_LONG
    outMsg.buf[3] = highByte(0x00); // ECU_ACC_LONG
    outMsg.buf[4] = lowByte(0x00);  // ECU_GYRO
    outMsg.buf[5] = highByte(0x00); // ECU_GYRO
    outMsg.buf[6] = lowByte(0x00);  // ECU_GEAR_BOX_T
    outMsg.buf[7] = highByte(0x00); // ECU_GEAR_BOX_T
    can->write(outMsg);

    outMsg.id = 0x5FB;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);                                            // ECU_ENG_TORQ
    outMsg.buf[1] = highByte(0x00);                                           // ECU_ENG_TORQ
    outMsg.buf[2] = lowByte(0x00);                                            // ECU_SLIP_ANG
    outMsg.buf[3] = highByte(0x00);                                           // ECU_SLIP_ANG
    outMsg.buf[4] = lowByte((uint16_t)((currentStatus.injAngle * 100) * 3));  // ECU_IGN_ANG1
    outMsg.buf[5] = highByte((uint16_t)((currentStatus.injAngle * 100) * 3)); // ECU_IGN_ANG1
    outMsg.buf[6] = lowByte((uint16_t)((currentStatus.injAngle * 100) * 3));  // ECU_IGN_ANG2
    outMsg.buf[7] = highByte((uint16_t)((currentStatus.injAngle * 100) * 3)); // ECU_IGN_ANG2
    can->write(outMsg);
    
    delay(1);

    outMsg.id = 0x5FC;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte((uint16_t)(currentStatus.PW1 / 1000.0f * 10));  // ECU_INJ_TIME1
    outMsg.buf[1] = highByte((uint16_t)(currentStatus.PW1 / 1000.0f * 10)); // ECU_INJ_TIME1
    outMsg.buf[2] = lowByte((uint16_t)(currentStatus.PW2 / 1000.0f * 10));  // ECU_INJ_TIME2
    outMsg.buf[3] = highByte((uint16_t)(currentStatus.PW2 / 1000.0f * 10)); // ECU_INJ_TIME2
    outMsg.buf[4] = lowByte(0x00);                                          // ECU_INJ_P1
    outMsg.buf[5] = highByte(0x00);                                         // ECU_INJ_P1
    outMsg.buf[6] = lowByte(0x00);                                          // ECU_INJ_P2
    outMsg.buf[7] = highByte(0x00);                                         // ECU_INJ_P2
    can->write(outMsg);

    outMsg.id = 0x5FD;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte((int16_t)((currentStatus.advance * 100) * 3));   // ECU_SPARK_ANG_1
    outMsg.buf[1] = highByte((int16_t)((currentStatus.advance * 100) * 3));  // ECU_SPARK_ANG_1
    outMsg.buf[2] = lowByte((int16_t)((currentStatus.advance * 100) * 3));   // ECU_SPARK_ANG_2
    outMsg.buf[3] = highByte((int16_t)((currentStatus.advance * 100) * 3));  // ECU_SPARK_ANG_2
    outMsg.buf[4] = lowByte((int16_t)((currentStatus.advance1 * 100) * 3));  // ECU_SPARK_ADV_1
    outMsg.buf[5] = highByte((int16_t)((currentStatus.advance1 * 100) * 3)); // ECU_SPARK_ADV_1
    outMsg.buf[6] = lowByte((int16_t)((currentStatus.advance2 * 100) * 3));  // ECU_SPARK_ADV_2
    outMsg.buf[7] = highByte((int16_t)((currentStatus.advance2 * 100) * 3)); // ECU_SPARK_ADV_2
    can->write(outMsg);

    outMsg.id = 0x5FE;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);  // ECC_USER01
    outMsg.buf[1] = highByte(0x00); // ECC_USER01
    outMsg.buf[2] = lowByte(0x00);  // ECC_USER02
    outMsg.buf[3] = highByte(0x00); // ECC_USER02
    outMsg.buf[4] = lowByte(0x00);  // ECC_USER03
    outMsg.buf[5] = highByte(0x00); // ECC_USER03
    outMsg.buf[6] = lowByte(0x00);  // ECC_USER04
    outMsg.buf[7] = highByte(0x00); // ECC_USER04
    can->write(outMsg);
    
    delay(1);

    outMsg.id = 0x5FF;
    outMsg.len = 8;
    outMsg.buf[0] = lowByte(0x00);  // ECC_USER05
    outMsg.buf[1] = highByte(0x00); // ECC_USER05
    outMsg.buf[2] = lowByte(0x00);  // ECC_USER06
    outMsg.buf[3] = highByte(0x00); // ECC_USER06
    outMsg.buf[4] = lowByte(0x00);  // ECC_USER07
    outMsg.buf[5] = highByte(0x00); // ECC_USER07
    outMsg.buf[6] = lowByte(0x00);  // ECC_USER08
    outMsg.buf[7] = highByte(0x00); // ECC_USER08
    can->write(outMsg);
  }
}


#endif
