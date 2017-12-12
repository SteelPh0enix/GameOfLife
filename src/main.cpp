#include <TGUI/TGUI.hpp>
#include <chrono>
#include <gameoflife.hpp>
#include <iostream>
#include <sstream>
#include <thread>

using namespace std::chrono_literals;

//#define TOOLTIP_ENABLED

int main() {
  sf::RenderWindow win;
  win.setFramerateLimit(60);
  GameOfLife g("34", "34");

  g.set_tick_rate(15);  // 5 ticks per second
  g.set_cell_chance(0.1);
  g.generate_board();

  win.create(g.get_window_size(), "Game of Life");

#ifdef TOOLTIP_ENABLED
  tgui::Gui ui(win);
  auto tooltip = tgui::Label::create("test");
  tooltip->getRenderer()->setBackgroundColor(tgui::Color(50, 50, 50));
  tooltip->getRenderer()->setBorderColor(tgui::Color(100, 100, 100));
  tooltip->getRenderer()->setBorders(1);
  tooltip->getRenderer()->setTextColor(tgui::Color::White);
  tooltip->setTextSize(10);
  // tooltip->hide();
  ui.add(tooltip);

  auto cell_coord = sf::Vector2i{10, 10};
#endif

  while (win.isOpen()) {
    sf::Event e;
    if (win.pollEvent(e)) {
      if (e.type == sf::Event::Closed) {
        win.close();
#ifdef TOOLTIP_ENABLED
      } else if (e.type == sf::Event::MouseMoved) {
        auto tmp_cell_coord = g.normalize_mpos(e.mouseMove.x, e.mouseMove.y);
        if (tmp_cell_coord.x < 1 || tmp_cell_coord.y < 1 ||
            tmp_cell_coord.x > static_cast<int>(g.get_board_size().x) ||
            tmp_cell_coord.y > static_cast<int>(g.get_board_size().y))
          continue;
        cell_coord = tmp_cell_coord;
        tooltip->setPosition(std::abs(e.mouseMove.x - tooltip->getSize().x),
                             std::abs(e.mouseMove.y - tooltip->getSize().y));
      }
      ui.handleEvent(e);
    }

    std::stringstream ss("");
    ss << "x: " << cell_coord.x << ", y: " << cell_coord.y << '\n'
       << "Cell state: " << g.get_cell_state(cell_coord.x, cell_coord.y) << '\n'
       << "Alive neightbours: "
       << g.get_alive_neightbours(cell_coord.x, cell_coord.y);

    tooltip->setText(ss.str());
#else
      }
    }
#endif
    win.clear();
    g.async_step();
    g.draw_on(win);
#ifdef TOOLTIP_ENABLED
    ui.draw();
#endif
    win.display();
  }
}
