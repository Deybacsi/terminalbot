#ifndef TUI_H
#define TUI_H

#endif // TUI_H

using namespace std;

const s_simplechar PRICECHAR={ " " , 2,0, false, false, false };

const int PRICELAYER = 3;

string statusBarStr = "";

class Ctui {

    private:
        // colors & attributes
        s_simplechar STATUSBAR = { " ", 4, 7, false, false, false};
        int STATUSBAR_LAYER = 0;

    public:
        // chart display toggles
        bool    ma7Visible=true,
                ma25Visible=true,
                ma99Visible=true,
                chartVisible=true;
        int     chartBottom;

        void putStatusBar(Cscreen &screen, string statusstr) {
            screen.lineXy(STATUSBAR_LAYER, 0, screen.getScreenHeight()-1, screen.getScreenWidth(), screen.getScreenHeight()-1, STATUSBAR);
            screen.stringXy(STATUSBAR_LAYER, 1, screen.getScreenHeight()-1, STATUSBAR, statusstr);
        }
        void putMenuBar(Cscreen &screen, string menustr) {
            screen.lineXy(STATUSBAR_LAYER, 0, 0, screen.getScreenWidth(), 0, STATUSBAR);
            screen.stringXy(STATUSBAR_LAYER, 1, 0, STATUSBAR, menustr);
        }
        void putMenu(Cscreen &screen) {
            string menustr=" Toggle MA: 7,2,9 | Toggle chart: c | Quit: q";
            putMenuBar(screen, menustr);
        }


        void drawDigit(Cscreen &screen, int layer, int px, int py, int digit, s_simplechar chr ) {
            int x,y;
            for (y=0; y<DIGITHEIGHT; y++) {
                for (x=0; x<DIGITHEIGHT; x++) {
                    chr.chr=DIGITS[ACTDIGITDESIGN][digit][y][x];
                    //screen.stringXy(layer,px+x,py+y,chr,DIGITS[ACTDIGITDESIGN][digit][y][x]);
                    screen.charXy(layer, px+x, py+y, chr);

                }
            }
        }

        // big price display
        void drawPrice(Cscreen &screen, int x, int y, double price) {
            string pricestr = doubleToString2(price);
            unsigned int i, digitNo;
            //screen.stringXy(3,10,30, { " " , 2,0, false, false, false },  to_string(price) );
            for (i=0; i<pricestr.length(); i++) {
                if (isdigit(pricestr[i])) {
                    digitNo=((int)pricestr[i])-48;
                } else {
                    digitNo=10;
                }
                drawDigit(screen, PRICELAYER , x + i*DIGITWIDTH,y, digitNo , PRICECHAR );
            }
        }

        // draw the chart and calculate important indicators
        void drawChart(Cscreen &screen, int candleLimit){
            int chartTop=1;
            chartBottom = (int)((screen.getScreenHeight()-2)/3*2 + 0.5);

            int     charRange=chartBottom-chartTop;         // how many chars we have vertically for chart
            int     i,j,currentX;
            int     priceMaxX, priceMinX;                   // X coords for writing out price min/max to chart
            double  priceMin=1000000, priceMax=0;           // min & max prices
            int     priceMinIndex, priceMaxIndex;           // indexes in candles[] for min&max
            double  fromY, toY;                             // for drawing direction of price changes
            short unsigned int candleColor;                 // C_RED or C_GREEN
            const int CHARTWIDTHOFFSET=14;                  // blank area size on right
            int prevMA7charY, prevMA25charY, prevMA99charY;   // used for MA curves display
            int MA7charY, MA25charY, MA99charY;
            string MAstr="⋯";


            // find min and max prices
            for (i=candleLimit-screen.getScreenWidth()+CHARTWIDTHOFFSET; i<candleLimit; i++) {
                // setup candle min&max for chart
                if ( candles[i].priceLow  < priceMin) { priceMin = candles[i].priceLow;  priceMinIndex=i;  }
                if ( candles[i].priceHigh > priceMax) { priceMax = candles[i].priceHigh; priceMaxIndex=i; }
            }

            // range between the lowest and the highest price
            double  priceRange=priceMax-priceMin,
                    // one charachter height's price
                    charHeightPrice=priceRange/charRange;

            const int HORZLINES=4;
            // horizontal lines
            double horzLinePrice;
            double  horzLineDistance    =charRange/(HORZLINES+1);
            double horzLinePriceDistance=priceRange/(HORZLINES+1);
            for (i=1;i<=HORZLINES+1; i++) {
                for (j=0; j<screen.getScreenWidth()-CHARTWIDTHOFFSET; j+=4) {
                    screen.charXy(0,j,(int)(i*horzLineDistance+0.5),{ "╴" , C_DGRAY,0, false, false, false } );
                }
                horzLinePrice=priceMax-i*horzLinePriceDistance+charHeightPrice*1.5;
                screen.stringXy(0,screen.getScreenWidth()-doubleToString2(horzLinePrice).length()-1,
                          (int)(i*horzLineDistance+0.5),
                          { " " , C_DGRAY,0, false, false, false }, doubleToString2(horzLinePrice) );
            }

            // main loop
            for (i=candleLimit-screen.getScreenWidth()+CHARTWIDTHOFFSET; i<candleLimit; i++) {
                // current X coord on screen
                currentX=i-(candleLimit-screen.getScreenWidth()+CHARTWIDTHOFFSET);
                if (chartVisible) {
                    // draw candle |
                    for (j=chartBottom-(int)((candles[i].priceHigh-priceMin)/charHeightPrice+0.5); j<=chartBottom-(int)((candles[i].priceLow-priceMin)/charHeightPrice+0.5); j++ ) {
                        screen.charXy(0,currentX,j,{ "│" , C_DGRAY,0, false, false, false } );
                    }

                    // price down
                    if (candles[i].priceOpen-candles[i].priceClose >= 0) {
                        fromY=candles[i].priceOpen; toY=candles[i].priceClose; candleColor=C_RED;
                    } else {
                        // price up
                        fromY=candles[i].priceClose; toY=candles[i].priceOpen; candleColor=C_GREEN;
                    }
                    // draw candle body
                    for (j=chartBottom-(int)((fromY-priceMin)/charHeightPrice+0.5); j<=chartBottom-(int)((toY-priceMin)/charHeightPrice+0.5); j++ ) {
                        screen.charXy(4,currentX,j,{ "▉" , candleColor,0, false, false, false } );
                    }

                    // get max price X coord for later output
                    if (i==priceMaxIndex) {
                        priceMaxX=currentX-doubleToString2(priceMax).length()-1;
                        if (priceMaxX < 0) { priceMaxX=currentX+1; }
                    }
                    // min price
                    if (i==priceMinIndex) {
                        priceMinX=currentX-doubleToString2(priceMin).length()-1;
                        if (priceMinX < 0) { priceMinX=currentX+1; }
                    }
                }




                //calc & draw moving averages

                // TODO: change shitty MA spaghetti below

                MA7=getMA(7,i);
                MA25=getMA(25,i);
                MA99=getMA(99,i);
                if (ma7Visible) {
                    MAstr="⋯";
                    prevMA7charY=MA7charY;
                    MA7charY=chartBottom-(int)((MA7-priceMin)/charHeightPrice+0.5);
                    if (MA7charY<chartBottom && MA7charY>1 ) {
                        if (prevMA7charY > MA7charY) { MAstr="⋰"; screen.charXy(3,currentX-1,prevMA7charY,{ MAstr, MA7COLOR,0, false, false, false } ); }
                        if (prevMA7charY < MA7charY) { MAstr="⋱"; screen.charXy(3,currentX-1,prevMA7charY,{ MAstr, MA7COLOR,0, false, false, false } ); }

                        screen.charXy(3,currentX,MA7charY,{ MAstr , MA7COLOR,0, false, false, false } );
                    }
                }
                if (ma25Visible) {
                    MAstr="⋯";
                    prevMA25charY=MA25charY;
                    MA25charY=chartBottom-(int)((MA25-priceMin)/charHeightPrice+0.5);
                    if (MA25charY<chartBottom && MA25charY>1) {
                        if (prevMA25charY > MA25charY) { MAstr="⋰"; screen.charXy(2,currentX-1,prevMA25charY,{ MAstr, MA25COLOR,0, false, false, false } ); }
                        if (prevMA25charY < MA25charY) { MAstr="⋱"; screen.charXy(2,currentX-1,prevMA25charY,{ MAstr, MA25COLOR,0, false, false, false } ); }
                        screen.charXy(2,currentX,MA25charY,{ MAstr, MA25COLOR,0, false, false, false } );
                    }
                }
                if (ma99Visible) {
                    MAstr="⋯";
                    prevMA99charY=MA99charY;
                    MA99charY=chartBottom-(int)((MA99-priceMin)/charHeightPrice+0.5);
                    if (MA99charY<chartBottom && MA99charY>1) {
                        if (prevMA99charY > MA99charY) { MAstr="⋰"; screen.charXy(1,currentX-1,prevMA99charY,{ MAstr, MA99COLOR,0, false, false, false } ); }
                        if (prevMA99charY < MA99charY) { MAstr="⋱"; screen.charXy(1,currentX-1,prevMA99charY,{ MAstr, MA99COLOR,0, false, false, false } ); }
                        screen.charXy(1,currentX,MA99charY,{ MAstr, MA99COLOR,0, false, false, false } );
                    }

                }

                // setup the indicators if we are constantly above/below the MAs
                if (i>=candleLimit-MAXPRICECHECKWINDOWSIZE) {
                    previousPricesBelow[i-(candleLimit-MAXPRICECHECKWINDOWSIZE)]=candles[i].priceClose < MA7 && candles[i].priceClose < MA25 && candles[i].priceClose < MA99;
                    previousPricesAbove[i-(candleLimit-MAXPRICECHECKWINDOWSIZE)]=candles[i].priceClose > MA7 && candles[i].priceClose > MA25 && candles[i].priceClose > MA99;


                }


            }
            // write out min/max price
            screen.stringXy(4,priceMaxX,chartTop
                            , { " " , C_GRAY,0, false, false, false }, doubleToString2(priceMax) );
            screen.stringXy(4,priceMinX,chartBottom-1
                            , { " " , C_GRAY,0, false, false, false }, doubleToString2(priceMin) );

            // write MA indicators at right
            screen.stringXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET+1,
                            chartBottom-(int)((MA7-priceMin)/charHeightPrice+0.5),
                            { " " , MA7COLOR, 0, false, false, false }, "MA7" );

            screen.stringXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET+1,
                            chartBottom-(int)((MA25-priceMin)/charHeightPrice+0.5),
                            { " " , MA25COLOR, 0, false, false, false }, "MA25" );
            screen.stringXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET+1,
                            chartBottom-(int)((MA99-priceMin)/charHeightPrice+0.5),
                            { " " , MA99COLOR, 0, false, false, false }, "MA99" );


            // bottom lines
            for (i=0; i<screen.getScreenWidth(); i++) {
                screen.charXy(4,i,chartBottom,{ "━" , C_GRAY,0, false, false, false } );
                screen.charXy(4,i,chartBottom+2,{ "━" , C_GRAY,0, false, false, false } );
            }
            screen.charXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET-MAXPRICECHECKWINDOWSIZE-1,chartBottom,{ "┫" , C_GRAY ,0, false, false, false } );
            screen.charXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET                       ,chartBottom,{ "┣" , C_GRAY ,0, false, false, false } );

            screen.charXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET-MAXPRICECHECKWINDOWSIZE-1,chartBottom+2,{ "┫" , C_GRAY ,0, false, false, false } );
            screen.charXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET                       ,chartBottom+2,{ "┣" , C_GRAY ,0, false, false, false } );

            // write out MA values
            screen.stringXy(4,1,chartBottom+1,
                { " " , MA7COLOR,0, false, false, false }, "MA7: "+doubleToString2(MA7) );
            screen.stringXy(4,18,chartBottom+1,
                { " " , MA25COLOR,0, false, false, false }, "MA25: "+doubleToString2(MA25) );
            screen.stringXy(4,36,chartBottom+1,
                { " " , MA99COLOR,0, false, false, false }, "MA99: "+doubleToString2(MA99) );

            // draw arrows above chart
            for (i=0; i<MAXPRICECHECKWINDOWSIZE; i++) {
                screen.charXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET-MAXPRICECHECKWINDOWSIZE+i,
                    chartBottom+2,{ previousPricesBelow[i] ? "🡇" : "┈" ,
                    (short unsigned int) (previousPricesBelow[i] ? C_RED : C_DGRAY),0, false, false, false } );
                screen.charXy(4,screen.getScreenWidth()-CHARTWIDTHOFFSET-MAXPRICECHECKWINDOWSIZE+i,
                    chartBottom,{ previousPricesAbove[i] ? "🡅" : "┈" ,
                    (short unsigned int) (previousPricesAbove[i] ? C_GREEN : C_DGRAY),0, false, false, false } );
            }
            // current price
            screen.stringXy(4,screen.getScreenWidth()-doubleToString2(currentPrice).length()-1,
                            chartBottom-(int)((currentPrice-priceMin)/charHeightPrice+0.5)
                            , { " " , C_GREEN,0, false, false, false }, doubleToString2(currentPrice) );


            //statusBarStr=to_string(priceMin)+"-"+to_string(priceMax)+"-"+to_string(candles[100].priceLow)+" - "+to_string(priceMaxIndex);
        }

        void drawFlags(Cscreen &screen, Cflags flags[]) {
            int chartBottom = (int)((screen.getScreenHeight()-2)/3*2 + 0.5);
            int i;
            screen.stringXy(4,1,chartBottom+3,
                { " " , C_WHITE,0, false, false, false }, "Current:" );
            screen.stringXy(4,1,chartBottom+4,
                { " " , C_GRAY,0, false, false, false }, "Above:" );
            screen.stringXy(4,14,chartBottom+4,
                { " " , MA7COLOR,0, false, false, false }, flags[0].priceAboveMa7 ? "MA7" : "   " );
            screen.stringXy(4,18,chartBottom+4,
                { " " , MA25COLOR,0, false, false, false }, flags[0].priceAboveMa25 ? "MA25" : "    " );
            screen.stringXy(4,23,chartBottom+4,
                { " " , MA99COLOR,0, false, false, false }, flags[0].priceAboveMa99 ? "MA99" : "    " );
            screen.charXy(4,28,chartBottom+4,
                { flags[0].priceAboveAll ? "✔️" : " " , C_GREEN ,0, false, false, false });
            screen.stringXy(4,1,chartBottom+5,

                { " " , C_GRAY,0, false, false, false }, "Below:" );
            screen.stringXy(4,14,chartBottom+5,
                { " " , MA7COLOR,0, false, false, false }, flags[0].priceBelowMa7 ? "MA7" : "   " );
            screen.stringXy(4,18,chartBottom+5,
                { " " , MA25COLOR,0, false, false, false }, flags[0].priceBelowMa25 ? "MA25" : "    " );
            screen.stringXy(4,23,chartBottom+5,
                { " " , MA99COLOR,0, false, false, false }, flags[0].priceBelowMa99 ? "MA99" : "    " );

            screen.charXy(4,28,chartBottom+5,
                { flags[0].priceBelowAll ? "✔️" : " " , C_GREEN ,0, false, false, false });

            for (i=chartBottom+3; i<chartBottom+6;i++) {
                screen.charXy(4,30,i,
                    { "┊" , C_GRAY,0, false, false, false } );
            }
            screen.stringXy(4,31,chartBottom+3,
                { " " , C_WHITE,0, false, false, false }, "Last" );
/*
            screen.stringXy(4,31,chartBottom+4,
                { " ", (unsigned short int) (flags[i].priceConstantAbove ? C_GREEN : C_GRAY) ,0, false, false, false },
                flags[i].priceConstantAbove ? "Constant" : " Wait:" );
            screen.stringXy(4,31,chartBottom+5,
                { " ", (unsigned short int) (flags[i].priceConstantBelow ? C_GREEN : C_GRAY) ,0, false, false, false },
                flags[i].priceConstantBelow ? "Constant" : " Wait:" );
     */
            for (i=0; i< MAXACTIVETRADES; i++) {

                screen.stringXy(4,36+i*4,chartBottom+3,
                    { " " , C_WHITE,0, false, false, false }, to_string(flags[i].priceCheckWindowSize) );

                screen.stringXy(4,36+i*4,chartBottom+4,
                    { " ", (unsigned short int) (flags[i].priceConstantAbove ? C_GREEN : C_GRAY) ,0, false, false, false },
                    flags[i].priceConstantAbove ? to_string(flags[i].priceConstantAboveCount) : to_string(flags[i].priceConstantAboveCount) );
                screen.stringXy(4,36+i*4,chartBottom+5,
                    { " ", (unsigned short int) (flags[i].priceConstantBelow ? C_GREEN : C_GRAY) ,0, false, false, false },
                    flags[i].priceConstantBelow ? to_string(flags[i].priceConstantBelowCount) : to_string(flags[i].priceConstantBelowCount) );
            }
        }

};
