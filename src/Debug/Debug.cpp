#include "Debug.h"
// #include <retroTerm.h> //Include terminal library
#include <iostream>
#include <string>
#include "Command.h"
#include "pico/stdlib.h"
#include "CLI.h"

namespace debugtools
{
    /*void Debug::initUI()
    {
        terminal.begin(Serial);           // Initialise the library
        terminal.eraseScreen();           // Clear the screen
        terminal.hideCursor();            // Hide the terminal cursor
        terminal.enableMouse();           // Capture the mouse so it can be used with widgets
        terminal.setScrollWindow(17, 20); // Set up somewhere to show the events without disrupting the widget
        widgetSetup();
    }

    void print_click(retroTerm terminal)
    {
        // terminal.scroll("clicked");
        // printf("hi\n");
        terminal.scroll("hii");
    }

    void Debug::widgetSetup()
    {
        int buttonId = terminal.newButton(1, 1, 15, 3, F("Button label"), COLOUR_GREEN, OUTER_BOX | BOX_SINGLE_LINE); // Create a green button in a box
        terminal.widgetShortcutKey(buttonId, f1Pressed);                                                              // Assign a shortcut key of F1
        terminal.showWidget(buttonId);                                                                                // Make the button visible, all widgets start 'invisible' for later display
        widgetIds[buttonId] = &print_click;
    }

    void Debug::updateUI()
    {
        for (auto i : widgetIds)
        {
            if (terminal.widgetClicked(i.first))
            {
                i.second(terminal);
            }
        }
        houseKeeping();
    }

    void Debug::houseKeeping()
    {
        runNextCommand(); // has to be ran first?
        terminal.houseKeeping();
    }*/

    //TODO shuld be private
    void Debug::runNextCommand(){
        if(cli->readUSB()==false) return;
        if(cli->findCommand()==false) return;
        pico::CLI_Cmd* cmd = cli->getNextCommand();
        // cmd->passInDrivers(drivers);
        cmd->Execute();
    }

}