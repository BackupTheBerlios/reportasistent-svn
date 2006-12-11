Attribute VB_Name = "MainModule"
Option Explicit ' Force explicit variable declaration.

'hlavni funkce spoustena z ActiveX exe-souboru
Public Static Sub Main()
    
    If (app.StartMode = vbSModeStandalone) And (Command() <> "register") Then
        Dim f1 As New Form1
        
        If (Not Command = "") Then
            f1.caption = Command
        End If
        
        f1.Show
    End If
End Sub

