/** ###################################################################
**     Filename  : Events.C
**     Project   : LowPowerTest_S08QB4
**     Processor : MC9S08QB4CTG
**     Component : Events
**     Version   : Driver 01.02
**     Compiler  : CodeWarrior HCS08 C Compiler
**     Date/Time : 08.06.2010, 14:43
**     Abstract  :
**         This is user's event module.
**         Put your event handler code here.
**     Settings  :
**     Contents  :
**         No public methods
**
** ###################################################################*/
/* MODULE Events */


#include "Cpu.h"
#include "Events.h"

/* User includes (#include below this line is not maintained by Processor Expert) */

/*
** ===================================================================
**     Event       :  _130Hz_OnInterrupt (module Events)
**
**     Component   :  _130Hz [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void _130Hz_OnInterrupt(void)
{

  Cpu_DisableInt();

  asm{                        // assambler uses faster execution
                              // switch on/off PortB ports
       //MOV  #0b00000100,PTBD  // Bit2 drives the current source to pre-load                       
                                  
       MOV  #0b00010000,PTBD  // Bit4 switches on IC 
       MOV  #0b00010100,PTBD  // Bit2 drives the current source to default connection   
       MOV  #0b00010100,PTBD  // make second pulse longer
       MOV  #0b00010100,PTBD  // make second pulse longer
       
       MOV  #0b00010000,PTBD  // 1. pause to reduce crosstalk
       MOV  #0b00011000,PTBD  // Bit3 changes the switch from default to second state
       MOV  #0b00011100,PTBD  // Bit2 drives again the current source
       MOV  #0b00011100,PTBD  // make second pulse longer
       MOV  #0b00011100,PTBD  // make second pulse longer
       
       MOV  #0b00011000,PTBD  // 2. pause to reduce crosstalk
       MOV  #0b00010000,PTBD  // change switch to default state
       //MOV  #0b00000000,PTBD  // switch off whole circuit to save power
  }

Cpu_EnableInt();
}

/*
** ===================================================================
**     Event       :  EInt1_OnInterrupt (module Events)
**
**     Component   :  EInt1 [ExtInt]
**     Description :
**         This event is called when an active signal edge/level has
**         occurred.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void EInt1_OnInterrupt(void)
{
extern byte counter2;
extern bool new_stim_data;
  
  Cpu_DisableInt();
  
  while(_130Hz_Disable()!=ERR_OK);     // switch off 130Hz output
  while(_100Hz_Disable()!=ERR_OK);      // switch off 10Hz output
  while(_2750ms_Enable()!=ERR_OK);     // switch on 3s-Timer, only to receive
  counter2++;                          // increment counter2 to count all edges, simple receiving
  
  Cpu_EnableInt();

}

/*
** ===================================================================
**     Event       :  _2750ms_OnInterrupt (module Events)
**
**     Component   :  _2750ms [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void _2750ms_OnInterrupt(void)
{
extern byte counter2,old_counter2,ValueHz,burst_mode;
extern bool new_stim_data,stim_on;
 
  Cpu_DisableInt();
  
  while(_2750ms_Disable()!=ERR_OK);        // stop 3s-Timer untill next receiving
  
  if(counter2==21){                    // now check if received data is valid
         
         //send_SetVal();// test1
         //new_stim_data=TRUE;           // correct data received, 50µA, bipolar, 
         stim_on=TRUE;                 // "switch on" variables
         ValueHz=130;
         //test//
         //setReg8(TPMSC, 0x08);       //  
         setReg16(TPMMOD, 0x0332);
         //setReg16(TPMC0V,0x0332);       // cDBS(20Hz) 

      }else if(counter2==23){          //check again, if another received data is valid
              
              //send_SetVal();// test1
              //new_stim_data=TRUE;      // correct data received, 50µA, off
              stim_on=FALSE;           // "switch on" only one variable
             

      }
      
  if(counter2==22){                    // now check if received data is valid
         
         //send_SetVal();// test1
         //new_stim_data=TRUE;           // correct data received, 50µA, bipolar, 
         stim_on=TRUE;                 // "switch on" variables
         ValueHz=130;
         //test//
         //setReg8(TPMSC, 0x08);       //  
         setReg16(TPMMOD, 0x00A2);
         //setReg16(TPMC0V,0x00A2);       //   cDBS(100Hz)

      }else if(counter2==23){          //check again, if another received data is valid
              
              //send_SetVal();// test1
              //new_stim_data=TRUE;      // correct data received, 50µA, off
              stim_on=FALSE;           // "switch on" only one variable
             

      }
      
  if(counter2==24){                    // now check if received data is valid
         
         //send_SetVal();// test1
         //new_stim_data=TRUE;           // correct data received, 50µA, bipolar,
         burst_mode=6;                 // value for burst mode cBBS(100Hz) 50ms pause interval
         stim_on=TRUE;                 // "switch on" variables
         ValueHz=100; 
         //test//
         setReg8(MTIMSC, 0x70);       //  
         //setReg8(MTIMCLK, 0x02);
         setReg8(MTIMMOD,0xA1);       //   
      }else if(counter2==23){          //check again, if another received data is valid
              
              //send_SetVal();// test1
              //new_stim_data=TRUE;      // correct data received, 50µA, off
              stim_on=FALSE;           // "switch on" only one variable
             

      }
   
  if(counter2==25){                    // now check if received data is valid
         
         //send_SetVal();// test1
         //new_stim_data=TRUE;           // correct data received, 50µA, bipolar, 
         stim_on=TRUE;                 // "switch on" variables
         ValueHz=130;
         //test//
         //setReg8(TPMSC, 0x08);       //  
         setReg16(TPMMOD, 0x007D);
         //setReg16(TPMC0V,0x007D);       // cDBS(130Hz)

      }else if(counter2==23){          //check again, if another received data is valid
              
              //send_SetVal();// test1
              //new_stim_data=TRUE;      // correct data received, 50µA, off
              stim_on=FALSE;           // "switch on" only one variable
             

      }
  
  if(counter2==26){                    // now check if received data is valid
         
         //send_SetVal();// test1
         //new_stim_data=TRUE;           // correct data received, 100µA, bipolar,
         burst_mode=21;                // value for burst mode cTBS(100Hz) 200ms pause interval 
         stim_on=TRUE;                 // "switch on" variables
         ValueHz=100;
         //test//
         setReg8(MTIMSC, 0x70);       //  
         //setReg8(MTIMCLK, 0x02);
         setReg8(MTIMMOD,0xA1);       //   

      }else if(counter2==23){          //check again, if another received data is valid
              
              //send_SetVal();// test1
              //new_stim_data=TRUE;      // correct data received, 50µA, off
              stim_on=FALSE;           // "switch on" only one variable
             

      }                                     
  
  if(counter2==27){                    // now check if received data is valid
         
         //send_SetVal();// test1
         //new_stim_data=TRUE;           // correct data received, 50µA, bipolar, 
         stim_on=TRUE;                 // "switch on" variables
         ValueHz=130;
         //test//
         //setReg8(TPMSC, 0x08);       //  
         setReg16(TPMMOD, 0x0147);
         //setReg16(TPMC0V,0x0332);       // cDBS(50Hz) 

      }else if(counter2==23){          //check again, if another received data is valid
              
              //send_SetVal();// test1
              //new_stim_data=TRUE;      // correct data received, 50µA, off
              stim_on=FALSE;           // "switch on" only one variable
             

      }
  if(counter2==28){                    // now check if received data is valid
         
         //send_SetVal();// test1
         //new_stim_data=TRUE;           // correct data received, 50µA, bipolar, 
         stim_on=TRUE;                 // "switch on" variables
         ValueHz=130;
         //test//
         //setReg8(TPMSC, 0x08);       //  
         setReg16(TPMMOD, 0x00CC);
         //setReg16(TPMC0V,0x0332);       // cDBS(80Hz) 

      }else if(counter2==23){          //check again, if another received data is valid
              
              //send_SetVal();// test1
              //new_stim_data=TRUE;      // correct data received, 50µA, off
              stim_on=FALSE;           // "switch on" only one variable
             

      }    
      
  new_stim_data=TRUE;                 // receiving finished
  old_counter2=counter2;
  counter2=0;
  Cpu_EnableInt();
}
/*
** ===================================================================
**     Event       :  _100Hz_OnInterrupt (module Events)
**
**     Component   :  _100Hz [TimerInt]
**     Description :
**         When a timer interrupt occurs this event is called (only
**         when the component is enabled - <Enable> and the events are
**         enabled - <EnableEvent>). This event is enabled only if a
**         <interrupt service/event> is enabled.
**     Parameters  : None
**     Returns     : Nothing
** ===================================================================
*/
void _100Hz_OnInterrupt(void)
{
  extern byte ISRcounter,puls_mode,burst_mode;
  
  Cpu_DisableInt();

  ISRcounter++;
  
  
  if(ISRcounter == puls_mode + burst_mode){
  
      ISRcounter=1;
  }
  
  if (ISRcounter<=3){
    
  asm{                        // assambler uses faster execution
                              // switch on/off PortB ports
       //MOV  #0b00000100,PTBD  // Bit2 drives the current source to pre-load
       //MOV  #0b00000100,PTBD  // Bit2 drives the current source to pre-load
       //MOV  #0b00000100,PTBD  // Bit2 drives the current source to pre-load
                              
       MOV  #0b00010000,PTBD  // Bit4 switches on IC 
       MOV  #0b00010100,PTBD  // Bit2 drives the current source to default connection   
       MOV  #0b00010100,PTBD
       MOV  #0b00010100,PTBD  // make second pulse longer
       
       MOV  #0b00010000,PTBD  // 1. pause to reduce crosstalk
       MOV  #0b00011000,PTBD  // Bit3 changes the switch from default to second state
       MOV  #0b00011100,PTBD  // Bit2 drives again the current source
       MOV  #0b00011100,PTBD
       MOV  #0b00011100,PTBD  // make second pulse longer
       
       MOV  #0b00011000,PTBD  // 2. pause to reduce crosstalk
       MOV  #0b00010000,PTBD  // change switch back to default state
       //MOV  #0b00000000,PTBD  // switch off whole circuit to save power
  }
 

}

Cpu_EnableInt();

}


