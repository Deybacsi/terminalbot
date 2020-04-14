#ifndef CONFIG_H
#define CONFIG_H

#endif // CONFIG_H

/* FIRST setup your API keys
 *
 * rename apikeys.h.sample to apikeys.h
 *
 * and paste your API key & API secret
 */

// the trading pair

const string    binanceSymbol="BTCUSDT";

/* number of **simultaneous** trades maintained by the bot
 *
 * this value sets how much separate orders can the bot play with
 * you can setup all of them differently -> see s_trades trades[MAXACTIVETRADES] below
 *
 *
 */
const int       MAXACTIVETRADES=1;

/* the last X candles to check to see if we are constantly below/above MAs
 *
 * lower value means quicker reactions to market price moves
 * higher value means *possible* bigger profits
 */

const int       PRICECHECKWINDOWSIZE=5;

/* minimum profit for selling - in percent -> 1 = 1%
 *
 * bot will not sell until price reaches this amount of gain
 *
 * sell price = buy price + MINIMUMPROFIT %
 */

const float     MINIMUMPROFIT=1;


/* how much will you trade at one time
 *
 * for eg. if you want to trade BTC/USDT , ONETRADEPRICE defines how much USDT the bot can spend at once for buying BTC
 *
 * example:
 * ONETRADEPRICE=10
 *
 * 1 - buy BTC for 10 USDT
 * 2 - watch market, and try to sell it at higher price than buy
 * 3 - at sell we will get ~ ONETRADEPRICE+(ONETRADEPRICE * MINIMUMPROFIT/100)  =>  ~10.1 USDT (minus exchange fees!!)
 * 4 - rinse, repeat
 */

const float     ONETRADEPRICE=10;

/* below you can specify your separate trade "threads" (amount = MAXACTIVETRADES)
 *
 * you can specify different options for each one
 *
 * for e.g. one can trade quickly with small amounts
 * Sample:
 * BTC/USDT with 15min candles
 * - PRICECHECKWINDOWSIZE=1, MINIMUMPROFIT=0.5, ONETRADEPRICE=10
 *   bot will buy BTC instantly when price drops below MAs (1*15min), for 10 USDT, and try to get 0.5% profit
 *
 * another one could be setup to wait more and trade larger amounts
 * - PRICECHECKWINDOWSIZE=5, MINIMUMPROFIT=2, ONETRADEPRICE=100
 *   wait 5*15min, buy for 100 USDT with 2% profits
 *
 * change only the first 3 values, the other ones are overwritten by bot later
 *
 */

s_trades trades[MAXACTIVETRADES] = {
    {
        PRICECHECKWINDOWSIZE,
        MINIMUMPROFIT,
        ONETRADEPRICE,
        "", "", 0, 0, false,
        "", "", 0, 0, false
    }
};
