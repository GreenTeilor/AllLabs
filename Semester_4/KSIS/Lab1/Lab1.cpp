#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <iptypes.h>
#include <iphlpapi.h>
//To use uChar
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <winnetwk.h>

// Dependencies
#pragma comment(lib, "mpr.lib")
#pragma comment(lib, "netapi32.lib")
void printStruct(int i, LPNETRESOURCE localPointer);
// Adapter info strcuture
typedef struct _ASTAT_
{
    ADAPTER_STATUS adapter;
    NAME_BUFFER buffer[30];
}Adapter;
Adapter adapter;

bool flag = false;

//Call Netbios after filling special structure, 0 if succesfull
void GetMacAddress()
{
    //Structure with network adapters numbers
    LANA_ENUM lanNums;
    //Return value of Netbios
    UCHAR resultCode;
    //Structure to work with Netbios interface. Contains data about instruction, buffer, etc
    NCB ncb;

    //Allocate memory for managing structure for working with Netbios
    memset(&ncb, 0, sizeof(ncb));
    //Enumerates numbers of network adapters (LANA).
    //With this code, ncb_buffer points to the buffer, which have to contain LANA_ENUM structure
    //NCBENUM is not default NetBIOS 3.0. instruction
    ncb.ncb_command = NCBENUM;
    // Data about working with Netbios is stored in ncb_buffer
    ncb.ncb_buffer = (UCHAR*)&lanNums;
    ncb.ncb_length = sizeof(lanNums);
    // Getting numbers of network adapters
    resultCode = Netbios(&ncb);

    // Walkthrough all network adapters
    for (int i = 0; i < lanNums.length; i++) {
        //Preparation. Using NCBRSET clean up names and sessions for another LAN adapter(numerated i)
        memset(&ncb, 0, sizeof(ncb));
        ncb.ncb_command = NCBRESET;
        ncb.ncb_lana_num = lanNums.lana[i];
        //Cleaning
        resultCode = Netbios(&ncb);

        //Preparation for getting address using instruction NCBSTAT with parameter *
        memset(&ncb, 0, sizeof(ncb));
        ncb.ncb_command = NCBASTAT;
        ncb.ncb_lana_num = lanNums.lana[i];
        strcpy((char*)ncb.ncb_callname, "*               ");
        //Function result direct to the variable of structure type Adapter
        ncb.ncb_buffer = (unsigned char*)&adapter;
        ncb.ncb_length = sizeof(adapter);
        //Getting MAC-address recult code
        resultCode = Netbios(&ncb);

        //If getting MAC-address was successful
        if (resultCode == 0) {
            printf("Полученный MAC на LANA %d: % 02x % 02x % 02x % 02x % 02x % 02x\n",
                lanNums.lana[i],
                adapter.adapter.adapter_address[0],
                adapter.adapter.adapter_address[1],
                adapter.adapter.adapter_address[2],
                adapter.adapter.adapter_address[3],
                adapter.adapter.adapter_address[4],
                adapter.adapter.adapter_address[5]);
        }

    }
}



BOOL WINAPI EnumerateFunc(LPNETRESOURCE nullPointer)
{
    //Resource descriptor
    HANDLE handleEnum;
    DWORD resVar1, resVar2;
    //Value -1 to enumerate all resources
    DWORD countRecources = -1;
    //Buffer length 
    DWORD lenBuffer = 16384;
    // Structure for buffer(size - 16384) to store stuctures array plNETRESOURCE, returned by function WNetEnumResource
    LPNETRESOURCE structPointer;
    DWORD i;
    //Call function WNetOpenEnum to start enumeration. Returns NO_ERROR, if successful
    //Resource_GLOBALNET - enumerate all network resources
    //RESOURCETYPE_ANY - all resources types
    //0 - if equales to 0, enumerating starts from top
    //nullPointer = NULL
    //handleEnum - descriptor address to know, where to read network resources
    resVar1 = WNetOpenEnum(RESOURCE_GLOBALNET, RESOURCETYPE_ANY, 0, nullPointer, &handleEnum);
    if (resVar1 != NO_ERROR)
    {
        //Handling errors.
        printf("WnetOpenEnum завершилась с ошибкой %d\n", resVar1);
        return FALSE;
    }
    structPointer = (LPNETRESOURCE)GlobalAlloc(GPTR, lenBuffer);
    if (structPointer == NULL) {
        printf("WnetOpenEnum fзавершилась с ошибкой %d\n", resVar1);
        return FALSE;
    }
    //To allocate buffer
    //structPointer = (LPNETRESOURCE)GlobalAlloc(GPTR,lenBuffer); 
    do
    {
        // Ininitialize buffer with 0(initial address, size)
        ZeroMemory(structPointer, lenBuffer);
        //Enumerate network resources with help of WNetEnumResoutce
        //handleEnum - desciptor(pointer) to resources. In this case directly to the resources root
        //countRecources - amount of enumerated resources, initialized with -1
        //structPointer - buffer for resources(consists of structures)
        //lenBuffer - buffer size
        resVar2 = WNetEnumResource(handleEnum, &countRecources, structPointer, &lenBuffer);
        //If call was succefull, structures are processed using cycles
        if (resVar2 == NO_ERROR)
        {
            for (i = 0; i < countRecources; i++)
            {
                //Call print, pass resourse number and structure address with information
                printStruct(i, &structPointer[i]);
                //If structure NETRESOURCE is container, we may recursively call container's components
                if (RESOURCEUSAGE_CONTAINER == (structPointer[i].dwUsage
                    & RESOURCEUSAGE_CONTAINER))
                    if (!EnumerateFunc(&structPointer[i]))
                        printf("EnumerateFunc вернула FALSE\n");
            }
        }
        //Handling errors
        else if (resVar2 != ERROR_NO_MORE_ITEMS)
        {
            printf("WNetEnumResource завершилась с ошибкой %d\n", resVar2);
            break;
        }
    } while (resVar2 != ERROR_NO_MORE_ITEMS);
    //Call GlobalFree to free resources. Free passed object of global memory and makes his desciptor invalid
    GlobalFree((HGLOBAL)structPointer);
    //Call WNetCloseEnum to stop enumeration. Close pointer to enumerator
    resVar1 = WNetCloseEnum(handleEnum);
    if (resVar1 != NO_ERROR)
    {
        //Handling errors
        printf("WNetCloseEnum завершилась с ошибкой %d\n", resVar1);
        return FALSE;
    }
    return TRUE;
}

void printStruct(int i, LPNETRESOURCE localPointer)
{
    //Define scope of enumeration 
    printf("NETRESOURCE[%d] Scope: ", i);
    switch (localPointer->dwScope) {
    case (RESOURCE_CONNECTED):
        printf("connected\n");
        break;
    case (RESOURCE_GLOBALNET):
        printf("all resources\n");
        break;
    case (RESOURCE_REMEMBERED):
        printf("remembered\n");
        break;
    default:
        printf("unknown scope %d\n", localPointer->dwScope);
        break;
    }

    printf("NETRESOURCE[%d] Type: ", i);
    switch (localPointer->dwType) {
    case (RESOURCETYPE_ANY):
        printf("any\n");
        break;
    case (RESOURCETYPE_DISK):
        printf("disk\n");
        break;
    case (RESOURCETYPE_PRINT):
        printf("print\n");
        break;
    default:
        printf("unknown type %d\n", localPointer->dwType);
        break;
    }

    printf("NETRESOURCE[%d] DisplayType: ", i);
    switch (localPointer->dwDisplayType) {
    case (RESOURCEDISPLAYTYPE_GENERIC):
        printf("generic\n");
        break;
    case (RESOURCEDISPLAYTYPE_DOMAIN):
        printf("domain\n");
        break;
    case (RESOURCEDISPLAYTYPE_SERVER):
        printf("server\n");
        break;
    case (RESOURCEDISPLAYTYPE_SHARE):
        printf("share\n");
        break;
    case (RESOURCEDISPLAYTYPE_FILE):
        printf("file\n");
        break;
    case (RESOURCEDISPLAYTYPE_GROUP):
        printf("group\n");
        break;
    case (RESOURCEDISPLAYTYPE_NETWORK):
        printf("network\n");
        break;
    default:
        printf("unknown display type %d\n", localPointer->dwDisplayType);
        break;
    }

    printf("NETRESOURCE[%d] Usage: 0x%x = ", i, localPointer->dwUsage);
    if (localPointer->dwUsage & RESOURCEUSAGE_CONNECTABLE)
        printf("connectable ");
    if (localPointer->dwUsage & RESOURCEUSAGE_CONTAINER)
        printf("container ");
    printf("\n");

    printf("NETRESOURCE[%d] Localname: %S\n", i, localPointer->lpLocalName);
    printf("NETRESOURCE[%d] Remotename: %S\n", i, localPointer->lpRemoteName);
    printf("NETRESOURCE[%d] Comment: %S\n", i, localPointer->lpComment);
    printf("NETRESOURCE[%d] Provider: %S\n", i, localPointer->lpProvider);
    printf("\n");
}

void main()
{
    setlocale(LC_ALL, "Russian");
    printf("Полученные мак адреса: \n");
    GetMacAddress();

    printf("\nПеречисление сетевых ресурсов: \n");
    //Pointer to structure lpNETRESOURCE is NULL, because when WNetOpenEnum receive NULL pointer, he returns desciptor into the network root,
    //but we have to output all we find
    LPNETRESOURCE lpnr = NULL;
    if (EnumerateFunc(lpnr) == FALSE)
        printf("Ошибка\n");

    //system("pause");
}
