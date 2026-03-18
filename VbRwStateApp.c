

IDIOT FILE FOR WRITING TWO REGISTERS IN NO SENSE + LLM GENERATED + CANT BREAK ITSELF UNTIL CRASH




#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Library/BaseMemoryLib.h>
#include <Protocol/EFIVerifiedBoot.h>

#define VB_RW_BUF_SIZE  3344

/**
  Entry point: Locate QCOM_VERIFIEDBOOT_PROTOCOL and call VBRwDeviceState
  with op=WRITE_CONFIG (1), 16-byte buffer with buf[0]=1, buf[8]=1.

  @param[in] ImageHandle    Image handle for this application.
  @param[in] SystemTable    Pointer to the EFI System Table.

  @retval EFI_SUCCESS      Call succeeded.
  @retval other            LocateProtocol or VBRwDeviceState failed.
**/
EFI_STATUS
EFIAPI
UefiMain (
  IN EFI_HANDLE        ImageHandle,
  IN EFI_SYSTEM_TABLE  *SystemTable
  )
{
  EFI_STATUS                    Status;
  QCOM_VERIFIEDBOOT_PROTOCOL   *VbProtocol;
  // UINT8                         Buf[VB_RW_BUF_SIZE];
  UINT32                        BufLen = VB_RW_BUF_SIZE;
    // EFI_GUID gEfiQcomVerifiedBootProtocolGuid1 =       { 0x8e5eff91, 0x21b6, 0x47d3, { 0xaf, 0x2b, 0xc1, 0x5a, 0x1, 0xe0, 0x20, 0xec } };
  UINT8 Buf[3344];

  // Locate QCOM Verified Boot Protocol
  Status = gBS->LocateProtocol (
                  &gEfiQcomVerifiedBootProtocolGuid,
                  NULL,
                  (VOID **)&VbProtocol
                  );
  if (EFI_ERROR (Status)) {
    Print (L"VbRwStateApp: LocateProtocol(VerifiedBoot) failed: %r\n", Status);
    return Status;
  }
  Status = VbProtocol->VBRwDeviceState (
                         VbProtocol,
                         READ_CONFIG,
                         Buf,
                         BufLen
                         );
  if (EFI_ERROR (Status)) {
    Print (L"VbRwStateApp: VBRwDeviceState(READ_CONFIG) failed: %r\n", Status);
    return Status;
  }
  // Prepare 16-byte buffer: byte 0 = 1, byte 8 = 1, rest zero
  // SetMem (Buf, sizeof (Buf), 0);
  Buf[13] = 0;
  Buf[14] = 0;
  // Buf[15]=1;
  // Call VBRwDeviceState: op = WRITE_CONFIG (1)
  Status = VbProtocol->VBRwDeviceState (
                         VbProtocol,
                         WRITE_CONFIG,
                         Buf,
                         BufLen
                         );
  if (EFI_ERROR (Status)) {
    Print (L"VbRwStateApp: VBRwDeviceState(WRITE_CONFIG) failed: %r\n", Status);
    return Status;
  }

  Print (L"VbRwStateApp: VBRwDeviceState(WRITE_CONFIG) success.\n");
//   while(1);
  return EFI_SUCCESS;
}
