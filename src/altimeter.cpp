#include "../include/altimeter.h"
#include "Wire.h"

Adafruit_BMP3XX bmp;

const double seaLevelPressure = 1013.25; //hpA

void setupBMP() {
  Serial.begin(9600); // Initialize Serial communication

  if(!bmp.begin_I2C()) {
    Serial.println("Could not find BMP390 sensor! Check wiring!");
    return;
   }   

  bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
  bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
  bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
  bmp.setOutputDataRate(BMP3_ODR_50_HZ); 
}


double readAltitude() {
  double current_altitude = bmp.readAltitude(seaLevelPressure);
  return current_altitude;

}
