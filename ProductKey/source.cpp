#include <windows.h>
#include <iostream>

using namespace std;

#pragma comment (lib, "advapi32.lib")

void main() {
  HKEY  Registry;
  BYTE *DigitalProductId = 0;
  DWORD RawLength;
  BYTE  raw[15];
  char  key[30];
  
  const char *key_map[] = {
    "B","C","D","F","G","H","J","K","M","P","Q","R",
    "T","V","W","X","Y","2","3","4","6","7","8","9",
  };
  
  if (RegOpenKeyEx(HKEY_LOCAL_MACHINE,
                   "SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion",
                   0,
                   KEY_QUERY_VALUE,
                   &Registry) == ERROR_SUCCESS) {
    RawLength = 164;
    DigitalProductId = new byte[RawLength]; //allocate memory
    memset(DigitalProductId, 0, RawLength); //memory initialization
    
    if (RegQueryValueEx(Registry,
                        "DigitalProductId",
                        NULL,
                        NULL,
                        DigitalProductId,
                        &RawLength) == ERROR_SUCCESS) {
      memcpy(raw, DigitalProductId + 52, 15); //raw key
      if (DigitalProductId) delete []DigitalProductId; //release memory
      RegCloseKey(Registry);
    }
  }
  
  memset(key, 0, sizeof(key));
  for (int i = 24; i >= 0; i--) {
    int k = 0;
    for (int j = 14; j >= 0; j--) {
      k = (k * 256) ^ raw[j];
      raw[j] = k / 24;
      k %= 24;
    }
    
    strcat_s(key, key_map[k]);
    if (!(i % 5) && i) strcat_s(key, "-");
  }
  
  cout << _strrev(key) << endl;
}
