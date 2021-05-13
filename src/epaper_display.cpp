
// #include <LOLIN_EPD.h>
// #include <Adafruit_GFX.h>
/*D32 Pro*/
// #define EPD_CS 14
// #define EPD_DC 27
// #define EPD_RST 33     // can set to -1 and share with microcontroller Reset!
// #define EPD_BUSY -1    // can set to -1 to not use a pin (will wait a fixed delay)

// LOLIN_IL3897 EPD(250, 122, EPD_DC, EPD_RST, EPD_CS, EPD_BUSY); //hardware SPI


// uint8_t PercentageFromVoltage(float voltage) {
//   // LOLIN D32 (no voltage divider need already fitted to board.
//   // or NODEMCU ESP32 with 100K+100K voltage divider
//   uint8_t percentage;
//   percentage = 2808.3808 * pow(voltage, 4) - 43560.9157 * pow(voltage, 3) + 252848.5888 * pow(voltage, 2) - 650767.4615 * voltage + 626532.5703;
//   if (voltage > 4.19) percentage = 100;
//   else if (voltage <= 3.50) percentage = 0;

//   return percentage;
// }

// void showVoltagePercentage() {
//   float voltage = analogRead(35) / 4096.0 * 7.23;
//   uint8_t percentage = PercentageFromVoltage(voltage);

//   console_serial.println(String(voltage)+"V " + String(percentage)+"%");
// }

// setup()
// {
      // EPD.begin();
  // EPD.setTextSize(3);
  // EPD.clearBuffer();
  // EPD.setTextColor(EPD_RED);
  // delay(100);

  // EPD.clearBuffer();
  // EPD.fillScreen(EPD_WHITE);
  // EPD.setCursor(0,0);

  // EPD.println("Humidity = " + String(telemetry.getHumidity()) + "%");

  // EPD.display();
// }

// loop()
// {
    //   EPD.begin();
//   EPD.clearBuffer();
// //  EPD.setTextWrap(true);
//   EPD.setTextSize(3);
//   EPD.setTextColor(EPD_BLACK);
//   EPD.setCursor(10, 18);    // 10 to the right and 18 down 
//   EPD.print("Temp:");
//   EPD.setCursor(177, 18);   // 177 to the right and 18 down
//   EPD.print(".  C");
//   EPD.setCursor(10, 58);    // 10 to the right and 58 down 
//   EPD.print("Humi:");
//   EPD.setCursor(177, 58);   // 177 to the right and 58 down
//   EPD.print(".  %");
//   EPD.partInit();
//   delay(100);
// }