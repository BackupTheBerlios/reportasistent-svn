VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "cbCommandEvents"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
'poziva se pro chytani eventu od zakladnich tlacitek - ne od aktivnich prvku

Option Explicit

Public WithEvents cbBtn As Office.CommandBarButton
Attribute cbBtn.VB_VarHelpID = -1

Dim mLMRA As LMRA_XML_WordLoader

Public Property Set LMRA_loader(P As LMRA_XML_WordLoader)
   Set mLMRA = P
End Property



Private Sub cbBtn_Click(ByVal Ctrl As Office.CommandBarButton, CancelDefault As Boolean)
    mLMRA.CommandEvent Ctrl.Tag
End Sub
