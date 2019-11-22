/*!*********************************************************************************************************************
@file user_app1.c                                                                
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
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
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags;                          /*!< @brief Global state flags */
static ButtonNameType Password[MAX_PASS_LENGTH] = {NOBUTTON, NOBUTTON, NOBUTTON, NOBUTTON, NOBUTTON, NOBUTTON, NOBUTTON, NOBUTTON, NOBUTTON, NOBUTTON};
static bool CorrectPassword;
static u32 u32PasswordCount = 0;

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;                   /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;                    /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;                     /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags;                /*!< @brief From main.c */


/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine;               /*!< @brief The state machine function pointer */
//static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */


/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/
/* 
@fn ButtonNameType CheckButtonPressed 
@brief
This function is used to return the button that is pressed.
*/
ButtonNameType CheckButtonPressed(void)
{
  ButtonNameType TheButton = NOBUTTON;
  if(WasButtonPressed(BUTTON0))
  {
    ButtonAcknowledge(BUTTON0);
    TheButton = BUTTON0;
  }
  if(WasButtonPressed(BUTTON1))
  {
    ButtonAcknowledge(BUTTON1);
    TheButton = BUTTON1;
  }
  if(WasButtonPressed(BUTTON2))
  {
    ButtonAcknowledge(BUTTON2);
    TheButton = BUTTON2;
  }
  if(WasButtonPressed(BUTTON3))
  {
    ButtonAcknowledge(BUTTON3);
    TheButton = BUTTON3;
  }
  return TheButton;
}
/* End of CheckButtonPressed */
/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
  /* If good initialization, set state to Idle */
  if( 1 )
  {
    LedOff(WHITE);
    LedOff(PURPLE);
    LedOff(BLUE);
    LedOff(CYAN);
    LedOff(YELLOW);
    LedOff(ORANGE);
    LedBlink(RED, LED_1HZ);
    LedBlink(GREEN, LED_1HZ);
    CorrectPassword = TRUE;
    UserApp1_pfStateMachine = UserApp1SM_SetPass;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

  
/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */


/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */                                                                                            
/*--------------------------------------------------------------------------------------------------------------------*/


/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
/* This State is for the user to enter their Password // PASSWORD ENTER STATE*/
static void UserApp1SM_SetPass(void)
{
  ButtonNameType RecentButtonPress = CheckButtonPressed();
  if(RecentButtonPress == BUTTON0)
  {
    Password[u32PasswordCount] = BUTTON0;
    u32PasswordCount++;
  }
  if(RecentButtonPress == BUTTON1)
  {
    Password[u32PasswordCount] = BUTTON1;
    u32PasswordCount++;
  }
  if(RecentButtonPress == BUTTON2)
  {
    Password[u32PasswordCount] = BUTTON2;
    u32PasswordCount++;
  }
  if(RecentButtonPress == BUTTON3)
  {
    UserApp1_pfStateMachine = UserApp1SM_Idle;
    LedOff(RED);
    LedOff(GREEN);
  }
} /* End of SetPass */

/* This state is for entering the password // INPUT STATE */
static void UserApp1SM_Idle(void)
{
  LedOn(RED);
  static u32 u32ButtonPressedCount = 0;
  ButtonNameType RecentButtonPress = CheckButtonPressed();
  if(RecentButtonPress != NOBUTTON)
  {
    if(RecentButtonPress != BUTTON3)
    {
      if(RecentButtonPress != Password[u32ButtonPressedCount])
      {
        LedOn(BLUE);
        CorrectPassword = FALSE;
        u32ButtonPressedCount++;
      }
      if(RecentButtonPress == Password[u32ButtonPressedCount])
      {
        LedOn(BLUE);
        u32ButtonPressedCount++;
      }
    }
    if(RecentButtonPress == BUTTON3 && CorrectPassword && u32ButtonPressedCount == u32PasswordCount)
    {
      LedOff(RED);
      LedOff(BLUE);
      LedBlink(GREEN, LED_2HZ);
      u32ButtonPressedCount = 0;
      UserApp1_pfStateMachine = UserApp1SM_Correct;
    }
    if((RecentButtonPress == BUTTON3 && !CorrectPassword) || u32ButtonPressedCount > 10)
    {
      LedOff(RED);
      LedOff(BLUE);
      LedBlink(RED, LED_2HZ);
      u32ButtonPressedCount = 0;
      UserApp1_pfStateMachine = UserApp1SM_Incorrect;
    }
  }
} /* end UserApp1SM_Idle() */

/* CORRECT PASSWORD STATE // This state is a counter to show that the password was inputed correctly */
static void UserApp1SM_Correct(void)
{
  static u32 u32CorrectCounter = 0;
  u32CorrectCounter++;
  if(u32CorrectCounter == 5000)
  {
    LedOff(GREEN);
    UserApp1_pfStateMachine = UserApp1SM_Idle;
    u32CorrectCounter = 0;
    CorrectPassword = TRUE;
  }
} /* end UserApp1SM_Correct() */

/* INCORRECT PASSWORD STATE // This state is a counter to show that the password was inputed incorrectly */
static void UserApp1SM_Incorrect(void)
{
  static u32 u32IncorrectCounter = 0;
  u32IncorrectCounter++;
  if(u32IncorrectCounter == 5000)
  {
    LedOff(RED);
    UserApp1_pfStateMachine = UserApp1SM_Idle;
    u32IncorrectCounter = 0;
    CorrectPassword = TRUE;
  }
} /* end UserApp1SM_Correct() */
     

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)          
{
  
} /* end UserApp1SM_Error() */




/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
