// #include "RadiationSensor.h"

// RadiationSernsor::RadiationSernsor()
//     {

//     }

// void RadiationSernsor::geiger_tube_impulse(){       //subprocedure for capturing events from Geiger Kit
//   counts++;
// }

// void RadiationSernsor::setup_geiger()
// {
//   counts = 0;
//   cpm = 0;
//   multiplier = max_period / log_period;      //calculating multiplier, depend on your log period
//   attachInterrupt(0, geiger_tube_impulse, FALLING); //define external interrupts 
// }

// void RadiationSernsor::check_geiger()
// {
//   unsigned long currentMillis = millis();
//   if(currentMillis - previousMillis > LOG_PERIOD)
//   {
//     previousMillis = currentMillis;
//     cpm = counts * multiplier;
    
//     counts = 0;
//   }
// }

// void RadiationSernsor::setLogPeriod(int logPeriod)
// {

// }

// void RadiationSernsor::setMaxPeriod(int maxPeriod)
// {

// }

// float RadiationSernsor::getClicksPerMinute()
// {

// }

// float RadiationSernsor::getRadiationInSieverts()
// {

// }

// float RadiationSernsor::getRadiationInBequerels()
// {

// }

// float RadiationSernsor::getRadiationInRoedgens()
// {

// }
// // 1 curie = 3.7 x 1010 disintegrations per second
// // 1 becquerel = 1 disintegration per second
// // 1 millicurie (mCi) = 37 megabecquerels (MBq)
// // 1 rad = 0.01 gray (Gy)
// // 1 rem = 0.01 sievert (Sv)
// // 1 roentgen (R) = 0.000258 coulomb/kilogram (C/kg)
// // 1 megabecquerel (MBq) = 0.027 millicuries (mCi)
// // 1 gray (Gy) = 100 rad
// // 1 sievert (Sv) = 100 rem