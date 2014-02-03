using namespace System;
using namespace Microsoft::Win32;
using namespace System::Reflection;
using namespace System::Collections;

[assembly: AssemblyVersion("2.0.0.0")];

static String^ DecodeProductKey(array<Byte>^digitalProductId) {
  array<Char>^_map = (gcnew String("BCDFGHJKMPQRTVWXY2346789")) -> ToCharArray();
  array<Char>^_key = gcnew array<Char>(29);
  ArrayList^  _raw = gcnew ArrayList();
  
  for (Int32 i = 52; i < 67; i++)
    _raw -> Add(digitalProductId[i]);
    
  for (Int32 i = 28; i >= 0; i--) {
    if ((i + 1) % 6 == 0) _key[i] = '-';
    else {
      Int32 k = 0;
      for (Int32 j = 14; j >= 0; j--) {
        k = (k * 256) ^ (Byte)_raw[j];
        _raw[j] = (Byte)(k / 24);
        k %= 24;
        _key[i] = _map[k];
      }
    }
  }
  
  return gcnew String(_key);
}

void main() {
  RegistryKey^ rk =
    Registry::LocalMachine -> OpenSubKey("SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion");
  array<Byte>^ data = array<Byte>(rk -> GetValue("DigitalProductId"));
  Console::WriteLine(DecodeProductKey(data));
  rk -> Close();
}
