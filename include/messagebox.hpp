#ifndef MESSAGEBOX_HPP
#define MESSAGEBOX_HPP
#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>
#include <memory>
#include <string>

class MessageBox {
 public:
  MessageBox(const std::string& text = "", const std::string& title = "");

  void show();

 private:
  sf::VideoMode window_size;
  std::string window_title;

  sf::RenderWindow window;
  tgui::Gui gui;
};
#endif  // MESSAGEBOX_HPP
