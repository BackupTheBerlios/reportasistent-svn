//CTime_Utils.h
/*
This file is part of LM Report Asistent.

Authors: Jan Dedek, Jan Kodym, Martin Chrz, Iva Bartunkova

LM Report Asistent is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

Foobar is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Foobar; if not, write to the Free Software
Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/
//these functions converts the time to the system format
#include "afx.h"

/**
 * Returns the date in the system format.
 *
 * @param time The variable of the type CTime.
 * @return CString containing the formated date. 
 */
CString get_date_in_user_format (CTime& time);

/**
 * Returns the time in system format.
 *
 * @param time The variable of the type CTime.
 * @return CString containing the formated time. 
 */
CString get_time_in_user_format (CTime& time);