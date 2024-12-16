#ifndef _UI_H_
#define _UI_H_

class Ui {

private:
  const int SCREEN_WIDTH = 1024;
  const int SCREEN_HEIGHT = 768;

  bool *die;

public:
  Ui(bool *die) : die(die) {}

  void ui_init();
  void ui_handle_events();
};

#endif
