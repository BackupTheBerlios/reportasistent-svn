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

Private WithEvents evWordApp As Word.Application
Attribute evWordApp.VB_VarHelpID = -1

Dim mstrLastId As String
Dim mstrLastError As String
Dim mWordForInfo As Word.Application
Dim mActiveElemetns As New Collection
Dim mWordEvents As New Collection
Dim ButtonEvent 'As cbAElButtonEvents   'pouziva se jete pro cbCommandEvents
Dim mWordEditor As Word.Application
Dim mstrParentTaskName As String
Dim mstrDefaultWordTemplate As String



'Public Event HonzaEvent(ByVal name As String)
Public Event ActiveElementSelected(ByVal name As String)
Public Event SetSources()
Public Event SetOptions()
Public Event SkeletonEditor()
Public Event WordQuit()
Public Event PrepareParentTaskActivation()

Public Property Let strParentTaskName(ByVal strName As String)
    mstrParentTaskName = strName
End Property

Public Property Let strDefaultWordTemplate(ByVal strTemplate As String)
    mstrDefaultWordTemplate = strTemplate
End Property

Public Property Get strDefaultWordTemplate() As String
    strDefaultWordTemplate = mstrDefaultWordTemplate
End Property


Public Property Get isWordEditorActive() As Boolean
    If mWordEditor Is Nothing Then
        isWordEditorActive = False
    Else
        isWordEditorActive = True
    End If
End Property

Public Sub ActivateWordEditor()
    If Not mWordEditor Is Nothing Then
        mWordEditor.Visible = True
        mWordEditor.Activate
    End If
End Sub

Public Sub AddActiveElement(ByVal strType As String, ByVal strLabel As String, ByVal strIamgePath As String)

'    MsgBox strType & vbNewLine & strLabel & vbNewLine & strIamgePath
    
    Dim AEl(2) As String
    
    
    AEl(0) = strType
    AEl(1) = strLabel
    AEl(2) = strIamgePath
    
    mActiveElemetns.Add AEl
End Sub


Private Sub Class_Initialize()
    strDefaultWordTemplate = "Normal.dot"
End Sub

Private Sub evWordApp_Quit()
    Set mWordEditor = Nothing
    
    ActivateParentTask
    
    RaiseEvent WordQuit
End Sub

Public Sub ActiveElementSelected(ByVal el_name As String)
    ActivateParentTask
    
    RaiseEvent ActiveElementSelected(el_name)
End Sub

Public Sub CommandEvent(ByVal button_tag As String)
    ActivateParentTask
           
    Select Case button_tag
        Case "Options"
            RaiseEvent SetOptions
        
        Case "Skeleton Editor"
            RaiseEvent SkeletonEditor
        
        Case "Data Sources"
            RaiseEvent SetSources
    End Select
End Sub

Private Sub AddButtonToBar(ByRef bar As Office.CommandBar, ByVal caption As String, ByVal faceid)
    Dim but As Office.CommandBarButton
    
    Set but = bar.Controls.Add(Type:=msoControlButton)
    but.style = msoButtonIconAndCaption
    but.caption = caption
    but.Tag = but.caption
    but.faceid = faceid
    Set ButtonEvent = New cbCommandEvents
    Set ButtonEvent.cbBtn = but
    Set ButtonEvent.LMRA_loader = Me
    mWordEvents.Add ButtonEvent
End Sub

Private Sub CreateRAToolbar(WordApp As Word.Application)
    Dim bar As Office.CommandBar
    Set bar = WordApp.CommandBars.Add(name:="Report Asistent", Position:=msoBarFloating, Temporary:=True)
        
    'ovladaci tlacitka
    AddButtonToBar bar, "Skeleton Editor", 1016
    AddButtonToBar bar, "Data Sources", 2308
    AddButtonToBar bar, "Options", 1607
            
    
    'tlacitka AP
    Dim but As Office.CommandBarButton
    Dim AEl
    Dim group_begin As Boolean
    group_begin = True
    
    For Each AEl In mActiveElemetns
 '       MsgBox "next " & AEl(0) & vbNewLine & AEl(1) & vbNewLine & AEl(2)
                
        Set but = bar.Controls.Add(Type:=msoControlButton)
        but.BeginGroup = group_begin
        group_begin = False
    
        
        but.style = msoButtonIconAndCaption
        
        but.Tag = AEl(0)
        but.caption = AEl(1)
        
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
    'bar.Left = 30
    bar.width = 0
    bar.Visible = True
End Sub

Public Sub OpenWordEditor()
    If Not mWordEditor Is Nothing Then
        mWordEditor.Visible = True
        ActivateWordEditor
        Exit Sub
    End If
       
    'MsgBox "word creating"
    Set mWordEditor = CreateObject("Word.Application")
    'MsgBox "word created"
    
    Set evWordApp = Nothing
    'MsgBox "ev set"
    Set evWordApp = mWordEditor
    'MsgBox "tool bar loading"
    
    On Error Resume Next
    mWordEditor.Documents.Add( _
        Template:=strDefaultWordTemplate).Select
    On Error GoTo 0
        
    CreateRAToolbar mWordEditor
    'MsgBox "tool bar added"
    
    
    mWordEditor.Visible = True
End Sub

Private Sub ActivateParentTask()
    'On Error Resume Next
    'Tasks("LMRA_WordLoader").Activate False
    
    
    RaiseEvent PrepareParentTaskActivation
    
    
    If Tasks.Exists(mstrParentTaskName) Then
        Tasks(mstrParentTaskName).Activate False
        
        If Not mWordEditor Is Nothing Then
            'mWordEditor.Visible = False
        End If
    Else
        MsgBox "Task not exist: " & mstrParentTaskName
    End If
End Sub

Public Property Get strLastProcessedId() As String
    strLastProcessedId = mstrLastId
End Property

Public Property Let strLastProcessedId(ByVal P As String)
   mstrLastId = P
End Property

Public Property Get strLastError() As String
    strLastError = mstrLastError
End Property

Public Property Let strLastError(ByVal P As String)
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

'x() as String ...... x je pole stringu
Public Function EnumWordStyles(ByVal template_file As String, ByRef char_s() As String, ByRef paragr_s() As String) As Boolean
    If mWordForInfo Is Nothing Then
        Set mWordForInfo = CreateObject("Word.Application")
    End If
    
    Dim template_doc As Word.Document
    
    On Error Resume Next
    
    Set template_doc = mWordForInfo.Documents.Open( _
        FileName:=template_file, ReadOnly:=True)
    
    On Error GoTo 0
    
    If template_doc Is Nothing Then
        EnumWordStyles = False
        Exit Function
    End If
    
    Dim s As Word.style
    Dim ch, para As Integer
    
    'zjistuime, kolik je stylu
    ch = -1
    para = -1
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeCharacter Then
            ch = ch + 1
        End If
        
        If s.Type = wdStyleTypeParagraph Then
            para = para + 1
        End If
    Next s
       
    ReDim char_s(0 To ch)
    ReDim paragr_s(0 To para)
    
    'ulozime styly do pole
    ch = 0
    para = 0
    For Each s In template_doc.Styles
        If s.Type = wdStyleTypeCharacter Then
            char_s(ch) = s.NameLocal
            ch = ch + 1
        End If
        
        If s.Type = wdStyleTypeParagraph Then
            paragr_s(para) = s.NameLocal
            para = para + 1
        End If
    Next s
    
 
    template_doc.Close
        
    EnumWordStyles = True
End Function


Public Sub LoadFromStringToClearDoc(ByVal strXMLSource As String, out_doc As Object)
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim word_loader As New WordLoader
    
    InitReaderWordLoader reader, word_loader

    word_loader.SetAndClearDocument out_doc
'    word_loader.NewDocument
    
    reader.parse strXMLSource
End Sub

Public Sub LoadFromStringToWordEditor(ByVal strXMLSource As String)
    If mWordEditor Is Nothing Then
        OpenWordEditor
    End If
    
    If mWordEditor.Selection Is Nothing Then
        On Error Resume Next
        mWordEditor.Documents.Add(Template:=strDefaultWordTemplate).Select
        On Error GoTo 0
        
        If mWordEditor.Selection Is Nothing Then
            mWordEditor.Documents.Add.Select
        End If
    End If
        
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim word_loader As New WordLoader
    InitReaderWordLoader reader, word_loader
        
    word_loader.SetWordApplication mWordEditor
    reader.parse strXMLSource
                
End Sub

Public Sub LoadFromString(ByVal strXMLSource As String)
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim word_loader As New WordLoader
    
    InitReaderWordLoader reader, word_loader

    word_loader.NewDocument mstrDefaultWordTemplate
           
    reader.parse strXMLSource
    

'    RaiseEvent HonzaEvent("DDccDDkonec*")

End Sub


Private Sub InitReaderWordLoader(ByRef reader As SAXXMLReader30, ByRef word_loader As WordLoader)
    Dim contentHandler As New ContentHandlerImpl 'Receives parsing events
    Dim errorHandler As New ErrorHandlerImpl     'Receive error events
    
    Set word_loader.LMRA_loader = Me
    
    Set contentHandler.word_loader = word_loader
    Set contentHandler.LMRA_loader = Me
    Set errorHandler.LMRA_loader = Me
    
    Set reader.contentHandler = contentHandler   'They work together
    Set reader.errorHandler = errorHandler       'They also work together
End Sub


Public Sub LoadFromFile(ByVal strFileName As String)
    Dim reader As New SAXXMLReader30             'Reads the XML document
    Dim word_loader As New WordLoader
    
    InitReaderWordLoader reader, word_loader

    word_loader.NewDocument "Normal.dot"
    
    reader.parseURL (strFileName)           'Parse the document
    
End Sub

Private Sub Class_Terminate()
    If Not mWordForInfo Is Nothing Then
        mWordForInfo.Quit
    End If
    
    If Not mWordEditor Is Nothing Then
        On Error Resume Next
        mWordEditor.Quit SaveChanges:=False
    End If
End Sub

