VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   7875
   ClientLeft      =   3480
   ClientTop       =   2595
   ClientWidth     =   10890
   LinkTopic       =   "Form1"
   ScaleHeight     =   7875
   ScaleWidth      =   10890
   Begin VB.CommandButton cmdXMLStringProcess 
      Caption         =   "Process XML string"
      Height          =   2175
      Left            =   8520
      TabIndex        =   4
      Top             =   1560
      Width           =   1815
   End
   Begin VB.TextBox txtXMLString 
      Height          =   3015
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Text            =   "Form1.frx":0000
      Top             =   960
      Width           =   7095
   End
   Begin VB.TextBox txtOutput 
      Height          =   3255
      Left            =   360
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   2
      Text            =   "Form1.frx":0006
      Top             =   4440
      Width           =   10215
   End
   Begin VB.CommandButton cmdXMLProcess 
      Caption         =   "process the XML!"
      Height          =   495
      Left            =   4800
      TabIndex        =   1
      Top             =   120
      Width           =   2175
   End
   Begin VB.TextBox txtFilePath 
      Height          =   375
      Left            =   360
      TabIndex        =   0
      Text            =   "..\xml\out.xml"
      Top             =   240
      Width           =   3615
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Sub XML_Process()
    Dim obj As New LMRA_XML_WordLoader
    
    Err.Clear
    On Error Resume Next
    txtOutput.text = obj.LoadFromFile(txtFilePath)
    
    If Not Err.Number = 0 Then
        MsgBox "Error in file opening." & vbNewLine & txtFilePath.text & vbNewLine & Err.Description
    End If
    
           
End Sub




Private Sub cmdXMLProcess_Click()
    XML_Process
End Sub

 
Private Sub cmdXMLStringProcess_Click()
    Dim obj As New LMRA_XML_WordLoader
    
    Err.Clear
    On Error Resume Next
    txtOutput.text = obj.LoadFromString(txtXMLString)
    
    If Not Err.Number = 0 Then
        MsgBox "Error in XML string processing." & vbNewLine & txtFilePath.text & vbNewLine & Err.Description
    End If
End Sub

Private Sub Form_Load()
    Caption = FileSystem.CurDir
'    XML_Process
End Sub
