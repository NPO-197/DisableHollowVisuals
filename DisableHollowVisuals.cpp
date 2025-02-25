//Disable Hollow Visuals mod for DS2 SotFS
//Written by NPO197

/* MIT-0 
Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the “Software”), to deal in the Software without restriction, 
including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

// Feel free to steal this code for any and all use! :D

namespace DisableHollowVisuals
{

void mainCall();

}


//First off basic entry point from dll injection
#include <minwindef.h>

BOOL APIENTRY DllMain(HMODULE hModule,DWORD reason_for_call,LPVOID lpReserved)
{
    //only need to run our code once during attach
    if (reason_for_call==DLL_PROCESS_ATTACH)
    {
        // MainCall to mod:
        DisableHollowVisuals::mainCall();
    }
    return TRUE;
}


#include <windows.h>
#include <stdio.h>

namespace DisableHollowVisuals
{

void ErrorWindow();

void mainCall()
{
    // Just to make code easier to read...
    using opcode = u_int64;
    using pointer = u_int64;

    const u_int CheckHollowOffset = 0x00203A39; //offset of the opcode we want to patch
    const opcode DefaultOpcode = 0x40000001ACB0B60F; // movzx esi,byte ptr [rax+000001AC]
		const opcode NewOpcode =     0x40909000000000BE; // mov esi,#0x00000000;nop;nop

    pointer ExeBaseAddress = (pointer)GetModuleHandleW(0);
    pointer pCheckHollow= ExeBaseAddress+CheckHollowOffset;
    if(*(opcode*)pCheckHollow != DefaultOpcode)
    {
        // This message will apear if the opcode read from the address is not the expected value
        // Check to make sure you have the right version of Dark Souls 2 SotFS...
        MessageBoxA(NULL, "Opcode not found... Cannot Patch Hollow Visuals, check DS2 SotFS version","DisableHollowVisuals", MB_OK);
        return;
    }

    //Apply Patch to game
    int succsess = WriteProcessMemory(GetCurrentProcess(),(void *)(pCheckHollow),&NewOpcode,8,0);
    if(succsess==0){
        ErrorWindow();
    }
    

}

void ErrorWindow()
{
    DWORD errorcode = GetLastError();
    char buffer[100];
    sprintf(buffer, "ERROR: %i",errorcode);
    MessageBoxA(NULL, buffer, "DisableHollowVisuals ERROR WINDOW",MB_OK);
}


}
