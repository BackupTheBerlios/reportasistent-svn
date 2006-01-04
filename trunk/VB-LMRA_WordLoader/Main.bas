Attribute VB_Name = "MainModule"
'*******************************************************
'zacatek maker by honza
'*******************************************************

Option Explicit ' Force explicit variable declaration.

'hlavni funkce spoustena z ActiveX exe-souboru
Public Static Sub Main()
    Dim f1 As New Form1
    f1.Caption = "start z lib"
    f1.Show
End Sub


'*********************************************************************
'*********************************************************************
'*********************************************************************
'*********************************************************************
'zaloha maker z word sablony

#If Mac Then

Sub InsertText(text_element As REPORTASISTENTLib.ElementText, Optional range As Word.range)
    If Not range Is Nothing Then range.Select
    
    If text_element.NewParagraph Then Selection.TypeParagraph
    
    
    If Not IsEmpty(text_element.style) Then
        Selection.style = text_element.style
        
        Selection.TypeText text_element.text
        
        If ActiveDocument.Styles(text_element.style).Type = wdStyleTypeCharacter Then
            Selection.style = wdStyleDefaultParagraphFont
        End If
    Else
        Selection.TypeText text_element.text
    End If
    
    
End Sub




Sub InsertCompound(compound_element As REPORTASISTENTLib.ElementCompound, Optional range As Word.range)
    If Not range Is Nothing Then range.Select
    
    While compound_element.continueInserting
        QueryInsertElement compound_element.GetNextInsertElement
    Wend
End Sub





Sub InsertTable(table_element As REPORTASISTENTLib.ElementTable, Optional range As Word.range)
'    ActiveDocument.Tables.Add range:=Selection.range, NumRows:=2, NumColumns:= _
'        4, DefaultTableBehavior:=wdWord9TableBehavior, AutoFitBehavior:= _
'        wdAutoFitFixed

    Dim t As Word.Table
    Dim x As Long
    Dim y As Long
    Dim word_cell As Word.Cell
    Dim ra_cell As REPORTASISTENTLib.TableCell
        
    If range Is Nothing Then Set range = Selection.range
    
    Set t = ActiveDocument.Tables.Add(range:=range, NumRows:=table_element.Cells_dy, NumColumns:=table_element.Cells_dx)
    
    For y = 1 To table_element.Cells_dy
        For x = 1 To table_element.Cells_dx
            Set word_cell = t.Cell(Row:=y, Column:=x)
            Set ra_cell = table_element.Cells(x - 1, y - 1)
            
            QueryInsertElement ra_cell.Content, word_cell.range
            
            word_cell.Shading.BackgroundPatternColor = ra_cell.BackgroundPatternColor
        Next x
    Next y
    
    t.AutoFitBehavior table_element.AutoFitBehavior
    t.Rows.Alignment = table_element.RowAlignment
        
    ActiveDocument.range(t.range.End, t.range.End).Select
End Sub




Sub InsertGraph(graph_element As REPORTASISTENTLib.ElementGraph, Optional range As Word.range)
    Dim x As Long
    Dim y As Long
    Dim g As Graph.Chart
    Dim shape As Word.InlineShape
    
    
    If range Is Nothing Then Set range = Selection.range
    
    Set shape = range.InlineShapes.AddOLEObject("MSGraph.chart")
    Set g = shape.OLEFormat.object
    
    g.ChartType = graph_element.graphType
            
    With g.Application.DataSheet
        .Cells.Clear
        For y = 1 To graph_element.Cells_dy
            For x = 1 To graph_element.Cells_dx
                .Cells(ColumnIndex:=x, RowIndex:=y) = graph_element.Cells(x - 1, y - 1)
            Next x
        Next y
    End With
    
    g.Application.Update
    g.Application.Quit
End Sub




Sub QueryInsertElement(element As REPORTASISTENTLib.InsertElement, Optional range As Word.range)

    Select Case element.elementType
    Case elGraph
        InsertGraph range:=range, graph_element:=element
    Case elText
        InsertText range:=range, text_element:=element
    Case elCompound
        InsertCompound range:=range, compound_element:=element
    Case elTable
        InsertTable range:=range, table_element:=element
    End Select
    
End Sub



'hlavni makro-procedura volana z toolbaru
Sub InsertObject()
    Dim Main As REPORTASISTENTLib.MainObject
    
    Dim element As REPORTASISTENTLib.InsertElement
    
           
    Set Main = CreateObject("ReportAsistent.MainObject")
    
    Set element = Main.GetNextInsertElement
    
    QueryInsertElement element
        
'    If element.elementType = elGraph Then
'        InserGraph range:=Selection.Tables(1).Cell(2, 2).range, graph_element:=element
'        InsertGraph range:=Selection.range, graph_element:=element
'    End If
         
End Sub

#End If
