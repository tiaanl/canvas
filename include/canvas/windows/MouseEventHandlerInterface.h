
#ifndef CANVAS_WINDOWS_MOUSEVENTHANDLER_H_
#define CANVAS_WINDOWS_MOUSEVENTHANDLER_H_

#include "canvas/windows/event.h"

namespace ca {

class MouseEventHandlerInterface {
    virtual void onMouseMoved(const MouseEvent& evt) = 0;
    virtual void onMousePressed(const MouseEvent& evt) = 0;
    virtual void onMouseReleased(const MouseEvent& evt) = 0;
    virtual void onMouseWheel(const MouseWheelEvent& evt) = 0;
};

}  // namespace ca

#endif  // CANVAS_WINDOWS_MOUSEVENTHANDLER_H_
