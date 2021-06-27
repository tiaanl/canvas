#pragma once

namespace ca {

class RenderState {
public:
  RenderState() = default;

  void depth_test(bool enabled) {
    depth_test_ = enabled;
  }

  NU_NO_DISCARD bool depth_test() const {
    return depth_test_;
  }

  void cull_face(bool enabled) {
    cull_face_ = enabled;
  }

  NU_NO_DISCARD bool cull_face() const {
    return cull_face_;
  }

private:
  bool depth_test_ = false;
  bool cull_face_ = false;
};

}  // namespace ca
