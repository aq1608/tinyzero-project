/*  This file holds most of the code needed to create the menu functionality 
 *  and graphics
 *  
 *  Written by: Ben Rose and Laveréna Wienclaw
 *  Last update: May 2021
 */

#define menu_debug_print true // Debug messages will print to the Serial Monitor when this is 'true'

// Change the menu font colors for fun! Pre-set color options are TS_16b_:
// Black, Gray, DarkGray, White, Blue, DarkBlue, Red, DarkRed, Green, DarkGreen, Brown, DarkBrown, Yellow
// You can make more colors in the TinyScreen library TinyScreen.h file, there are over 65000+ color combos!
// uint16_t defaultFontColor = TS_16b_White;
// uint16_t defaultFontBG = TS_16b_Black;
// uint16_t inactiveFontColor = TS_16b_Gray;
// uint16_t inactiveFontBG = TS_16b_Black;

// uint8_t menuHistory[5];
// uint8_t menuHistoryIndex = 0;
// uint8_t menuSelectionLineHistory[5];
// int currentMenu = 0;
// int currentMenuLine = 0;
// int lastMenuLine = -1;
// int currentSelectionLine = 0;
// int lastSelectionLine = -1;

// void (*menuHandler)(uint8_t) = NULL;

// Use this struct outline to create menus
// typedef struct
// {
//   const uint8_t amtLines;
//   const char* const * strings;
//   void (*selectionHandler)(uint8_t);
// } menu_info;

// // First menu variables for 5 options
// static const char PROGMEM homeMenuStrings0[] = "Calendar";
// static const char PROGMEM homeMenuStrings1[] = "Lang";
// static const char PROGMEM homeMenuStrings2[] = "BPM";


// static const char* const PROGMEM homeMenuStrings[] =
// {
//   homeMenuStrings0,
//   homeMenuStrings1,
//   homeMenuStrings2,
// };

// const menu_info homeMenuInfo =
// {
//   3,
//   homeMenuStrings, 
//   homeMenu, 
// };

// // Date and Time menu variables
// static const char PROGMEM dateTimeMenuStrings0[] = "Set Year";
// static const char PROGMEM dateTimeMenuStrings1[] = "Set Month";
// static const char PROGMEM dateTimeMenuStrings2[] = "Set Day";
// static const char PROGMEM dateTimeMenuStrings3[] = "Set Hour";
// static const char PROGMEM dateTimeMenuStrings4[] = "Set Minute";
// static const char PROGMEM dateTimeMenuStrings5[] = "Set Second";

// static const char* const PROGMEM dateTimeMenuStrings[] =
// {
//   dateTimeMenuStrings0,
//   dateTimeMenuStrings1,
//   dateTimeMenuStrings2,
//   dateTimeMenuStrings3,
//   dateTimeMenuStrings4,
//   dateTimeMenuStrings5,
// };

// const menu_info dateTimeMenuInfo =
// {
//   6,
//   dateTimeMenuStrings,
//   dateTimeMenu,
// };


// Second  sub-menu variables for 3 options
// Use Ctrl + f on these menu options to see where to program the logic for these menu titles, noted in comments
// static const char PROGMEM secondMenuStrings0[] = "English";
// static const char PROGMEM secondMenuStrings1[] = "Chinese";
// static const char PROGMEM secondMenuStrings2[] = "Bahasa Melayu";

// static const char* const PROGMEM secondMenuStrings[] =
// {
//   secondMenuStrings0,
//   secondMenuStrings1,
//   secondMenuStrings2,
// };

// const menu_info secondMenuInfo =
// {
//   3,
//   secondMenuStrings,//loggingMenuStrings
//   secondMenu,//loggingMenu
// };

// const menu_info menuList[] = {
//   emergencyMenuIndex, 
//   // dateTimeMenuInfo, 
//   };
// // #define homeMenuIndex 0
// // // #define dateTimeMenuIndex 2
// // #define secondMenuIndex 1
// #define emergencyMenuIndex 0

bool needMenuDraw = true;



void newMenu(int8_t newIndex) {
  currentMenuLine = 0;
  lastMenuLine = -1;
  currentSelectionLine = 0;
  lastSelectionLine = -1;
  if (newIndex >= 0) {
    menuHistory[menuHistoryIndex++] = currentMenu;
    currentMenu = newIndex;
  } else {
    if (currentDisplayState == displayEmergency) {
      menuHistoryIndex--;
      currentMenu = menuHistory[menuHistoryIndex];
    }
  }
  if (menuHistoryIndex) {
    currentDisplayState = displayEmergency;
    if (menu_debug_print)SerialMonitorInterface.print("New menu index ");
    if (menu_debug_print)SerialMonitorInterface.println(currentMenu);
    currentSelectionLine = menuSelectionLineHistory[menuHistoryIndex];
  } else {
    if (menu_debug_print)SerialMonitorInterface.print("New menu index ");
    if (menu_debug_print)SerialMonitorInterface.println("home");
    menuSelectionLineHistory[menuHistoryIndex + 1] = 0;
    currentDisplayState = displayStateHome;
    initHomeScreen();
  }
}

// int currentVal = 0;
// int digits[4];
// int currentDigit = 0;
// int maxDigit = 4;
// int *originalVal;
// void (*editIntCallBack)() = NULL;

// uint8_t editInt(uint8_t button, int *inVal, char *intName, void (*cb)()) {
//   if (menu_debug_print)SerialMonitorInterface.println("editInt");
//   if (!button) {
//     if (menu_debug_print)SerialMonitorInterface.println("editIntInit");
//     editIntCallBack = cb;
//     currentDisplayState = displayStateEditor;
//     editorHandler = editInt;
//     currentDigit = 0;
//     originalVal = inVal;
//     currentVal = *originalVal;
    // digits[3] = currentVal % 10; currentVal /= 10;
    // digits[2] = currentVal % 10; currentVal /= 10;
    // digits[1] = currentVal % 10; currentVal /= 10;
    // digits[0] = currentVal % 10;
//     currentVal = *originalVal;

//     displayBuffer.clearWindow(0, 8, 96, 64);
//     writeArrows();

//     displayBuffer.fontColor(defaultFontColor, defaultFontBG);
//     int width = displayBuffer.getPrintWidth(intName);
//     displayBuffer.setCursor(96 / 2 - width / 2, menuTextY[1]);
//     displayBuffer.print(intName);

//     displayBuffer.setCursor(8, 15 - 6);
//     displayBuffer.print("Back");
//     displayBuffer.setCursor(8, 45 + 6);
//     displayBuffer.print("Next/Save");

//     displayBuffer.drawLine(1, 14,    1, 12, 0xFFFF);
//     displayBuffer.drawLine(1, 12,    6, 12, 0xFFFF);

//     displayBuffer.drawLine(1, 54,    1, 56, 0xFFFF);
//     displayBuffer.drawLine(1, 56,    6, 56, 0xFFFF);

//   } else if (button == upButton) {
    // if (digits[currentDigit] < 9)
    //   digits[currentDigit]++;
//   } else if (button == downButton) {
    // if (digits[currentDigit] > 0)
    //   digits[currentDigit]--;
//   } else if (button == selectButton) {
//     if (currentDigit < maxDigit - 1) {
//       currentDigit++;
//     } else {
//       //save
      // int newValue = (digits[3]) + (digits[2] * 10) + (digits[1] * 100) + (digits[0] * 1000);
//       *originalVal = newValue;
//       viewMenu(backButton);
//       if (editIntCallBack) {
//         editIntCallBack();
//         editIntCallBack = NULL;
//       }
//       return 1;
//     }
//   } else if (button == backButton) {
//     if (currentDigit > 0) {
//       currentDigit--;
//     } else {
//       if (menu_debug_print)SerialMonitorInterface.println("back");
//       viewMenu(backButton);
//       return 0;
//     }
//   }

//   displayBuffer.setCursor(96 / 2 - 16, menuTextY[2] + 3);
//   for (uint8_t i = 0; i < 4; i++) {
//     if (i != currentDigit)displayBuffer.fontColor(inactiveFontColor, defaultFontBG);
    // displayBuffer.print(digits[i]);
//     if (i != currentDigit)displayBuffer.fontColor(defaultFontColor, defaultFontBG);
//   }
//   displayBuffer.print(F("   "));
//   displayBuffer.fontColor(0xFFFF, ALPHA_COLOR);
//   return 0;
// }


// void printCenteredAt(int y, char * text) {
//   int width = displayBuffer.getPrintWidth(text);
//   //displayBuffer.clearWindow(96 / 2 - width / 2 - 1, y, width + 2, 8);
//   displayBuffer.clearWindow(10, y, 96 - 20, 10);
//   displayBuffer.setCursor(96 / 2 - width / 2, y);
//   displayBuffer.print(text);
// }

// int tempOffset = 0;

// void saveTempCalibration() {
//   tempOffset = constrain(tempOffset,0,20);
// //  writeSettings();
// }

// void homeMenu(uint8_t selection) {
//   if (menu_debug_print)SerialMonitorInterface.println("MenuHandler");
//   if (selection == 0) {
//     // newMenu(dateTimeMenuIndex);
//     currentDisplayState = displayCalendar;
//   }
//   if (selection == 1) {
//     // char buffer[20];
//     // strcpy_P(buffer, (PGM_P)pgm_read_word(&(menuList[homeMenuIndex].strings[selection])));
//     // editInt(0, &brightness, buffer, setBrightnessCB);
//     newMenu(secondMenuIndex);
//   }
//   if (selection == 2) {
//       currentDisplayState = displayHeartRate;
//       bpmsetup();
//   }
//   // if (selection == 3) {
      
//   // }
//   // if (selection == 4) {
      
//   // }
// }


void setBrightnessCB(){
  brightness = constrain(brightness, 0, 15);
}

// void secondMenu(uint8_t selection) {
//   if (menu_debug_print)SerialMonitorInterface.println("secondMenuHandler");
//   if (selection == 0) {
//     currentDisplayState = displayStateHome;
//   }
//   if (selection == 1) {
//     currentDisplayState = displayChineseHome;
//   }
//   if (selection == 2) {
//     currentDisplayState = displayMalayHome;
//   }
// }


// uint8_t dateTimeSelection = 0;
// int dateTimeVariable = 0;

// void saveChangeCallback() {
//   int timeData[] = {year(), month(), day(), hour(), minute(), second()};
//   timeData[dateTimeSelection] = dateTimeVariable;
//   setTime(timeData[3], timeData[4], timeData[5], timeData[2], timeData[1], timeData[0]);
//   noInterrupts();
//   counter = now();
//   interrupts();
//   if (menu_debug_print)SerialMonitorInterface.print("set time ");
//   if (menu_debug_print)SerialMonitorInterface.println(dateTimeVariable);
// }

// void dateTimeMenu(uint8_t selection) {
//   if (menu_debug_print)SerialMonitorInterface.print("dateTimeMenu ");
//   if (menu_debug_print)SerialMonitorInterface.println(selection);
//   if (selection >= 0 && selection < 6) {
//     int timeData[] = {year(), month(), day(), hour(), minute(), second()};
//     dateTimeVariable = timeData[selection];
//     dateTimeSelection = selection;
//     char buffer[20];
//     strcpy_P(buffer, (PGM_P)pgm_read_word(&(menuList[dateTimeMenuIndex].strings[selection])));
//     editInt(0, &dateTimeVariable, buffer, saveChangeCallback);
//   }
// }




int changeDir;
int changeEnd;
int changeStart;
int yChange;

void drawMenu() {
  //for (int yChange = changeStart; yChange != changeEnd; yChange += changeDir) {
  if (needMenuDraw) {
    needMenuDraw = false;
    displayBuffer.clearWindow(0, 7, 96, 56);
    for (int i = 0; i < menuList[currentMenu].amtLines; i++) {
      if (i == currentSelectionLine) {
        displayBuffer.fontColor(defaultFontColor, ALPHA_COLOR);
      } else {
        displayBuffer.fontColor(inactiveFontColor, ALPHA_COLOR);
      }
      char buffer[20];
      strcpy_P(buffer, (PGM_P)pgm_read_word(&(menuList[currentMenu].strings[currentMenuLine + i])));
      int width = displayBuffer.getPrintWidth(buffer);
      displayBuffer.setCursor(96 / 2 - width / 2, menuTextY[i] + 5 + yChange - (currentSelectionLine * 8) + 16);
      displayBuffer.print(buffer);
    }

    writeArrows();
  }
  if (yChange != changeEnd) {
    if (abs(yChange - changeEnd) > 5) {
      yChange += changeDir;
    }
    if (abs(yChange - changeEnd) > 3) {
      yChange += changeDir;
    }
    yChange += changeDir;
    needMenuDraw = true;
  }
  displayBuffer.fontColor(0xFFFF, ALPHA_COLOR);
}

void emergencyMenu(uint8_t selection) {
  if (menu_debug_print) SerialMonitorInterface.println("emergencyMenuHandler");

  // Handle selections
  if (selection == 0) {
    // User selected "Yes"
    displayBuffer.clearWindow(0, 7, 96, 56); // Clear the menu area
    displayBuffer.fontColor(TS_16b_Red, TS_16b_Black);
    char message[] = "User is not okay!";
    int width1 = displayBuffer.getPrintWidth(message);
    displayBuffer.setCursor(96 / 2 - width1 / 2, menuTextY[2]); // Adjust menuTextY[2] for the first line
    displayBuffer.print(message);

    display.writeBufferDMA(displayBuffer.getBuffer(), displayBuffer.getBufferSize());
    sendNotification("User needs help!");

    needMenuDraw = false;

    // Non-blocking delay
    unsigned long startTime = millis();
    while (millis() - startTime < 10000) {
      delay(50);
    }

    needMenuDraw = true;
  } else if (selection == 1) {
    // User selected "No"
    displayBuffer.clearWindow(0, 7, 96, 56); // Clear the menu area
    displayBuffer.fontColor(TS_16b_White, TS_16b_Black);
    char message[] = "User is okay!";
    int width = displayBuffer.getPrintWidth(message);
    displayBuffer.setCursor(96 / 2 - width / 2, menuTextY[2] + 5);
    displayBuffer.print(message);
    display.writeBufferDMA(displayBuffer.getBuffer(), displayBuffer.getBufferSize());

    needMenuDraw = false;

    // Non-blocking delay
    unsigned long startTime = millis();
    while (millis() - startTime < 10000) {
      delay(50);
    }

    needMenuDraw = true;
    newMenu(-1); // Return to previous menu
  }
}

void viewMenu(uint8_t button) {
  if (menu_debug_print)SerialMonitorInterface.print("viewMenu ");
  if (menu_debug_print)SerialMonitorInterface.println(button);
  if (!button) {

  } else {
    if (button == upButton) {
      if (currentSelectionLine > 0) {
        currentSelectionLine--;
      }
    } else if (button == downButton) {
      
      if (currentSelectionLine < menuList[currentMenu].amtLines - 1) {
        currentSelectionLine++;
      }
    } else if (button == selectButton) {
      if (menu_debug_print)SerialMonitorInterface.print("select ");
      if (menu_debug_print)SerialMonitorInterface.println(currentMenuLine + currentSelectionLine);
      menuList[currentMenu].selectionHandler(currentMenuLine + currentSelectionLine);
    } else if (button == selectButton) {
      newMenu(-1);
      if (!menuHistoryIndex)
        return;
    }
  }
  if (lastMenuLine != currentMenuLine || lastSelectionLine != currentSelectionLine) {
    if (menu_debug_print)SerialMonitorInterface.println("drawing menu ");
    if (menu_debug_print)SerialMonitorInterface.println(currentMenu);


    if (currentSelectionLine < lastSelectionLine) {
      changeDir = 1;
      changeEnd = 0;
      changeStart = -7;
    } else {
      changeDir = -1;
      changeEnd = 0;
      changeStart = 7;
    }
    if (lastSelectionLine == -1) {
      changeStart = changeEnd; //new menu, just draw once
    }
    yChange = changeStart;
    needMenuDraw = true;
  }
  lastMenuLine = currentMenuLine;
  lastSelectionLine = currentSelectionLine;
  menuSelectionLineHistory[menuHistoryIndex] = currentSelectionLine;
  displayBuffer.fontColor(0xFFFF, ALPHA_COLOR);
}


void writeArrows() {
  leftArrow(0, 15 + 2);
  rightArrow(0, 45 + 5);

  upArrow(90, 15 + 2);
  downArrow(90, 45 + 4);
}


void leftArrow(int x, int y) {
  displayBuffer.drawLine(x + 2, y - 2, x + 2, y + 2, 0xFFFF);
  displayBuffer.drawLine(x + 1, y - 1, x + 1, y + 1, 0xFFFF);
  displayBuffer.drawLine(x + 0, y - 0, x + 0, y + 0, 0xFFFF);
}

void rightArrow(int x, int y) {
  displayBuffer.drawLine(x + 0, y - 2, x + 0, y + 2, 0xFFFF);
  displayBuffer.drawLine(x + 1, y - 1, x + 1, y + 1, 0xFFFF);
  displayBuffer.drawLine(x + 2, y - 0, x + 2, y + 0, 0xFFFF);
}

void upArrow(int x, int y) {
  displayBuffer.drawLine(x + 0, y - 0, x + 4, y - 0, 0xFFFF);
  displayBuffer.drawLine(x + 1, y - 1, x + 3, y - 1, 0xFFFF);
  displayBuffer.drawLine(x + 2, y - 2, x + 2, y - 2, 0xFFFF);
}
void downArrow(int x, int y) {
  displayBuffer.drawLine(x + 0, y + 0, x + 4, y + 0, 0xFFFF);
  displayBuffer.drawLine(x + 1, y + 1, x + 3, y + 1, 0xFFFF);
  displayBuffer.drawLine(x + 2, y + 2, x + 2, y + 2, 0xFFFF);
}
