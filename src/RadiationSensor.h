// class RadiationSernsor
// {
//   public:
//     RadiationSernsor();
//     void setup_geiger();
//     void geiger_tube_impulse();
//     void check_geiger();

//     void setLogPeriod(int logPeriod);
//     void setMaxPeriod(int maxPeriod);

//     float getClicksPerMinute();
//     float getRadiationInSieverts();
//     float getRadiationInBequerels();
//     float getRadiationInRoedgens();


//   private:
//     unsigned long counts;     //variable for GM Tube events
//     unsigned long cpm;        //variable for CPM
//     unsigned int multiplier;  //variable for calculation CPM in this sketch
//     unsigned long previousMillis;  //variable for time measurement
//     unsigned int log_period=15000;    //Logging period in milliseconds, recommended value 15000-60000.
//     unsigned int max_period=60000;    //Maximum logging period without modifying this sketch

//     // #define LOG_PERIOD 15000  
//     // #define MAX_PERIOD 60000  
// };