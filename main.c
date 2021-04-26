#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

// I plan to create bindings as I progress through the levels to make understanding what I do easier.
#define PUSH_FUNCTION(C_FUNCTION, GLOBAL_NAME){ \
      lua_pushcfunction(L, C_FUNCTION); \
      lua_setglobal(L, GLOBAL_NAME); \
}

// prime checker, algorithm is based off the one found at https://en.wikipedia.org/wiki/Primality_test#Python_code
static int l_is_prime(lua_State *L)
{
  int n = (int)lua_tonumber(L, 1);
  if (n<=3){
    lua_pushboolean(L, n>1);
    return 1;
  };
  if (n%2 == 0 || n%3 == 0){
    lua_pushboolean(L, 0);
    return 1;
  }
  int i = 5;
  while (i*2<n){
    if (n%i==0 || n%(i+2)==0){
      lua_pushboolean(L, 0);
      return 1;
    };
    i+=6;
  };
  lua_pushboolean(L, 1);
  return 1;
};

int factorial(int n){
	int m = 1;
	int i = 2;
	while (i<=n){
		m*=i;
		i++;
	};
	return m;
};

static int l_factorial(lua_State *L)
{
	int n = (int)lua_tonumber(L, 1);
	lua_pushnumber(L, factorial(n));
	return 1;
};

int main() {
  // Create lua state
  lua_State *L = luaL_newstate();
  // Load in default lua libraries (not that these are actually used, it is just convention)
  luaL_openlibs(L);
  // Use my macro above to load in a lua-C function in one line
  PUSH_FUNCTION(l_is_prime, "c_is_prime")
  PUSH_FUNCTION(l_factorial, "c_factorial")
  // Execute the demo script
  luaL_dofile(L, "demo.lua");
  return 0;
}
