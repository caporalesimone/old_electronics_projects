VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmMain 
   BorderStyle     =   1  'Fixed Single
   Caption         =   "frmMain"
   ClientHeight    =   2565
   ClientLeft      =   45
   ClientTop       =   330
   ClientWidth     =   3240
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   2565
   ScaleWidth      =   3240
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame2 
      Caption         =   "Trasmetti ora "
      Height          =   1455
      Left            =   1680
      TabIndex        =   8
      Top             =   960
      Width           =   1335
      Begin VB.CommandButton Command2 
         Caption         =   "Trasmetti ora generica"
         Height          =   495
         Left            =   120
         TabIndex        =   10
         Top             =   840
         Width           =   1095
      End
      Begin VB.CommandButton cmdTrasmOraPC 
         Caption         =   "Trasmetti ora del computer"
         Height          =   495
         Left            =   120
         TabIndex        =   9
         Top             =   240
         Width           =   1095
      End
   End
   Begin VB.Timer tmrOra 
      Interval        =   1000
      Left            =   2640
      Top             =   480
   End
   Begin MSCommLib.MSComm Seriale 
      Left            =   2160
      Top             =   120
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      CommPort        =   2
      DTREnable       =   -1  'True
   End
   Begin VB.Timer tmrPIC 
      Interval        =   1000
      Left            =   2640
      Top             =   0
   End
   Begin VB.Frame Frame1 
      Caption         =   "Leggi ora dal PIC"
      Height          =   1455
      Left            =   120
      TabIndex        =   0
      Top             =   960
      Width           =   1455
      Begin VB.OptionButton optLetturaContinua 
         Caption         =   "Continua"
         Height          =   255
         Left            =   120
         TabIndex        =   3
         Top             =   600
         Width           =   975
      End
      Begin VB.OptionButton optLetturaSingola 
         Caption         =   "Singola"
         Height          =   255
         Left            =   120
         TabIndex        =   2
         Top             =   360
         Value           =   -1  'True
         Width           =   855
      End
      Begin VB.CommandButton cmdLeggiOra 
         Caption         =   "Leggi Ora"
         Height          =   375
         Left            =   120
         TabIndex        =   1
         Top             =   960
         Width           =   1215
      End
   End
   Begin VB.Label lblOraPIC 
      Height          =   255
      Left            =   840
      TabIndex        =   7
      Top             =   480
      Width           =   1695
   End
   Begin VB.Label lblOraPC 
      Height          =   255
      Left            =   840
      TabIndex        =   6
      Top             =   120
      Width           =   1575
   End
   Begin VB.Label Label2 
      Caption         =   "Ora PIC :"
      Height          =   255
      Left            =   120
      TabIndex        =   5
      Top             =   480
      Width           =   735
   End
   Begin VB.Label Label1 
      Caption         =   "Ora PC :"
      Height          =   255
      Left            =   120
      TabIndex        =   4
      Top             =   120
      Width           =   735
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub cmdLeggiOra_Click()
Dim str As String
Dim bOraLetta As Boolean
Dim cntTentativi As Integer

If bLeggiOraPic = False Then
    
    optLetturaContinua.Enabled = False
    optLetturaSingola.Enabled = False
    
    If optLetturaContinua.Value = True Then
        bLeggiOraPic = True
        cmdLeggiOra.Caption = "Ferma Lettura"
        bLetturaContinua = True
    Else
        bOraLetta = False
        cntTentativi = 0
        str = "Errore"
        While (bOraLetta = False And cntTentativi < 100)
            Seriale.Output = "1"
            Delay_ms (50)
            str = ConvertiOra(LeggiNByte(11))
            If Len(Trim(str)) <> 0 Then bOraLetta = True
            cntTentativi = cntTentativi + 1
        Wend

        lblOraPIC.Caption = str
       
        optLetturaContinua.Enabled = True
        optLetturaSingola.Enabled = True
    End If

Else
    bLeggiOraPic = False
    cmdLeggiOra.Caption = "Leggi Ora"
    optLetturaContinua.Enabled = True
    optLetturaSingola.Enabled = True

End If

End Sub


Private Sub cmdTrasmOraPC_Click()
Dim giorno, ora, min, sec As Integer
Dim inp As Long
    
    Seriale.Output = Chr(2)
    'Delay_ms (100)
    
    giorno = Weekday(Now, 2) - 1
    ora = Hour(Now)
    min = Minute(Now)
    sec = Second(Now)
    
    Seriale.InputLen = 1
        
    Seriale.Output = Chr(giorno)
    Delay_ms (100)
    Seriale.Output = Chr(ora)
    Delay_ms (100)
    Seriale.Output = Chr(min)
    Delay_ms (100)
    Seriale.Output = Chr(sec)
    
    MsgBox "Trasmissione effettutata", vbInformation
End Sub

Private Sub Form_Load()

    Seriale.PortOpen = True

End Sub

Private Sub tmrOra_Timer()
    
    strOra = Left(WeekdayName(Weekday(Now), , 1), 3)
    strOra = strOra & " " & Format(Now, "HH:MM:SS")
    lblOraPC.Caption = strOra

End Sub

Private Sub tmrPIC_Timer()
Dim strOra As String

    If bLeggiOraPic = True Then
        Seriale.Output = "1"
        lblOraPIC.Caption = ConvertiOra(LeggiNByte(11))
    End If

End Sub
