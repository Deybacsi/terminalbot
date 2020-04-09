#ifndef TIMERS_H
#define TIMERS_H

#endif // TIMERS_H

// current price checking interval in ms
const int   PRICECHECKINTERVAL  = 1100,
            CANDLECHECKINTERVAL = 10000;

class Ctimer {
private:
    int currentMilliSecs    = 0,    // current ms epoch
        lastPriceCheckTime  = 0,    // last current price checked
        lastCandleCheckTime = 0;    // last candle check


public:
    void getCurrentPrice(Cexchange &exch, string symbol) {
        double priceResponse;
        currentMilliSecs=GetMilliCount();
        if (currentMilliSecs > lastPriceCheckTime + PRICECHECKINTERVAL) {
            priceResponse=exch.getCurrentPrice(symbol);
            if (priceResponse !=0) {
                currentPrice=priceResponse;
            }
            lastPriceCheckTime=GetMilliCount();
        }
    }

    void getCandles(Cexchange &exch, string symbol) {
        currentMilliSecs=GetMilliCount();
        if (currentMilliSecs > lastCandleCheckTime + CANDLECHECKINTERVAL) {
            exch.getCandles(symbol);
            lastCandleCheckTime=GetMilliCount();
        }
    }
};
