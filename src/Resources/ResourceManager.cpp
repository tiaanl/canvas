
#include "canvas/Resources/ResourceManager.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

ResourceManager::ResourceManager(nu::Allocator *allocator)
    : m_allocator(allocator), m_rootPath(m_allocator) {}

ResourceManager::~ResourceManager() = default;

}  // namespace ca
