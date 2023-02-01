-- require("LuaPanda").start("127.0.0.1",8818)
-- require("socket.core")
-- require("socket.core");
-- require("socket.core")
local game = game
print("game",game)

function test1()
    print("game.TestLua.counter",game.TestLua.counter)
    print("game.TestLua.name",test.name)
    test.name_value = "yanhuayileng"
    print("game.TestLua.name",test.name)
    local sum,aver = average(10,20,30,40,50)
    print("sum",sum)
    print("average",aver)
    print(sum,aver)
end

function lua_test()
    local lua_test = game.TestLua("test.lua")
    print("lua_test",lua_test.name)
end





