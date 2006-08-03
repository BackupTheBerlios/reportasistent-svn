VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "LMRA_XML_WordLoader"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = True
Option Explicit

Dim mstrLastId As String
Dim mstrLastError As String
Dim mWordForInfo As Word.Application
Dim mActiveElemetns As New Collection
Dim mWordEvents As New Collection
Dim ButtonEvent As cbAElButtonEvents

Public Event HonzaEvent(ByVal name As String)
Public Event ActiveElementSelected(ByVal name As String)

Public Sub AddActiveElement(ByVal strType As String, ByVal strLabel As String, ByVal strIamgePath As String)

'    MsgBox strType & vbNewLine & strLabel & vbNewLine & strIamgePath
    
    Dim AEl(2) As String
    
    
    AEl(0) = strType
    AEl(1) = strLabel
    AEl(2) = strIamgePath
    
    mActiveElemetns.Add AEl
End Sub


Private Sub CreateRAToolbar(WordApp As Word.Application)
    Dim bar As Office.CommandBar
    Set bar = WordApp.CommandBars.Add(name:="Report Asistent", Temporary:=True)
    
    'MsgBox "in bar added"
    
    Dim but As Office.CommandBarButton
    Dim AEl
    
    For Each AEl In mActiveElemetns
 '       MsgBox "next " & AEl(0) & vbNewLine & AEl(1) & vbNewLine & AEl(2)
        Set but = bar.Controls.Add(Type:=msoControlButton)
        but.style = msoButtonIconAndCaption
        
        but.Tag = AEl(0)
        but.Caption = AEl(1)
        
        Dim img As IPictureDisp
        Set img = Nothing
        On Error Resume Next
        Set img = LoadPicture(AEl(2))
        On Error GoTo 0
        If (Not img Is Nothing) Then
            Clipboard.SetData img
            but.PasteFace
        End If
                        
        Set ButtonEvent = New cbAElButtonEvents
        Set ButtonEvent.cbBtn = but
        Set ButtonEvent.LMRA_loader = Me
        mWordEvents.Add ButtonEvent
        
'        MsgBox "hotovo " & AEl(0)
    Next
       
    'udela z toolobaru svisly
    bar.Width = 0
    bar.Visible = True
End Sub




Public Sub ActiveElementSelected(ByVal el_name As String)
    MsgBox "element: " & el_name
    RaiseEvent ActiveElementSelected(el_name)
End Sub




Public Sub OpenWordEditor()
    Dim WordApp As Word.Application
    
    Set WordApp = CreateObject("Word.Application")
    'MsgBox "word created"
    
    CreateRAToolbar WordApp
    'MsgBox "tool bar added"
    
    WordApp.Visible = True
End Sub


Public Property Get strLastProcessedId() As String
    strLastProcessedId = mstrLastId
End Property

Public Property Let strLastProcessedId(P As String)
   mstrLastId = P
End Property

Public Property Get strLastError() As String
    strLastError = mstrLastError
End Property

Public Property Let strLastError(P As String)
   mstrLastError = P
End Property

'vraci pole stringu
Public Function EnumTemplates() As String()
    If mWordForInfo Is Nothing Then
        Set mWordForInfo = CreateObject("Word.Application")
    End If
    
    
    Dim ret() As String
    
    ReDim ret(0 To mWordForInfo.Templates.Count - 1)
    
    Dim t As Word.Template
    Dim n As Integer
    
    n = 0
    For Each t In mWordForInfo.Templates
        ret(n) = t.name
        n = n + 1
    Next t
    
    EnumTemplates = ret
End Function

'vraci pole stringu
Public Function EnumParagraphStyles(ByVal template_id) As String()
    Dim ret() As String

    If mWordForInfo Is Nothing Then
        Set mWordForInfo = CreateObject("Word.Application")
    End If
    
    Dim template_doc As Word.Document
    On Error GoTo end_ret
    Set template_doc = mWordForInfo.Templates(template_id).OpenAsDocument
    
    Dim s As Word.style
    Dim n As Integer
    
    'zjistuime, kolik je character stylu
    n = -1
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeParagraph Then
            n = n + 1
        End If
    Next s
    
    
    
    ReDim ret(0 To n)
    
    'ulozime charcter styly do pole
    n = 0
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeParagraph Then
            ret(n) = s.NameLocal
            n = n + 1
        End If
    Next s
    
 
    template_doc.Close
    
end_ret:
    EnumParagraphStyles = ret

End Function

'vraci pole stringu
Public Function EnumCharacterStyles(ByVal template_id) As String()
    Dim ret() As String

    If mWordForInfo Is Nothing Then
        Set mWordForInfo = CreateObject("Word.Application")
    End If
    
    Dim template_doc As Word.Document
    
    On Error GoTo end_ret
    Set template_doc = mWordForInfo.Templates(template_id).OpenAsDocument
    
    Dim s As Word.style
    Dim n As Integer
    
    'zjistuime, kolik je character stylu
    n = -1
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeCharacter Then
            n = n + 1
        End If
    Next s
    
    
    
    ReDim ret(0 To n)
    
    'ulozime charcter styly do pole
    n = 0
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeCharacter Then
            ret(n) = s.NameLocal
            n = n + 1
        End If
    Next s
    
 
    template_doc.Close
    
end_ret:
    EnumCharacterStyles = ret

End Function


Public Function LoadFromStringToDoc(ByVal strXMLSource As String, out_doc As Object)
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim contentHandler As New ContentHandlerImpl 'Receives parsing events
    Dim errorHandler As New ErrorHandlerImpl     'Receive error events
    Dim word_loader As New WordLoader
    
        
    Set contentHandler.word_loader = word_loader
    Set contentHandler.LMRA_loader = Me
    Set errorHandler.LMRA_loader = Me
    
    contentHandler.strOutput = ""
        
'    Dim dtdHandler As New DTDHandlerImpl
'    txtOutput.text = ""
    Set reader.contentHandler = contentHandler   'They work together
    Set reader.errorHandler = errorHandler       'They also work together
'    Set reader.dtdHandler = dtdHandler
'    On Error GoTo 10

    word_loader.SetDocument out_doc
'    word_loader.NewDocument
    
    

    
    'chyba se osetri az vne procedury
'    On Error Resume Next
    reader.parse strXMLSource

End Function

Public Function LoadFromString(ByVal strXMLSource As String)
'    MsgBox strXMLSource
    
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim contentHandler As New ContentHandlerImpl 'Receives parsing events
    Dim errorHandler As New ErrorHandlerImpl     'Receive error events
    Dim word_loader As New WordLoader
    
    

    
    Set contentHandler.word_loader = word_loader
    Set contentHandler.LMRA_loader = Me
    Set errorHandler.LMRA_loader = Me
    Set word_loader.LMRA_loader = Me

    contentHandler.strOutput = ""
        
'    Dim dtdHandler As New DTDHandlerImpl
'    txtOutput.text = ""
    Set reader.contentHandler = contentHandler   'They work together
    Set reader.errorHandler = errorHandler       'They also work together
'    Set reader.dtdHandler = dtdHandler
'    On Error GoTo 10

    word_loader.NewDocument
    
    

    
    'chyba se osetri az vne procedury
'    On Error Resume Next
    reader.parse strXMLSource
    
'    LoadFromFile = contentHandler.strOutput

    RaiseEvent HonzaEvent("DDccDDkonec*")

End Function


Public Function LoadFromFile(ByVal strFileName As String) As String
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim contentHandler As New ContentHandlerImpl 'Receives parsing events
    Dim errorHandler As New ErrorHandlerImpl     'Receive error events
    Dim word_loader As New WordLoader
    
    Set contentHandler.word_loader = word_loader
    Set contentHandler.LMRA_loader = Me
    Set errorHandler.LMRA_loader = Me
    contentHandler.strOutput = ""
            
'    Dim dtdHandler As New DTDHandlerImpl
'    txtOutput.text = ""
    Set reader.contentHandler = contentHandler   'They work together
    Set reader.errorHandler = errorHandler       'They also work together
'    Set reader.dtdHandler = dtdHandler
'    On Error GoTo 10

    word_loader.NewDocument
    
    

    
    'chyba se osetri az vne procedury
    'On Error Resume Next
    reader.parseURL (strFileName)           'Parse the document
    
    LoadFromFile = contentHandler.strOutput
    
'    RaiseEvent HonzaEvent("DDccDDkonec*")

End Function

Private Sub Class_Terminate()
    If Not mWordForInfo Is Nothing Then
        mWordForInfo.Quit
    End If
End Sub
