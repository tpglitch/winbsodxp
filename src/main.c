#include <windows.h>
#include <stdio.h>

int main()
{
  BOOLEAN enabled;
  ULONG resp;
  HMODULE ntdll = LoadLibraryA("ntdll.dll");
  if (!ntdll)
  {
    printf("Failed to load ntdll.dll\n");
    return 1;
  }
  NTSTATUS(WINAPI * RtlAdjustPrivilege)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN) =
      (NTSTATUS(WINAPI *)(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN))GetProcAddress(ntdll, "RtlAdjustPrivilege");
  NTSTATUS(WINAPI * NtRaiseHardError)(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG) =
      (NTSTATUS(WINAPI *)(NTSTATUS, ULONG, ULONG, PULONG_PTR, ULONG, PULONG))GetProcAddress(ntdll, "NtRaiseHardError");
  if (!RtlAdjustPrivilege || !NtRaiseHardError)
  {
    printf("Failed to resolve functions\n");
    return 1;
  }
  RtlAdjustPrivilege(19, TRUE, FALSE, &enabled);
  NtRaiseHardError(0xC0000420, 0, 0, NULL, 6, &resp);
  return 0;
}
