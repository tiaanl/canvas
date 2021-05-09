
#include "canvas/Renderer/UniformBuffer.h"

#include "nucleus/Logging.h"

namespace ca {

void UniformBuffer::set(UniformId uniformId, F32 value) {
  addUniformData(uniformId, ComponentType::Float32, 1, &value);
}

void UniformBuffer::set(UniformId uniformId, const fl::Vec2& value) {
  addUniformData(uniformId, ComponentType::Float32, 2, &value.x);
}

void UniformBuffer::set(UniformId uniformId, const fl::Vec3& value) {
  addUniformData(uniformId, ComponentType::Float32, 3, &value.x);
}

void UniformBuffer::set(UniformId uniformId, const fl::Vec4& value) {
  addUniformData(uniformId, ComponentType::Float32, 4, &value.x);
}

void UniformBuffer::set(UniformId uniformId, const fl::Mat4& value) {
  addUniformData(uniformId, ComponentType::Float32, 16, &value.col[0].x);
}

void UniformBuffer::set(UniformId uniformId, const Color& value) {
  addUniformData(uniformId, ComponentType::Float32, 4, &value.r);
}

void UniformBuffer::set(UniformId uniformId, U32 value) {
  addUniformData(uniformId, ComponentType::Unsigned32, 1, &value);
}

void UniformBuffer::set(UniformId uniformId, I32 value) {
  addUniformData(uniformId, ComponentType::Signed32, 1, &value);
}

void UniformBuffer::apply(ApplyFunc func) const {
  for (const auto& data : m_uniforms) {
    func(data.uniformId, data.type, data.count, &data.data);
  }
}

void UniformBuffer::addUniformData(UniformId uniform_id, ComponentType type, U32 count,
                                   const void* data) {
  MemSize component_size = 0;
  switch (type) {
    case ComponentType::Signed8:
    case ComponentType::Unsigned8:
      component_size = 1;
      break;
    case ComponentType::Signed16:
    case ComponentType::Unsigned16:
      component_size = 2;
      break;
    case ComponentType::Float32:
    case ComponentType::Signed32:
    case ComponentType::Unsigned32:
      component_size = 4;
      break;
  }

  m_uniforms.constructBack([&](UniformData* storage) {
    storage->uniformId = uniform_id;
    storage->type = type;
    storage->count = count;
    std::memcpy(&storage->data, data, component_size * count);
  });
}

}  // namespace ca
