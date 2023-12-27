VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form frmMain 
   BackColor       =   &H8000000A&
   BorderStyle     =   1  'Fixed Single
   Caption         =   "Monitor Carica Batterie"
   ClientHeight    =   6495
   ClientLeft      =   1560
   ClientTop       =   1980
   ClientWidth     =   9990
   LinkTopic       =   "Form1"
   MaxButton       =   0   'False
   MinButton       =   0   'False
   ScaleHeight     =   6495
   ScaleWidth      =   9990
   Begin MSCommLib.MSComm MSComm1 
      Left            =   2280
      Top             =   6360
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Timer Timer1 
      Enabled         =   0   'False
      Interval        =   1500
      Left            =   9240
      Top             =   5880
   End
   Begin VB.TextBox txtFocus 
      Height          =   405
      Left            =   480
      MultiLine       =   -1  'True
      ScrollBars      =   2  'Vertical
      TabIndex        =   1
      Top             =   6720
      Width           =   1455
   End
   Begin VB.Frame Frame3 
      Height          =   6375
      Left            =   120
      TabIndex        =   0
      Top             =   0
      Width           =   9735
      Begin VB.CommandButton Command1 
         Caption         =   "Start"
         Height          =   375
         Left            =   4080
         TabIndex        =   10
         Top             =   240
         Width           =   1575
      End
      Begin VB.CommandButton Command2 
         Caption         =   "Stop"
         Height          =   375
         Left            =   4080
         TabIndex        =   9
         Top             =   1200
         Width           =   1575
      End
      Begin VB.PictureBox pctGrafico 
         BackColor       =   &H00FFFFFF&
         Height          =   4455
         Left            =   120
         ScaleHeight     =   4395
         ScaleWidth      =   9435
         TabIndex        =   6
         Top             =   1800
         Width           =   9495
         Begin VB.Line Line2 
            BorderColor     =   &H00008000&
            X1              =   8760
            X2              =   9240
            Y1              =   360
            Y2              =   360
         End
         Begin VB.Line Line1 
            BorderColor     =   &H000000FF&
            X1              =   8760
            X2              =   9240
            Y1              =   120
            Y2              =   120
         End
         Begin VB.Label Label2 
            BackStyle       =   0  'Transparent
            Caption         =   "Out 2"
            Height          =   255
            Left            =   8280
            TabIndex        =   8
            Top             =   240
            Width           =   495
         End
         Begin VB.Label Label1 
            BackStyle       =   0  'Transparent
            Caption         =   "Out 1"
            Height          =   255
            Left            =   8280
            TabIndex        =   7
            Top             =   1
            Width           =   495
         End
      End
      Begin VB.Frame Frame1 
         Caption         =   "Uscita 1"
         Height          =   1575
         Left            =   120
         TabIndex        =   3
         Top             =   120
         Width           =   3735
         Begin VB.TextBox txt_out1 
            Alignment       =   2  'Center
            BackColor       =   &H00000000&
            BeginProperty Font 
               Name            =   "LcdD"
               Size            =   54.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H0000FF00&
            Height          =   1245
            Left            =   120
            Locked          =   -1  'True
            TabIndex        =   4
            Text            =   "00.00 V"
            Top             =   240
            Width           =   3495
         End
      End
      Begin VB.Frame Frame2 
         Caption         =   "Uscita 2"
         Height          =   1575
         Left            =   5880
         TabIndex        =   2
         Top             =   120
         Width           =   3735
         Begin VB.TextBox txt_out2 
            Alignment       =   2  'Center
            BackColor       =   &H00000000&
            BeginProperty Font 
               Name            =   "LcdD"
               Size            =   54.75
               Charset         =   0
               Weight          =   400
               Underline       =   0   'False
               Italic          =   0   'False
               Strikethrough   =   0   'False
            EndProperty
            ForeColor       =   &H0000FF00&
            Height          =   1245
            Left            =   120
            Locked          =   -1  'True
            TabIndex        =   5
            Text            =   "00.00 V"
            Top             =   240
            Width           =   3495
         End
      End
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Dim LarghezzaGrafico As Integer
Dim X0 As Integer
Dim Y0 As Integer

Dim Y_old1 As Integer
Dim Y_old2 As Integer

Dim NumCampione As Integer

Const MaxVolt = 2
Const MaxCampioni = 300



Private Sub PreparaGrafico()
Dim i As Integer
Dim pos As Integer

pctGrafico.ScaleMode = 3
pctGrafico.DrawWidth = 2
LarghezzaGrafico = pctGrafico.ScaleWidth - 10
Y0 = pctGrafico.ScaleHeight - 10
X0 = 10
pctGrafico.Line (X0, 10)-(X0, Y0), vbBlack
pctGrafico.Line (X0, Y0)-(LarghezzaGrafico, Y0), vbBlack

pos = Y0

pctGrafico.DrawWidth = 1

For i = 0 To MaxVolt
    pos = pos - (Y0 / (MaxVolt + 1))
    pctGrafico.Line (X0 + 650, pos)-(X0 - 5, pos), &HE0E0E0
Next i

pos = X0

For i = 0 To MaxCampioni
    pos = pos + (LarghezzaGrafico / (MaxCampioni + 1))
    If i Mod 3 = 0 Then
        pctGrafico.Line (pos, Y0 - 280)-(pos, Y0 + 5), &HE0E0E0
    End If
Next i

NumCampione = 1

End Sub


Function CalcolaY_Tensione(v As Integer) As Integer
Dim num As Long
num = (Y0 - 10) * (CLng(v) / 100)
CalcolaY_Tensione = Y0 - (num / MaxVolt)
End Function

Function CalcolaX_Tensione(n As Integer) As Integer
Dim Inc As Integer

If n = 1 Then
    CalcolaX_Tensione = X0
Else
    Inc = LarghezzaGrafico / (MaxCampioni + 1)
    CalcolaX_Tensione = n * Inc
End If

End Function


Private Sub PlotTensione(v1 As Integer, v2 As Integer)
Dim X As Integer
Dim Y As Integer
Dim x_old As Integer

X = CalcolaX_Tensione(NumCampione)

If NumCampione = 1 Then
    Y = CalcolaY_Tensione(v1)
    Y_old1 = Y
    pctGrafico.PSet (X, Y), vbRed
    Y = CalcolaY_Tensione(v2)
    pctGrafico.PSet (X0, Y), vbGreen
    Y_old2 = Y
Else
    Y = CalcolaY_Tensione(v1)
    x_old = CalcolaX_Tensione(NumCampione - 1)
    pctGrafico.Line (X, Y)-(x_old, Y_old1), vbRed
    Y_old1 = Y
    Y = CalcolaY_Tensione(v2)
    x_old = CalcolaX_Tensione(NumCampione - 1)
    pctGrafico.Line (X, Y)-(x_old, Y_old2), vbGreen
    Y_old2 = Y

End If

NumCampione = NumCampione + 1
If NumCampione > MaxCampioni Then
    NumCampione = 1
    pctGrafico.Refresh
    PreparaGrafico
End If


End Sub

Private Sub Command1_Click()
' Buffer in cui viene memorizzata la stringa di
   ' input
   
   MSComm1.CommPort = 4
   MSComm1.Settings = "9600,N,8,1"
   ' Comunica al controllo di leggere l'intero buffer
   ' quando viene utilizzata la proprietà Input.
   MSComm1.InputLen = 0
   ' Apre la porta.
   MSComm1.PortOpen = True
   ' Invia al modem il comando di attivazione.
   
   Timer1.Enabled = True
End Sub

Private Sub Command2_Click()
MSComm1.PortOpen = False
Timer1.Enabled = False
End Sub

Private Sub Form_Activate()
Call PreparaGrafico
End Sub



Private Sub Timer1_Timer()

Dim num1 As String
Dim num2 As String
Dim buffer As String
Dim i As Integer

'Il pic trasmette una serie di stringhe
'[12345678][12345678]... prendo l'ultima
'sezione [ ] dal buffer e ne stampo i valori

buffer = ""
Do
  DoEvents
  buffer = buffer & MSComm1.Input
Loop Until InStr(buffer, Chr(93))
   
buffer = Right(buffer, 10)
  
If Left(buffer, 1) = "[" Then
    
  buffer = Right(buffer, 9)
  buffer = Left(buffer, 8)

  For i = 1 To 4
    num1 = num1 + Trim(Str(Asc(Mid(buffer$, i, 1))))
  Next
   
  For i = 5 To 8
    num2 = num2 + Trim(Str(Asc(Mid(buffer$, i, 1))))
  Next
      
  txt_out1.Text = Format(Int(num1) / 100, "00.00 V")
  txt_out2.Text = Format(Int(num2) / 100, "00.00 V")
  Call PlotTensione(Int(num1) - 1250, Int(num2) - 1250)

Else
 Call Timer1_Timer
End If

  
End Sub

Private Sub txt_out1_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
txtFocus.SetFocus
End Sub
Private Sub txt_out2_MouseMove(Button As Integer, Shift As Integer, X As Single, Y As Single)
txtFocus.SetFocus
End Sub
