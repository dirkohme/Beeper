//==============================================================================
// Beep - example for beep
// piezo crystal is connected between GPIO D0 and GPIO D8
// (c) 2019-2022 by Dirk Ohme
//==============================================================================

//---| definitions |------------------------------------------------------------
#undef TEST
//#define TEST

//---| includes |---------------------------------------------------------------
#if defined(ESP8266)
#  include <pgmspace.h>
#else
#  include <avr/pgmspace.h>
#endif
#include <Arduino.h>
#include <Beeper.h>

//---| static variables |-----------------------------------------------------
bool    boToggle_m = false;
CBeeper coBeep_m(D8, D0, false);

//------------------------------------------------------------------------------
// setup routine
//------------------------------------------------------------------------------
void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
	digitalWrite(LED_BUILTIN, HIGH);
	coBeep_m.Init();
}

//------------------------------------------------------------------------------
// main loop
//------------------------------------------------------------------------------
void loop()
{
	boToggle_m = !boToggle_m;
	digitalWrite(LED_BUILTIN, boToggle_m ? HIGH : LOW);
	coBeep_m.Beep(1000000);
}

//===| eof - end of file |======================================================
