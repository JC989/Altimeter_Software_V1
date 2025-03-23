#pragma once
#ifndef ALTIMETER_H
#define ALTIMETER_H
#include "Arduino.h"
#include "Adafruit_BMP3XX.h"

// Extern declaration of bmp
extern Adafruit_BMP3XX bmp;

void setupBMP();

double readAltitude();

#endif