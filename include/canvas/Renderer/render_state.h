#pragma once

namespace ca {

class RenderState {
public:
  RenderState() = default;

  void depth_test(bool enabled) {
    depth_test_ = enabled;
  }

  bool depth_test() const {
    return depth_test_;
  }

private:
  bool depth_test_ = false;
};

}  // namespace ca
