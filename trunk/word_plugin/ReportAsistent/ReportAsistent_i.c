/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Fri Nov 04 16:27:20 2005
 */
/* Compiler settings for D:\LM\WORD_PLUGIN\ReportAsistent\ReportAsistent.idl:
    Oicf (OptLev=i2), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_REPORTASISTENTLib = {0x43476C69,0x1127,0x4317,{0x80,0x65,0x32,0xDD,0x02,0xCE,0x7A,0xD3}};


const IID IID_IInsertElement = {0xF5EBE35B,0x1ABC,0x4F40,{0x81,0xAE,0x0D,0x5D,0x69,0x2B,0xFD,0xCC}};


const CLSID CLSID_InsertElement = {0x399FF362,0x6189,0x48A0,{0x90,0xA3,0xDC,0x4A,0xE0,0xAF,0x0E,0x41}};


const IID IID_IMainObject = {0x528746CB,0x465B,0x4DC2,{0x97,0x58,0x54,0xEF,0x90,0xE9,0x32,0x53}};


const IID IID_IElementGraph = {0xF6EE1307,0x8A05,0x4191,{0xB3,0x01,0xBB,0xA7,0x53,0x09,0xC5,0xF9}};


const CLSID CLSID_MainObject = {0x6775171E,0x053A,0x4C35,{0x84,0x2D,0xEE,0xD5,0x6C,0x4B,0x35,0x31}};


const CLSID CLSID_ElementGraph = {0x286AE5CF,0xB993,0x4B21,{0xA8,0x2D,0xE1,0xA3,0x76,0x17,0x6E,0xE1}};


#ifdef __cplusplus
}
#endif

