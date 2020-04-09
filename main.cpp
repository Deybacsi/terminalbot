/*
#include <iostream>

#include "3rdparty/cpp-httplib/httplib.h"
#include "3rdparty/json/single_include/nlohmann/json.hpp"

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
#include "config.h"
#include "3rdparty/plog/include/plog/Log.h"
#include "inc/common.h"

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
    //system("stty raw");
    int ch = 0;

    // initialize the screen
    plog::init(plog::debug, "logs/log.txt", 1000000, 30);
    Cscreen screen;
    Ctui tui;
    Cexchange binance;
    Cflags flags;

    Ctimer mytimer;
    //string json=simpleCurl("https://api.binance.com/api/v3/","ticker/price?symbol=BTCUSDT");
    //Document d;
    //d.Parse(json);

    //jute::jValue jsonn;

    screen.init();
    binance.candleLimit=screen.getScreenWidth()+100;
    screen.clearAllLayer(CLEARCHAR);
    cout << "ok" << endl;
    //cout << time(0);
    //cout << commandToString("ls -la");
    cout << to_string(binance.getCurrentPrice(binanceSymbol));
//exit(0);
    // main loop until 3 ESC / x / q pressed
    while(ch!=27 && ch!=113 && ch!=120) {
        int nTimeStart = GetMilliCount();
        screen.clearAllLayer(CLEARCHAR);
        //currentPrice=binance.getCurrentPrice(binanceSymbol);

        mytimer.getCurrentPrice(binance,binanceSymbol);
        mytimer.getCandles(binance,binanceSymbol);
        tui.putStatusBar(screen, statusBarStr);
        tui.putMenu(screen);
        tui.drawChart(screen, binance.candleLimit );
        flags.checkFlags();
        tui.drawFlags(screen, flags);

        if (keyPressed()) {

            ch=getchar();
            switch (ch) {

            //if (ch==27) {
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

        //screen.charXy(4,10,5, { "▀" , 0,1, false, false, false } );
        //screen.stringXy(3,10,7, { " " , 0,1, false, false, false },  commandToString("date +%s") );
        //screen.stringXy(3,10,9, { " " , 0,1, false, false, false },  to_string(currentPrice) );
        //tui.drawDigit(screen, 3, 15,15,2, { "a" , 2,0, false, false, false });
        tui.drawPrice(screen, screen.getScreenWidth()-doubleToString2(currentPrice).length()*DIGITWIDTH, screen.getScreenHeight()-1-DIGITHEIGHT, currentPrice);
        //screen.stringXy(3,10,9, { " " , 0,1, false, false, false }, " commandToString('date +%s')" );
        //gotoXy(0,0);
        //cout << "EZ";

        screen.mergeLayers();
        screen.printScreen();



        //usleep(FPS2NANOSEC);
        // get elapsed time in ms
        int nTimeElapsed = GetMilliSpan( nTimeStart );
        // wait some ms to have the needed FPS
        std::this_thread::sleep_for(std::chrono::milliseconds(FPS2MILLISEC-nTimeElapsed));



    }

    system("stty cooked echo");
    cout << "end";

    return 0;
}
