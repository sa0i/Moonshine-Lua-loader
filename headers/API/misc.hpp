#pragma once

#include "lua_extensions.hpp"

extern sf::RenderWindow window;
extern std::string FONTS_PATH;
extern size_t print_offset;

namespace API
{
	static int print(lua_State* L) {
        LuaStack args(L);
        std::string result;
        constexpr size_t size = 20;

        for (size_t i = 0, args_size = args.size(); i < args_size; ++i) {
            lua_getglobal(L, "tostring");
            bool is_number = false;

            if (lua_isfunction(L, -1)) {
                switch (args.get_type(i)) {
                    case LuaMultiValue::Number:
                        lua_pushnumber(L, args.get<double>(i));
                        is_number = true;
                        break;
                    case LuaMultiValue::Function:
                        lua_pushstring(L, "'function'");
                        break;
                    case LuaMultiValue::String:
                        lua_pushstring(L, args.get<std::string>(i).c_str());
                        break;
                    case LuaMultiValue::Boolean:
                        lua_pushboolean(L, args.get<bool>(i));
                        break;
                    case LuaMultiValue::Table:
                        lua_pushstring(L, "'table'");
                        break;
                    case LuaMultiValue::Userdata:
                        lua_pushstring(L, "'userdata'");
                        break;
                    default:
                        lua_pushnil(L);
                }

                lua_pcall(L, 1, 1, 0);

                if (!lua_isnil(L, -1)) {
                    std::string tmp = lua_tostring(L, -1);
                    size_t length = tmp.length();
                    
                    if (is_number && length >= 3 && tmp[length - 2] == '.' && tmp[length - 1] == '0')
                        tmp.resize(tmp.size() - 2);

                    result += tmp + '\t';
                    lua_pop(L, 1);
                }
            }
        }

        sf::Font font;
        if (!font.loadFromFile(FONTS_PATH + "arial.ttf"))
            throw_error("[print] Failed to create the font face.");

        sf::Text text(sf::String::fromUtf8(result.begin(), result.end()), font, size);
        text.setPosition(sf::Vector2f(0, print_offset));
        text.setFillColor(sf::Color::White);

        window.draw(text);

        print_offset += size;

        if (print_offset >= window.getSize().y)
            print_offset = 0;

        return 0;
    }
}