
#ifndef CANVAS_RENDERER_UNIFORM_BUFFER_H_
#define CANVAS_RENDERER_UNIFORM_BUFFER_H_

#include <functional>

#include "canvas/Renderer/Types.h"
#include "canvas/Utils/Color.h"
#include "floats/Mat4.h"
#include "floats/Vec2.h"
#include "floats/Vec3.h"
#include "floats/Vec4.h"
#include "nucleus/Containers/DynamicArray.h"
#include "nucleus/function.h"

namespace ca {

class UniformBuffer {
public:
  using ApplyFunc = nu::Function<void(UniformId uniformId, U32 count, const F32* values)>;

  void set(UniformId uniformId, F32 value);
  void set(UniformId uniformId, const fl::Vec2& value);
  void set(UniformId uniformId, const fl::Vec3& value);
  void set(UniformId uniformId, const fl::Vec4& value);
  void set(UniformId uniformId, const fl::Mat4& value);
  void set(UniformId uniformId, const Color& value);

  void apply(ApplyFunc func) const;

private:
  struct UniformData {
    UniformId uniformId;
    U32 count;
    F32 values[16];
  };

  void addUniformData(UniformId uniformId, U32 count, const F32* values);

  nu::DynamicArray<UniformData> m_uniforms;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_UNIFORM_BUFFER_H_
