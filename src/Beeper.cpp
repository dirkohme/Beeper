/*
 The MIT License (MIT)

 Copyright (c) 2019-2020 Dirk Ohme

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

//---| definitions |----------------------------------------------------------
#undef TEST

//---| includes |-------------------------------------------------------------
#if defined(ESP8266)
#  include <pgmspace.h>
#else
#  include <avr/pgmspace.h>
#endif
#include <Arduino.h>
#include "Beeper.h"

//----------------------------------------------------------------------------
// constructor
//----------------------------------------------------------------------------
CBeeper::CBeeper(const int  iGPIO    /*= -1*/,
                 const int  iGPIONeg /*= -1*/,
                 const bool boNeg    /*= false*/,
		 const bool boAuto   /*= false*/)
{
	InitInternal(iGPIO, iGPIONeg, boNeg, boAuto);
}

//----------------------------------------------------------------------------
// init internally
//----------------------------------------------------------------------------
void CBeeper::InitInternal(const int  iGPIO    /*= -1*/,
                           const int  iGPIONeg /*= -1*/,
                           const bool boNeg    /*= false*/,
			   const bool boAuto   /*= false*/)
{
	m_boAuto         = boAuto;
	m_boInit         = (iGPIO >= 0) ? true : false;
	m_iDelayMicroSec = 100;
	m_iGPIO          = iGPIO;
	m_iGPIONeg       = iGPIONeg;
	m_iLevelLow      = (boNeg) ? HIGH : LOW;
	m_iLevelHigh     = (boNeg) ? LOW : HIGH;
}

//----------------------------------------------------------------------------
// init
//----------------------------------------------------------------------------
bool CBeeper::Init(const int  iGPIO    /*= -1*/,
                   const int  iGPIONeg /*= -1*/,
                   const bool boNeg    /*= false*/,
		   const bool boAuto   /*= false*/)
{
	if (iGPIO >= 0)
	{
		InitInternal(iGPIO, iGPIONeg, boNeg, boAuto);
	}
	
	if (m_boInit)
	{
		if ((m_boAuto == false) && (m_iGPIONeg >= 0))
		{
			pinMode(m_iGPIONeg, OUTPUT);
			digitalWrite(m_iGPIONeg, m_iLevelLow);
		}

		pinMode(m_iGPIO, OUTPUT);
		digitalWrite(m_iGPIO, m_iLevelLow);
	}
	
	return m_boInit;
}

//----------------------------------------------------------------------------
// beep
//----------------------------------------------------------------------------
void CBeeper::Beep(const int iMicroSec /*= 100000*/)
{
	// check mode
	if (m_boInit == false)
	{
		// dummy
		delayMicroseconds(iMicroSec);
	}
	else
	if (m_boAuto)
	{
		// automatic beeper
		digitalWrite(m_iGPIO, m_iLevelHigh);
		delayMicroseconds(iMicroSec);
		digitalWrite(m_iGPIO, m_iLevelLow);
	}
	else
	{
		// dynamic beeper
		int iHigh = m_iLevelHigh;
		int iLow  = m_iLevelLow;
		int iSwap, iTime;
		
		// loop
		for (iTime = iMicroSec; iTime >= 0; iTime -= m_iDelayMicroSec)
		{
			digitalWrite(m_iGPIO,    iHigh);
			digitalWrite(m_iGPIONeg, iLow);
			iSwap = iHigh;
			iHigh = iLow;
			iLow  = iSwap;
			delayMicroseconds(m_iDelayMicroSec);
		}

		// finish
		digitalWrite(m_iGPIO,    m_iLevelLow);
		digitalWrite(m_iGPIONeg, m_iLevelLow);
	}
}

//----------------------------------------------------------------------------
// interval beep
//----------------------------------------------------------------------------
void CBeeper::Interval(const int iMicroSec /*= 100000*/)
{
	int iTime = iMicroSec >> 1;

	Beep(iTime);
	delayMicroseconds(iMicroSec - iTime);
}

//----------------------------------------------------------------------------
// set frequency
//----------------------------------------------------------------------------
bool CBeeper::SetFrequency(const int iFreq /*= 5000*/)
{
	bool boResult = false;
	
	// check mode
	if (m_boAuto || (m_boInit == false))
	{
		boResult = false;
	}
	else
	if ((iFreq >= 50) && (iFreq <= 16000))
	{
		m_iDelayMicroSec = 500000 / iFreq;
		boResult = true;
	}

	return boResult;
}

//===| eof - end of file |====================================================
