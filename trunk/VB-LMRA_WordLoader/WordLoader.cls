VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "WordLoader"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Private Declare Function FindEnumValInTypeLib Lib "TypeLibFind.dll" (ByVal strProhId As String, ByVal strVal As String) As Integer


Dim mintHeadinglevel As Integer
Dim mintGraphCharts As Integer
Dim mintLastGraphCell As Integer
Dim mboolTextInserting As Boolean


Dim mLMRA As LMRA_XML_WordLoader


Dim mWordApp As Word.Application
Dim mGraph As Graph.Chart
Dim mstrGraphProgID As String
Dim mTable As Word.Table

Public Sub SetWordApplication(ByRef app As Word.Application)
    Set mWordApp = app
End Sub

Public Property Set LMRA_loader(P As LMRA_XML_WordLoader)
   Set mLMRA = P
End Property

Private Sub Class_Initialize()
    mintHeadinglevel = 1
    mboolTextInserting = False
End Sub


Public Sub SetAndClearDocument(doc As Word.Document)
    Set mWordApp = doc.Application
    
    mWordApp.Visible = True
    
    doc.Select
    mWordApp.Selection.Delete
    
    
End Sub


Public Sub NewDocument()
    Dim D As Word.Document
    
    
    Set mWordApp = CreateObject("Word.Application")
    
    mWordApp.Visible = True
    
    Set D = mWordApp.Documents.Add("Normal.dot")
    
    D.Select
     
    
    
    'mWordApp.Quit

End Sub

Private Sub AddParagraph(Optional style)
    mWordApp.Selection.TypeParagraph
    If Not IsMissing(style) Then mWordApp.Selection.style = style
End Sub

Private Sub SetTextStyle(style)
        mWordApp.Selection.style = style
End Sub

Private Sub ReSetTextStyle()
        SetTextStyle wdStyleDefaultParagraphFont
End Sub


Private Sub AddText(text As String, Optional style)
    If IsMissing(style) Then
        mWordApp.Selection.TypeText text
    Else
        mWordApp.Selection.style = style
        mWordApp.Selection.TypeText text
        mWordApp.Selection.style = wdStyleDefaultParagraphFont
    End If
    
End Sub

Private Sub FirstTitle(text As String)
'nedela se novy odstavec
    mWordApp.Selection.style = wdStyleTitle
    AddText text
End Sub

Private Sub AddTitle(text As String)
    Select Case mintHeadinglevel
        Case 1
            AddParagraph wdStyleHeading1
        Case 2
            AddParagraph wdStyleHeading2
        Case 3
            AddParagraph wdStyleHeading3
        Case 4
            AddParagraph wdStyleHeading4
        Case 5
            AddParagraph wdStyleHeading5
        Case 6
            AddParagraph wdStyleHeading6
        Case 7
            AddParagraph wdStyleHeading7
        Case 8
            AddParagraph wdStyleHeading8
        Case 9
            AddParagraph wdStyleHeading9
        Case Else
            AddParagraph wdStyleHeading9
    End Select
    
    AddText text
End Sub

Public Sub EndTableColumn()
    If Not mWordApp.Selection.Cells(1).Next Is Nothing Then
        mWordApp.Selection.MoveRight Unit:=wdCell ', Count:=cs - 1, Extend:=wdExtend
    End If
    
'    If Not mWordApp.Selection.Cells(1).Next Is Nothing Then
'        mWordApp.Selection.Cells(1).Next.Select
'    End If

    
    'If Not mWordApp.Selection.Cells(1).IsLast Then
    '    mWordApp.Selection.MoveRight Unit:=wdCell
    'End If
End Sub

Public Sub EndTableRow()
'    If Not mWordApp.Selection.Rows(1).IsLast Then
'        mWordApp.Selection.MoveRight Unit:=wdCell
'    End If
End Sub

Public Static Function HTMLRGB_2_VBRGB(ByVal html_hex_color As String) As Long
    Dim n As Long
    
    Dim r As Long
    Dim g As Long
    Dim b As Long

    html_hex_color = Replace(html_hex_color, "#", "&H")
    n = html_hex_color
    
    b = n And &HFF
    n = n \ 256
    g = (n And &HFF)
    n = n \ 256
    r = (n And &HFF)
    
    
    HTMLRGB_2_VBRGB = RGB(r, g, b)

End Function


Public Static Sub SetCellBorder(ByRef border As Word.border, ByVal width As Double)
    If width > 0 Then
        border.LineStyle = wdLineStyleSingle
        border.LineWidth = CountBorderLineWidth(width)
    Else
        border.LineStyle = wdLineStyleNone
    End If
End Sub


Public Sub LoadTableColumn(oAttributes As MSXML2.IVBSAXAttributes)
    Dim cs As Integer
    Dim rs As Integer
    
    'Dim c As Integer
    'Dim r As Integer
    Dim hex_bg As String
    'Dim bg_color As Long
    'Dim Num As Long
    
    Dim bTop As Variant
    Dim bBottom As Variant
    Dim bLeft As Variant
    Dim bRight As Variant
    
     
    Dim fc As Word.Cell
    Dim pom_c As Word.Cell
    
    cs = 1
    rs = 1
    
    On Error Resume Next
    
    cs = oAttributes.getValueFromName("", "colspan")
    rs = oAttributes.getValueFromName("", "rowspan")
    
    On Error GoTo 0
    
    If cs > 1 Or rs > 1 Then
        Set fc = mWordApp.Selection.Cells(1)
        
        mWordApp.Selection.MoveRight Unit:=wdCell, Count:=cs - 1
        mWordApp.Selection.MoveDown Unit:=wdLine, Count:=rs - 1
        Set pom_c = mWordApp.Selection.Cells(1)
        fc.Select
        fc.Merge pom_c
        fc.Select
       
    End If
        
    On Error Resume Next
    
    bTop = oAttributes.getValueFromName("", "border_top")
    bBottom = oAttributes.getValueFromName("", "border_bottom")
    bLeft = oAttributes.getValueFromName("", "border_left")
    bRight = oAttributes.getValueFromName("", "border_right")
    
    On Error GoTo 0
    
    If Not bTop = "" Then SetCellBorder mWordApp.Selection.Cells(1).Borders(wdBorderTop), bTop
    If Not bBottom = "" Then SetCellBorder mWordApp.Selection.Cells(1).Borders(wdBorderBottom), bBottom
    If Not bLeft = "" Then SetCellBorder mWordApp.Selection.Cells(1).Borders(wdBorderLeft), bLeft
    If Not bRight = "" Then SetCellBorder mWordApp.Selection.Cells(1).Borders(wdBorderRight), bRight
    
    
    On Error GoTo EndSub
    
    hex_bg = oAttributes.getValueFromName("", "bgcolor")
    
            
    mWordApp.Selection.Cells(1).Shading.BackgroundPatternColor = HTMLRGB_2_VBRGB(hex_bg)
    
           
EndSub:
       
End Sub

Public Sub LoadTableRow(oAttributes As MSXML2.IVBSAXAttributes)
End Sub

Public Sub EndTable()
    mTable.AutoFitBehavior wdAutoFitContent
    'mTable.Columns(1).AutoFit
    'mTable.Rows.Alignment = mTable.Rows.Alignment

    mWordApp.ActiveDocument.range(mTable.range.End, mTable.range.End).Select
End Sub

Public Static Function CountBorderLineWidth(ByVal width As Double) As Word.WdLineWidth
    Select Case width
        Case 0
            CountBorderLineWidth = wdLineStyleNone
        Case Is > 4.5
            CountBorderLineWidth = wdLineWidth600pt
        Case Is > 3
            CountBorderLineWidth = wdLineWidth450pt
        Case Is > 2.25
            CountBorderLineWidth = wdLineWidth300pt
        Case Is > 1.5
            CountBorderLineWidth = wdLineWidth225pt
        Case Is > 1
            CountBorderLineWidth = wdLineWidth150pt
        Case Is > 0.75
            CountBorderLineWidth = wdLineWidth100pt
        Case Is > 0.5
            CountBorderLineWidth = wdLineWidth075pt
        Case Is > 0.25
            CountBorderLineWidth = wdLineWidth050pt
        Case Is > 0
            CountBorderLineWidth = wdLineWidth025pt
    End Select
End Function

Public Sub LoadTable(oAttributes As MSXML2.IVBSAXAttributes)
    Dim bw As Double
    
    Set mTable = mWordApp.ActiveDocument.Tables.Add( _
        range:=mWordApp.Selection.range, _
        NumRows:=oAttributes.getValueFromName("", "rows"), _
        NumColumns:=oAttributes.getValueFromName("", "cols"))
        
    On Error Resume Next
    
    bw = 0
    bw = oAttributes.getValueFromName("", "borderwidth")
    
    On Error GoTo 0
    
    If bw > 0 Then
        mTable.Borders.InsideLineStyle = wdLineStyleSingle
        mTable.Borders.OutsideLineStyle = wdLineStyleSingle
                
        mTable.Borders.InsideLineWidth = CountBorderLineWidth(bw)
        mTable.Borders.OutsideLineWidth = CountBorderLineWidth(bw)
    Else
        mTable.Borders.InsideLineStyle = wdLineStyleNone
        mTable.Borders.OutsideLineStyle = wdLineStyleNone
    End If
End Sub

Public Sub EndText()
    mboolTextInserting = False
    ReSetTextStyle
End Sub

Public Sub TypeText(text As String)
    If mboolTextInserting Then
        AddText text
    End If
End Sub

Public Sub LoadText(oAttributes As MSXML2.IVBSAXAttributes)
    On Error GoTo no_style
    SetTextStyle oAttributes.getValueFromName("", "style")
    
'    Exit Sub

no_style:
    'AddText oAttributes.getValueFromName("", "value")
    
    mboolTextInserting = True

End Sub

Public Sub LoadParagraph(oAttributes As MSXML2.IVBSAXAttributes)
    On Error GoTo no_style
    AddParagraph oAttributes.getValueFromName("", "style")
    
    Exit Sub

no_style:
    AddParagraph
End Sub

Public Sub LoadInclude(oAttributes As MSXML2.IVBSAXAttributes)
    Dim cur_doc As Word.Document
    Dim open_doc As Word.Document
    
    Set cur_doc = mWordApp.ActiveDocument
    
'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
'!!!!!!!!!!nastavuje pocatek relativnicj cest!!!!!!!!
'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    mWordApp.ChangeFileOpenDirectory app.Path
'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
'!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        
    On Error GoTo FileError
    Set open_doc = mWordApp.Documents.Open( _
        FileName:=oAttributes.getValueFromName("", "file"), _
        ConfirmConversions:=False, _
        ReadOnly:=True, _
        AddToRecentFiles:=False, _
        PasswordDocument:="", _
        PasswordTemplate:="", Revert:=False, WritePasswordDocument:="", _
        WritePasswordTemplate:="", Format:=wdOpenFormatAuto)
            
               
    open_doc.Select
    mWordApp.Selection.Copy
    open_doc.Close SaveChanges:=False
        
    mWordApp.Selection.Paste
    mWordApp.Selection.Select
    
    Exit Sub
    
FileError:

    mLMRA.strLastError = "Error in iclude file loading!" _
        & vbNewLine & "filename: " & oAttributes.getValueFromName("", "file") & vbNewLine _
        & "file open directory: " & app.Path & vbNewLine
    
   
    Err.Clear
    Err.Raise vbObjectError + 1
                    
End Sub


Public Sub LoadChart(oAttributes As MSXML2.IVBSAXAttributes)
    Dim title As String
    Dim color As String
    
    mintLastGraphCell = 2
    mintGraphCharts = mintGraphCharts + 1
    
    
    On Error GoTo NoTitle
    
    title = oAttributes.getValueFromName("", "title")
    mGraph.Application.DataSheet.Cells(mintGraphCharts + 1, 1) = title
    
    
NoTitle:
    On Error GoTo EndSub
    'pokud neni titulek, aby se vytvorila series ktere se pak priradi barva
    mGraph.Application.DataSheet.Cells(mintGraphCharts + 1, 2) = 0
    
    color = oAttributes.getValueFromName("", "color")
    mGraph.SeriesCollection(mintGraphCharts).Interior.color = HTMLRGB_2_VBRGB(color)
    
    

EndSub:

End Sub

Public Sub LoadChartValue(oAttributes As MSXML2.IVBSAXAttributes)
    Dim val As String
    Dim color As String
    
    val = oAttributes.getValueFromName("", "value")
    mGraph.Application.DataSheet.Cells(mintGraphCharts + 1, mintLastGraphCell) = val
    
    On Error GoTo EndSub
    
    color = oAttributes.getValueFromName("", "color")
    
    On Error GoTo 0
    
    If Not color = "" Then
        mGraph.SeriesCollection(mintGraphCharts).Points(mintLastGraphCell - 1).Interior.color = _
            HTMLRGB_2_VBRGB(color)
    End If
    
    
EndSub:
    mintLastGraphCell = mintLastGraphCell + 1
End Sub

Public Sub LoadGraphCategories(oAttributes As MSXML2.IVBSAXAttributes)
    mintLastGraphCell = 2
End Sub

Public Sub LoadGraphCategory(oAttributes As MSXML2.IVBSAXAttributes)
    Dim title As String
    
    title = oAttributes.getValueFromName("", "title")
    mGraph.Application.DataSheet.Cells(1, mintLastGraphCell) = title
    
    mintLastGraphCell = mintLastGraphCell + 1
End Sub

Public Sub LoadGraph(oAttributes As MSXML2.IVBSAXAttributes)
    Dim shape As Word.InlineShape
    Dim bHasLegend As Boolean
    Dim sTitle As String
    Dim sType As String
    Dim intChartType As Integer
    Dim intWidth As Variant
    Dim intHeight As Variant
    Dim sBGColor As String
    
    mintLastGraphCell = 1
    mintGraphCharts = 0
    
    Set shape = mWordApp.Selection.InlineShapes.AddOLEObject("MSGraph.chart")
    Set mGraph = shape.OLEFormat.object
    mstrGraphProgID = shape.OLEFormat.ProgId
        
    intWidth = 1
    intHeight = 0.7
    
    sBGColor = ""
    
    On Error Resume Next
    
    sTitle = oAttributes.getValueFromName("", "title")
    sType = oAttributes.getValueFromName("", "charttype")
    bHasLegend = oAttributes.getValueFromName("", "showlegend")
    intWidth = oAttributes.getValueFromName("", "width")
    intHeight = oAttributes.getValueFromName("", "height")
    intHeight = oAttributes.getValueFromName("", "height")
    sBGColor = oAttributes.getValueFromName("", "bgcolor")

    
    On Error GoTo 0
    
    mGraph.width = mWordApp.ActiveDocument.PageSetup.PageWidth * intWidth
    mGraph.Height = mWordApp.ActiveDocument.PageSetup.PageWidth * intHeight

    
    If Len(sTitle) > 0 Then
        mGraph.HasTitle = True
        mGraph.ChartTitle.text = sTitle
    End If
    
    If (Not sBGColor = "") Then
        mGraph.Walls.Interior.color = HTMLRGB_2_VBRGB(sBGColor)
    End If
    
    mGraph.HasLegend = bHasLegend
         
    intChartType = FindEnumValInTypeLib(mstrGraphProgID, sType)
    If intChartType <> -1 Then mGraph.ChartType = intChartType
    
    mGraph.Application.DataSheet.Cells.Clear
               
End Sub

Public Sub EndGraph()
    mGraph.Application.Update
    mGraph.Application.Quit
End Sub


Public Sub LoadChapter(oAttributes As MSXML2.IVBSAXAttributes)
    AddTitle oAttributes.getValueFromName("", "title")
    mintHeadinglevel = mintHeadinglevel + 1

End Sub

Public Sub EndChapter()
    mintHeadinglevel = mintHeadinglevel - 1
End Sub


Public Sub LoadReport(oAttributes As MSXML2.IVBSAXAttributes)
'    Dim i As Integer
    
'    AddParagraph wdStyleHeading1
    
    'prametry jsou nepovinne
    On Error Resume Next
    
    FirstTitle oAttributes.getValueFromName("", "title")
    mintHeadinglevel = 2
    AddTitle oAttributes.getValueFromName("", "subtitle")
    AddTitle oAttributes.getValueFromName("", "author")
    mintHeadinglevel = 1
 
End Sub

Public Sub EndDocument()
    mWordApp.Visible = True
End Sub

