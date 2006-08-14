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
   Begin VB.CommandButton cmdTasks 
      Caption         =   "tasks"
      Height          =   375
      Left            =   7920
      TabIndex        =   8
      Top             =   3480
      Width           =   495
   End
   Begin VB.CommandButton cmdFileToStr 
      Caption         =   "Load file to str ^"
      Height          =   375
      Left            =   480
      TabIndex        =   7
      Top             =   3240
      Width           =   1575
   End
   Begin VB.CommandButton cmdOpenEditor 
      Caption         =   "OpenWordEditor"
      Height          =   975
      Left            =   8760
      TabIndex        =   6
      Top             =   3120
      Width           =   1455
   End
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
      Height          =   1335
      Left            =   8400
      TabIndex        =   4
      Top             =   480
      Width           =   1935
   End
   Begin VB.TextBox txtXMLString 
      Height          =   2535
      Left            =   480
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
      Text            =   "Form1.frx":0390
      Top             =   4440
      Width           =   10215
   End
   Begin VB.CommandButton cmdXMLProcess 
      Caption         =   "process the XML file!"
      Height          =   375
      Left            =   2400
      TabIndex        =   1
      Top             =   3240
      Width           =   1695
   End
   Begin VB.TextBox txtFilePath 
      Height          =   375
      Left            =   480
      TabIndex        =   0
      Text            =   "..\XML\redukovany.xml"
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
    
    
Private WithEvents evLMRA As LMRA_XML_WordLoader
Attribute evLMRA.VB_VarHelpID = -1
    
Dim mLMRA As New LMRA_XML_WordLoader

Private Sub XML_Process()
    Dim obj As New LMRA_XML_WordLoader
    
    Err.Clear
    On Error Resume Next
    obj.LoadFromFile txtFilePath
    
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

Private Sub cmdFileToStr_Click()
    Dim fs As New FileSystemObject
    
    
    txtXMLString = fs.GetFile(txtFilePath).OpenAsTextStream(ForReading).ReadAll
End Sub

Private Sub cmdOpenEditor_Click()
    mLMRA.strParentTaskName = caption
    
    If Not mLMRA.isWordEditorActive Then
        mLMRA.AddActiveElement "category", "Category", "D:\Sources\MyProjects\LM_Report_Asistent\svn\elements\hyp_4ft\icon.bmp"
        mLMRA.AddActiveElement "hyp_cf", "CF hypotesis", "D:\Sources\MyProjects\LM_Report_Asistent\svn\elements\hyp_cf\icon.bmp"
        mLMRA.AddActiveElement "bool_cedent", "Bool cedent", "D:\Sources\MyProjects\LM_Report_Asistent\svn\elements\attribute\icon.bmp"
        mLMRA.AddActiveElement "bool_cedent", "Bool cedent", "D:\Sources\MyProjects\LM_Report_Asistent\svn\elements\bool_cedent\icon.bmp"
        mLMRA.AddActiveElement "hyp_cf", "CF hypotesis", "D:\Sources\MyProjects\LM_Report_Asistent\svn\elements\hyp_sdcf\icon.bmp"
        mLMRA.AddActiveElement "bool_cedent", "Bool cedent", "D:\Sources\MyProjects\LM_Report_Asistent\svn\elements\bool_cedent\icon.bmp"
        mLMRA.AddActiveElement "category", "Category", "D:\Sources\MyProjects\LM_Report_Asistent\svn\elements\quantifier\icon.bmp"
    End If
    
'    Visible = False
    mLMRA.OpenWordEditor
End Sub

Private Sub cmdTasks_Click()
    Dim t As Task
    For Each t In Tasks
        txtOutput = txtOutput & t.name & vbTab & t.Parent & vbNewLine
        
    Next
End Sub

Private Sub cmdXMLProcess_Click()
    XML_Process
End Sub

 
Private Sub cmdXMLStringProcess_Click()
    Err.Clear
    On Error Resume Next
    mLMRA.LoadFromStringToWordEditor (txtXMLString)
    
    txtOutput.text = txtOutput.text & vbNewLine & mLMRA.strLastError & vbNewLine & mLMRA.strLastProcessedId
    
    
    If Not Err.Number = 0 Then
        MsgBox "Error in XML string processing." & vbNewLine & txtFilePath.text & vbNewLine & Err.Description
    End If
End Sub


Private Sub evLMRA_SkeletonEditor()
    On Error Resume Next
    Visible = True
    SetFocus
    
    
    
    MsgBox "Skeleton editor"
End Sub

Private Sub evLMRA_WordQuit()
    Visible = True
End Sub

Private Sub Form_Load()
    'caption = FileSystem.CurDir
    
    Set evLMRA = mLMRA
'    XML_Process
End Sub

