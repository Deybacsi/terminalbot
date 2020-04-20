#!/bin/bash

#
# Binance API check
#

SYMBOL="BTCUSDT";

APIURL="https://api.binance.com/api/v3";

# get key & secret from apikeys.h
APIKEY=$(grep binanceApiKey apikeys.h | cut -f2 -d'"' | sed 's/"//');
APISECRET=$(grep binanceApiSecret apikeys.h | cut -f2 -d'"' | sed 's/"//');
CURTIME=$(date +%s%N | cut -b1-13);

clear

echo "Current price for $SYMBOL:"
curl $APIURL/ticker/price?symbol=$SYMBOL
echo -e "\n\n";

echo "Signed query to get open orders for $SYMBOL:"
QUERY="symbol=$SYMBOL&timestamp=$CURTIME";
SIGNATURE=$(echo -n "$QUERY" | openssl dgst -sha256 -hmac "$APISECRET" | cut -f2 -d" ");
curl -H "X-MBX-APIKEY: $APIKEY" "$APIURL/openOrders?$QUERY&signature=$SIGNATURE"
echo -e "\n\n";

