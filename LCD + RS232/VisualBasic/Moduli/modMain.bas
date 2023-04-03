Attribute VB_Name = "modMain"
Global bLeggiOraPic As Boolean
Public Declare Function GetTickCount Lib "kernel32" () As Long



Public Function LeggiNByte(ByVal numByte As Integer) As String
Dim i       As Integer
Dim stringa As String

    stringa = ""
    frmMain.Seriale.InputLen = 1

    For i = 1 To numByte
        stringa = stringa & frmMain.Seriale.Input
        'Delay_ms (10)
    Next

    LeggiNByte = stringa

End Function

Public Function ConvertiOra(ByVal sOra As String) As String
Dim i       As Integer
Dim stringa As String

    stringa = Left(sOra, 3)
    stringa = stringa & " "
    stringa = stringa & Mid(sOra, 4, 8)
    ConvertiOra = stringa

End Function


Public Sub Delay_ms(ByVal millisecondi As Long)

Dim tick_fine   As Long
Dim tick_inizio As Long


tick_inizio = GetTickCount
tick_fine = tick_inizio + millisecondi

While GetTickCount < tick_fine

Wend


End Sub



Sub main()

    bLeggiOraPic = False
    Load frmMain
    frmMain.Show
    
End Sub
