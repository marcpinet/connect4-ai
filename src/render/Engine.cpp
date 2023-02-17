#include "render/Engine.hpp"
#include "player/Player.hpp"
#include "game_logic/Coord.hpp"
#include "player/HumanPlayer.hpp"
#include "player/AIPlayer.hpp"

const sf::Time Engine::TimePerFrame = sf::seconds(1.f / 60.f);

Engine::Engine(std::unique_ptr<Player> &&p1, std::unique_ptr<Player> &&p2) {
    this->player1 = std::move(p1);
    this->player2 = std::move(p2);

    this->turn = 0;

    this->resolution = sf::Vector2i(Engine::WIDTH, Engine::HEIGHT);
    this->window.create(sf::VideoMode(this->resolution.x, this->resolution.y), "Connect4AI",
                        sf::Style::Titlebar | sf::Style::Close);
    this->window.setFramerateLimit(this->FPS);

    // Board image
    board_tex.loadFromFile("assets/board.png");
    this->board_sprite.setTexture(board_tex);
    this->board_sprite.setPosition(0, 0);

    red_disc_tex.loadFromFile("assets/disc_red.png");
    yellow_disc_tex.loadFromFile("assets/disc_yellow.png");
}

void Engine::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    Board board;

    while(this->window.isOpen()) {
        // Read events
        sf::Event event{};
        while(this->window.pollEvent(event)) {
            // Close window: exit
            if(event.type == sf::Event::Closed)
                this->window.close();

            // Mouse click
            if(event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    PlayerColor color;
                    if(!board.is_terminal() && dynamic_cast<HumanPlayer *>(this->player1.get()) != nullptr ||
                       dynamic_cast<HumanPlayer *>(this->player2.get()) != nullptr) {
                        color = this->turn % 2 == 0 ? player1->get_type() : player2->get_type();
                        int move = this->get_human_move();
                        if(move == -1)
                            continue;
                        board.place(move, color);
                        this->turn++;
                    }
                }
            }

            // Restart game R keyboard
            if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::R) {
                    this->ask_for_restart();
                    board = Board();
                    this->turn = 0;
                }
            }
        }

        // Clock stuff
        sf::Time elapsedTime = clock.restart();
        timeSinceLastUpdate += elapsedTime;

        // Actual display loop
        if(timeSinceLastUpdate > TimePerFrame) {
            // Used for FPS Cap
            timeSinceLastUpdate = sf::Time::Zero;

            // Making AI place (only if they're instanced as AIPlayer)
            if(dynamic_cast<AIPlayer *>(this->player1.get()) != nullptr && this->turn % 2 == 0) {
                int move = this->player1->get_move(board);
                board.place(move, this->player1->get_type());
                this->turn++;
            } else if(dynamic_cast<AIPlayer *>(this->player2.get()) != nullptr && this->turn % 2 == 1) {
                int move = this->player2->get_move(board);
                board.place(move, this->player2->get_type());
                this->turn++;
            }

            this->update(board);
        }
    }
}

void Engine::update_discs_sprites(const Board &board) {
    // Clearing discs_sprites, thanks to unique_ptr we don't have to delete each sprite manually
    this->discs_sprites.clear();

    // Updating discs_sprites
    for(int x = 0; x < Board::get_height(); x++) {
        for(int y = 0; y < Board::get_width(); y++) {
            Coord coord(x, y);
            if(board.get(coord) != PlayerColor::NONE) {
                auto disc_sprite = std::make_unique<sf::Sprite>();

                if(board.get(coord) == PlayerColor::RED)
                    disc_sprite->setTexture(red_disc_tex);
                else if(board.get(coord) == PlayerColor::YELLOW) {
                    disc_sprite->setTexture(yellow_disc_tex);
                }
                disc_sprite->setPosition(static_cast<float>(8 + 71 * y), static_cast<float>(8 + 71 * x));
                this->discs_sprites.emplace_back(std::move(disc_sprite));
            }
        }
    }
}

void Engine::update(const Board &board) {
    this->window.clear(sf::Color::White);

    this->window.draw(this->board_sprite);

    // Handle hover in function of the player turn and color (and only if they're Human)
    if(!board.is_terminal() && dynamic_cast<HumanPlayer *>(this->player1.get()) != nullptr ||
       dynamic_cast<HumanPlayer *>(this->player2.get()) != nullptr) {
        PlayerColor color = this->turn % 2 == 0 ? player1->get_type() : player2->get_type();
        this->handle_hover(color);
    }

    // Updating discs and drawing them
    this->update_discs_sprites(board);
    for(auto &disc_sprite: this->discs_sprites)
        this->window.draw(*disc_sprite);

    if(board.is_terminal())
        this->ask_for_restart();

    this->window.display();
}

Engine::~Engine() {
    this->window.close();
}

void Engine::handle_hover(PlayerColor player) {
    sf::Color color;
    if(player == PlayerColor::RED)
        color = sf::Color(255, 0, 0, 80);
    else if(player == PlayerColor::YELLOW)
        color = sf::Color(255, 255, 0, 80);

    sf::Vector2i cursorPos = sf::Mouse::getPosition(this->window);

    int column_to_hover = -1;
    for(int i = 0; i < Board::get_width(); i++)
        if(cursorPos.x > 8 + 71 * i && cursorPos.x < 8 + 71 * (i + 1))
            column_to_hover = i;

    if(column_to_hover != -1) {
        for(int i = 0; i < Board::get_height(); i++) {
            sf::CircleShape hover(27);
            hover.setPosition(static_cast<float>(8 + 71 * column_to_hover), static_cast<float>(8 + i * 71));
            hover.setFillColor(color);
            this->window.draw(hover);
        }
    }
}

int Engine::get_human_move() const {
    sf::Vector2i cursorPos = sf::Mouse::getPosition(this->window);

    int column_to_play = -1;
    for(int i = 0; i < Board::get_width(); i++)
        if(cursorPos.x > 8 + 71 * i && cursorPos.x < 8 + 71 * (i + 1))
            column_to_play = i;

    return column_to_play;
}

void Engine::ask_for_restart() {
    sf::Texture restart_tex;
    restart_tex.loadFromFile("assets/end.png");
    sf::Sprite restart_sprite;
    restart_sprite.setTexture(restart_tex);
    restart_sprite.setPosition(static_cast<int>(Engine::WIDTH / 2) - 185, static_cast<int>(Engine::HEIGHT / 2) - 98);

    sf::Color color(0, 0, 0, 99);
    sf::RectangleShape darken(sf::Vector2f(Engine::WIDTH, Engine::HEIGHT));
    darken.setPosition(0, 0);
    darken.setFillColor(color);

    this->window.draw(darken);
    this->window.draw(restart_sprite);
}
