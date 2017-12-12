#include <algorithm>
#include <gameoflife.hpp>
#include <iostream>
#include <random>

GameOfLife::GameOfLife(std::string survive,
                       std::string revive,
                       double chance_alive,
                       unsigned width,
                       unsigned height,
                       unsigned tickrate) {
  cell.setOutlineThickness(1);
  cell.setOutlineColor(sf::Color(130, 130, 130));
  cell.setSize({3.f, 3.f});
  cell.setFillColor(sf::Color::Red);

  set_cell_chance(chance_alive);
  set_tick_rate(tickrate);

  set_board_size(width, height);
  set_rules(survive, revive);
}

void GameOfLife::set_rules(std::string survive, std::string revive) {
  cell_survive = survive;
  cell_revive = revive;
}

void GameOfLife::set_board_size(unsigned width, unsigned height) {
  board_width = width;
  board_height = height;
  // +2, to make neightbours checking easy (look at step() code)
  cell_states.resize((width + 2) * (height + 2), false);
}

void GameOfLife::set_cell_chance(double chance) {
  cell_chance = chance;
}

void GameOfLife::set_tick_rate(unsigned tickrate) {
  tick_rate = tickrate;
  tick_period = std::chrono::milliseconds(1000 / tick_rate);
  next_tick = std::chrono::high_resolution_clock::now() + tick_period;
}

unsigned GameOfLife::get_tick_rate() const {
  return tick_rate;
}

std::pair<std::string, std::string> GameOfLife::get_rules() const {
  return {cell_survive, cell_revive};
}

sf::Vector2u GameOfLife::get_board_size() const {
  return {board_width, board_height};
}

double GameOfLife::get_cell_chance() const {
  return cell_chance;
}

sf::VideoMode GameOfLife::get_window_size() const {
  auto size = get_cell_size();
  return sf::VideoMode((board_width + 2u) * size.x,
                       (board_height + 2u) * size.y, 32);
}

void GameOfLife::generate_board() {
  std::mt19937 gen(static_cast<std::uint_fast32_t>(
      std::chrono::high_resolution_clock::now().time_since_epoch().count()));
  std::bernoulli_distribution dist(cell_chance);

  for (std::size_t y{1}; y < board_height; y++)
    for (std::size_t x{1}; x < board_width; x++) {
      set_cell_state(x, y, dist(gen));
    }
}

void GameOfLife::clear_board() {
  std::fill(cell_states.begin(), cell_states.end(), false);
}

unsigned GameOfLife::get_alive_neightbours(std::size_t x, std::size_t y) const {
  return static_cast<unsigned>(
      get_cell_state(x - 1, y - 1) + get_cell_state(x, y - 1) +
      get_cell_state(x + 1, y - 1) + get_cell_state(x - 1, y) +
      get_cell_state(x + 1, y) + get_cell_state(x - 1, y + 1) +
      get_cell_state(x, y + 1) + get_cell_state(x + 1, y + 1));
}

void GameOfLife::step() {
  std::vector<bool> temp_states(cell_states.size(), false);
  // Iterate throught whole board
  for (std::size_t y{1}; y < board_height; y++)
    for (std::size_t x{1}; x < board_width; x++) {
      unsigned alive_neightbours = get_alive_neightbours(x, y);

      // Set cell state according to rules in board copy
      // (copy is necessary because if i'd operate on original board, cell
      // states would be invalidated each iteration, as the state of partially
      // changed board would be used)
      if (get_cell_state(x, y)) {
        for (const char c : cell_survive) {
          if (alive_neightbours == static_cast<unsigned>(c - '0')) {
            temp_states[get_cell_offset(x, y)] = true;
          }
        }
      } else {
        for (const char c : cell_revive) {
          if (alive_neightbours == static_cast<unsigned>(c - '0')) {
            temp_states[get_cell_offset(x, y)] = true;
          }
        }
      }
    }

  cell_states.swap(temp_states);
}

void GameOfLife::draw_on(sf::RenderTarget& target) {
  auto size = get_cell_size();
  for (std::size_t y{1}; y < board_height; y++)
    for (std::size_t x{1}; x < board_width; x++)
      if (get_cell_state(x, y)) {
        cell.setPosition((x + 1u) * size.x, (y + 1u) * size.y);
        target.draw(cell);
      }
}

bool GameOfLife::async_step() {
  auto now = std::chrono::high_resolution_clock::now();
  if (now < next_tick)
    return false;

  step();
  next_tick = now + tick_period;
  return true;
}
