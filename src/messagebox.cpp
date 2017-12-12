#include <iostream>
#include <messagebox.hpp>

MessageBox::MessageBox(const std::string& text, const std::string& title)
    : window_title(title) {
  window.setFramerateLimit(60);

  auto label = tgui::Label::create(text);
  label->getRenderer()->setTextColor(tgui::Color::White);
  label->setPosition(15, 10);
  label->setTextSize(12u);
  label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Center);
  label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
  gui.add(label);

  auto button = tgui::Button::create("OK");
  button->setSize(90, 30);
  button->setPosition(
      label->getPosition().x + ((label->getSize().x - button->getSize().x) / 2),
      label->getPosition().y + label->getSize().y);
  button->getRenderer()->setBackgroundColorHover(tgui::Color(200, 200, 200));
  button->connect("Pressed", [&]() { window.close(); });
  gui.add(button);

  //  std::cout << label->getPosition().x << ", " << label->getPosition().y <<
  //  '\n'
  //            << label->getSize().x << ", " << label->getSize().y << '\n'
  //            << button->getPosition().x << ", " << button->getPosition().y
  //            << '\n'
  //            << button->getSize().x << ", " << button->getSize().y << '\n';

  window_size.bitsPerPixel = 32;
  window_size.width = label->getSize().x + (label->getPosition().x * 2);
  window_size.height =
      label->getSize().y + (label->getPosition().y * 2) + button->getSize().y;
}

void MessageBox::show() {
  window.create(window_size, window_title, sf::Style::Titlebar);
  gui.setTarget(window);

  while (window.isOpen()) {
    sf::Event e;
    if (window.pollEvent(e)) {
      if (e.type == sf::Event::Closed)
        window.close();

      gui.handleEvent(e);
    }

    window.clear();
    gui.draw();
    window.display();
  }
}
