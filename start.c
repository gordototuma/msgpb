/*
* April 2021
*
* Program that displays the battery power status,  in order to 
* protect the batteries of our laptops (optimize the battery life span).

*
* Libraries used:
* 
* [windows.h]
* I use the structure "_SYSTEM_POWER_STATUS" which has the member 
* "BatteryLifePercent", it shows the battery status (percentage) 
* or the code 255 if it is not possible to display.
* Also use the ACLineStatus member to know if the machine is 
* connected to AC power.
* I use this to displays a message box. (function MessageBox()).
*
* [unistd.h]
* To use access() function.
*
* Written by Luis González <email:lagonzalezsm3@gmail.com> <twitter:@gordototuma>
*/

#include<windows.h>
#include<unistd.h>

//Path where saves and execute our program
#define path "/ProgramData/Microsoft/Windows/Start Menu/Programs/StartUp/msgbp.exe"
//typedef from _SYSTEM_POWER_STATUS
SYSTEM_POWER_STATUS status;

int existFile();
void msgStatusBattery();

/*check if a file exists in path
*/
int existFile(){
    if(access(path, F_OK) == 0)        
        return 1;
    else 
        return 0;
}

/*Show information the system power status in MessageBox
*/
void msgStatusBattery(){
    if(status.BatteryLifePercent == 255) 
        MessageBox(NULL,"Unknown status [255]: unable to read the battery flag information.","Battery Level - msgbp",MB_OK|0x00000040L);        
    else if(status.BatteryLifePercent<=20 && status.ACLineStatus == 0)
        MessageBox(NULL,"Battery level less than or equal to 20%, please conect The AC power.","Battery level - msgbp", MB_OK|0x00000030L);
    else if(status.BatteryLifePercent>=90 && status.ACLineStatus == 1)
        MessageBox(NULL,"Battery level greater than or equal to 90%, please desconect The AC power.","Battery level - msgbp", MB_OK|0x00000030L);
}

int main(){    
    //Hide console
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    if(existFile()){                
        //GetSystemPowerStatus retrieves the power status of the system
        if(GetSystemPowerStatus(&status)){
            while (1){
                msgStatusBattery();
                Sleep(60000);
            }
        }
        else
            MessageBox(NULL,"Error: Can't get Information the System Power Status.","Battery level - msgbp", MB_OK|0x00000010L);
    }else{
        MoveFile("./msgbp.exe", path);
        MessageBox(NULL,"File have been moved to StartUp. Please restart to finish.","Battery level - msgbp", MB_OK|0x00000040L);        
    }       
    return 0;
}