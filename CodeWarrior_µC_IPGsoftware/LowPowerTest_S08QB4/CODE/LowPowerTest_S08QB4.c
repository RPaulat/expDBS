/** ###################################################################
**     Filename  : LowPowerTest_S08QB4.C
**     Project   : LowPowerTest_S08QB4
**     Processor : MC9S08QB4CTG
**     Version   : Driver 01.11
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 08.06.2010, 14:43
**     Abstract  :
**         Main module.
**         This module contains user's application code.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE LowPowerTest_S08QB4 */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "_130Hz.h"
#include "drive_Reed.h"
#include "EInt1.h"
#include "_2750ms.h"
#include "send.h"
#include "_5VOnOff.h"
#include "T5_OnOff.h"
#include "_100Hz.h"
#include "Bit1.h"
/* Include shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
bool stim_on=FALSE,new_stim_data=FALSE,stop_switch=FALSE;
int   i=0,j=0;
byte  a,b;
byte  counter2,counter3=0,old_counter2,ValueHz,ISRcounter=0;
byte  puls_mode=3,burst_mode,burst_duration_ratio,puls_counter;
word  rest_mode=0;
/* User includes (#include below this line is not maintained by Processor Expert) */

void main(void)
{
  /* Write your local variable definition here */
 
  /*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
  PE_low_level_init();
  /*** End of Processor Expert internal initialization.                    ***/
  
  /* INIT befor start */
  
  _130Hz_EnableEvent();
  _100Hz_EnableEvent();
  _2750ms_EnableEvent();
  _5VOnOff_SetVal(); //Test for DCC-IPGs
  T5_OnOff_ClrVal(); // -"-


  
  //REAL MAIN PROGRAM//
  for(;;){
    
    if(stim_on==TRUE){          // routine for signal 
      
      drive_Reed_ClrVal();          // ready for next ExtInt
      counter2=0;
      new_stim_data=FALSE;          // reset all variables for next receiving
      EInt1_Enable();               // receiving possible   
      
      
      if(ValueHz==130){
        while(_100Hz_Disable()!=ERR_OK);
        while(_130Hz_Disable()!=ERR_OK);
       
       if(old_counter2==21){
        //blinking 3 times 15ms
        while(a<=2){
          Bit1_SetVal(); 
            for(i=0;i>65535;i++){
            }
          Bit1_ClrVal();
           while(b<=67){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
       }
       
       if(old_counter2==22){
        //blinking 5 times 15ms
        while(a<=4){
          Bit1_SetVal(); 
            for(i=0;i>65535;i++){
            }
          Bit1_ClrVal();
           while(b<=67){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
       }
       
       if(old_counter2==25){
        //blinking 7 times 15ms
        while(a<=6){
          Bit1_SetVal(); 
            for(i=0;i>65535;i++){
            }
          Bit1_ClrVal();
           while(b<=67){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
       }
       
       if(old_counter2==27){
        //blinking 13 times 15ms
        while(a<=12){
          Bit1_SetVal(); 
            for(i=0;i>65535;i++){
            }
          Bit1_ClrVal();
           while(b<=67){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
       }
       
       if(old_counter2==28){
        //blinking 15 times 15ms
        while(a<=14){
          Bit1_SetVal(); 
            for(i=0;i>65535;i++){
            }
          Bit1_ClrVal();
           while(b<=67){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
       }
       
        while(_130Hz_Enable()!=ERR_OK);
      }
      if(ValueHz==100){
        while(_100Hz_Disable()!=ERR_OK);
        while(_130Hz_Disable()!=ERR_OK);
        ///cTBS setup//////////////////////////////
        
        
        //burst_duration_ratio = 90;  //  60/100 burst pulses
        //burst_mode = (200 / 0x09);//  pause interval burst mode 200ms/T + 3 pulse
        //rest_mode  = (20000 / 0x09) - (burst_mode * 100);
        ///cTBS setup/////////////////////////////
       if(burst_mode==6){        
       //blinking  9 times 15ms
        while(a<=8){
          Bit1_SetVal(); 
            for(i=0;i>65535;i++){
            }
          Bit1_ClrVal();
           while(b<=67){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
       }
       if(burst_mode==21){        
       //blinking  11 times 15ms
        while(a<=10){
          Bit1_SetVal(); 
            for(i=0;i>65535;i++){
            }
          Bit1_ClrVal();
           while(b<=67){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
       }
        while(_100Hz_Enable()!=ERR_OK);
      }
     
    }else if(stim_on==FALSE){   //new battery was set by soldering to board or stimulation prgrammed to off-state
  
        //LED on 500ms
        while(a<=0){
          Bit1_SetVal(); 
           while(b<=32){
            for(j=0;j>65535;j++){
            }
           b++;
           }
         Bit1_ClrVal();
         b=0;  
         a++; 
        }
        a=0;
        b=0;
        //          
            drive_Reed_ClrVal();          // ready for next ExtInt
            EInt1_Enable();               // receiving possible        
            new_stim_data=FALSE;          // reset all variables for next receiving
            //send_ClrVal();// test1
            
            
            SPMSC2_LPR  = 1;      // 
            
            if(stop_switch==TRUE){
              Cpu_SetStopMode();    /*Init Stop Mode*/ //better for FEE 
            }
            else{
              Cpu_SetWaitMode();    /*Init Low Power Wait Mode*/ //better for FBE or FBELP
              stop_switch=TRUE;
            }
            
             
    }
    
    //send_ClrVal();// test1
    
    while(new_stim_data==FALSE){     // simple wait structure
                                     // get out if receiving is finished    
      Cpu_SetWaitMode();    /*Init Low Power Wait Mode*/
     
    }                                
  
  }


  /*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END LowPowerTest_S08QB4 */
/*
** ###################################################################
**
**     This file was created by Processor Expert 3.07 [04.34]
**     for the Freescale HCS08 series of microcontrollers.
**
** ###################################################################
*/
