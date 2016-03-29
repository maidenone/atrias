## Why RTTLua? ##

[Performance comparison of Lua and C](https://docs.google.com/viewer?url=http%3A%2F%2Flwn.net%2Fimages%2Fconf%2Frtlws-2011%2Fproc%2FKlotzbuecher.pdf)


## Setup ##

Get started with RTTLua by reading the [Lua Cookbook](http://www.orocos.org/wiki/orocos/toolchain/orocostoolchainluacookbook).

Get RTTLua tab completion [here](https://gitorious.org/orocos-toolchain/rttlua_completion).

Put the following in your ~/.bashrc:
```
# RTTLua
RTTLUA_MODULES=`rospack find ocl`/lua/modules/?.lua
if [ "x$LUA_PATH" == "x" ]; then
    LUA_PATH=";;"
fi
export LUA_PATH="$LUA_PATH;$RTTLUA_MODULES"

# RTTLua tab-completion
export LUA_PATH="$LUA_PATH;`rospack find rttlua_completion`/?.lua"
export LUA_CPATH="$LUA_CPATH;`rospack find rttlua_completion`/?.so"
```

Put the following in your ~/.rttlua:
```
require("rttlib")
rttlib.color=true
require("complete")
```