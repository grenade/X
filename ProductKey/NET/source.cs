using System;
using Microsoft.Win32;
using System.Reflection;
using System.Collections;

[assembly: AssemblyVersion("2.0.0.0")]

namespace ProductKey {
  internal sealed class Program {
    internal static String DecodeProductKey(Byte[] digitalProductId) {
      Char[] map = ("BCDFGHJKMPQRTVWXY2346789").ToCharArray();
      Char[] key = new Char[29];
      ArrayList raw = new ArrayList();
      
      for (Int32 i = 52; i < 67; i++)
        raw.Add(digitalProductId[i]);
        
      for (Int32 i = 28; i >= 0; i--) {
        if ((i + 1) % 6 == 0) key[i] = '-';
        else {
          Int32 k = 0;
          for (Int32 j = 14; j >= 0; j--) {
            k = (k * 256) ^ (Byte)raw[j];
            raw[j] = (Byte)(k / 24);
            k %= 24;
            key[i] = map[k];
          }
        }
      }
      return new String(key);
    }
    
    internal static void Main() {
      using (RegistryKey rk =
        Registry.LocalMachine.OpenSubKey(@"SOFTWARE\Microsoft\Windows NT\CurrentVersion")) {
        Byte[] val = rk.GetValue("DigitalProductId") as Byte[];
        Console.WriteLine(DecodeProductKey(val));
      }
    }
  }
}
