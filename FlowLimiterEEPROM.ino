#include <M5StickCPlus.h>
#include <EEPROM.h>

/*
 * Initialize flow-limiter EEPROM:
 * - Set device number in byte 0
 * - Set simulation mode in byte 1: 0 means simulate flow, 1 means use real HW
 * - Set initial index into flowLimitTable in byte 2
 * 
 * Use: Modify values as appropriate for new units or new EEPROM data, then load
 * the M5Stick with this sketch. It will write the EEPROM then print what it wrote
 * on serial and display "Done"
 */

#define DEVICE_NUMBER 1
#define SIMULATE_FLOW 1
#define DEFAULT_FLOW_LIMIT_INDEX 0

// EEPROM variable offsets
#define DEV_NUM_ADDR 0
#define SIM_FLOW_ADDR 1
#define FLOW_LIMIT_INDEX_ADDR 2
#define EEPROM_SIZE 3  // define the size of EEPROM(Byte).

void setup()
{
  M5.begin();
  M5.Lcd.setRotation(3);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.setTextColor(TFT_WHITE,TFT_BLACK);
  M5.Lcd.setTextSize(2);

  Serial.begin(115200);
  
  while (!EEPROM.begin(EEPROM_SIZE)) {  // Request storage of size of data
    Serial.println("\nFailed to initialise EEPROM!");
    M5.Lcd.println("EEPROM Fail");
    delay(1000000);
  }

  EEPROM.write(DEV_NUM_ADDR, DEVICE_NUMBER);
  EEPROM.write(SIM_FLOW_ADDR, SIMULATE_FLOW);
  EEPROM.write(FLOW_LIMIT_INDEX_ADDR, DEFAULT_FLOW_LIMIT_INDEX);
  EEPROM.commit();

  M5.Lcd.println("Done");
}

void loop()
{
  unsigned char deviceNum = EEPROM.read(DEV_NUM_ADDR);
  unsigned char simFlow = EEPROM.read(SIM_FLOW_ADDR);
  unsigned char flowLimitIndex = EEPROM.read(FLOW_LIMIT_INDEX_ADDR);

  Serial.printf("deviceNum: %d simFlow %d flowLimitIndex %d\n", deviceNum, simFlow, flowLimitIndex);
  delay(5000);
}
