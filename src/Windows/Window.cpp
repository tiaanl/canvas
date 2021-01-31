
#include "canvas/Windows/Window.h"

#include <cmath>

#include "canvas/OpenGL.h"
// r
#include "GLFW/glfw3.h"
#include "nucleus/HighResolutionTimer.h"
#include "nucleus/Text/Utils.h"

namespace ca {

namespace {

inline Window* getUserPointer(GLFWwindow* window) {
  return static_cast<Window*>(glfwGetWindowUserPointer(window));
}

Key getKeyFromGLFWKey(int key) {
  switch (key) {
    case GLFW_KEY_SPACE:
      return Key::Space;
    case GLFW_KEY_APOSTROPHE:
      return Key::Quote;
    case GLFW_KEY_COMMA:
      return Key::Comma;
    case GLFW_KEY_MINUS:
      return Key::Subtract;
    case GLFW_KEY_PERIOD:
      return Key::Period;
    case GLFW_KEY_SLASH:
      return Key::Slash;
    case GLFW_KEY_0:
      return Key::Num0;
    case GLFW_KEY_1:
      return Key::Num1;
    case GLFW_KEY_2:
      return Key::Num2;
    case GLFW_KEY_3:
      return Key::Num3;
    case GLFW_KEY_4:
      return Key::Num4;
    case GLFW_KEY_5:
      return Key::Num5;
    case GLFW_KEY_6:
      return Key::Num6;
    case GLFW_KEY_7:
      return Key::Num7;
    case GLFW_KEY_8:
      return Key::Num8;
    case GLFW_KEY_9:
      return Key::Num9;
    case GLFW_KEY_SEMICOLON:
      return Key::SemiColon;
    case GLFW_KEY_EQUAL:
      return Key::Equal;
    case GLFW_KEY_A:
      return Key::A;
    case GLFW_KEY_B:
      return Key::B;
    case GLFW_KEY_C:
      return Key::C;
    case GLFW_KEY_D:
      return Key::D;
    case GLFW_KEY_E:
      return Key::E;
    case GLFW_KEY_F:
      return Key::F;
    case GLFW_KEY_G:
      return Key::G;
    case GLFW_KEY_H:
      return Key::H;
    case GLFW_KEY_I:
      return Key::I;
    case GLFW_KEY_J:
      return Key::J;
    case GLFW_KEY_K:
      return Key::K;
    case GLFW_KEY_L:
      return Key::L;
    case GLFW_KEY_M:
      return Key::M;
    case GLFW_KEY_N:
      return Key::N;
    case GLFW_KEY_O:
      return Key::O;
    case GLFW_KEY_P:
      return Key::P;
    case GLFW_KEY_Q:
      return Key::Q;
    case GLFW_KEY_R:
      return Key::R;
    case GLFW_KEY_S:
      return Key::S;
    case GLFW_KEY_T:
      return Key::T;
    case GLFW_KEY_U:
      return Key::U;
    case GLFW_KEY_V:
      return Key::V;
    case GLFW_KEY_W:
      return Key::W;
    case GLFW_KEY_X:
      return Key::X;
    case GLFW_KEY_Y:
      return Key::Y;
    case GLFW_KEY_Z:
      return Key::Z;
    case GLFW_KEY_LEFT_BRACKET:
      return Key::LBracket;
    case GLFW_KEY_BACKSLASH:
      return Key::BackSlash;
    case GLFW_KEY_RIGHT_BRACKET:
      return Key::RBracket;
    case GLFW_KEY_GRAVE_ACCENT:
      return Key::Tilde;
    case GLFW_KEY_WORLD_1:
      return Key::Unknown;
    case GLFW_KEY_WORLD_2:
      return Key::Unknown;

    case GLFW_KEY_ESCAPE:
      return Key::Escape;
    case GLFW_KEY_ENTER:
      return Key::Return;
    case GLFW_KEY_TAB:
      return Key::Tab;
    case GLFW_KEY_BACKSPACE:
      return Key::BackSpace;
    case GLFW_KEY_INSERT:
      return Key::Insert;
    case GLFW_KEY_DELETE:
      return Key::Delete;
    case GLFW_KEY_RIGHT:
      return Key::Right;
    case GLFW_KEY_LEFT:
      return Key::Left;
    case GLFW_KEY_DOWN:
      return Key::Down;
    case GLFW_KEY_UP:
      return Key::Up;
    case GLFW_KEY_PAGE_UP:
      return Key::PageDown;
    case GLFW_KEY_PAGE_DOWN:
      return Key::PageUp;
    case GLFW_KEY_HOME:
      return Key::Home;
    case GLFW_KEY_END:
      return Key::End;
    case GLFW_KEY_CAPS_LOCK:
      return Key::Unknown;
    case GLFW_KEY_SCROLL_LOCK:
      return Key::Unknown;
    case GLFW_KEY_NUM_LOCK:
      return Key::Unknown;
    case GLFW_KEY_PRINT_SCREEN:
      return Key::Unknown;
    case GLFW_KEY_PAUSE:
      return Key::Pause;
    case GLFW_KEY_F1:
      return Key::F1;
    case GLFW_KEY_F2:
      return Key::F2;
    case GLFW_KEY_F3:
      return Key::F3;
    case GLFW_KEY_F4:
      return Key::F4;
    case GLFW_KEY_F5:
      return Key::F5;
    case GLFW_KEY_F6:
      return Key::F6;
    case GLFW_KEY_F7:
      return Key::F7;
    case GLFW_KEY_F8:
      return Key::F8;
    case GLFW_KEY_F9:
      return Key::F9;
    case GLFW_KEY_F10:
      return Key::F10;
    case GLFW_KEY_F11:
      return Key::F11;
    case GLFW_KEY_F12:
      return Key::F12;
    case GLFW_KEY_F13:
      return Key::F13;
    case GLFW_KEY_F14:
      return Key::F14;
    case GLFW_KEY_F15:
      return Key::F15;
    case GLFW_KEY_F16:
      return Key::F16;
    case GLFW_KEY_F17:
      return Key::F17;
    case GLFW_KEY_F18:
      return Key::F18;
    case GLFW_KEY_F19:
      return Key::F19;
    case GLFW_KEY_F20:
      return Key::F20;
    case GLFW_KEY_F21:
      return Key::F21;
    case GLFW_KEY_F22:
      return Key::F22;
    case GLFW_KEY_F23:
      return Key::F23;
    case GLFW_KEY_F24:
      return Key::F24;
    case GLFW_KEY_F25:
      return Key::F25;
    case GLFW_KEY_KP_0:
      return Key::Numpad0;
    case GLFW_KEY_KP_1:
      return Key::Numpad1;
    case GLFW_KEY_KP_2:
      return Key::Numpad2;
    case GLFW_KEY_KP_3:
      return Key::Numpad3;
    case GLFW_KEY_KP_4:
      return Key::Numpad4;
    case GLFW_KEY_KP_5:
      return Key::Numpad5;
    case GLFW_KEY_KP_6:
      return Key::Numpad6;
    case GLFW_KEY_KP_7:
      return Key::Numpad7;
    case GLFW_KEY_KP_8:
      return Key::Numpad8;
    case GLFW_KEY_KP_9:
      return Key::Numpad9;
    case GLFW_KEY_KP_DECIMAL:
      return Key::Unknown;
    case GLFW_KEY_KP_DIVIDE:
      return Key::Unknown;
    case GLFW_KEY_KP_MULTIPLY:
      return Key::Unknown;
    case GLFW_KEY_KP_SUBTRACT:
      return Key::Unknown;
    case GLFW_KEY_KP_ADD:
      return Key::Unknown;
    case GLFW_KEY_KP_ENTER:
      return Key::Unknown;
    case GLFW_KEY_KP_EQUAL:
      return Key::Unknown;
    case GLFW_KEY_LEFT_SHIFT:
      return Key::LShift;
    case GLFW_KEY_LEFT_CONTROL:
      return Key::LControl;
    case GLFW_KEY_LEFT_ALT:
      return Key::LAlt;
    case GLFW_KEY_LEFT_SUPER:
      return Key::LSystem;
    case GLFW_KEY_RIGHT_SHIFT:
      return Key::RShift;
    case GLFW_KEY_RIGHT_CONTROL:
      return Key::RControl;
    case GLFW_KEY_RIGHT_ALT:
      return Key::RAlt;
    case GLFW_KEY_RIGHT_SUPER:
      return Key::RSystem;
    case GLFW_KEY_MENU:
      return Key::Menu;

    default:
      return Key::Unknown;
  };
}

void glfwErrorCallback(int error, const char* description) {
  LOG(Error) << "GLFW Error (" << error << ") " << description;
}

}  // namespace

Window::Window() = default;

bool Window::initialize(WindowDelegate* delegate) {
  DCHECK(delegate) << "Can't create a window with no delegate.";

  m_delegate = delegate;

  // Initialize GLFW.
  if (!glfwInit()) {
    LOG(Error) << "Could not initialize glfw.";
    m_delegate = nullptr;
    return false;
  }

  glfwSetErrorCallback(glfwErrorCallback);

  m_clientSize = {1600, 900};

  // Set up our hints.
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  // Create the window.
  auto title = nu::zeroTerminated(m_delegate->getTitle());
  m_window =
      glfwCreateWindow(m_clientSize.width, m_clientSize.height, title.data(), nullptr, nullptr);
  if (!m_window) {
    LOG(Error) << "Could not create window.";
    m_delegate = nullptr;
    return false;
  }

  // Center the window on the screen.
  GLFWmonitor* currentMonitor = glfwGetPrimaryMonitor();
  if (currentMonitor) {
    const GLFWvidmode* videoMode = glfwGetVideoMode(currentMonitor);
    int currentWidth, currentHeight;
    glfwGetWindowSize(m_window, &currentWidth, &currentHeight);

    glfwSetWindowPos(m_window, (videoMode->width - currentWidth) / 2,
                     (videoMode->height - currentHeight) / 2);
  }

  // Set up the callbacks for the window.
  glfwSetWindowUserPointer(m_window, this);
  glfwSetFramebufferSizeCallback(m_window, frameBufferSizeCallback);
  glfwSetCursorPosCallback(m_window, cursorPositionCallback);
  glfwSetMouseButtonCallback(m_window, mouseButtonCallback);
  glfwSetScrollCallback(m_window, scrollCallback);
  glfwSetKeyCallback(m_window, keyCallback);

  // Make the new window the current context.
  glfwMakeContextCurrent(m_window);

  // Enable v-sync.
  glfwSwapInterval(1);

  // Initialize glad, so we can use GL extensions.
  gladLoadGL();

  I32 major = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MAJOR);
  I32 minor = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_VERSION_MINOR);
  I32 rev = glfwGetWindowAttrib(m_window, GLFW_CONTEXT_REVISION);

  LOG(Info) << "OpenGL version: " << major << "." << minor << "." << rev;
  LOG(Info) << "Supported OpenGL is " << glGetString(GL_VERSION);
  LOG(Info) << "Supported GLSL is " << glGetString(GL_SHADING_LANGUAGE_VERSION);

  m_renderer.resize(m_clientSize);

  // Initialize the debug interface.
  m_debugInterface.initialize();

  // Let the delegate know we were just created.
  bool success = delegate->onWindowCreated(this);
  if (!success) {
    m_delegate = nullptr;
    return false;
  }

  // We send a window resized to the delegate as well so that it can do any
  // setup needed.
  delegate->onWindowResized(m_clientSize);

  return true;
}

Window::~Window() {
  glfwDestroyWindow(m_window);

  glfwTerminate();
}

bool Window::processEvents() {
  // Handle events...
  glfwPollEvents();

  // ...and tell the caller if event processing should continue or not.
  return !glfwWindowShouldClose(m_window);
}

void Window::activateContext() {
  glfwMakeContextCurrent(m_window);
}

void Window::paint() {
  nu::Timer timer;

  m_renderer.beginFrame();

  PROFILE("frame")

  {
    PROFILE("delegate paint")
    m_delegate->onRender(&m_renderer);
  }

  {
    PROFILE("debug interface render")
    m_debugInterface.render(m_lastFPS);
  }

  nu::detail::getCurrentProfileMetrics()->reset();

  m_renderer.endFrame();

  // Swap buffers.
  glfwSwapBuffers(m_window);

  m_lastFPS = 1000000.0 / timer.elapsed();
}

// static
void Window::frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
  Window* windowPtr = getUserPointer(window);

  windowPtr->m_clientSize = {width, height};

  // Resize our renderer.
  windowPtr->m_renderer.resize(windowPtr->m_clientSize);

  windowPtr->m_debugInterface.resize({width, height});

  fl::Size windowSize(static_cast<U32>(width), static_cast<U32>(height));
  windowPtr->m_delegate->onWindowResized(windowPtr->m_clientSize);
}

// static
void Window::cursorPositionCallback(GLFWwindow* window, double xPos, double yPos) {
  Window* windowPtr = getUserPointer(window);

  // Send the event to the delegate.
  fl::Pos mousePos{static_cast<I32>(std::round(xPos)), static_cast<I32>(std::round(yPos))};

  MouseEvent evt{Event::MouseMoved, mousePos, MouseEvent::Button::None};
  windowPtr->m_delegate->onMouseMoved(evt);
}

// static
void Window::mouseButtonCallback(GLFWwindow* window, int button, int action, int NU_UNUSED(mods)) {
  Window* windowPtr = getUserPointer(window);

  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  fl::Pos mousePos{static_cast<I32>(std::round(xPos)), static_cast<I32>(std::round(yPos))};

  MouseEvent::Button evtButton{MouseEvent::Button::None};
  switch (button) {
    case GLFW_MOUSE_BUTTON_LEFT:
      evtButton = MouseEvent::Button::Left;
      break;

    case GLFW_MOUSE_BUTTON_MIDDLE:
      evtButton = MouseEvent::Button::Middle;
      break;

    case GLFW_MOUSE_BUTTON_RIGHT:
      evtButton = MouseEvent::Button::Right;
      break;

    default:
      NOTREACHED() << "Invalid button type.";
      break;
  }

  if (action == GLFW_PRESS) {
    MouseEvent evt{Event::MousePressed, mousePos, evtButton};
    windowPtr->m_delegate->onMousePressed(evt);
  } else if (action == GLFW_RELEASE) {
    MouseEvent evt{Event::MouseReleased, mousePos, evtButton};
    windowPtr->m_delegate->onMouseReleased(evt);
  }
}

// static
void Window::scrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
  Window* windowPtr = getUserPointer(window);

  double xPos, yPos;
  glfwGetCursorPos(window, &xPos, &yPos);
  fl::Pos mousePos{static_cast<I32>(std::round(xPos)), static_cast<I32>(std::round(yPos))};

  fl::Pos scrollOffset{static_cast<I32>(std::lround(xOffset)),
                       static_cast<I32>(std::lround(yOffset))};
  MouseWheelEvent evt{Event::MouseWheel, mousePos, scrollOffset};
  windowPtr->m_delegate->onMouseWheel(evt);
}

// static
void Window::keyCallback(GLFWwindow* window, int key, int NU_UNUSED(scancode), int action,
                         int NU_UNUSED(mods)) {
  // We don't care for repeats.
  if (action == GLFW_REPEAT) {
    return;
  }

  Window* windowPtr = getUserPointer(window);

  if (action == GLFW_PRESS) {
    KeyEvent evt{Event::KeyPressed, getKeyFromGLFWKey(key)};
    windowPtr->m_delegate->onKeyPressed(evt);
  } else {
    KeyEvent evt{Event::KeyReleased, getKeyFromGLFWKey(key)};
    windowPtr->m_delegate->onKeyReleased(evt);
  }
}

}  // namespace ca
