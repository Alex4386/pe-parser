#include <string>
#include <time.h>

std::string printMachineTypeByMachineCode(int machineCode) {
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
            return "Reloc stripped";
        case 1:
            return "Executable";
        case 2:
            return "Line Number Stripped";
        case 3:
            return "Local Symbols Stripped";
        case 4: 
            return "WhiteSpaces are aggresively trimmed";
        case 5:
            return "Large Addresses Awareness";
        case 6:
            return "16-bit Machine";
        case 7:
            return "Reversed Bytes to LOW";
        case 8:
            return "32-bit Machine";
        case 9:
            return "Is Debug Data Stripped";
        case 10:
            return "Removable from SwapRun";
        case 11:
            return "Net runnable from swaprun";
        case 12:
            return "System File";
        case 13:
            return "DLL File";
        case 14:
            return "System ONLY";
        case 15:
            return "Reversed Bytes to HIGH";
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
