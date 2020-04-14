/*

    Useful little functions

*/

#include <algorithm>
#include <iomanip>

using namespace std;

const int KEY_LEFT  = 68;
const int KEY_RIGHT = 67;


// to store the current candle datas -> display
struct s_candles {
    long int openTime;
    long int closeTime;
    double priceLow;
    double priceHigh;
    double priceOpen;
    double priceClose;
    double volume;
    int trades;

};

s_candles candles[500];

// current calculated moving averages
double MA7, MA25, MA99;

// color codes for displaying MAs (codes->screen.h)
short unsigned int  MA7COLOR=10,    // C_LGREEN
                    MA25COLOR=6,    // C_CYAN
                    MA99COLOR=9;    // C_LRED

// to store current price
double currentPrice=0;

// storing bools for checking if we are constantly below/above MAs for the last X candles
const int MAXPRICECHECKWINDOWSIZE=50;
bool    previousPricesBelow[MAXPRICECHECKWINDOWSIZE],
        previousPricesAbove[MAXPRICECHECKWINDOWSIZE];

struct s_trades {
    int priceCheckWindow;
    float minimumProfit;
    float oneTradePrice;
    string buyId;
    string buyTimeStamp;
    float buyQuantity;
    float buyQuote;
    bool buyFilled;
    string sellId;
    string sellTimeStamp;
    float sellQuantity;
    float sellQuote;
    bool sellFilled;
};

struct s_orders {
    string Id;
    string timeStamp;
    float quantity;
    float quote;
    bool filled;
};


double getMA(int avg, int current) {
    int i, sum=0;
    for (i=current-avg; i<current; i++) {
        sum+=candles[i].priceClose;
    }
    return sum/avg;
}

// get milliseconds time
// http://www.firstobject.com/getmillicount-milliseconds-portable-c++.htm

int GetMilliCount()
{
  // Something like GetTickCount but portable
  // It rolls over every ~ 12.1 days (0x100000/24/60/60)
  // Use GetMilliSpan to correct for rollover
  timeb tb;
  ftime( &tb );
  int nCount = tb.millitm + (tb.time & 0xfffff) * 1000;
  return nCount;
}

int GetMilliSpan( int nTimeStart )
{
  int nSpan = GetMilliCount() - nTimeStart;
  if ( nSpan < 0 )
    nSpan += 0x100000 * 1000;
  return nSpan;
}

// return the count of chars available to read
int keyPressed() {
    int i;
    ioctl(0, FIONREAD, &i);
    return i; 
}

string commandToString(string cmd) {
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
      while (!feof(stream))
        if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
          pclose(stream);
      }
    data.erase(std::remove(data.begin(), data.end(), '\n'), data.end());
    return data;
}

string doubleToString2 ( double var ) {
    std::ostringstream streamObj3;

    // Set Fixed -Point Notation
    streamObj3 << std::fixed;

    // Set precision to 2 digits
    streamObj3 << std::setprecision(2);

    //Add double to stream
    streamObj3 << var;

    // Get string from output string stream
    std::string strObj3 = streamObj3.str();
    return strObj3;
}
