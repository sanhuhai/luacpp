#include "luaNumber.h"

int TestLua::counter = 0;

void TestLua::SetName(std::string n)
{
	name = n;
}

std::string TestLua::GetName() const
{
	return name;
}

int TestLua::func(lua_State* L)
{
	lua_pushstring(L, "str1");
	lua_pushstring(L, "str2");
	return 2;
}

void TestLua::Add(int x, int y)
{
	std::cout << "x = " << x << " y = " << y << "  x + y = " << x + y << std::endl;
}

void TestLuaChild::SetName(std::string n)
{
	c_str = n;
}

std::string TestLuaChild::GetName() const
{
	return c_str;
}
