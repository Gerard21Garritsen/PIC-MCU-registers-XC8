<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()> _
Partial Class frmUSB
    Inherits System.Windows.Forms.Form

    'Form overrides dispose to clean up the component list.
    <System.Diagnostics.DebuggerNonUserCode()> _
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Required by the Windows Form Designer
    Private components As System.ComponentModel.IContainer

    'NOTE: The following procedure is required by the Windows Form Designer
    'It can be modified using the Windows Form Designer.  
    'Do not modify it using the code editor.
    <System.Diagnostics.DebuggerStepThrough()> _
    Private Sub InitializeComponent()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(frmUSB))
        Me.PIC18F4550 = New System.Windows.Forms.Label()
        Me.LED = New System.Windows.Forms.Button()
        Me.PictureBox1 = New System.Windows.Forms.PictureBox()
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).BeginInit()
        Me.SuspendLayout()
        '
        'PIC18F4550
        '
        Me.PIC18F4550.AutoSize = True
        Me.PIC18F4550.Location = New System.Drawing.Point(226, 26)
        Me.PIC18F4550.Name = "PIC18F4550"
        Me.PIC18F4550.Size = New System.Drawing.Size(52, 13)
        Me.PIC18F4550.TabIndex = 0
        Me.PIC18F4550.Text = "USB_PIC"
        '
        'LED
        '
        Me.LED.BackColor = System.Drawing.Color.CadetBlue
        Me.LED.Location = New System.Drawing.Point(215, 58)
        Me.LED.Name = "LED"
        Me.LED.Size = New System.Drawing.Size(75, 23)
        Me.LED.TabIndex = 1
        Me.LED.Text = "ON"
        Me.LED.UseVisualStyleBackColor = False
        '
        'PictureBox1
        '
        Me.PictureBox1.Image = CType(resources.GetObject("PictureBox1.Image"), System.Drawing.Image)
        Me.PictureBox1.Location = New System.Drawing.Point(30, 26)
        Me.PictureBox1.Name = "PictureBox1"
        Me.PictureBox1.Size = New System.Drawing.Size(159, 143)
        Me.PictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage
        Me.PictureBox1.TabIndex = 2
        Me.PictureBox1.TabStop = False
        '
        'frmUSB
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.ClientSize = New System.Drawing.Size(509, 222)
        Me.Controls.Add(Me.PictureBox1)
        Me.Controls.Add(Me.LED)
        Me.Controls.Add(Me.PIC18F4550)
        Me.Name = "frmUSB"
        Me.Text = "PIC18F4550 USB"
        CType(Me.PictureBox1, System.ComponentModel.ISupportInitialize).EndInit()
        Me.ResumeLayout(False)
        Me.PerformLayout()

    End Sub

    Friend WithEvents PIC18F4550 As Label
    Friend WithEvents LED As Button
    Friend WithEvents PictureBox1 As PictureBox
End Class
