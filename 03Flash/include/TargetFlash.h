#ifndef TARGET_FLASH_H
#define TARGET_FLASH_H

typedef enum {
	CommandRegister,
	StatusRegister
} Flash_Registers;

typedef enum {
	ProgramCommand = 0x40,
	Reset = 0xff
} Flash_Command;

typedef enum {
	ReadyBit = 1<<7,
	VppErrorBit = 1<<3,
	EraseErrorBit = 1<<4,
	BlockProtectionErrorBit = 1<<5,
	ProgramErrorBit = 1<<6
} StatusRegisterBits;

#endif
