Function GetProductKey(ByVal digitalProductId)
  Dim raw
  Dim val(15)
  
  map = "BCDFGHJKMPQRTVWXY2346789"
  key = ""
  j = 0
  
  With (WScript.CreateObject("WScript.Shell"))
    raw = .RegRead(digitalProductId)
  End With
  
  For i = 52 To 66
    val(j) = raw(i)
    j = j + 1
  Next
  
  For i = 24 To 0 Step - 1
    k = 0
    For j = 14 To 0 Step - 1
      k = (k * 256) XOR val(j)
      val(j) = k \ 24
      k = k Mod 24
    Next
    key = Mid(map, k + 1, 1) & key
    
    If i Mod 5 = 0 And i <> 0 Then
      key = "-" & key
    End If
  Next
  
  WScript.Echo key
End Function

GetProductKey("HKLM\SOFTWARE\Microsoft\Windows NT\CurrentVersion\DigitalProductId")
