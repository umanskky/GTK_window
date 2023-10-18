
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
   // Define the five bytes to send ("hello")
   char bytes_to_send[15];
   bytes_to_send[0] = '\n';
   bytes_to_send[1] = 'a';
   bytes_to_send[2] = 'd';
   bytes_to_send[3] = 'm';
   bytes_to_send[4] = 'i';
   bytes_to_send[5] = 'n';
   bytes_to_send[6] = '\n';
   bytes_to_send[7] = 's';
   bytes_to_send[8] = 'h';
   bytes_to_send[9] = 'o';
   bytes_to_send[10] = 'w';
   bytes_to_send[11] = ' ';
   bytes_to_send[12] = 'i';
   bytes_to_send[13] = 'p';
   bytes_to_send[14] = '\n';

// Declare variables and structures
   HANDLE hSerial;
   DCB dcbSerialParams = {0};
   COMMTIMEOUTS timeouts = {0};

   // Open the highest available serial port number
   fprintf(stderr, "Opening serial port...");
   hSerial = CreateFile(
               "\\\\.\\COM2", GENERIC_READ|GENERIC_WRITE, 0, NULL,
               OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL );
   if (hSerial == INVALID_HANDLE_VALUE)
   {
         fprintf(stderr, "Error\n");
         return 1;
   }
   else fprintf(stderr, "OK\n");

   // Set device parameters (38400 baud, 1 start bit,
   // 1 stop bit, no parity)
   dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
   if (GetCommState(hSerial, &dcbSerialParams) == 0)
   {
      fprintf(stderr, "Error getting device state\n");
      CloseHandle(hSerial);
      return 1;
   }

   dcbSerialParams.BaudRate = CBR_115200;
   dcbSerialParams.ByteSize = 8;
   dcbSerialParams.StopBits = ONESTOPBIT;
   dcbSerialParams.Parity = NOPARITY;
   if(SetCommState(hSerial, &dcbSerialParams) == 0)
   {
      fprintf(stderr, "Error setting device parameters\n");
      CloseHandle(hSerial);
      return 1;
   }

   // Set COM port timeout settings
   timeouts.ReadIntervalTimeout = 50;
   timeouts.ReadTotalTimeoutConstant = 50;
   timeouts.ReadTotalTimeoutMultiplier = 10;
   timeouts.WriteTotalTimeoutConstant = 50;
   timeouts.WriteTotalTimeoutMultiplier = 10;
   if(SetCommTimeouts(hSerial, &timeouts) == 0)
   {
      fprintf(stderr, "Error setting timeouts\n");
      CloseHandle(hSerial);
      return 1;
   }

   // Send specified text (remaining command line arguments)
   DWORD bytes_written, total_bytes_written = 0;
   fprintf(stderr, "Sending bytes...");
   if(!WriteFile(hSerial, bytes_to_send, sizeof(bytes_to_send), &bytes_written, NULL))
   {
      fprintf(stderr, "Error\n");
      CloseHandle(hSerial);
      return 1;
   }

   fprintf(stderr, "%d bytes written\n", bytes_written);

   // Close serial port
   fprintf(stderr, "Closing serial port...");
   if (CloseHandle(hSerial) == 0)
   {
      fprintf(stderr, "Error\n");
      return 1;
   }
   fprintf(stderr, "OK\n");
   fprintf(stderr, "the sent sentence is: ");
   for(int i=0;i<sizeof(bytes_to_send);i++){
      fprintf(stderr,"%c",bytes_to_send[i]);
   }

   // exit normally
   return 0;
}
