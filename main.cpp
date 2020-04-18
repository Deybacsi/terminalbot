/*
 * Terminalbot v1.0
 *
 * Simple trading bot using the 7,25,99 moving average (MA) indicators
 * to buy/sell cryptocurrency trading pairs
 *
 * Strategy:
 *
 * If the current price drops below all of the MA indicators               -> buy
 * If the current price rises above them & it's greater than our buy price -> sell
 *
 * You can fine-tune some detailed settings in config.h
 *
*/

#include <iostream>
#include <math.h>
#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/timeb.h>
#include <unistd.h>
#include <vector>
#include <map>
#include <string>
#include <cstring>
#include <sstream>
#include <fstream>
#include <memory>
#include <ctime>
#include <chrono>
#include <thread>
using namespace std;

#include "curl/curl.h"
#include "3rdparty/jsoncpp/include/json/json.h"
#include "3rdparty/jsoncpp/include/json/reader.h"
#include "3rdparty/plog/include/plog/Log.h"

#include "inc/common.h"
#include "apikeys.h"
#include "config.h"
#include "inc/digits.h"
#include "inc/http.h"
#include "inc/screen.h"
#include "inc/binance.h"
#include "inc/tui.h"

#include "inc/timers.h"
#include "inc/csv.h"

// elapsed time counter in msec
int nTimeElapsed =0;


int main(void) {
    system("mkdir logs botdata");
    system("stty raw -echo");
    hideCursor();
    int ch = 0;

    // initialize the screen
    plog::init(plog::debug, "logs/log.txt", 1000000, 30);
    Cscreen screen;
    Ctui tui;
    Cexchange binance;
    Cflags flags;
    Ctimer mytimer;
    screen.init();
    binance.candleLimit=screen.getScreenWidth()+100;
    screen.clearAllLayer(CLEARCHAR);
    cout << "Starting..." << endl;

    // main loop until 3 ESC / x / q pressed
    while(ch!=27 && ch!=113 && ch!=120) {
        int nTimeStart = GetMilliCount();        // for counting milliseconds, needed for screen refresh
        screen.clearAllLayer(CLEARCHAR);
        // call our timer functions
        mytimer.getCurrentPrice(binance,binanceSymbol);
        mytimer.getCandles(binance,binanceSymbol);

        // draw things to screen buffer
        tui.putMenu(screen);
        tui.putStatusBar(screen, statusBarStr);
        tui.drawChart(screen, binance.candleLimit );
        flags.checkFlags();
        tui.drawFlags(screen, flags);
        tui.drawPrice(screen, screen.getScreenWidth()-doubleToString2(currentPrice).length()*DIGITWIDTH, screen.getScreenHeight()-1-DIGITHEIGHT, currentPrice);
        // print out all buffers/layers
        screen.mergeLayers();
        screen.printScreen();

        if (keyPressed()) {
            ch=getchar();
            switch (ch) {
                case 27:
                    getchar(); ch=getchar();
                    switch (ch) {
                    case 27:

                        cout << endl << "ESC" << ch << endl;  // key left
                        exit(0);
                        break;
                    case KEY_LEFT:
                        cout << "Left";
                        break;
                    case KEY_RIGHT:
                        cout << "Right";
                        break;
                    }
                    break;
                case 50:    // 2
                    tui.ma25Visible=!tui.ma25Visible; break;
                case 55:    // 7
                    tui.ma7Visible=!tui.ma7Visible; break;
                case 57:    // 9
                    tui.ma99Visible=!tui.ma99Visible; break;
                case 99:    // c
                    tui.chartVisible=!tui.chartVisible; break;
            }
        }
        // get elapsed time in ms since loop start
        int nTimeElapsed = GetMilliSpan( nTimeStart );
        // wait some ms to have the needed FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS2MILLISEC-nTimeElapsed));
    }
    // restore terminal
    system("stty cooked echo");
    textReset();
    showCursor();
    cout << "Thanks for using Terminalbot :)\n";
    return 0;
}
