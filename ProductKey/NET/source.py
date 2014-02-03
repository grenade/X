from System import Array, Char, Console
from Microsoft.Win32 import Registry
from System.Collections import ArrayList

def DecodeProductKey(digitalProductId):
   _map = ('BCDFGHJKMPQRTVWXY2346789').ToCharArray()
   _key = Array.CreateInstance(Char, 29)
   _raw = ArrayList()
   
   for i in range(52, 67):
      _raw.Add(digitalProductId[i])
      
   i = 28
   while i >= 0:
      if (i + 1) % 6 == 0: _key[i] = '-'
      else:
         k = 0
         j = 14
         while j >= 0:
            k = (k * 256) ^ _raw[j]
            _raw[j] = k / 24
            k %= 24
            _key[i] = _map[k]
            j -= 1
      i -= 1
      
   return _key



if __name__ == '__main__':
   with Registry.LocalMachine.OpenSubKey(r'SOFTWARE\Microsoft\Windows NT\CurrentVersion') as rk:
      Console.WriteLine(DecodeProductKey(rk.GetValue('DigitalProductId')))
