#include <retroTerm.h>
//taken from here: https://github.com/ncmreynolds/retroTerm/blob/main/examples/Example01_terminalCapabilityTests/Example01_terminalCapabilityTests.ino

retroTerm terminal;

uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;

char textToShow[] = "HAMLET: To be, or not to be--that is the question: \
Whether 'tis nobler in the mind to suffer \
The slings and arrows of outrageous fortune \
Or to take arms against a sea of troubles \
And by opposing end them. To die, to sleep-- \
No more--and by a sleep to say we end \
The heartache, and the thousand natural shocks \
That flesh is heir to. 'Tis a consummation \
Devoutly to be wished. To die, to sleep-- \
To sleep--perchance to dream: ay, there's the rub, \
For in that sleep of death what dreams may come \
When we have shuffled off this mortal coil, \
Must give us pause. There's the respect \
That makes calamity of so long life. \
For who would bear the whips and scorns of time, \
Th' oppressor's wrong, the proud man's contumely \
The pangs of despised love, the law's delay, \
The insolence of office, and the spurns \
That patient merit of th' unworthy takes, \
When he himself might his quietus make \
With a bare bodkin? Who would fardels bear, \
To grunt and sweat under a weary life, \
But that the dread of something after death, \
The undiscovered country, from whose bourn \
No traveller returns, puzzles the will, \
And makes us rather bear those ills we have \
Than fly to others that we know not of? \
Thus conscience does make cowards of us all, \
And thus the native hue of resolution \
Is sicklied o'er with the pale cast of thought, \
And enterprise of great pitch and moment \
With this regard their currents turn awry \
And lose the name of action. -- Soft you now, \
The fair Ophelia! -- Nymph, in thy orisons \
Be all my sins remembered.";

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

void buttonExample()
{
  newPage(F("Button test"));
  red = terminal.newButton(1, 16, terminal.columns() / 3, 3, F("Red button"), COLOUR_WHITE | ATTRIBUTE_BRIGHT | BACKGROUND_COLOUR_RED, SHORTCUT_INLINE | LABEL_CENTRED); // Create three new buttons and record the IDs
  green = terminal.newButton(terminal.columns() / 3 + 1, 16, terminal.columns() / 3, 3, F("Green button"), COLOUR_GREEN, OUTER_BOX | BOX_SINGLE_LINE | SHORTCUT_INLINE); // The method returns 0 if it fails
  blue = terminal.newButton(terminal.columns() * 2 / 3 + 1, 16, terminal.columns() / 3, 3, F("Blue button"), COLOUR_BLUE, OUTER_BOX | BOX_DOUBLE_LINE | LABEL_CENTRED);  // Colour is the colour of the frame, lettering can be different
  if (red)
  {
    terminal.labelAttributes(red, COLOUR_WHITE | ATTRIBUTE_BRIGHT | BACKGROUND_COLOUR_RED); // Make the button text more emphasised, for better contrast
    terminal.widgetShortcutKey(red, f1Pressed);
    terminal.scroll("Red button created ID=" + String(red) + " in background, displaying in 1s");
    terminal.scroll("Red button keyboard shortcut F1");
  }
  if (green)
  {
    terminal.labelAttributes(green, COLOUR_GREEN | ATTRIBUTE_BRIGHT); // Make the button text more emphasised, for better contrast
    terminal.widgetShortcutKey(green, f2Pressed);
    terminal.scroll("Green button created ID=" + String(green) + " in background, displaying in 5s");
    terminal.scroll("Green button keyboard shortcut F2");
  }
  if (blue)
  {
    terminal.labelAttributes(blue, COLOUR_BLUE | ATTRIBUTE_BRIGHT); // Make the button text more emphasised, for better contrast
    terminal.widgetShortcutKey(blue, f3Pressed);
    terminal.scroll("Blue button created ID=" + String(blue) + " in background, displaying in 10s");
    terminal.scroll("Blue button keyboard shortcut F3");
  }
  terminal.scroll("Click on the buttons once they appear, or use the shortcut keys");
  bool redDemoStarted = false;
  bool greenDemoStarted = false;
  bool blueDemoStarted = false;
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    if (red) // The button was successfully created
    {
      if (redDemoStarted == false && millis() - timeout > 1000ul && not terminal.widgetVisible(red)) // Show the button near the start of the test
      {
        terminal.scroll("Showing red button");
        redDemoStarted = true;
        terminal.showWidget(red); // Make this button visible
      }
      else if (terminal.widgetVisible(red) && millis() - timeout > 20000ul) // Hide the button again near the end of the test
      {
        terminal.scroll("Hiding red button");
        terminal.hideWidget(red); // Make this button invisible
      }
    }
    if (green) // The button was successfully created
    {
      if (greenDemoStarted == false && millis() - timeout > 5000ul && not terminal.widgetVisible(green)) // Show the button near the start of the test
      {
        terminal.scroll("Showing green button");
        greenDemoStarted = true;
        terminal.showWidget(green); // Make this button visible
      }
      else if (terminal.widgetVisible(green) && millis() - timeout > 22000ul) // Hide the button again near the end of the test
      {
        terminal.scroll("Hiding green button");
        terminal.hideWidget(green); // Make this button invisible
      }
    }
    if (blue) // The button was successfully created
    {
      if (blueDemoStarted == false && millis() - timeout > 10000ul && not terminal.widgetVisible(blue)) // Show the button near the start of the test
      {
        terminal.scroll("Showing blue button");
        blueDemoStarted = true;
        terminal.showWidget(blue); // Make this button visible
      }
      else if (terminal.widgetVisible(blue) && millis() - timeout > 24000ul) // Hide the button again near the end of the test
      {
        terminal.scroll("Hiding blue button");
        terminal.hideWidget(blue); // Make this button invisible
      }
    }
    if (terminal.widgetClicked(red))
    {
      terminal.scroll("Red clicked");
    }
    if (terminal.widgetClicked(green))
    {
      terminal.scroll("Green clicked");
    }
    if (terminal.widgetClicked(blue))
    {
      terminal.scroll("Blue clicked");
    }
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  endPage();
}
void checkboxExample()
{
  newPage(F("Checkbox test"));
  red = terminal.newCheckbox(terminal.columns() / 3, 16, 14, 1, F("Red"), COLOUR_RED, SHORTCUT_INLINE);       // Create three new widgets and record the IDs
  green = terminal.newCheckbox(terminal.columns() / 3, 17, 14, 1, F("Green"), COLOUR_GREEN, SHORTCUT_INLINE); // The method returns 0 if it fails
  blue = terminal.newCheckbox(terminal.columns() / 3, 18, 14, 1, F("Blue"), COLOUR_BLUE, SHORTCUT_INLINE);    // Colour is the colour of the frame, lettering can be different
  if (red)
  {
    terminal.labelAttributes(red, COLOUR_RED | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Red widget created"));
    terminal.showWidget(red); // Make this button visible
    terminal.widgetShortcutKey(red, f4Pressed);
  }
  if (green)
  {
    terminal.labelAttributes(green, COLOUR_GREEN | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Green widget created"));
    terminal.showWidget(green); // Make this button visible
    terminal.widgetShortcutKey(green, f5Pressed);
  }
  if (blue)
  {
    terminal.labelAttributes(blue, COLOUR_BLUE | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Blue widget created"));
    terminal.showWidget(blue); // Make this button visible
    terminal.widgetShortcutKey(blue, f6Pressed);
  }
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    if (terminal.widgetClicked(red))
    {
      if (terminal.widgetValue(red))
      {
        terminal.scroll(F("Red checked"));
      }
      else
      {
        terminal.scroll(F("Red unchecked"));
      }
    }
    if (terminal.widgetClicked(green))
    {
      if (terminal.widgetValue(green))
      {
        terminal.scroll(F("Green checked"));
      }
      else
      {
        terminal.scroll(F("Green unchecked"));
      }
    }
    if (terminal.widgetClicked(blue))
    {
      if (terminal.widgetValue(blue))
      {
        terminal.scroll(F("Blue checked"));
      }
      else
      {
        terminal.scroll(F("Blue unchecked"));
      }
    }
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  endPage();
}
void listBoxExample()
{
  newPage(F("List box test"));
  red = terminal.newListBox(1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Red"), COLOUR_RED, OUTER_BOX);                                                                                                                     // Create a window to display the text
  green = terminal.newListBox(terminal.columns() / 3 + 1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Green"), COLOUR_GREEN | ATTRIBUTE_FAINT, OUTER_BOX | LABEL_IN_BOX | LABEL_CENTRED | SHORTCUT_INLINE | BOX_DOUBLE_LINE); // Create a window to display the text
  blue = terminal.newListBox(terminal.columns() * 2 / 3 + 1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, COLOUR_BLUE);                                                                                                           // Create a window to display the text
  if (red)                                                                                                                                                                                                                                                     // The widget ID is zero if it failed to create. This is most likely because the max number of widgets was reached.
  {
    terminal.labelAttributes(red, COLOUR_RED);
    terminal.contentAttributes(red, COLOUR_RED | ATTRIBUTE_BRIGHT);
#if defined(__AVR__)
    terminal.setWidgetContent(red, F("Red Zero\rRed One\rRed Two\rRed Three\rRed Four\rRed Five\rRed Six\rRed Seven\rRed Eight")); // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
#else
    terminal.setWidgetContent(red, F("Red Zero\rRed One\rRed Two\rRed Three\rRed Four\rRed Five\rRed Six\rRed Seven\rRed Eight\rRed Nine\rRed Ten\rRed Eleven\rRed Twelve\rRed Thirteen\rRed Fourteen\rRed Fifteen\rRed Sixteen\rRed Seventeen\rRed Eighteen\rRed Nineteen\rRed Twenty"));                                             // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
#endif
    terminal.widgetShortcutKey(red, f10Pressed);
    terminal.widgetValue(red, 1); // Select option 1
    terminal.showWidget(red);     // All widgets starts as invivisble, so change this to show it
  }
  if (green)
  {
    terminal.labelAttributes(green, COLOUR_GREEN);
    terminal.contentAttributes(green, COLOUR_GREEN | ATTRIBUTE_BRIGHT);
#if defined(__AVR__)
    terminal.setWidgetContent(green, F("Green Zero\rGreen One\rGreen Two\rGreen Three\rGreen Four")); // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
#else
    terminal.setWidgetContent(green, F("Green Zero\rGreen One\rGreen Two\rGreen Three\rGreen Four\rGreen Five\rGreen Six\rGreen Seven\rGreen Eight\rGreen Nine\rGreen Ten\rGreen Eleven\rGreen Twelve\rGreen Thirteen\rGreen Fourteen\rGreen Fifteen\rGreen Sixteen\rGreen Seventeen\rGreen Eighteen\rGreen Nineteen\rGreen Twenty")); // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
#endif
    terminal.widgetShortcutKey(green, f11Pressed);
    terminal.widgetValue(green, 2); // Select option 2
    terminal.showWidget(green);     // All widgets starts as invisible, so change this to show it
  }
  if (blue)
  {
    terminal.contentAttributes(blue, COLOUR_BLUE | ATTRIBUTE_BRIGHT);
#if defined(__AVR__)
    terminal.setWidgetContent(blue, F("Blue Zero\rBlue One\rBlue Two")); // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
#else
    terminal.setWidgetContent(blue, F("Blue Zero\rBlue One\rBlue Two\rBlue Three\rBlue Four"));                                                                                                                                                                                                                                        // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
#endif
    terminal.widgetValue(blue, 3); // Select option 3
    terminal.showWidget(blue);     // All widgets starts as invivisble, so change this to show it
  }
  terminal.scroll("You can scroll through the items and select one. There is no multi-select in this version.");
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    if (terminal.widgetClicked(red))
    {
      terminal.scroll("Red listbox selected, option " + String(terminal.widgetValue(red)));
    }
    if (terminal.widgetClicked(green))
    {
      terminal.scroll("Green listbox selected, option " + String(terminal.widgetValue(green)));
    }
    if (terminal.widgetClicked(blue))
    {
      terminal.scroll("Blue listbox selected, option " + String(terminal.widgetValue(blue)));
    }
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  endPage();
}
void probingExample()
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
void radioButtonExample()
{
  newPage(F("Radio button test"));
  red = terminal.newRadioButton(terminal.columns() / 3 - 1, 15, 16, 5, F("Red"), COLOUR_WHITE, OUTER_BOX | SHORTCUT_INLINE); // Create three new widgets and record the IDs
  green = terminal.newRadioButton(terminal.columns() / 3, 17, 14, 1, F("Green"), COLOUR_WHITE, SHORTCUT_INLINE);             // The method returns 0 if it fails
  blue = terminal.newRadioButton(terminal.columns() / 3, 18, 14, 1, F("Blue"), COLOUR_WHITE, SHORTCUT_INLINE);               // Colour is the colour of the frame, lettering can be different
  if (red)
  {
    terminal.labelAttributes(red, COLOUR_RED | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Red radio button created"));
    terminal.showWidget(red); // Make this button visible
    terminal.widgetShortcutKey(red, f7Pressed);
    terminal.widgetValue(red, true); // Make this button selected at the start. All visible radio buttons are in a single group
  }
  if (green)
  {
    terminal.labelAttributes(green, COLOUR_GREEN | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Green radio button created"));
    terminal.showWidget(green); // Make this button visible
    terminal.widgetShortcutKey(green, f8Pressed);
  }
  if (blue)
  {
    terminal.labelAttributes(blue, COLOUR_BLUE | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Blue radio button created"));
    terminal.showWidget(blue); // Make this button visible
    terminal.widgetShortcutKey(blue, f9Pressed);
  }
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    if (terminal.widgetClicked(red))
    {
      if (terminal.widgetValue(red))
      {
        terminal.scroll(F("Red radio button selected"));
      }
    }
    if (terminal.widgetClicked(green))
    {
      if (terminal.widgetValue(green))
      {
        terminal.scroll(F("Green radio button selected"));
      }
    }
    if (terminal.widgetClicked(blue))
    {
      if (terminal.widgetValue(blue))
      {
        terminal.scroll(F("Blue radio button selected"));
      }
    }
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  endPage();
}
void textDisplayExample()
{
  newPage(F("Text display window test"));
  red = terminal.newTextDisplay(1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Window 1"), COLOUR_RED, OUTER_BOX);                                                                                                                   // Create a window to display the text
  green = terminal.newTextDisplay(terminal.columns() / 3 + 1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Window 2"), COLOUR_GREEN | ATTRIBUTE_FAINT, OUTER_BOX | LABEL_IN_BOX | LABEL_CENTRED | SHORTCUT_INLINE | BOX_DOUBLE_LINE); // Create a window to display the text
  blue = terminal.newTextDisplay(terminal.columns() * 2 / 3 + 1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Window 3"), COLOUR_BLUE, OUTER_BOX | BOX_ASCII);                                                                        // Create a window to display the text
  if (red)
  {
    terminal.labelAttributes(red, COLOUR_RED);
    terminal.contentAttributes(red, COLOUR_RED | ATTRIBUTE_BRIGHT);
    terminal.setWidgetContent(red, textToShow); // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
    terminal.widgetShortcutKey(red, f10Pressed);
    terminal.showWidget(red); // All widgets starts as invisible, so change this to show it
  }
  if (green)
  {
    terminal.setWidgetLabel(green, F("Window 2")); // Another way to add the label
    terminal.labelAttributes(green, COLOUR_GREEN);
    terminal.setWidgetContent(green, textToShow); // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
    terminal.contentAttributes(green, COLOUR_GREEN | ATTRIBUTE_BRIGHT);
    terminal.widgetShortcutKey(green, f11Pressed);
    terminal.showWidget(green); // All widgets starts as invisible, so change this to show it
  }
  if (blue)
  {
    terminal.contentAttributes(blue, COLOUR_BLUE | ATTRIBUTE_BRIGHT);
    terminal.setWidgetContent(blue, textToShow); // The address of the content to show in the window. It MUST remain in scope all the time you want it to be available to show.
    terminal.showWidget(blue);                   // All widgets starts as invisible, so change this to show it
  }
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    if (terminal.widgetClicked(red))
    {
      terminal.scroll(F("Red window selected"));
    }
    if (terminal.widgetClicked(green))
    {
      terminal.scroll(F("Green window selected"));
    }
    if (terminal.widgetClicked(blue))
    {
      terminal.scroll(F("Blue window selected"));
    }
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  endPage();
}
void textInputExample()
{
  newPage(F("Text input field test"));
  red = terminal.newTextInput(terminal.columns() / 4, terminal.lines() / 2 - 2, terminal.columns() / 2, 1, F("Red:"), COLOUR_WHITE | BACKGROUND_COLOUR_RED, SHORTCUT_INLINE);                                                                  // Create three new widgets and record the IDs
  green = terminal.newTextInput(terminal.columns() / 4, terminal.lines() / 2, terminal.columns() / 2, 4, F("Green"), COLOUR_GREEN, OUTER_BOX);                                                                                                 // The method returns 0 if it fails
  blue = terminal.newTextInput(terminal.columns() / 4, terminal.lines() / 2 + 4, terminal.columns() / 2, 5, F("Blue (Password)"), COLOUR_BLUE, OUTER_BOX | BOX_DOUBLE_LINE | LABEL_IN_BOX | LABEL_CENTRED | SHORTCUT_INLINE | PASSWORD_FIELD); // Colour is the colour of the frame, lettering can be different
  if (red)
  {
    terminal.labelAttributes(red, COLOUR_WHITE | ATTRIBUTE_BRIGHT | BACKGROUND_COLOUR_RED); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Red text input field created"));
    terminal.showWidget(red); // Make this widget visible
    terminal.widgetShortcutKey(red, f10Pressed);
    terminal.setWidgetContent(red, F("Red text input")); // Populate the field at the start
  }
  if (green)
  {
    terminal.labelAttributes(green, COLOUR_GREEN | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Green text input field created"));
    terminal.showWidget(green); // Make this widget visible
    terminal.widgetShortcutKey(green, f11Pressed);
    terminal.setWidgetContent(green, F("Green text input")); // Populate the field at the start
  }
  if (blue)
  {
    terminal.labelAttributes(blue, COLOUR_BLUE | ATTRIBUTE_BRIGHT); // Make the label text more emphasised, for better contrast
    terminal.scroll(F("Blue text input field created"));
    terminal.showWidget(blue); // Make this widget visible
    terminal.widgetShortcutKey(blue, f12Pressed);
    terminal.setWidgetContent(blue, F("Blue password input")); // Populate the field at the start
  }
  terminal.scroll(F("Press enter when finished to see the inputs")); // It is for the application to decide what to do with everything that isn't a line editing key
  uint32_t timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    if (terminal.widgetClicked(red))
    {
      terminal.scroll(F("Red text input field selected"));
    }
    if (terminal.widgetClicked(green))
    {
      terminal.scroll(F("Green text input field selected"));
    }
    if (terminal.widgetClicked(blue))
    {
      terminal.scroll(F("Blue text input field selected"));
    }
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  if (red && terminal.contentChanged(red))
  {
    terminal.scroll("Red string changed - " + String(terminal.retrieveContent(red)));
  }
  if (green && terminal.contentChanged(green))
  {
    terminal.scroll("Green string changed - " + String(terminal.retrieveContent(green)));
  }
  if (blue && terminal.contentChanged(blue))
  {
    terminal.scroll("Blue string changed - " + String(terminal.retrieveContent(blue)));
  }
  terminal.deselectWidget(); // Deselect the currently typed in widget, to prevent more typing
  if (red)
  {
    terminal.widgetPassive(red); // Stop the widget being clicked on again
  }
  if (green)
  {
    terminal.widgetPassive(green); // Stop the widget being clicked on again
  }
  if (blue)
  {
    terminal.widgetPassive(blue); // Stop the widget being clicked on again
  }
  terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  if (terminal.keyPressed())
  {
    terminal.readKeypress(); // Gobble up the enter key so the script will wait to show the strings
  }
  timeout = millis();
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  if (terminal.keyPressed())
  {
    terminal.readKeypress(); // Gobble up the keypress so the script will wait for the next page
  }
  endPage();
}
void textLogExample()
{
  newPage(F("Text log window test"));
  red = terminal.newTextLog(1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Window 1"), COLOUR_RED, OUTER_BOX);                                                                                                                   // Create a window to display the text
  green = terminal.newTextLog(terminal.columns() / 3 + 1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Window 2"), COLOUR_GREEN | ATTRIBUTE_FAINT, OUTER_BOX | LABEL_IN_BOX | LABEL_CENTRED | SHORTCUT_INLINE | BOX_DOUBLE_LINE); // Create a window to display the text
  blue = terminal.newTextLog(terminal.columns() * 2 / 3 + 1, terminal.lines() / 2, terminal.columns() / 3, (terminal.lines() - 2) / 2, F("Window 3"), COLOUR_BLUE | ATTRIBUTE_FAINT, OUTER_BOX | BOX_ASCII);                                                      // Create a window to display the text
  if (red)
  {
    terminal.labelAttributes(red, COLOUR_RED);
    terminal.contentAttributes(red, COLOUR_RED | ATTRIBUTE_BRIGHT);
    terminal.widgetShortcutKey(red, f10Pressed);
    terminal.showWidget(red); // All widgets starts as invisible, so change this to show it
  }
  if (green)
  {
    terminal.labelAttributes(green, COLOUR_GREEN);
    terminal.contentAttributes(green, COLOUR_GREEN | ATTRIBUTE_BRIGHT);
    terminal.widgetShortcutKey(green, f11Pressed);
    terminal.showWidget(green); // All widgets starts as invisible, so change this to show it
  }
  if (blue)
  {
    terminal.contentAttributes(blue, COLOUR_BLUE | ATTRIBUTE_BRIGHT);
    terminal.showWidget(blue); // All widgets starts as invisible, so change this to show it
  }
  uint32_t timeout = millis();
  uint32_t randomContentTimer = millis();
  // We will use clicks to show content can be added dynamically to each window
  uint8_t redClicks = 0;
  uint8_t greenClicks = 0;
  uint8_t blueClicks = 0;
  while (millis() - timeout < 30000ul && not terminal.keyPressed())
  {
    if (terminal.widgetClicked(red))
    {
      terminal.scroll(F("Red window selected"));
      terminal.appendWidgetContent(red, ("Red click " + String(redClicks++)).c_str()); // By default appendWidgetContent adds it to the 'end' of the circular buffer, the library manages memory allocation for this.
      // terminal.appendWidgetContent(red, F("Red click"));
    }
    if (terminal.widgetClicked(green))
    {
      terminal.scroll(F("Green window selected"));
      terminal.prependWidgetContent(green, ("Green click " + String(greenClicks++)).c_str()); // By default appendWidgetContent adds it to the 'end' of the circular buffer, the library manages memory allocation for this.
    }
    if (terminal.widgetClicked(blue))
    {
      terminal.scroll(F("Blue window selected"));
      terminal.appendWidgetContent(blue, ("Blue click " + String(blueClicks++)).c_str()); // By default appendWidgetContent adds it to the 'end' of the circular buffer, the library manages memory allocation for this.
    }
    // Generate some random scrolling content
    if (millis() - randomContentTimer > 500)
    {
      randomContentTimer = millis();
      switch (random(4))
      {
      case 1:
        terminal.appendWidgetContent(red, ("Random red " + String(random(1, 100))).c_str());
        break;
      case 2:
        terminal.prependWidgetContent(green, ("Random green " + String(random(1, 100))).c_str());
        break;
      case 3:
        terminal.appendWidgetContent(blue, ("Random blue " + String(random(1, 100))).c_str());
        break;
      }
    }
    terminal.houseKeeping(); // You MUST run housekeeping to show any changes!
  }
  endPage();
}


void setup()
{
  terminal.begin(Serial);                                            // Initialise the library
  terminal.defaultAttributes(BACKGROUND_COLOR_BLACK | COLOUR_WHITE); // Set some initial attributes for printing
  terminal.probeSize();                                              // Attempts to determine how many lines and columns the terminal has
}
void loop()
{
  probingExample();     // Demo methods that 'probe' the terminal, see the tab 'probingDemo' for code
  buttonExample();      // Demo methods for creating and checking the state of button widgets, see the tab 'buttonDemo' for code
  checkboxExample();    // Demo methods for creating and checking the state of checkbox widgets, see the tab 'checkboxDemo' for code
  radioButtonExample(); // Demo methods for creating and checking the state of radio button widgets, see the tab 'radiobuttonDemo' for code
  textDisplayExample(); // Demo methods for creating static content text box widgets, see the tab 'textDisplayDemo' for code
  textLogExample();     // Demo methods for creating 'logging' text box widgets, see the tab 'textLogDemo' for code. This widget does NOT store content long term, it's intended to be a logging/chat window etc.
  listBoxExample();     // Demo methods for creating list box widgets, see the tab 'listBoxExample' for code
  textInputExample();   // Demo methods for creating and retrieving input from text input fields, see the tab 'textInputDemo' for code
}
