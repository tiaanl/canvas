
#include "canvas/Renderer/UniformBuffer.h"

#include "nucleus/Logging.h"

namespace ca {

UniformBuffer::UniformBuffer() = default;

UniformBuffer::~UniformBuffer() = default;

void UniformBuffer::set(UniformId uniformId, F32 value) {
  addUniformData(uniformId, 1, &value);
}

void UniformBuffer::set(UniformId uniformId, const fl::Vec2& value) {
  addUniformData(uniformId, 2, &value.x);
}

void UniformBuffer::set(UniformId uniformId, const fl::Vec3& value) {
  addUniformData(uniformId, 3, &value.x);
}

void UniformBuffer::set(UniformId uniformId, const fl::Vec4& value) {
  addUniformData(uniformId, 4, &value.x);
}

void UniformBuffer::set(UniformId uniformId, const fl::Mat4& value) {
  addUniformData(uniformId, 16, &value.col[0].x);
}

void UniformBuffer::set(UniformId uniformId, const Color& value) {
  addUniformData(uniformId, 4, &value.r);
}

void UniformBuffer::apply(ApplyFunc func) const {
  for (const auto& data : m_uniforms) {
    func(data.uniformId, data.count, static_cast<const F32*>(data.values));
  }
}

void UniformBuffer::addUniformData(UniformId uniformId, U32 count, const F32* values) {
  DCHECK(count <= sizeof(UniformData::values) / sizeof(F32));

  UniformData data{};
  data.uniformId = uniformId;
  data.count = count;
  std::copy(values, values + count, data.values);

  m_uniforms.pushBack(data);
}

}  // namespace ca
