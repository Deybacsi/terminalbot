#ifndef CSV_H
#define CSV_H

#endif // CSV_H

struct s_order {
    string symbol;
    long int orderId;
    string clientOrderId;
    long int transactTime;
    float price;
    float origQty;
    float executedQty;
    float cumulativeQuoteQty;
    string status;
    string timeInForce;
    string type;
    string side;
};

void writeToFile (string name, string line) {
    std::ofstream outfile;
    outfile.open( name, std::ios_base::app); // append instead of overwrite
    outfile << line;
    outfile.close();

}

// https://stackoverflow.com/questions/38402800/c-failing-to-parse-csv-into-my-struct
