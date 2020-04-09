#ifndef CONFIG_H
#define CONFIG_H

#endif // CONFIG_H


const string    binanceApiKey="1APwdJLU9cIuDMQzCclwCXFbFLKVtyLnLVQGT8OSKmU1C30LvcMq4bKDrXMnC1mq",
                binanceApiSecret="RCC5NpHV16Coe4ojaMu7orwtzPDBFLvOmi90DEHWy72JoTPzBIASxpVoQTtczSMI",
                binanceSymbol="BTCUSDT";

// number of simultaneous trades
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


