Imports System
Imports Microsoft.Win32
Imports System.Reflection
Imports System.Collections

<assembly: AssemblyVersion("2.0.0.0")>

Namespace ProductKey
  Class Program
    Friend Shared Function DecodeProductKey(ByVal digitalProductId As Byte()) As String
      Dim map As Char() = ("BCDFGHJKMPQRTVWXY2346789").ToCharArray()
      Dim key As Char() = New Char(28) {}
      Dim raw As New ArrayList()
      
      For i As Int32 = 52 To 66
        raw.Add(digitalProductId(i))
      Next
      
      For i As Int32 = 28 To 0 Step - 1
        If (i + 1) Mod 6 = 0 Then
          key(i) = "-"C
        Else
          Dim k As Int32 = 0
          For j As Int32 = 14 To 0 Step - 1
            k = (k * 256) Xor CByte(raw(j))
            raw(j) = CByte(k \ 24)
            k = k Mod 24
            key(i) = map(k)
          Next
        End If
      Next
      Return New String(key)
    End Function
    
    Shared Sub Main()
      Using rk As RegistryKey = _
        Registry.LocalMachine.OpenSubKey("SOFTWARE\Microsoft\Windows NT\CurrentVersion")
        Dim val As Byte() = TryCast(rk.GetValue("DigitalProductId"), Byte())
        Console.WriteLine(DecodeProductKey(val))
      End Using
    End Sub
  End Class
End Namespace
