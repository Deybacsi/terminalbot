# How to configure your settings

Currently configuration options are only available in the form of direct source code modification.

## Don't panic

There are only 2 configuration files.

1. First login to Binance and generate an API key & secret
2. Rename `apikeys.h.sample` to `apikeys.h`
3. Paste your key & secret
4. See `config.h` for custom bot details

After configuring your bot, you'll need to (re)compile.

## Build  bot:
```
cmake .
make
```

Or you can run `./compile.sh`.

## Run:

```
./terminalbot
```

:)


