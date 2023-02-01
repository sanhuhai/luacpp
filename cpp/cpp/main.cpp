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
	// lua_gettop(L):ȡ��ջ��������ֵ,��ʱ����ջ�ڵ�Ԫ�ظ���
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
	//��ʼ��Lua �����ǵõ���lua_close(lua_state)�ͷţ�
	lua_State* lua_state = luaL_newstate();
	//����Lua������
	luaL_openlibs(lua_state);
	luabridge::getGlobalNamespace(lua_state)
		.beginNamespace("game")
			.beginClass<TestLua>("TestLua")
				.addConstructor<void (*) (void)>()//�޲ι��캯����ע��
				.addConstructor<void (*) (std::string)>()//�޲ι��캯����ע��
				.addData("name", &TestLua::name)//ע�������lua
				.addStaticData("counter", &TestLua::counter)//ע�ᾲ̬������lua
				.addFunction("Add",&TestLua::Add)
				//.addFunction("SetName", &TestLua::SetName)//ע��test��������lua��addStaticFunction��̬����ע��Ҳ���ƣ�
				.addProperty("name_value", &TestLua::GetName, &TestLua::SetName)//���Է�����ע�ᣨaddStaticProperty��̬���Է���Ҳ���ƣ�
				.addFunction("func", &TestLua::func)//ע�᷵�ض��������lua�ķ���
			.endClass()
			.deriveClass<TestLuaChild, TestLua>("TestLuaChild")//�����ע��
				.addConstructor<void (*) (std::string,std::string)>()//�вι��캯����ע��
				.addData("c_str", &TestLuaChild::c_str)//ע�������lua
			.endClass()
		.endNamespace();

	//����test_lua����
	TestLua test("hello world");
	test.SetName("su xuan jing");
	lua_register(lua_state, "average", average);
	luabridge::setGlobal(lua_state, &test, "test");//ע��test_lua����lua

	//����lua�ű�
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
	//�ر�Lua
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