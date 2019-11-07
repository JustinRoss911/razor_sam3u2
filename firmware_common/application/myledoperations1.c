/*!*********************************************************************************************************************
@file myledoperations1.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this myledoperations1 as a template:
 1. Copy both myledoperations1.c and myledoperations1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "myledoperations1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "MyLedOperations1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "MY_LED_OPERATIONS1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void MyLedOperations1Initialize(void)
- void MyLedOperations1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>MyLedOperations1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32MyLedOperations1Flags;                          /*!< @brief Global state flags */


/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "MyLedOperations1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type MyLedOperations1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 MyLedOperations1_u32Timeout;                           /*!< @brief Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void MyLedOperations1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void MyLedOperations1Initialize(void)
{
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    MyLedOperations1_pfStateMachine = MyLedOperations1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    MyLedOperations1_pfStateMachine = MyLedOperations1SM_Error;
  }

} /* end MyLedOperations1Initialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void MyLedOperations1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void MyLedOperations1RunActiveState(void)
{
  MyLedOperations1_pfStateMachine();

} /* end MyLedOperations1RunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */
static void MyLedOperations1SM_Idle(void)
{
  static u16 u16BlinkCount = 0;
  static u8 u8BinaryCounter = 0;
  static bool Forward = TRUE;
  static bool Reverse = FALSE;
  u16BlinkCount++;
  
  if(u16BlinkCount == 200)
  {
    u16BlinkCount = 0;
    u8BinaryCounter++;
    if(u8BinaryCounter == 1 && Forward)
    {
      LedToggle(RED);
      LedToggle(WHITE);
    }
    if(u8BinaryCounter == 2 && Forward)
    {
      LedToggle(ORANGE);
      LedToggle(PURPLE);
    }
    if(u8BinaryCounter == 3 && Forward)
    {
      LedToggle(YELLOW);
      LedToggle(BLUE);
    }
    if(u8BinaryCounter == 4 && Forward)
    {
      LedToggle(GREEN);
      LedToggle(CYAN);
    }
    if(u8BinaryCounter == 6 && Forward)
    {
      LedOff(RED);
      LedOff(WHITE);
      LedOff(ORANGE);
      LedOff(PURPLE);
      LedOff(YELLOW);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(BLUE);
      Forward = FALSE;
      Reverse = TRUE;
      u8BinaryCounter = 0;
    }
    if(u8BinaryCounter == 1 && Reverse)
    {
      LedToggle(GREEN);
      LedToggle(CYAN);
    }
    if(u8BinaryCounter == 2 && Reverse)
    {
      LedToggle(YELLOW);
      LedToggle(BLUE);
    }
    if(u8BinaryCounter == 3 && Reverse)
    {
      LedToggle(ORANGE);
      LedToggle(PURPLE);
    }
    if(u8BinaryCounter == 4 && Reverse)
    {
      LedToggle(RED);
      LedToggle(WHITE);
    }
    if(u8BinaryCounter == 6 && Reverse)
    {
      LedOff(RED);
      LedOff(WHITE);
      LedOff(ORANGE);
      LedOff(PURPLE);
      LedOff(YELLOW);
      LedOff(CYAN);
      LedOff(GREEN);
      LedOff(BLUE);
      Forward = TRUE;
      Reverse = FALSE;
      u8BinaryCounter = 0;
    }
  }
} /* end MyLedOperations1SM_Idle() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void MyLedOperations1SM_Error(void)          
{
  
} /* end MyLedOperations1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
