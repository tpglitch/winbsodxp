#include <windows.h>
#include <stdio.h>

typedef NTSTATUS(WINAPI *RtlAdjustPrivilegeFunc)(
    ULONG Privilege,
    BOOLEAN Enable,
    BOOLEAN CurrentThread,
    PBOOLEAN Enabled);

typedef NTSTATUS(WINAPI *NtRaiseHardErrorFunc)(
    NTSTATUS ErrorStatus,
    ULONG NumberOfParameters,
    ULONG UnicodeStringParameterMask,
    PULONG_PTR Parameters,
    ULONG ValidResponseOption,
    PULONG Response);

int main()
{
  BOOLEAN bEnabled;
  ULONG uResp;

  HMODULE hNtdll = LoadLibraryA("ntdll.dll");
  if (!hNtdll)
  {
    printf("Failed to load ntdll.dll\n");
    return 1;
  }

  RtlAdjustPrivilegeFunc RtlAdjustPrivilege =
      (RtlAdjustPrivilegeFunc)GetProcAddress(hNtdll, "RtlAdjustPrivilege");
  NtRaiseHardErrorFunc NtRaiseHardError =
      (NtRaiseHardErrorFunc)GetProcAddress(hNtdll, "NtRaiseHardError");

  if (!RtlAdjustPrivilege || !NtRaiseHardError)
  {
    printf("Failed to resolve functions\n");
    return 1;
  }

  // Enable SeShutdownPrivilege
  RtlAdjustPrivilege(19, TRUE, FALSE, &bEnabled);

  // Cause a hard error (STATUS_ASSERTION_FAILURE = 0xC0000420)
  NtRaiseHardError(0xC0000420, 0, 0, NULL, 6, &uResp);

  return 0;
}
