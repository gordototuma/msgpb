/*
* April 2021
*
* Program that displays the battery power status,  in order to 
* protect the batteries of our laptops (optimize the battery life span).

*
* Libraries used:
* 
* [winbase.h] 
* I use the structure "_SYSTEM_POWER_STATUS" which has the member 
* "BatteryLifePercent", it shows the battery status (percentage) 
* or the code 255 if it is not possible to display.
* Also use the ACLineStatus member to know if the machine is 
* connected to AC power.
*
* [windows.h]
* I use this to displays a message box. (function MessageBox()).
*
* Written by Luis González <email:lagonzalezsm3@gmail.com> <twitter:@gordototuma>
*/

#include<windows.h>
#include<stdio.h>
//typedef from _SYSTEM_POWER_STATUS
SYSTEM_POWER_STATUS status;

int main(){            
    //GetSystemPowerStatus retrieves the power status of the system
    if(GetSystemPowerStatus(&status) != 0){
        if(status.BatteryLifePercent == 255) 
            MessageBox(NULL,"Unknown status [255]: unable to read the battery flag information.","Battery Level",MB_OK|0x00000040L);        
        else if(status.BatteryLifePercent<=20 && status.ACLineStatus == 0)
            MessageBox(NULL,"Battery level less than or equal to 20%%, please conect The AC power.","Battery level", MB_OK|0x00000030L);
        else if(status.BatteryLifePercent>=90 && status.ACLineStatus == 1)
            MessageBox(NULL,"Battery level greater than or equal to 90%%,, please desconect The AC power.","Battery level", MB_OK|0x00000030L);
    }
    else{
        printf("Error: Can't get Information the System Power Status");
    }       
    return 0;
}