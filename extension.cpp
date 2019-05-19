// Extensions for Pay1oad PE Parser
// Copyright (c) Alex4386
//
// Source Code is distributed under HRPL.

#include <string>
#include <time.h>

int mergeCharsToIntLittleEndian(char a, char b, char c, char d) {
    return ((int) ((unsigned char)a) << 0) |
           ((int) ((unsigned char)b) << 8) |
           ((int) ((unsigned char)c) << 16)  |
           ((int) ((unsigned char)d) << 24);
}

unsigned int mergeCharArrayToIntLittleEndian(unsigned char* c) {
    int result = 0;
    for (int i = 0; i < 4; i++) {
        result |= (unsigned char)c[i] << (i * 8);
    }
    return result;
}

unsigned short mergeCharArrayToShortLittleEndian(unsigned char* c) {
    int result = 0;
    for (int i = 0; i < 2; i++) {
        result |= (unsigned char)c[i] << (i * 8);
    }
    return result;
}

std::string getMachineTypeByMachineCode(unsigned short machineCode) {
    switch(machineCode) {
        case 0:
            return "UNKNOWN";
        case 0x014d:
            return "i860";
        case 0x014c:
            return "i386";
        case 0x0162:
            return "R3000";
        case 0x0166:
            return "R4000";
        case 0x0168:
            return "R10000";
        case 0x0169:
            return "WCEMIPSV2";
        case 0x0184:
            return "alpha";
        case 0x01a2:
            return "sh3";
        case 0x01a3:
            return "sh3dsp";
        case 0x01a4:
            return "sh3e";
        case 0x01a6:
            return "sh4";
        case 0x01a8:
            return "sh5";
        case 0x01c0:
            return "arm";
        case 0x01c2:
            return "thumb";
        case 0x01c4:
            return "armNT";
        case 0xaa64:
            return "arm64";
        case 0x01d3:
            return "am33";
        case 0x01f0:
            return "powerPC";
        case 0x01f1:
            return "powerPCFP";
        case 0x0200:
            return "IA-64";
        case 0x0266:
            return "MIPS16";
        case 0x0284:
            return "alpha64";
        case 0x0366:
            return "mipsfpu";
        case 0x0466:
            return "mipsfpu16";
        case 0x0520:
            return "tricore";
        case 0x0cef:
            return "CEF";
        case 0x0ebc:
            return "EBC";
        case 0x8664:
            return "amd64";
        case 0x9041:
            return "m32r";
        case 0xc0ee:
            return "CEE";
        default:
            return "not-found";
    }
}

std::string getCharacteristic(int i) {
    switch(i) {
        case 0:
            return "Relocation info Stripped";
        case 1:
            return "Executable (All Ext. Ref. Resolved)";
        case 2:
            return "COFF Line Number Stripped";
        case 3:
            return "COFF Local Symbols Table Stripped";
        case 4: 
            return "Aggresively trimmed Working Set (obsolete)";
        case 5:
            return "Large Addresses (2GB) Handleable";
        case 6:
            return "16-bit Machine";
        case 7:
            return "Reversed Bytes to LOW (obsolete)";
        case 8:
            return "32-bit Machine";
        case 9:
            return "Debug Data Stripped";
        case 10:
            return "SwapRun when launched on Removable Media";
        case 11:
            return "SwapRun when launched via Network";
        case 12:
            return "System File";
        case 13:
            return "DLL File";
        case 14:
            return "UniProcessor System Only";
        case 15:
            return "Reversed Bytes to HIGH (obsolete)";
        default:
            return "error";
    }
}

std::string timeStampToHumanReadble(const time_t rawtime) {
    struct tm * dt;
    char buffer [30];
    dt = localtime(&rawtime);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", dt);
    return std::string(buffer);
}

std::string getSubSystemString(int subsystem) {
    switch (subsystem) {
    case 1:
        return "native";
    case 2:
        return "Windows GUI";
    case 3:
        return "Windows CommandLine";
    case 5:
        return "OS/2 CommandLine";
    case 7:
        return "POSIX CommandLine";
    case 9:
        return "Windows CE GUI";
    case 10:
        return "EFI Application";
    case 11:
        return "EFI Boot Service Driver";
    case 12:
        return "EFI Runtime Driver";
    case 13:
        return "EFI ROM Image";
    case 14:
        return "XBOX";
    case 16:
        return "Windows Boot Application";
    case 0:
    default:
        return "unknown";
        break;
    }
}

std::string getDLLCharacteristic(int i) {
    switch (i) {
        case 6:
            return "Relocatable in loadtime";
        case 7:
            return "Force integrity check";
        case 8:
            return "Data Execution Prevention Support";
        case 9:
            return "DLL should not be Isolated";
        case 10:
            return "Doesn't use Structured Exception Handling";
        case 11:
            return "DLL should not be binded";
        case 13:
            return "Is WDM Driver";
        case 15:
            return "DLL is Terminal Server Aware";
        default:
            return "Reserved";
    }
}

std::string getStandardCOFFHeaderName(unsigned char* c) {
    if (c[1] == '\x01') {
        if (c[0] == '\x0b') {
            return "IMAGE_OPTIONAL_HEADER32";
        } else if (c[0] == '\x07') {
            return "IMAGE_ROM_OPTIONAL_HEADER";
        }
    } else if (c[1] == '\x02' && c[0] == '\x0b') {
        return "IMAGE_OPTIONAL_HEADER64";
    }
    return "UNKNOWN";
}