#ifndef BINANCE_H
#define BINANCE_H

#endif // BINANCE_H




class Cexchange {
    private:
        string apiUrl="https://api.binance.com/api/v3/";

    public:

        string  candleInterval  = "15m";
        int     candleLimit     = 77;


        // what should be this? :D
        double getCurrentPrice(string symbol) {
            try {
                Json::Value resp=simpleCurl(apiUrl,"ticker/price?symbol="+symbol);
                return stod(resp["price"].asString());
            } catch (...) { // the worst exception handling ever ! :o
                // TODO!
                return 0;
            }

        }

        // get previous price candle datas - set by candleInterval & candleLimit
        void getCandles(string symbol) {
            unsigned int i;

            Json::Value resp=simpleCurl(apiUrl,"klines?symbol="+symbol+"&interval="+candleInterval+"&limit="+to_string(candleLimit));

            for (i=0; i<resp.size(); i++) {
                //store candle datas
                candles[i]= {
                    stoll(resp[i][0].asString()),stoll(resp[i][6].asString()),stod(resp[i][3].asString()),
                    stod(resp[i][2].asString()),stod(resp[i][1].asString()),stod(resp[i][4].asString()),
                    stod(resp[i][7].asString()),stoi(resp[i][8].asString())
                };
            }
        }

        // sign an API request query with the API secret
        string signQuery(string query) {
            string signature=commandToString("echo -n '"+query+"' | openssl dgst -sha256 -hmac '"+binanceApiSecret+"' | cut -f2 -d' '");
            return signature;
        }

        void getActiveOrders(string symbol) {
            string query="symbol="+symbol+"&timestamp="+to_string(getTimeStamp());
            string signedQuery=signQuery(query);

            Json::Value resp=simpleCurl(apiUrl,"openOrders?"+query+"&signature="+signedQuery);
            //cout << resp;

        }
};

class Cflags {
    public:
        bool    priceBelowMa7,
                priceBelowMa25,
                priceBelowMa99,
                priceAboveMa7,
                priceAboveMa25,
                priceAboveMa99,
                priceAboveAll,
                priceBelowAll,
                priceConstantAbove,
                priceConstantBelow,
                timeToBuy,
                timeToSell;
        int     priceConstantAboveCount,
                priceConstantBelowCount;

        // initial values
        int     priceCheckWindowSize;
        float   minimumProfit;

        void checkFlags() {
            int i;
            priceAboveMa7 = currentPrice > MA7;
            priceAboveMa25= currentPrice > MA25;
            priceAboveMa99= currentPrice > MA99;
            priceBelowMa7 = currentPrice < MA7;
            priceBelowMa25= currentPrice < MA25;
            priceBelowMa99= currentPrice < MA99;
            priceBelowAll = currentPrice !=0 && currentPrice < MA7 && currentPrice < MA25 && currentPrice < MA99 ;
            priceAboveAll = currentPrice !=0 && currentPrice > MA7 && currentPrice > MA25 && currentPrice > MA99;
            priceConstantBelowCount=0;
            for (i=0; i<priceCheckWindowSize; i++ ) {
                priceConstantBelowCount+=previousPricesBelow[MAXPRICECHECKWINDOWSIZE-i-1] ? 1 : 0;
            }
            priceConstantBelow= priceConstantBelowCount==priceCheckWindowSize;
            priceConstantAboveCount=0;
            for (i=0; i<priceCheckWindowSize; i++ ) {
                priceConstantAboveCount+=previousPricesAbove[MAXPRICECHECKWINDOWSIZE-i-1] ? 1 : 0;
            }
            priceConstantAbove= priceConstantAboveCount==priceCheckWindowSize;
        }
};
