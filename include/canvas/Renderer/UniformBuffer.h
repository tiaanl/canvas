
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
  using ApplyFunc =
      nu::Function<void(UniformId uniformId, ComponentType type, U32 count, const void* values)>;

  void set(UniformId uniformId, F32 value);
  void set(UniformId uniformId, const fl::Vec2& value);
  void set(UniformId uniformId, const fl::Vec3& value);
  void set(UniformId uniformId, const fl::Vec4& value);
  void set(UniformId uniformId, const fl::Mat4& value);
  void set(UniformId uniformId, const Color& value);
  void set(UniformId uniformId, U32 value);
  void set(UniformId uniformId, I32 value);

  void apply(ApplyFunc func) const;

private:
  struct UniformData {
    UniformId uniformId;
    ComponentType type;
    U32 count;
    U8 data[sizeof(F32) * 16];
  };

  void addUniformData(UniformId uniform_id, ComponentType type, U32 count, const void* data);

  nu::DynamicArray<UniformData> m_uniforms;
};

}  // namespace ca

#endif  // CANVAS_RENDERER_UNIFORM_BUFFER_H_
