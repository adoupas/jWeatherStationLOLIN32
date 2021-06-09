const char * FIRMWARE_VERSION = "190.1";

#define DEBUG_FAST_LOOP //makes looping faster without big delays
#define ONBOARD_LED 5

#include <limits.h> // limits for variable types (for ?)

#include <Arduino.h>
#include "IotWebConfFactory.h"
#include <IotWebConfUsing.h>
#include <string>

#include "HardwareSerial.h"
static HardwareSerial console_serial(0); // UART 0 - CONSOLE
static HardwareSerial MHZ19_serial(1);   // UART 1
static HardwareSerial PMS7003_serial(2); // UART 2

#include <MHZ19.h>                       // include CO2 sensor library
#define MHZ19_RX_PIN 32                  // Rx pin which the MHZ19 Tx pin is attached to
#define MHZ19_TX_PIN 33                  // Tx pin which the MHZ19 Rx pin is attached to
MHZ19 CO2_MHZ19;                         // Constructor for MH-Z19 class

#include <PMS.h>                          // include dust sensor library
#define PMS7003_RX_PIN 12
#define PMS7003_TX_PIN 14
PMS pms(PMS7003_serial);
PMS::DATA data;

#include <Adafruit_Sensor.h>            //include BME280 atmospheric pressure, hunidity, temperature sensor library
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1019.50)
Adafruit_BME280 bme280;

#include "telemetry.h"                //library that collects and sends data to the IoT server
Telemetry telemetry;

void read_barometric_pressure()
{
  telemetry.setBarometricPressure(bme280.readPressure() / 100);
  console_serial.println("Barometric pressure is: " + (String)telemetry.getBarometricPressure() + " hPa");
}

void read_humidity()
{
  telemetry.setHumidity(bme280.readHumidity());
  console_serial.println("Humidity is: " + (String)telemetry.getHumidity() + " %");
}

void read_BMEtemperature()
{
  telemetry.setTemperatureCelcius(bme280.readTemperature());
  console_serial.println("BME280 temperature is: " + (String)telemetry.getTemperatureCelcius() + " C");
}

void read_pms7003_data()
{
  pms.wakeUp();
  #ifdef DEBUG_FAST_LOOP
  console_serial.println("Waking up PMS7003, wait 3 seconds for stable readings...");
  IotWebConfFactory::mydelay(3000);
  #else
  console_serial.println("Waking up PMS7003, wait 30 seconds for stable readings...");
  IotWebConfFactory::mydelay(30000);
  #endif

  console_serial.println("Sending read request to PMS7003...");
  pms.requestRead();

  if (pms.readUntil(data, 2000))
  {
    telemetry.setPMS7003_MP_1(data.PM_AE_UG_1_0);
    console_serial.print("PM 1.0 (ug/m3): ");
    console_serial.println(telemetry.getPMS7003_MP_1());
    
    telemetry.setPMS7003_MP_2_5(data.PM_AE_UG_2_5);
    console_serial.print("PM 2.5 (ug/m3): ");
    console_serial.println(telemetry.getPMS7003_MP_2_5());
    
    telemetry.setPMS7003_MP_10(data.PM_AE_UG_10_0);
    console_serial.print("PM 10.0 (ug/m3): ");
    console_serial.println(telemetry.getPMS7003_MP_10());
  }
  else
  {
    console_serial.println("No PMS7003 data.");
    telemetry.setPMS7003_MP_1(-300);
    telemetry.setPMS7003_MP_2_5(-300);
    telemetry.setPMS7003_MP_10(-300);
  }

  console_serial.println("Setting PMS7003 to sleep again.");
  pms.sleep();
}

void read_mh_z19_co2_data()
{
  telemetry.setCarbonDioxide(CO2_MHZ19.getCO2());
  
  console_serial.print("CO2: ");
  console_serial.println(telemetry.getCarbonDioxide());
}

void setup() 
{
  pinMode(ONBOARD_LED,OUTPUT);  //we'll use it to blink it every time we send data to server

  console_serial.begin(115200, SERIAL_8N1, 3, 1);  //start serial output for debugging

  telemetry.setFirmwareVersion(FIRMWARE_VERSION); //pass firmware version to telemetry object

  //setup PMS7003 sensor
  PMS7003_serial.begin(PMS::BAUD_RATE, SERIAL_8N1, -1,-1);
  
  //setup CO2 sensor
  delay(100); //delay workaround for MHZ19 sensor readings in standalone power mode 
  MHZ19_serial.begin(9600, SERIAL_8N1, -1,-1); 
  CO2_MHZ19.begin(MHZ19_serial);                                // *Important, Pass your Stream reference 
  CO2_MHZ19.autoCalibration();                              // Turn auto calibration ON (disable with autoCalibration(false))

  delay(1000);   // why?
  
  // setup BME280 sensor
  unsigned bme280_status;
  bme280_status = bme280.begin(0x76); //set bme280 address manually  
  if (!bme280_status) 
  {
      console_serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
      console_serial.print("SensorID was: 0x"); 
      console_serial.println(bme280.sensorID(),16);
      console_serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
      console_serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
      console_serial.print("        ID of 0x60 represents a BME 280.\n");
      console_serial.print("        ID of 0x61 represents a BME 680.\n");
  } 
  else 
  {
      console_serial.println("BME280 initialization success");
  }

  IotWebConfFactory::setup();

  console_serial.println("Setup done! Entering environmental monitoring station main loop");
}

void loop() {
  console_serial.println("Begin loop");
  // console_serial.println("Firmware version: " + str(FIRMWARE_VERSION));

  //wait time in sec before reading sensors again
  #ifdef DEBUG_FAST_LOOP
  static unsigned long DEVICE_DELAY_MS = 15000; //15 seconds
  #else
  static unsigned long DEVICE_DELAY_MS = 300000; //300 seconds
  #endif
  
  IotWebConfFactory::loop();
  //setTelemetryUrl, setTelemetryToken and setTelemetryPort should be called on IoTWebConfFactory::configSaved callback.
  //Till we implement the callback, we use it as it is bellow for simplicity
  telemetry.setTelemetryUrl(IotWebConfFactory::getConfigUrl());
  telemetry.setTelemetryToken(IotWebConfFactory::getConfigToken());
  telemetry.setTelemetryPort(IotWebConfFactory::getConfigPort());

  read_pms7003_data();
  
  read_mh_z19_co2_data();

  read_barometric_pressure();
  read_humidity();
  read_BMEtemperature();
  
  //send all sensor data to the IoT server
  digitalWrite(ONBOARD_LED,LOW);
  telemetry.send_data_to_iot_server();
  // telemetry.send_data_to_iot_server2();
  digitalWrite(ONBOARD_LED,HIGH);

  console_serial.println("Delaying for: " + (String)(DEVICE_DELAY_MS / 1000) + " sec before next read..");
  console_serial.println("\n");
  IotWebConfFactory::mydelay(DEVICE_DELAY_MS);
}
