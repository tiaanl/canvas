
#include "canvas/App.h"
#include "canvas/Rendering/Canvas.h"

class MinimalWindow : public ca::WindowDelegate {
public:
  MinimalWindow() : ca::WindowDelegate("Minimal") {}
  ~MinimalWindow() override {}

  // Override: ca::WindowDelegate
  void onPaint(ca::Canvas* canvas) override {
    canvas->clear(ca::Color{31, 63, 95});
  }

private:
  DISALLOW_COPY_AND_ASSIGN(MinimalWindow);
};

CANVAS_APP(MinimalWindow);
