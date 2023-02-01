print("lua print")
pro.g_var = 5         -- okay
pro.s_var = 120
pro.g_string = "hello world"
pro.g_value = 1389
print("foo",pro.foo())
print("func",pro.func())
pro.g_var_r = 123456

-- test.var2 = 6         -- error: var2 is not writable
-- test.prop1 = "Hello"  -- okay
-- test.prop1 = 68       -- okay, Lua converts the number to a string
-- test.prop2 = "bar"    -- error: prop2 is not writable

-- test.foo ()           -- calls foo and discards the return value
-- test.var1 = foo ()    -- calls foo and stores the result in var1
-- test.bar ("Employee") -- calls bar with a string
-- test.bar (test)       -- error: bar expects a string not a table
