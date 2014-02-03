require 'System'

Registry = Microsoft::Win32::Registry

def DecodeProductKey(digitalProductId)
  _map = ("BCDFGHJKMPQRTVWXY2346789").split('')
  _key = []
  _raw = []
  
  for i in 52..67 do
    _raw.Add(digitalProductId[i])
  end
  
  i = 28
  while i >= 0
    if (i + 1) % 6 == 0
      _key[i] = '-'
    else
      k = 0
      j = 14
      while j >= 0
        k = (k * 256) ^ _raw[j]
        _raw[j] = k / 24
        k %= 24
        _key[i] = _map[k]
        j -= 1
      end
    end
    i -= 1
  end
  
  return _key.to_s
end

rk = Registry.LocalMachine.OpenSubKey('SOFTWARE\Microsoft\Windows NT\CurrentVersion')
puts DecodeProductKey(rk.GetValue('DigitalProductId'))
rk.Close()
