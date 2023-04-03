VERSION 5.00
Object = "{648A5603-2C6E-101B-82B6-000000000014}#1.1#0"; "MSCOMM32.OCX"
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   3795
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   5790
   LinkTopic       =   "Form1"
   ScaleHeight     =   3795
   ScaleWidth      =   5790
   StartUpPosition =   3  'Windows Default
   Begin VB.CommandButton Command10 
      Caption         =   "STOP"
      Height          =   1335
      Left            =   4680
      TabIndex        =   8
      Top             =   2040
      Width           =   855
   End
   Begin VB.CommandButton Command9 
      Caption         =   "\/"
      Height          =   615
      Left            =   3840
      TabIndex        =   7
      Top             =   2760
      Width           =   735
   End
   Begin VB.CommandButton Command8 
      Caption         =   "/\"
      Height          =   615
      Left            =   3840
      TabIndex        =   6
      Top             =   2040
      Width           =   735
   End
   Begin VB.CommandButton Command7 
      Caption         =   "STOP"
      Height          =   495
      Left            =   4560
      TabIndex        =   5
      Top             =   1200
      Width           =   975
   End
   Begin VB.CommandButton Command6 
      Caption         =   "STOP"
      Height          =   495
      Left            =   4560
      TabIndex        =   2
      Top             =   240
      Width           =   975
   End
   Begin VB.CommandButton Command5 
      Caption         =   "-5"
      Height          =   495
      Left            =   3480
      TabIndex        =   4
      Top             =   1200
      Width           =   975
   End
   Begin VB.CommandButton Command4 
      Caption         =   "+5"
      Height          =   495
      Left            =   2400
      TabIndex        =   3
      Top             =   1200
      Width           =   975
   End
   Begin VB.CommandButton Command3 
      Caption         =   "-5"
      Height          =   495
      Left            =   3480
      TabIndex        =   1
      Top             =   240
      Width           =   975
   End
   Begin VB.CommandButton Command2 
      Caption         =   "+5"
      Height          =   495
      Left            =   2400
      TabIndex        =   0
      Top             =   240
      Width           =   975
   End
   Begin VB.CommandButton Command1 
      Caption         =   "send"
      Height          =   375
      Left            =   1320
      TabIndex        =   11
      Top             =   2280
      Width           =   855
   End
   Begin VB.TextBox Text2 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   720
      TabIndex        =   10
      Text            =   "127"
      Top             =   1080
      Width           =   1455
   End
   Begin VB.TextBox Text1 
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   855
      Left            =   720
      TabIndex        =   9
      Text            =   "127"
      Top             =   120
      Width           =   1455
   End
   Begin MSCommLib.MSComm Serial 
      Left            =   2640
      Top             =   2760
      _ExtentX        =   1005
      _ExtentY        =   1005
      _Version        =   393216
      DTREnable       =   -1  'True
   End
   Begin VB.Label Label2 
      Caption         =   "S"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   13
      Top             =   1200
      Width           =   495
   End
   Begin VB.Label Label1 
      Caption         =   "D"
      BeginProperty Font 
         Name            =   "MS Sans Serif"
         Size            =   24
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
      Height          =   615
      Left            =   120
      TabIndex        =   12
      Top             =   240
      Width           =   495
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command10_Click()
Text1.Text = "127"
Text2.Text = "127"
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command2_Click()
Text1.Text = Int(Text1.Text) + 5
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command3_Click()
Text1.Text = Int(Text1.Text) - 5
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command4_Click()
Text2.Text = Int(Text2.Text) + 5
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command5_Click()
Text2.Text = Int(Text2.Text) - 5
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command6_Click()
Text1.Text = "127"
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))

End Sub

Private Sub Command7_Click()
Text2.Text = "127"
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command8_Click()
Text1.Text = Int(Text1.Text) + 5
Text2.Text = Int(Text2.Text) + 5
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Command9_Click()
Text1.Text = Int(Text1.Text) - 5
Text2.Text = Int(Text2.Text) - 5
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Form_Load()
Serial.CommPort = 2
Serial.Settings = "9600,N,8,1"
Serial.InputLen = 0
Serial.PortOpen = True
Serial.Output = Chr$(Int(Text1.Text)) & Chr$(Int(Text2.Text))
End Sub

Private Sub Text1_Change()
If Int(Text1.Text) > 255 Then Text1.Text = 255
If Int(Text1.Text) < 0 Then Text1.Text = 0
End Sub

Private Sub Text2_Change()
If Int(Text2.Text) > 255 Then Text2.Text = 255
If Int(Text2.Text) < 0 Then Text2.Text = 0
End Sub
