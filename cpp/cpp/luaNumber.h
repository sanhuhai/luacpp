#pragma once
#include <iostream>
#include <string>
#ifdef __cplusplus
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "LuaBridge/LuaBridge.h"
#else
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
#include "LuaBridge/LuaBridge.h"
}
#endif // __cplusplus

class TestLua {
public:
	TestLua() { name = "yanhuayileng"; };
	TestLua(std::string n):name(n){}
	void SetName(std::string n);
	std::string GetName() const;
	int func(lua_State* L);
	std::string name;
	void Add(int x, int y);
	static int counter;
private:
	
};

class TestLuaChild : public TestLua
{
public:
	TestLuaChild(std::string f, std::string c) :TestLua(f), c_str(c) {};
	void SetName(std::string n);
	std::string GetName() const;
	std::string c_str;
private:
	
};