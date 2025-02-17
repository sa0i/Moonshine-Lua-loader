#include "API/Objects/Sprite.hpp"

API::Sprite::Sprite(const LuaStack& args) {
    if (args.size() != 3 && args.size() != 7)
        throw_error("[Sprite:new] Incorrect number of arguments!");

    path = args.get<std::string>();
    float w = args.get<float>();
    float h = args.get<float>();
    size_t t_x = (args.size() == 7 ? args.get<size_t>() : 0);
    size_t t_y = (args.size() == 7 ? args.get<size_t>() : 0);
    size_t t_w = (args.size() == 7 ? args.get<size_t>() : 0);
    size_t t_h = (args.size() == 7 ? args.get<size_t>() : 0);

    if (!texture.loadFromFile(path))
        throw_error("[Sprite:new] Texture by path '" + path + "' cannot be loaded!");

    if (args.size() == 3) {
        t_w = texture.getSize().x;
        t_h = texture.getSize().y;
    }

    setTexture(texture);
    setScale(sf::Vector2(w / t_w, h / t_h));

    if (args.size() == 7)
        setTextureRect(sf::IntRect(t_x, t_y, t_w, t_h));
}

const std::string API::Sprite::get_path() const {
    return path;
}