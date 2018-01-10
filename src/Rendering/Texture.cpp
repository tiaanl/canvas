
#include "canvas/Rendering/Texture.h"

#include "canvas/Utils/GLCheck.h"
#include "nucleus/Logging.h"

#include "nucleus/MemoryDebug.h"

namespace ca {

namespace {

static I32 getMaxTextureSize() {
  GLint size;
  GL_CHECK(glGetIntegerv(GL_MAX_TEXTURE_SIZE, &size));
  return size;
}

}  // namespace

// static
void Texture::bind(const Texture* texture) {
  if (!texture) {
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
  } else {
    GL_CHECK(glBindTexture(GL_TEXTURE_2D, texture->m_name));
  }
}

Texture::Texture(Texture&& other) : m_name(std::move(other.m_name)), m_size(std::move(other.m_size)) {
  other.m_name = 0;
  other.m_size = {};
}

Texture::~Texture() {
  if (m_name != 0) {
    glDeleteTextures(1, &m_name);
  }
}

Texture& Texture::operator=(Texture&& other) {
  m_name = std::move(other.m_name);
  m_size = std::move(other.m_size);

  other.m_name = 0;
  other.m_size = {};

  return *this;
}

bool Texture::create(const Size<I32>& size) {
  I32 maxTextureSize = getMaxTextureSize();
  if (size.width == 0 || (size.width & (size.width - 1)) != 0 || size.width > maxTextureSize || size.height == 0 ||
      (size.height & (size.height - 1)) != 0 || size.height > maxTextureSize) {
    LOG(Error) << "Can't create texture with invalid size. (" << size.width << ", " << size.height << ")";
    return false;
  }

  // Store the size.
  m_size = size;

  createNewName();

  // Initialize the texture.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_name));
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.width, m_size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr));

  const bool smooth = false;
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST));

  return true;
}

bool Texture::createFromImage(const Image& image) {
  createNewName();
  m_size = image.getSize();

  // Bind the texture.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, m_name));

  // Upload the image data.
  GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_size.width, m_size.height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
                        image.getData().getData()));

  // Set the texture clamping.
  const bool smooth = false;
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, smooth ? GL_LINEAR : GL_NEAREST));
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, smooth ? GL_LINEAR : GL_NEAREST));

  // Unbind the texture we were working on.
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));

  return true;
}

void Texture::update(const U8* pixels, const Rect<I32>& rect) {
  DCHECK(rect.pos.x + rect.size.width < m_size.width);
  DCHECK(rect.pos.y + rect.size.height < m_size.height);

  if (!pixels || !m_name) {
    LOG(Warning) << "No texture update performed.";
    return;
  }

  // TODO: Make sure there is a GL context available.

  bind(this);
  GL_CHECK(glTexSubImage2D(GL_TEXTURE_2D, 0, rect.pos.x, rect.pos.y, rect.size.width, rect.size.height, GL_RGBA,
                           GL_UNSIGNED_BYTE, pixels));
}

void Texture::createNewName() {
  if (m_name != 0) {
    GL_CHECK(glDeleteTextures(1, &m_name));
    m_name = 0;
  }

  GL_CHECK(glGenTextures(1, &m_name));
}

}  // namespace ca
