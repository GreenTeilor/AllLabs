#include <stdio.h>
#include <sys/io.h>

#include <errno.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include <values.h>
#include "pci.h"

//-------------------------END INCLUDES------------------------


#define MAX_BUS 256
#define MAX_DEVICE 32
#define MAX_FUNCTIONS 8

#define ID_REGISTER 0

#define DEVICEID_SHIFT 16
#define BUS_SHIFT 16
#define DEVICE_SHIFT 11
#define FUNCTION_SHIFT 8
#define REGISTER_SHIFT 2

#define CONTROL_PORT 0x0CF8
#define DATA_PORT 0x0CFC

//-------------------------END DEFINES------------------------




void PrintInfo(int bus, int device, int function);
bool IfBridge(int bus,int device, int function);
long readRegister(int bus, int device, int function, int reg);
void outputGeneralData(int bus, int device, int function, int regData);
char *getDeviceName(int vendorID, int deviceID);
char *getVendorName(int vendorID);
void outputIOMemorySpaceBARData(long regData);
void outputMemorySpaceBARData(long regData);
void outputBARsData(int bus, int device, int function);
void outputIOLimitBaseData(long regData);
void outputInterruptData(long regData);
void outputClassCode(long regData);


FILE *out;

//================================1TASK===================================================

void outputClassCode(long regData){
    fputs("           TASK 1\n", out);
    puts("           TASK 1");

    int ClassCode = (regData>>8) & 0xFF;
    char *ClassCodeData;

    switch (ClassCode)
    {
    case 0:
        ClassCodeData="device";
        break;
    case 1:
        ClassCodeData="controlers";
        break;
    case 2:
        ClassCodeData="network controlers";
        break;
    case 3:
        ClassCodeData="display controllers";
        break;
    case 4:
        ClassCodeData="multimedia device";
        break;
    case 5:
        ClassCodeData="memory controller";
        break;
    case 6:
        ClassCodeData="bridge";
        break;
    case 7:
        ClassCodeData="communication controllers";
        break;
    case 8:
        ClassCodeData="system pereferi";
        break;
    case 9:
        ClassCodeData="device input controller";
        break;
    case 10:
        ClassCodeData="doc station";
        break;
    case 11:
        ClassCodeData="processor";
        break;
    case 12:
        ClassCodeData="bus controller";
        break;

    
    default:
        ClassCodeData="not found";
        break;
    }
    fprintf(out, "Class Code: %s\n", ClassCodeData);
    printf( "Class Code: %s\n", ClassCodeData);

}






//================================6 TASK===================================================

void outputInterruptData(long regData){
    fputs("           TASK 6\n", out);
    puts("           TASK 6");


    int interruptPin = (regData >> 8) & 0xFF;
    char *interruptPinData;

    switch (interruptPin) {
        case 0:
            interruptPinData = "not used";
            break;
        case 1:
            interruptPinData = "INTA#";
            break;
        case 2:
            interruptPinData = "INTB#";
            break;
        case 3:
            interruptPinData = "INTC#";
            break;
        case 4:
            interruptPinData = "INTD#";
            break;
        default:
            interruptPinData = "invalid pin number";
            break;
    }

    fprintf(out, "Interrupt pin: %s\n", interruptPinData);
    printf( "Interrupt pin: %s\n", interruptPinData);
}



//================================8 TASK===================================================


// Номер считываемого регистра - 6(начиная с 0), первый байт - Primary BN, 2 byte - Secondary BN, 3 byte - Subordinate BN
void outputBusData(long  regData) {
  fputs("           TASK 8\n", out);
     puts("           TASK 8");

  printf("\n Soderjimoe registra: %ld \n", regData);
  
  int PrimaryBN = regData & 0xFF;
  int SecondaryBn = (regData >> 8) & 0xFF;
  int SubBN = (regData >> 16) & 0xFF;
  printf("\nНомер первичной шины: %d ", PrimaryBN);
  printf("\nНомер вторичной шины (номер моста): %d ", SecondaryBn);
  printf("\nМаксимальный номер подчиненной шины: %d \n", SubBN);
  fprintf(out,"\nНомер первичной шины: %d ", PrimaryBN);
  fprintf(out,"\nНомер вторичной шины (номер моста): %d ", SecondaryBn);
  fprintf(out,"\nМаксимальный номер подчиненной шины: %d \n", SubBN);
}


//=======================GENERAL=======================================================================

char *getVendorName(int vendorID) {
int i;
    for (i = 0; i < PCI_VENTABLE_LEN; i++) {
        if (PciVenTable[i].VendorId == vendorID) {
            return PciVenTable[i].VendorName;
        }
    }
    return NULL;
}

char *getDeviceName(int vendorID, int deviceID) {
int i;
    for ( i = 0; i < PCI_DEVTABLE_LEN; i++) {
        if (PciDevTable[i].VendorId == vendorID && PciDevTable[i].DeviceId == deviceID) {
            return PciDevTable[i].DeviceName;
        }
    }
    return NULL;
}

void outputVendorData(int vendorID)
{
    char *vendorName = getVendorName(vendorID);
    fprintf(out, "Vendor ID: %04d, %s\n", vendorID, vendorName ? vendorName : "unknown vendor");
   printf( "Vendor ID: %04d, %s\n", vendorID, vendorName ? vendorName : "Unknown vendor");
}

void outputDeviceData(int vendorID, int deviceID)
{
    char *deviceName = getDeviceName(vendorID, deviceID);
    fprintf(out, "Device ID: %04d, %s\n", deviceID, deviceName ? deviceName : "unknown device");
	printf( "Device ID: %04d, %s\n", deviceID, deviceName ? deviceName : "Unknown device");
}

void outputGeneralData(int bus, int device, int function, int regData){
    fprintf(out, "%x:%x:%x\n", bus, device, function);
    printf( "%x:%x:%x\n", bus, device, function);
    int deviceID = regData >> DEVICEID_SHIFT;
    int vendorID = regData & 0xFFFF;
    outputVendorData(vendorID);
    outputDeviceData(vendorID, deviceID);
}

long readRegister(int bus, int device, int function, int reg) {
   long  configRegAddress = (1 << 31) | (bus << BUS_SHIFT) | (device << DEVICE_SHIFT) |(function << FUNCTION_SHIFT) | (reg << REGISTER_SHIFT);
    outl(configRegAddress, CONTROL_PORT);
    return inl(DATA_PORT);

	return 0;
}

bool IfBridge(int bus,int device, int function){
 long htypeRegData = readRegister(bus, device, function, 3);
    return ((htypeRegData >> 16) & 0xFF) & 1;
}


void PrintInfo(int bus, int device, int function) {
   long idRegData = readRegister(bus, device, function, ID_REGISTER);

   if (idRegData != 0xFFFFFFFF) { // if there is a device 
        outputGeneralData(bus, device, function, idRegData);

        if (IfBridge(bus, device, function)) {
            fprintf(out, "\nIs bridge\n\n");
		    printf("\nIs bridge\n\n");
            outputBusData(readRegister(bus, device, function, 6)); 
            
        } else {
            fprintf(out, "\nNot a bridge\n\n");
            printf("\nNot a bridge\n\n");
            outputInterruptData(readRegister(bus, device, function, 15));
            outputClassCode(readRegister(bus,device,function,2));
        }
        fputs("---------------------------------------------------\n", out);
	    puts("---------------------------------------------------\n");
    }
}


int main() { 
	
    if (iopl(3)) {   
       printf("I/O Privilege level change error: %s\nTry running under ROOT user\n", strerror(errno));
       return 2;
    }
	
   int bus; 
   int device;
   int func;

    out = fopen("output.txt", "w");

    for ( bus = 0; bus < MAX_BUS; bus++){
        for (device = 0; device < MAX_DEVICE; device++){
            for ( func = 0; func < MAX_FUNCTIONS; func++){
                PrintInfo(bus,device,func);
			}
		}
	}

    fclose(out);
    return 0;
}