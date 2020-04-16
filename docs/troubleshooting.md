# Troubleshooting

### No price data shown after start

Please check the `logs/log.txt` file.
```
$ tail logs/log.txt

2020-04-15 17:43:13.776 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:14.974 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:16.169 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:17.388 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:18.619 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:19.778 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:21.000 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:21.993 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/klines?symbol=BTCUSDT&interval=15m&limit=311
2020-04-15 17:43:22.193 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
2020-04-15 17:43:23.400 ERROR [13488] [simpleCurl@59] simpleCurl ERROR! HTTP 0 - URL: https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT
```

If there are lots of HTTP 0 errors, the bot can't reach the exchange API endpoint, you should check your internet connection.

You can test if the endpoint is reachable with curl:

```
$ curl https://api.binance.com/api/v3/ticker/price?symbol=BTCUSDT

{"symbol":"BTCUSDT","price":"7044.54000000"}
```

or

```
$ curl https://api.binance.com

<!DOCTYPE html><html><head><title>Test OK</title></head><body></body></html>
```

### Bot seems 'stuck', no price and chart updates on screen

Please check the log, and internet connection, as above.
