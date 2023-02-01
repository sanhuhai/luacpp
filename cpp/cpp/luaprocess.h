#pragma once
#include <iostream>
#include <string>
#include <functional>

#if __cplusplus
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
#else
extern "C" {
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#endif

#include "LuaBridge/LuaBridge.h"

int lua_pross_g_var;
static float lua_pross_s_var;

std::string lua_pross_g_string;
std::string getString() { return lua_pross_g_string; }
void setString(std::string s) { lua_pross_g_string = s; }

int foo() { return 42; }
void bar(char const*) { std::cout << __FUNCTION__ << std::endl; }
int cFunc(lua_State* L) { 
	lua_pushstring(L, "hello");
	lua_pushstring(L, "world");
	return 2; 
}

void signin() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	luabridge::Namespace x = luabridge::getGlobalNamespace(L);
	x.beginNamespace("pro")
		.addFunction("foo", foo)
		.addFunction("bar", bar)
		.addFunction("func", cFunc)
		.addProperty("g_string", &lua_pross_g_string)
		.addProperty("g_var", &lua_pross_g_var)
		.addProperty("s_var", &lua_pross_s_var)
		.addProperty("g_value", getString, setString)
		.addVariable("g_var_r", &lua_pross_g_var, false)
	.endNamespace();
	luaL_dofile(L, R"(../../luacode/test1.lua)");
	lua_close(L);
	std::cout << R"(c++ print)" << std::endl;
	std::cout << lua_pross_g_var << std::endl;
	std::cout << lua_pross_g_string << std::endl;
	std::cout << lua_pross_s_var << std::endl;
}

void printLuaInfo(lua_State* L)
{
	for (auto i = 1; i <= lua_gettop(L); ++i)
	{
		std::string str;
		switch (lua_type(L, i))
		{
		case LUA_TSTRING:
			std::cout << lua_tostring(L, i) << std::endl;
			break;
		case LUA_TNUMBER:
			std::cout << lua_tonumber(L, i) << std::endl;
			break;
		case LUA_TBOOLEAN:
			str = lua_toboolean(L, i) ? R"(true)" : R"(false)";
			std::cout << str << std::endl;
			break;
		case LUA_TNIL:
			std::cout << "nil" << std::endl;
			break;
		case LUA_TFUNCTION:
			str = "function";
		case LUA_TTABLE:
			str = "table";
		case LUA_TUSERDATA:
			str = "userdata";
		case LUA_TTHREAD:
			
			std::cout << str << std::endl;
			break;
		default:
			return;
		}
	}
	std::cout << std::endl << std::endl;
}

int f(lua_State*L) {
	std::cout << "hello world yanhuayileng" << std::endl;
	return 0;
}

void testLuaP()
{
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	printLuaInfo(L);
	lua_pushstring(L,"yanhuayileng");
	printLuaInfo(L); 
	lua_pushnil(L);
	printLuaInfo(L);
	lua_pushnumber(L,1000);
	printLuaInfo(L);
	lua_pushcfunction(L,f);
	printLuaInfo(L); 
	lua_pushvalue(L, -4);
	printLuaInfo(L);
}