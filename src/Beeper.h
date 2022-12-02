/*
 The MIT License (MIT)

 Copyright (c) 2019-2023 Dirk Ohme

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

#pragma once

class Beeper {
public:
protected:
	bool		m_boAuto;
	bool		m_boInit;
	int		m_iDelayMicroSec;
	int		m_iGPIO;
	int		m_iGPIONeg;
	int		m_iLevelLow;
	int		m_iLevelHigh;
	
	void InitInternal(const int  iGPIO    = -1,
	                  const int  iGPIONeg = -1,
	                  const bool boNeg    = false,
			  const bool boAuto   = false);

public:
	// constructor
	// @param iGPIO first GPIO pin
	// @param iGPIONeg second GPIO pin
	// @param boNeg negate output logic
	// @param boAuto true on automatic beeper
	Beeper(const int  iGPIO    = -1,
	       const int  iGPIONeg = -1,
	       const bool boNeg    = false,
	       const bool boAuto   = false);
	
	// initialization
	// @param iGPIO first GPIO pin or -1 to keep setting
	// @param iGPIONeg second GPIO pin or -1 to keep setting
	// @param boNeg negate output logic (only valid if iGPIO valid)
	// @param boAuto true on automatic beeper
	// @return true on success, false on error
	bool Init(const int  iGPIO    = -1,
	          const int  iGPIONeg = -1,
	          const bool boNeg    = false,
		  const bool boAuto   = false);
	
	// beep
	// @param iMicroSec microseconds
	void Beep(const int iMicroSec = 100000);

	// interval beep
	// @param iMicroSec microseconds
	void Interval(const int iMicroSec = 100000);

	// set frequency
	// @param iFreq frequency in hertz
	// @return true on success, false on error
	bool SetFrequency(const int iFreq = 5000);
};

//===| eof - end of file |====================================================
