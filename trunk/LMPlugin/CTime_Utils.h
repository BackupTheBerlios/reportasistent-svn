//CTime_Utils.h
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