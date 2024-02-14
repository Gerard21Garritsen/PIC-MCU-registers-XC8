Public Class frmUSB
    ' vendor and product IDs
    Private Const VendorID As Integer = &H4D8    'Replace with your device's
    Private Const ProductID As Integer = &H3F      'product and vendor IDs

    ' read and write buffers
    Private Const BufferInSize As Integer = 64 'Size of the data buffer coming IN to the PC
    Private Const BufferOutSize As Integer = 64    'Size of the data buffer going OUT from the PC
    Dim BufferIn(BufferInSize) As Byte          'Received data will be stored here - the first byte in the array is unused
    Dim BufferOut(BufferOutSize) As Byte    'Transmitted data is stored here - the first item in the array must be 0
    Dim Led_byte As Byte 'Variable para el control del LED

    ' ****************************************************************
    ' when the form loads, connect to the HID controller - pass
    ' the form window handle so that you can receive notification
    ' events...
    '*****************************************************************
    Private Sub Form1_Load(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles MyBase.Load
        ' do not remove!
        ConnectToHID(Me)
    End Sub

    '*****************************************************************
    ' disconnect from the HID controller...
    '*****************************************************************
    Private Sub Form1_FormClosed(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosedEventArgs) Handles Me.FormClosed
        DisconnectFromHID()
    End Sub

    '*****************************************************************
    ' a HID device has been plugged in...
    '*****************************************************************
    Public Sub OnPlugged(ByVal pHandle As Integer)
        If hidGetVendorID(pHandle) = VendorID And hidGetProductID(pHandle) = ProductID Then
            PIC18F4550.Text = "PIC18F4550 Conectado" 'Titulo cuando se conecta el PIC
        End If
    End Sub

    '*****************************************************************
    ' a HID device has been unplugged...
    '*****************************************************************
    Public Sub OnUnplugged(ByVal pHandle As Integer)
        If hidGetVendorID(pHandle) = VendorID And hidGetProductID(pHandle) = ProductID Then
            hidSetReadNotify(hidGetHandle(VendorID, ProductID), False)
            PIC18F4550.Text = "PIC18F4550 Desconectado" 'Titulo cuando se desconecta el PIC
        End If
    End Sub

    '*****************************************************************
    ' controller changed notification - called
    ' after ALL HID devices are plugged or unplugged
    '*****************************************************************
    Public Sub OnChanged()
        ' get the handle of the device we are interested in, then set
        ' its read notify flag to true - this ensures you get a read
        ' notification message when there is some data to read...
        Dim pHandle As Integer
        pHandle = hidGetHandle(VendorID, ProductID)
        hidSetReadNotify(hidGetHandle(VendorID, ProductID), True)
    End Sub

    '*****************************************************************
    ' on read event...
    '*****************************************************************
    Public Sub OnRead(ByVal pHandle As Integer)
        ' read the data (don't forget, pass the whole array)...
        If hidRead(pHandle, BufferIn(0)) Then
            ' ** YOUR CODE HERE **
            ' first byte is the report ID, e.g. BufferIn(0)
            ' the other bytes are the data from the microcontroller...
        End If
    End Sub

    Private Sub LED_Click(sender As Object, e As EventArgs) Handles LED.Click
        'Acciones del boton
        If LED.Text = "ON" Then 'Si se presiona el boton en ON cambiara a OFF y encendera el LED
            LED.Text = "OFF"
            Led_byte = 1
        ElseIf LED.Text = "OFF" Then 'Si se presiona el boton en OFF cambiara a ON y se apagara el LED
            LED.Text = "ON"
            Led_byte = 0
        End If
        BufferOut(0) = 0 'Se asigna cero al buffer 0 por que no existen en Visual Basic
        BufferOut(1) = Led_byte 'Se asigna a buffer(1) el valor de Led_byte y este se manda a Buffer[0] del PIC
        hidWriteEx(VendorID, ProductID, BufferOut(0)) 'Para los datos de salida
    End Sub
End Class
