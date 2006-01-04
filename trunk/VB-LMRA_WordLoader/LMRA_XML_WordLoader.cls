VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "LMRA_XML_WordLoader"
Attribute VB_GlobalNameSpace = True
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False

Public Function LoadFromFile(ByVal strFileName As String) As String
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim contentHandler As New ContentHandlerImpl 'Receives parsing events
    Dim errorHandler As New ErrorHandlerImpl     'Receive error events
    Dim word_loader As New WordLoader
    
    Set contentHandler.word_loader = word_loader
    contentHandler.strOutput = ""
        
'    Dim dtdHandler As New DTDHandlerImpl
'    txtOutput.text = ""
    Set reader.contentHandler = contentHandler   'They work together
    Set reader.errorHandler = errorHandler       'They also work together
'    Set reader.dtdHandler = dtdHandler
'    On Error GoTo 10

    word_loader.NewDocument
    
    

    
    'chyba se osetri az vne procedury
    On Error Resume Next
    reader.parseURL (strFileName)           'Parse the document
    
    LoadFromFile = contentHandler.strOutput

End Function
