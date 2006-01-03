VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   1230
   ClientLeft      =   3480
   ClientTop       =   2595
   ClientWidth     =   2175
   LinkTopic       =   "Form1"
   ScaleHeight     =   1230
   ScaleWidth      =   2175
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit


Private Declare Function FindEnumValInTypeLib Lib "TypeLibFind.dll" Alias "_FindEnumValInTypeLib@8" (ByVal Str1 As String, ByVal Str2 As String) As Integer


 
Private Sub Form_Load()
    Caption = FindEnumValInTypeLib("MSGraph.Chart.8", "xlAreaStacked100")
End Sub
