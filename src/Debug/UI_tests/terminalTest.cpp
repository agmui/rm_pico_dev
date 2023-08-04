#include <retroTerm.h>

//taken from here: https://github.com/ncmreynolds/retroTerm/blob/main/examples/Example01_terminalCapabilityTests/Example01_terminalCapabilityTests.ino
retroTerm terminal;



void newPage(String title)
{
  terminal.reset();                                                      // Resets the terminal, clearing colours etc.
  terminal.hideCursor();                                                 // Hide the cursor
  terminal.printAt(1, 1, title + ", press a key or wait 30s to finish"); // Print the title at the top of the page
  terminal.println();                                                    // Print a blank line
}

/*
 * The 'endPage' function tidies up after the test
 */
void endPage()
{
  terminal.houseKeeping();
  if (terminal.keyPressed())
  {
    terminal.readKeypress();
  }
  terminal.houseKeeping();
}

void probingDemo()
{
  newPage(F("Probing test"));
  terminal.moveCursorTo(1, 3);
  terminal.print(F("Probing terminal type"));
  if (terminal.probeType())
  {
    terminal.print(F(", success - '"));
    terminal.print(terminal.type());
    terminal.println('\'');
  }
  else
  {
    terminal.println((", failure assuming VT100"));
  }
  terminal.print(F("Probing terminal size"));
  if (terminal.probeSize())
  {
    terminal.print(F(", success - "));
    terminal.print(terminal.columns());
    terminal.print('x');
    terminal.println(terminal.lines());
  }
  else
  {
    terminal.println(F(", failure assuming 80x24"));
  }
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  endPage();
}

void attributeDemo()
{
  newPage(F("Character attributes test"));

  terminal.moveCursorTo(1, 3);
  terminal.print(F("Testing bold text - "));
  terminal.attributes(ATTRIBUTE_BOLD);
  terminal.print(F("Bold Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing faint text - "));
  terminal.attributes(ATTRIBUTE_FAINT);
  terminal.print(F("Faint Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing underlined text - "));
  terminal.attributes(ATTRIBUTE_UNDERLINE);
  terminal.print(F("Underlined Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing blinking text - "));
  terminal.attributes(ATTRIBUTE_BLINK);
  terminal.print(F("Blinking Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing inverse text - "));
  terminal.attributes(ATTRIBUTE_INVERSE);
  terminal.print(F("Inverse Text"));
  terminal.resetAttributes();
  terminal.println();
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
  }
  endPage();
}

void boxDrawingDemo()
{
  newPage(F("Box drawing test"));
  uint8_t boxWidth = (terminal.columns()) / 4;
  uint8_t boxHeight = (terminal.lines() - 2) / 2;

  terminal.drawBox(1, 2, boxWidth, boxHeight);                                                                                                // Default style box with no title
  terminal.drawBoxWithTitle(boxWidth + 1, 2, boxWidth, boxHeight, "Single");                                                                  // Default style box with title
  terminal.drawBoxWithScrollbar(boxWidth * 2 + 1, 2, boxWidth, boxHeight, 0, 256, COLOUR_GREEN, BOX_SINGLE_LINE);                             // Scrollbar is shown at the top (0/256)
  terminal.drawBoxWithTitleAndScrollbar(boxWidth * 3 + 1, 2, boxWidth, boxHeight, "Single w/scroll", 64, 256, COLOUR_GREEN, BOX_SINGLE_LINE); // Scrollbar is shown at one quarter (64/256)

  terminal.drawBox(1, 2 + boxHeight, boxWidth, boxHeight, COLOUR_RED, BOX_DOUBLE_LINE);                                                                      // Specific style and colour boxes
  terminal.drawBoxWithTitle(boxWidth + 1, 2 + boxHeight, boxWidth, boxHeight, "Double", COLOUR_GREEN, BOX_DOUBLE_LINE);                                      // Title, colour and style
  terminal.drawBoxWithScrollbar(boxWidth * 2 + 1, 2 + boxHeight, boxWidth, boxHeight, 128, 256, COLOUR_BLUE, BOX_DOUBLE_LINE);                               // Scrollbar at middle (128/256)
  terminal.drawBoxWithTitleAndScrollbar(boxWidth * 3 + 1, 2 + boxHeight, boxWidth, boxHeight, "Double w/scroll", 256, 256, COLOUR_MAGENTA, BOX_DOUBLE_LINE); // Scrollbar at end (256/256)
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
  }
  endPage();
}

void eightColourDemo()
{
  newPage(F("8-colour test"));

  terminal.moveCursorTo(1, 3);
  terminal.print(F("Testing black text - "));
  terminal.attributes(COLOUR_BLACK);
  terminal.print(F("Black Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing red text - "));
  terminal.attributes(COLOUR_RED);
  terminal.print(F("Red Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing green text - "));
  terminal.attributes(COLOUR_GREEN);
  terminal.print(F("Green Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing yellow text - "));
  terminal.attributes(COLOUR_YELLOW);
  terminal.print(F("Yellow Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing blue text - "));
  terminal.attributes(COLOUR_BLUE);
  terminal.print(F("Blue Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing magenta text - "));
  terminal.attributes(COLOUR_MAGENTA);
  terminal.print(F("Magenta Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing cyan text - "));
  terminal.attributes(COLOUR_CYAN);
  terminal.print(F("Cyan Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing white text - "));
  terminal.attributes(COLOUR_WHITE);
  terminal.print(F("White Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing black background - "));
  terminal.attributes(BACKGROUND_COLOUR_BLACK);
  terminal.print(F("Black Background"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing red background - "));
  terminal.attributes(BACKGROUND_COLOUR_RED);
  terminal.print(F("Red Background"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing green background - "));
  terminal.attributes(COLOUR_BLACK | BACKGROUND_COLOUR_GREEN);
  terminal.print(F("Green Background"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing yellow background - "));
  terminal.attributes(COLOUR_BLACK | BACKGROUND_COLOUR_YELLOW);
  terminal.print(F("Yellow Background"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing blue background - "));
  terminal.attributes(BACKGROUND_COLOUR_BLUE);
  terminal.print(F("Blue Background"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing magenta background - "));
  terminal.attributes(BACKGROUND_COLOUR_MAGENTA);
  terminal.print(F("Magenta Background"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing cyan background - "));
  terminal.attributes(COLOUR_BLACK | BACKGROUND_COLOUR_CYAN);
  terminal.print(F("Cyan Background"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing white background - "));
  terminal.attributes(COLOUR_BLACK | BACKGROUND_COLOUR_WHITE);
  terminal.print(F("White Background"));
  terminal.resetAttributes();
  terminal.println();
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
  }
  endPage();
}

void largeFontDemo()
{
  newPage(F("Large font test"));

  terminal.moveCursorTo(1, 3);
  terminal.println(F("Testing double width text"));
  terminal.attributes(ATTRIBUTE_DOUBLE_WIDTH);
  terminal.print(F("Double Width Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.println(F("Testing double width & height text"));
  terminal.attributes(ATTRIBUTE_DOUBLE_SIZE);
  terminal.print(F("Double Width & Height Text"));
  terminal.resetAttributes();
  terminal.println();
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
  }
  endPage();
}

void mouseDemo()
{
  newPage(F("Mouse capture test - prints D at mouse button down, U at mouse button up, N at wheel up, S at wheel down"));
  terminal.moveCursorTo(1, terminal.lines());
  terminal.print(F("Press any key to continue, or wait 30s"));
  terminal.hideCursor();
  terminal.enableMouse();
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
    if (terminal.mouseButtonDown())
    {
      terminal.printAt(terminal.mouseColumn(), terminal.mouseRow(), "D");
    }
    if (terminal.mouseButtonUp())
    {
      terminal.printAt(terminal.mouseColumn(), terminal.mouseRow(), "U");
    }
    if (terminal.mouseWheelDown())
    {
      terminal.printAt(terminal.mouseColumn(), terminal.mouseRow(), "N");
    }
    if (terminal.mouseWheelUp())
    {
      terminal.printAt(terminal.mouseColumn(), terminal.mouseRow(), "S");
    }
  }
  terminal.readKeypress();
  terminal.disableMouse();
}

void sixteenColourDemo()
{
  newPage(F("16-colour test"));

  terminal.moveCursorTo(1, 3);
  terminal.print(F("Testing bright black text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_BLACK);
  terminal.print(F("Bright Black Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing bright red text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_RED);
  terminal.print(F("Bright Red Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing bright green text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_GREEN);
  terminal.print(F("Bright Green Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing bright yellow text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_YELLOW);
  terminal.print(F("Bright Yellow Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing bright blue text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_BLUE);
  terminal.print(F("Bright Blue Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing bright magenta text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_MAGENTA);
  terminal.print(F("Bright Magenta Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing bright cyan text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_CYAN);
  terminal.print(F("Bright Cyan Text"));
  terminal.resetAttributes();
  terminal.println();

  terminal.print(F("Testing bright white text - "));
  terminal.attributes(ATTRIBUTE_BRIGHT | COLOUR_WHITE);
  terminal.print(F("Bright White Text"));
  terminal.resetAttributes();
  terminal.println();
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
  }
  endPage();
}

void twoHundredAndFiftySixColourDemo()
{
  newPage(F("256-colour test"));
  for (uint8_t column = 0; column < 16; column++)
  {
    for (uint8_t row = 0; row < 16; row++)
    {
      terminal.foregroundColour(column + 16 * row);                 // Set 256-colour mode
      terminal.printAt(column * 4 + 3, row + 3, column + 16 * row); // Print the colour
    }
  }
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
  }
  endPage();
}

void scrollingWindowDemo()
{
  newPage(F("Scroll windowing test, this line should not move"));
  terminal.setScrollWindow(3, terminal.lines() - 2);
  // terminal.drawBox(1, 3 , terminal.columns()/2, terminal.lines()-4);
  // terminal.setScrollWindow(2,4,terminal.columns()/2-2,terminal.lines()-6);
  for (uint8_t scroll = 0; scroll < terminal.lines() - 6; scroll++)
  {
    terminal.scroll("Scrolling whole line " + String(scroll + 1) + " of " + String(terminal.lines() - 6));
    delay(100);
  }
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping();
  }
  endPage();
}
void setup(){
  terminal.begin(Serial);
}

void loop()
{
  probingDemo();
  attributeDemo();
  largeFontDemo();
  eightColourDemo();
  sixteenColourDemo();
  twoHundredAndFiftySixColourDemo();
  boxDrawingDemo();
  scrollingWindowDemo();
  mouseDemo();
}
