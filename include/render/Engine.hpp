#pragma once

#include "player/Player.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class Engine {
private:
    static const unsigned int WIDTH = 497;
    static const unsigned int HEIGHT = 427;
    sf::Vector2i resolution;
    sf::RenderWindow window;
    const unsigned int FPS = 60;
    static const sf::Time TimePerFrame;

    sf::Texture board_tex;
    sf::Texture red_disc_tex;
    sf::Texture yellow_disc_tex;

    sf::Sprite board_sprite;
    std::vector<std::unique_ptr<sf::Sprite>> discs_sprites;

    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;

    int turn;

public:
    Engine(std::unique_ptr<Player> &&p1, std::unique_ptr<Player> &&p2);

    ~Engine();

    void run();

    void update_discs_sprites(const Board &);

    void handle_hover(PlayerColor player);

    int get_human_move() const;

    void update(const Board &);

    void ask_for_restart();
};