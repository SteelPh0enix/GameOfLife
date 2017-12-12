#ifndef GAMEOFLIFE_HPP
#define GAMEOFLIFE_HPP
#include <SFML/Graphics.hpp>
#include <chrono>
#include <future>
#include <string>
#include <thread>
#include <utility>
#include <vector>

class GameOfLife {
 public:
  GameOfLife(std::string survive = "23",
             std::string revive = "3",
             double chance_alive = 0.25,
             unsigned width = 150,
             unsigned height = 150,
             unsigned tickrate = 15);

  void set_rules(std::string survive, std::string revive);
  void set_board_size(unsigned width, unsigned height);
  void set_cell_chance(double chance);
  void set_tick_rate(unsigned tickrate);

  std::pair<std::string, std::string> get_rules() const;
  sf::Vector2u get_board_size() const;
  double get_cell_chance() const;
  sf::VideoMode get_window_size() const;

  bool get_cell_state(std::size_t x, std::size_t y) const {
    return cell_states[get_cell_offset(x, y)];
  }

  unsigned get_alive_neightbours(std::size_t x, std::size_t y) const;

  unsigned get_tick_rate() const;

  sf::Vector2i normalize_mpos(unsigned x, unsigned y) const {
    auto size = get_cell_size();

    return {static_cast<int>((x / size.x)) - 1,
            static_cast<int>((y / size.y)) - 1};
  }

  void step();
  bool async_step();

  void generate_board();
  void clear_board();

  void draw_on(sf::RenderTarget& target);

 private:
  std::size_t get_cell_offset(std::size_t x, std::size_t y) const {
    return (y * board_width) + x;
  }

  void set_cell_state(std::size_t x, std::size_t y, bool state) {
    cell_states[get_cell_offset(x, y)] = state;
  }

  sf::Vector2<unsigned> get_cell_size() const {
    return {
        static_cast<unsigned>(cell.getSize().x + cell.getOutlineThickness()),
        static_cast<unsigned>(cell.getSize().y + cell.getOutlineThickness())};
  }

  std::string cell_survive, cell_revive;
  double cell_chance;
  unsigned board_width, board_height;

  sf::RectangleShape cell;
  std::vector<bool> cell_states;

  unsigned tick_rate;
  std::chrono::milliseconds tick_period;
  std::chrono::high_resolution_clock::time_point next_tick;
};

#endif  // GAMEOFLIFE_HPP
