VERSION 1.0 CLASS
BEGIN
  MultiUse = 0   'False
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

Public Event HonzaEvent(ByVal name As String)



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
Public Function EnumParagraphStyles(ByVal template_name As String) As String()

    If mWordForInfo Is Nothing Then
        Set mWordForInfo = CreateObject("Word.Application")
    End If
    
    Dim template_doc As Word.Document
    Set template_doc = mWordForInfo.Templates(template_name).OpenAsDocument
    
    Dim s As Word.style
    Dim n As Integer
    
    'zjistuime, kolik je character stylu
    n = 0
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeParagraph Then
            n = n + 1
        End If
    Next s
    
    
    Dim ret() As String
    
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
    
    EnumParagraphStyles = ret

End Function

'vraci pole stringu
Public Function EnumCharacterStyles(ByVal template_name As String) As String()

    If mWordForInfo Is Nothing Then
        Set mWordForInfo = CreateObject("Word.Application")
    End If
    
    Dim template_doc As Word.Document
    Set template_doc = mWordForInfo.Templates(template_name).OpenAsDocument
    
    Dim s As Word.style
    Dim n As Integer
    
    'zjistuime, kolik je character stylu
    n = 0
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeCharacter Then
            n = n + 1
        End If
    Next s
    
    
    Dim ret() As String
    
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
