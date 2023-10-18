
#include <winsock2.h> 
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <ws2bth.h>
#include <bluetoothapis.h>

int main(int argc, char **argv)

{
   int i;
   HANDLE hRadio, hDeviceFind;
   BLUETOOTH_DEVICE_INFO deviceInfo;
   BLUETOOTH_DEVICE_SEARCH_PARAMS deviceSearchParams;
   BLUETOOTH_RADIO_INFO radioInfo;
   GUID guidServices[10];
   DWORD numServices, result;
   i = 1;
   BLUETOOTH_FIND_RADIO_PARAMS btfrp = { sizeof(BLUETOOTH_FIND_RADIO_PARAMS) };
   HBLUETOOTH_RADIO_FIND hFind = BluetoothFindFirstRadio(&btfrp, &hRadio);
   if (hFind != NULL)
   {
      printf("BluetoothFindFirstRadio() ok\n");
   }
   else printf("BluetoothFindFirstRadio() bad\n");

   
   return 0; //
}

