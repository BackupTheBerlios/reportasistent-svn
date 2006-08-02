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
   Begin VB.CommandButton cmdEnumTest 
      Caption         =   "Enum test1"
      Height          =   375
      Left            =   4800
      TabIndex        =   5
      Top             =   3840
      Width           =   2535
   End
   Begin VB.CommandButton cmdXMLStringProcess 
      Caption         =   "Process XML string"
      Height          =   2175
      Left            =   8400
      TabIndex        =   4
      Top             =   960
      Width           =   1815
   End
   Begin VB.TextBox txtXMLString 
      Height          =   2535
      Left            =   240
      MultiLine       =   -1  'True
      ScrollBars      =   3  'Both
      TabIndex        =   3
      Text            =   "Form1.frx":0000
      Top             =   360
      Width           =   7815
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
      Caption         =   "process the XML file!"
      Height          =   375
      Left            =   480
      TabIndex        =   1
      Top             =   3120
      Width           =   1695
   End
   Begin VB.TextBox txtFilePath 
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Text            =   "normal.dot"
      Top             =   3840
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




Private Sub cmdEnumTest_Click()
    txtOutput.text = txtOutput.text & vbNewLine & vbNewLine & "tmplates:"
    
    Dim obj As New LMRA_XML_WordLoader
    Dim strings() As String
    Dim s
    
    
    strings = obj.EnumTemplates
    For Each s In strings
        txtOutput.text = txtOutput.text & vbNewLine & s
    Next
    
    
    txtOutput.text = txtOutput.text & vbNewLine & vbNewLine & "pragraph styles:"
    
    strings = obj.EnumParagraphStyles(txtFilePath.text)
    For Each s In strings
        txtOutput.text = txtOutput.text & vbNewLine & s
    Next
    
    
    txtOutput.text = txtOutput.text & vbNewLine & vbNewLine & "character styles:"
    
    strings = obj.EnumCharacterStyles(txtFilePath.text)
    For Each s In strings
        txtOutput.text = txtOutput.text & vbNewLine & s
    Next
    
    
    

End Sub

Private Sub cmdXMLProcess_Click()
    XML_Process
End Sub

 
Private Sub cmdXMLStringProcess_Click()
    Dim obj As New LMRA_XML_WordLoader
    
    Err.Clear
    On Error Resume Next
    txtOutput.text = obj.LoadFromString(txtXMLString)
    
    txtOutput.text = txtOutput.text & vbNewLine & obj.strLastError & vbNewLine & obj.strLastProcessedId
    
    
    If Not Err.Number = 0 Then
        MsgBox "Error in XML string processing." & vbNewLine & txtFilePath.text & vbNewLine & Err.Description
    End If
End Sub

Private Sub Form_Load()
    Caption = FileSystem.CurDir
'    XML_Process
End Sub
