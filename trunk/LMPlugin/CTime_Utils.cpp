//CTime_Utils.cpp
#include "CTime_Utils.h"

CString get_date_in_user_format (CTime& time)
{
 CString strTmpFormat;
 CString strDate;
 WCHAR* szData = NULL;
 int num_chars = GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, szData, 0);
 if (num_chars != 0)
 {
  szData = new WCHAR[num_chars+1];
  szData[num_chars] = '\0';
  GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SSHORTDATE, szData, num_chars);
  CString strTmp (szData);
  int ind = 0;
  int len = strTmp.GetLength();
  while (ind < len)
  {
   switch (strTmp[ind])
   {
    case 'y':
    {
     int year_type = 0;
     while (ind < len && strTmp[ind] == 'y'){ 
      ind++;
      year_type++;
     }
     ind--;
     switch (year_type){
      case 4: strTmpFormat.Format("%d", time.GetYear());         strDate += strTmpFormat; break;
      case 2: strTmpFormat.Format("%02d", time.GetYear() % 100); strDate += strTmpFormat; break;
      case 1: strTmpFormat.Format("%d", time.GetYear() % 10);    strDate += strTmpFormat; break;
     }
     break;
    }
    case 'M':
    {
     int month_type = 0;
     while (ind < len && strTmp[ind] == 'M'){ 
      ind++;
      month_type++;
     }
     ind--;
     switch (month_type){
      case 4:
      {
       WCHAR szMonth[500]={0};
       if (0<GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SMONTHNAME1+time.GetMonth()-1, szMonth, 499)){
        strDate += szMonth;
       }
       break;
      }
      case 3:
      {
       WCHAR szMonth[500]={0};
       if (0<GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SABBREVMONTHNAME1+time.GetMonth()-1, szMonth, 499)){
        strDate += szMonth;
       }
       break;
      }
      case 2: strTmpFormat.Format("%02d", time.GetMonth()); strDate += strTmpFormat; break;
      case 1: strTmpFormat.Format("%d", time.GetMonth());   strDate += strTmpFormat; break;
     }
     break;
    }
    case 'd':
    {
     int day_type = 0;
     while (ind < len && strTmp[ind] == 'd'){ 
      ind++;
      day_type++;
     }
     ind--;
     switch (day_type){
      case 4:
      {
       UINT DayOfWeekFull[] = {
        LOCALE_SDAYNAME7,   // Sunday
        LOCALE_SDAYNAME1,   
        LOCALE_SDAYNAME2,
        LOCALE_SDAYNAME3,
        LOCALE_SDAYNAME4, 
        LOCALE_SDAYNAME5, 
        LOCALE_SDAYNAME6   // Saturday
       };
       WCHAR szDayOfWeek[500]={0};
       if (0<GetLocaleInfoW(LOCALE_USER_DEFAULT, DayOfWeekFull[time.GetDayOfWeek()-1], szDayOfWeek, 499)){
        strDate += szDayOfWeek;
       }
       break;
      }
      case 3:
      {
       UINT DayOfWeekAbbr[] = {
        LOCALE_SABBREVDAYNAME7,   // Sunday
        LOCALE_SABBREVDAYNAME1,   
        LOCALE_SABBREVDAYNAME2,
        LOCALE_SABBREVDAYNAME3,
        LOCALE_SABBREVDAYNAME4, 
        LOCALE_SABBREVDAYNAME5, 
        LOCALE_SABBREVDAYNAME6   // Saturday
       };
       WCHAR szDayOfWeek[500]={0};
       if (0<GetLocaleInfoW(LOCALE_USER_DEFAULT, DayOfWeekAbbr[time.GetDayOfWeek()-1], szDayOfWeek, 499)){
        strDate += szDayOfWeek;
       }
       break;
      }
      case 2: strTmpFormat.Format("%02d", time.GetDay()); strDate += strTmpFormat; break;
      case 1: strTmpFormat.Format("%d", time.GetDay());   strDate += strTmpFormat; break;
     }
     break;
    }
    default:
     strDate += CString(strTmp[ind]);
     break;
   }
   ind++;
  }
  delete szData;
 }

 
  if (strDate.IsEmpty()){
  strDate = time.Format("%x");
 }
 
  return strDate;
}
 
CString get_time_in_user_format (CTime& time)
{
 CString strTmpFormat;
 CString strTime;
 WCHAR* szData = NULL;
 int num_chars = GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT, szData, 0);
 if (num_chars != 0)
 {
  szData = new WCHAR[num_chars+1];
  szData[num_chars] = '\0';
  GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_STIMEFORMAT, szData, num_chars);
  CString strTmp (szData);
  int ind = 0;
  int len = strTmp.GetLength();
  while (ind < len)
  {
   switch (strTmp[ind])
   {
    case 't':
    {
     int time_marker_type = 0;
     while (ind < len && strTmp[ind] == 't'){ 
      ind++;
      time_marker_type++;
     }
     ind--;
     switch (time_marker_type){
      case 2:
      case 1:
      {
       WCHAR szTimemarker[500]={0};
       LCTYPE am_or_pm = LOCALE_S1159; //AM
       if (time.GetHour() >= 0 && time.GetHour() < 12){
        am_or_pm = LOCALE_S1159; //AM
       }else{
        am_or_pm = LOCALE_S2359; //PM
       }
       if (0<GetLocaleInfoW(LOCALE_USER_DEFAULT, am_or_pm, szTimemarker, 499)){
        if (time_marker_type == 1){
         strTime += CString(szTimemarker, 1);
        }else{
         strTime += szTimemarker;
        }
       }
       break;
      }
     }
     break;
    }
    case 's':
    {
     int seconds_type = 0;
     while (ind < len && strTmp[ind] == 's'){ 
      ind++;
      seconds_type++;
     }
     ind--;
     switch (seconds_type){
      case 2: strTmpFormat.Format("%02d", time.GetSecond()); strTime += strTmpFormat; break;
      case 1: strTmpFormat.Format("%d", time.GetSecond());   strTime += strTmpFormat; break;
     }
     break;
    }
    case 'm':
    {
     int minute_type = 0;
     while (ind < len && strTmp[ind] == 'm'){ 
      ind++;
      minute_type++;
     }
     ind--;
     switch (minute_type){
      case 2: strTmpFormat.Format("%02d", time.GetMinute()); strTime += strTmpFormat; break;
      case 1: strTmpFormat.Format("%d", time.GetMinute());   strTime += strTmpFormat; break;
     }
     break;
    }
    case 'H':
    {
     int hour_type = 0;
     while (ind < len && strTmp[ind] == 'H'){ 
      ind++;
      hour_type++;
     }
     ind--;
     switch (hour_type){
      case 2: strTmpFormat.Format("%02d", time.GetHour()); strTime += strTmpFormat; break;
      case 1: strTmpFormat.Format("%d", time.GetHour());   strTime += strTmpFormat; break;
     }
     break;
    }
    case 'h':
    {
     int hour_12_format = time.GetHour() % 12;
     if (hour_12_format==0){
      hour_12_format = 12;
     }
     int hour_type = 0;
     while (ind < len && strTmp[ind] == 'h'){ 
      ind++;
      hour_type++;
     }
     ind--;
     switch (hour_type){
      case 2: strTmpFormat.Format("%02d", hour_12_format); strTime += strTmpFormat; break;
      case 1: strTmpFormat.Format("%d", hour_12_format);   strTime += strTmpFormat; break;
     }
     break;
    }
    default:
     strTime += CString(strTmp[ind]);
     break;
   }
   ind++;
  }
  delete szData;
 }
 


  if (strTime.IsEmpty()){
  strTime = time.Format("%X");
 }
 
  return strTime;
}