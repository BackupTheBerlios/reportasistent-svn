VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ContentHandlerImpl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements IVBSAXContentHandler


Dim wl As WordLoader
Dim mstrOutput As String

Public Property Let strOutput(P As String)
    mstrOutput = P
End Property

Public Property Get strOutput() As String
    strOutput = mstrOutput
End Property

Public Property Set word_loader(P As WordLoader)
   Set wl = P
End Property



Private Sub IVBSAXContentHandler_startElement(strNamespaceURI As String, strLocalName As String, strQName As String, ByVal oAttributes As MSXML2.IVBSAXAttributes)
    Dim i As Integer
    
    mstrOutput = mstrOutput & "<" & strLocalName
    
    For i = 0 To (oAttributes.Length - 1)
        mstrOutput = mstrOutput & " " & _
        oAttributes.getLocalName(i) & "=""" & oAttributes.getValue(i) & """"
    Next
    
    mstrOutput = mstrOutput & ">"
            


    
    Select Case strLocalName
        Case "report"
            wl.LoadReport oAttributes
        Case "chapter"
            wl.LoadChapter oAttributes
        Case "paragraph"
            wl.LoadParagraph oAttributes
        Case "text"
            wl.LoadText oAttributes
        Case "table"
            wl.LoadTable oAttributes
        Case "tr"
            wl.LoadTableRow oAttributes
        Case "td"
            wl.LoadTableColumn oAttributes
            
        Case "graph"
            wl.LoadGraph oAttributes
        Case "category"
            wl.LoadGraphCategory oAttributes
        Case "categories"
            wl.LoadGraphCategories oAttributes
        Case "chart"
            wl.LoadChart oAttributes
        Case "value"
            wl.LoadChartValue oAttributes

    End Select
End Sub

Private Sub IVBSAXContentHandler_endElement(strNamespaceURI As String, strLocalName As String, strQName As String)
    mstrOutput = mstrOutput & "</" & strLocalName & ">"
    
    Select Case strLocalName
        Case "chapter"
            wl.EndChapter
        Case "table"
            wl.EndTable
        Case "tr"
            wl.EndTableRow
        Case "td"
            wl.EndTableColumn
        Case "graph"
            wl.EndGraph
            
    End Select

End Sub

Private Sub IVBSAXContentHandler_characters(strChars As String)
    strChars = Replace(strChars, vbLf, vbNewLine)
    mstrOutput = mstrOutput & strChars
End Sub

Private Sub IVBSAXContentHandler_endDocument()
    wl.EndDocument
End Sub



Private Property Set IVBSAXContentHandler_documentLocator(ByVal RHS As MSXML2.IVBSAXLocator)
End Property
Private Sub IVBSAXContentHandler_endPrefixMapping(strPrefix As String)
End Sub
Private Sub IVBSAXContentHandler_ignorableWhitespace(strChars As String)
End Sub
Private Sub IVBSAXContentHandler_processingInstruction(strTarget As String, strData As String)
End Sub
Private Sub IVBSAXContentHandler_skippedEntity(strName As String)
End Sub
Private Sub IVBSAXContentHandler_startDocument()
End Sub
Private Sub IVBSAXContentHandler_startPrefixMapping(strPrefix As String, strURI As String)
End Sub
