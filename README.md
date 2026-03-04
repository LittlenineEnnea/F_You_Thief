# qualcomm_gbl_exploit_poc
Unlocking qualcomm bootloader via gbl exploit.

Qualcomm adds a gbl boot stage in its ABL because it wants to limit OEM's ability.
gbl is loaded as an uefi app.
it stores in efisp partition
you need to flash the efi file into the partition.
Qualcomm uses its own verification instead of UEFI secure boot.
But GBL is unsigned.
So we can load unsigned uefi app
This way,we can achieve arbitary code execution.
So we can overwrite the lock state storing in RPMB.
Because the ABL it self reads/writes devinfo via a special function.
Before milestone,we can call the function to overwrite the lock state.
