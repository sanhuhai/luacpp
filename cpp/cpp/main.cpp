#include "head.h"
#include <fstream>
#include <sstream>
#include <string>
#ifdef __cplusplus
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
//#include "luasocket.h"
#else
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
//#include "luasocket.h"
}
#endif // __cplusplus

#include "luaNumber.h"
#include "luaprocess.h"



void readFile(const std::string& fileNmae) 
{
	const char* filename = fileNmae.c_str();
	std::ifstream ifs;
	ifs.open(filename, std::ios::in | std::ios::binary);
	char* arr = new char[1024];
	std::string ss;
	while (getline(ifs, ss)) {
		/*::memccpy(arr, ss.c_str(), sizeof(char), ss.length());
		std::cout << arr;*/
		for (size_t i = 0; i < ss.length(); i++)
		{
			printf("%c", ss[i]%128);
		}
		//std::cout << ss.c_str();
	}
	ifs.close();

}

int average(lua_State* L)
{
	// lua_gettop(L):取出栈顶的索引值,此时就是栈内的元素个数
	int n = lua_gettop(L);
	int sum = 0;
	for (size_t i = 1; i <= n; i++)
	{
		sum += lua_tonumber(L, i);
	}
	lua_pushnumber(L, sum / n);
	lua_pushnumber(L, sum);
	return 2;
}

void testLua()
{
	lua_State* l = luaL_newstate();
	luaL_openlibs(l);
	//luaL_dostring(l, R"(print("Hello world"))");
	lua_register(l, "average", average);
	luaL_dofile(l, R"(../../luacode/test.lua)");
	
	lua_close(l);
}

void testCore() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	std::string str = R"(
		-- require("socket.core");
		-- require("socket.core")
		print("lua begin");
		local sum,aver = average(10,20,30,40,50)
		print("sum",sum)
		print("average",aver)
	)";
	luaL_dostring(L, str.c_str());
	lua_close(L);
}

//void testLuasocket(char* name)
//{
//	lua_State* L = luaL_newstate();
//	luaopen_base(L);
//	luaL_openlibs(L);
//
//	luaopen_socket_core(L);
//
//	int ret = luaL_dofile(L, R"(../../luacode/test.lua)");
//	if (ret != 0)
//	{
//		printf("%s", lua_tostring(L, -1));
//	}
//}

void testLuaNumber() {
	std::cout << "hello test lua begin" << std::endl;
	//初始化Lua （最后记得调用lua_close(lua_state)释放）
	lua_State* lua_state = luaL_newstate();
	//加载Lua基本库
	luaL_openlibs(lua_state);
	luabridge::getGlobalNamespace(lua_state)
		.beginNamespace("game")
			.beginClass<TestLua>("TestLua")
				.addConstructor<void (*) (void)>()//无参构造函数的注册
				.addConstructor<void (*) (std::string)>()//无参构造函数的注册
				.addData("name", &TestLua::name)//注册变量到lua
				.addStaticData("counter", &TestLua::counter)//注册静态变量到lua
				.addFunction("Add",&TestLua::Add)
				//.addFunction("SetName", &TestLua::SetName)//注册test、方法到lua（addStaticFunction静态函数注册也类似）
				.addProperty("name_value", &TestLua::GetName, &TestLua::SetName)//属性方法的注册（addStaticProperty静态属性方法也类似）
				.addFunction("func", &TestLua::func)//注册返回多个参数给lua的方法
			.endClass()
			.deriveClass<TestLuaChild, TestLua>("TestLuaChild")//子类的注册
				.addConstructor<void (*) (std::string,std::string)>()//有参构造函数的注册
				.addData("c_str", &TestLuaChild::c_str)//注册变量到lua
			.endClass()
		.endNamespace();

	//创建test_lua对象
	TestLua test("hello world");
	test.SetName("su xuan jing");
	lua_register(lua_state, "average", average);
	luabridge::setGlobal(lua_state, &test, "test");//注册test_lua对象到lua

	//运行lua脚本
	//int errorcode = luaL_dofile(lua_state, R"(../../luacode/test.lua)");
	int errorcode = luaL_dofile(lua_state, R"(../../luacode/test.lua)");
	if (errorcode) {
		std::cout << "load file error:" << errorcode << std::endl;
	}
	else {
		lua_getglobal(lua_state, "test1");
		if (lua_pcall(lua_state, 0, 0, 0)) {
			std::cout << "carry on error" << std::endl;
		}
		
	}
	//关闭Lua
	lua_close(lua_state);

	std::cout << "hello test lua end" << std::endl;
}

void testLuaProcess() {
	signin();
}


int main(int argc, char** argv)
{
	//std::cout << "Hello world" << std::endl
	std::cout << argv[0] << std::endl;
	
	//readFile(R"(C:\Users\yqz23\OneDrive\Desktop\weapon_skin.lua)");
	//testLua();
	//testCore();
	//testLuasocket(argv[1]);
	//testLuaProcess();
	testLuaNumber();
	//testLuaP();
	return 0;
}