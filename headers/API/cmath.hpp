#pragma once

#include "lua_extensions.hpp"
#include "misc_functions.hpp"

#include <random>
#include <sstream>

namespace API
{
    static std::random_device rd;
    static std::mt19937 gen{ rd() };

    static int rand_int(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[cmath.rand_int] Incorrect number of arguments!");

        const int min = args.get<int>();
        const int max = args.get<int>();

        std::uniform_int_distribution dist{ min, max };

        lua_pushinteger(L, dist(gen));
        return 1;
    }

    static int rand_double(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 2)
            throw_error("[cmath.rand_double] Incorrect number of arguments!");

        std::stringstream tmp;
        const double min = args.get<double>();
        const double max = args.get<double>();

        tmp << std::abs(min);
        int first = tmp.str().length();

        tmp.clear();

        tmp << std::abs(max);
        int second = tmp.str().length();

        int n = std::pow(10, std::max(first, second - 3));
        std::uniform_real_distribution dist{ min, max };

        lua_pushnumber(L, std::round(dist(gen) * n) / n);
        return 1;
    }

    static int lerp(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3)
            throw_error("[cmath.lerp] Incorrect number of arguments!");

        const float start = args.get<float>();
        const float end = args.get<float>();
        const float time = args.get<float>();

        lua_pushnumber(L, (start + time * (end - start)));
        return 1;
    }

    static int clamp(lua_State* L) {
        LuaStack args(L);

        if (args.size() != 3)
            throw_error("[cmath.clamp] Incorrect number of arguments!");

        const float number = args.get<float>();
        const float lower = args.get<float>();
        const float upper = args.get<float>();
        
        lua_pushnumber(L, std::clamp(number, lower, upper));
        return 1;
    }
}