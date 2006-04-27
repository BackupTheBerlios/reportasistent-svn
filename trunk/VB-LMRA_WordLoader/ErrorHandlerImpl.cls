VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
  Persistable = 0  'NotPersistable
  DataBindingBehavior = 0  'vbNone
  DataSourceBehavior  = 0  'vbNone
  MTSTransactionMode  = 0  'NotAnMTSObject
END
Attribute VB_Name = "ErrorHandlerImpl"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = True
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit

Implements IVBSAXErrorHandler

Dim mLMRA As LMRA_XML_WordLoader


Public Property Set LMRA_loader(P As LMRA_XML_WordLoader)
   Set mLMRA = P
End Property



Private Sub IVBSAXErrorHandler_error(ByVal oLocator As MSXML2.IVBSAXLocator, strErrorMessage As String, ByVal nErrorCode As Long)
    mLMRA.strLastError = "error (" & nErrorCode & "): " & strErrorMessage
    'Form1.txtOutput.text = Form1.txtOutput.text & vbNewLine & "*** error ***" & strErrorMessage
End Sub

Private Sub IVBSAXErrorHandler_fatalError(ByVal oLocator As MSXML2.IVBSAXLocator, strErrorMessage As String, ByVal nErrorCode As Long)
    If (nErrorCode <> vbObjectError + 1) Then
        mLMRA.strLastError = "fatal error (" & nErrorCode & "): " & strErrorMessage
    End If
    'Form1.txtOutput.text = Form1.txtOutput.text & vbNewLine & "*** fatal error ***" & strErrorMessage
End Sub

Private Sub IVBSAXErrorHandler_ignorableWarning(ByVal oLocator As MSXML2.IVBSAXLocator, strErrorMessage As String, ByVal nErrorCode As Long)
    mLMRA.strLastError = "warning (" & nErrorCode & "): " & strErrorMessage
    'Form1.txtOutput.text = Form1.txtOutput.text & vbNewLine & "*** warning ***" & strErrorMessage
End Sub
