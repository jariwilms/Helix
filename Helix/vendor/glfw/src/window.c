//========================================================================
// GLFW 3.4 - www.glfw.org
//------------------------------------------------------------------------
// Copyright (c) 2002-2006 Marcus Geelnard
// Copyright (c) 2006-2019 Camilla Löwy <elmindreda@glfw.org>
// Copyright (c) 2012 Torsten Walluhn <tw@mad-cad.net>
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would
//    be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not
//    be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//
//========================================================================
// Please use C89 style variable declarations in this file because VS 2010
//========================================================================

#include "internal.h"

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>


//////////////////////////////////////////////////////////////////////////
//////                         GLFW event API                       //////
//////////////////////////////////////////////////////////////////////////

// Notifies shared code that a window has lost or received input focus
//
void _glfwInputWindowFocus(_GLFWwindow* m_window, GLFWbool focused)
{
    if (m_window->callbacks.focus)
        m_window->callbacks.focus((GLFWwindow*) m_window, focused);

    if (!focused)
    {
        int key, button;

        for (key = 0;  key <= GLFW_KEY_LAST;  key++)
        {
            if (m_window->keys[key] == GLFW_PRESS)
            {
                const int scancode = _glfw.platform.getKeyScancode(key);
                _glfwInputKey(m_window, key, scancode, GLFW_RELEASE, 0);
            }
        }

        for (button = 0;  button <= GLFW_MOUSE_BUTTON_LAST;  button++)
        {
            if (m_window->mouseButtons[button] == GLFW_PRESS)
                _glfwInputMouseClick(m_window, button, GLFW_RELEASE, 0);
        }
    }
}

// Notifies shared code that a window has moved
// The position is specified in content area relative screen coordinates
//
void _glfwInputWindowPos(_GLFWwindow* m_window, int x, int y)
{
    if (m_window->callbacks.pos)
        m_window->callbacks.pos((GLFWwindow*) m_window, x, y);
}

// Notifies shared code that a window has been resized
// The size is specified in screen coordinates
//
void _glfwInputWindowSize(_GLFWwindow* m_window, int width, int height)
{
    if (m_window->callbacks.size)
        m_window->callbacks.size((GLFWwindow*) m_window, width, height);
}

// Notifies shared code that a window has been iconified or restored
//
void _glfwInputWindowIconify(_GLFWwindow* m_window, GLFWbool iconified)
{
    if (m_window->callbacks.iconify)
        m_window->callbacks.iconify((GLFWwindow*) m_window, iconified);
}

// Notifies shared code that a window has been maximized or restored
//
void _glfwInputWindowMaximize(_GLFWwindow* m_window, GLFWbool maximized)
{
    if (m_window->callbacks.maximize)
        m_window->callbacks.maximize((GLFWwindow*) m_window, maximized);
}

// Notifies shared code that a window framebuffer has been resized
// The size is specified in pixels
//
void _glfwInputFramebufferSize(_GLFWwindow* m_window, int width, int height)
{
    if (m_window->callbacks.fbsize)
        m_window->callbacks.fbsize((GLFWwindow*) m_window, width, height);
}

// Notifies shared code that a window content scale has changed
// The scale is specified as the ratio between the current and default DPI
//
void _glfwInputWindowContentScale(_GLFWwindow* m_window, float xscale, float yscale)
{
    if (m_window->callbacks.scale)
        m_window->callbacks.scale((GLFWwindow*) m_window, xscale, yscale);
}

// Notifies shared code that the window contents needs updating
//
void _glfwInputWindowDamage(_GLFWwindow* m_window)
{
    if (m_window->callbacks.refresh)
        m_window->callbacks.refresh((GLFWwindow*) m_window);
}

// Notifies shared code that the user wishes to close a window
//
void _glfwInputWindowCloseRequest(_GLFWwindow* m_window)
{
    m_window->shouldClose = GLFW_TRUE;

    if (m_window->callbacks.close)
        m_window->callbacks.close((GLFWwindow*) m_window);
}

// Notifies shared code that a window has changed its desired monitor
//
void _glfwInputWindowMonitor(_GLFWwindow* m_window, _GLFWmonitor* monitor)
{
    m_window->monitor = monitor;
}

//////////////////////////////////////////////////////////////////////////
//////                        GLFW public API                       //////
//////////////////////////////////////////////////////////////////////////

GLFWAPI GLFWwindow* glfwCreateWindow(int width, int height,
                                     const char* title,
                                     GLFWmonitor* monitor,
                                     GLFWwindow* share)
{
    _GLFWfbconfig fbconfig;
    _GLFWctxconfig ctxconfig;
    _GLFWwndconfig wndconfig;
    _GLFWwindow* m_window;

    assert(title != NULL);
    assert(width >= 0);
    assert(height >= 0);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);

    if (width <= 0 || height <= 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE,
                        "Invalid window size %ix%i",
                        width, height);

        return NULL;
    }

    fbconfig  = _glfw.hints.framebuffer;
    ctxconfig = _glfw.hints.context;
    wndconfig = _glfw.hints.m_window;

    wndconfig.width   = width;
    wndconfig.height  = height;
    wndconfig.title   = title;
    ctxconfig.share   = (_GLFWwindow*) share;

    if (!_glfwIsValidContextConfig(&ctxconfig))
        return NULL;

    m_window = _glfw_calloc(1, sizeof(_GLFWwindow));
    m_window->next = _glfw.windowListHead;
    _glfw.windowListHead = m_window;

    m_window->videoMode.width       = width;
    m_window->videoMode.height      = height;
    m_window->videoMode.redBits     = fbconfig.redBits;
    m_window->videoMode.greenBits   = fbconfig.greenBits;
    m_window->videoMode.blueBits    = fbconfig.blueBits;
    m_window->videoMode.refreshRate = _glfw.hints.refreshRate;

    m_window->monitor          = (_GLFWmonitor*) monitor;
    m_window->resizable        = wndconfig.resizable;
    m_window->decorated        = wndconfig.decorated;
    m_window->autoIconify      = wndconfig.autoIconify;
    m_window->floating         = wndconfig.floating;
    m_window->focusOnShow      = wndconfig.focusOnShow;
    m_window->mousePassthrough = wndconfig.mousePassthrough;
    m_window->cursorMode       = GLFW_CURSOR_NORMAL;

    m_window->doublebuffer = fbconfig.doublebuffer;

    m_window->minwidth    = GLFW_DONT_CARE;
    m_window->minheight   = GLFW_DONT_CARE;
    m_window->maxwidth    = GLFW_DONT_CARE;
    m_window->maxheight   = GLFW_DONT_CARE;
    m_window->numer       = GLFW_DONT_CARE;
    m_window->denom       = GLFW_DONT_CARE;

    if (!_glfw.platform.createWindow(m_window, &wndconfig, &ctxconfig, &fbconfig))
    {
        glfwDestroyWindow((GLFWwindow*) m_window);
        return NULL;
    }

    return (GLFWwindow*) m_window;
}

void glfwDefaultWindowHints(void)
{
    _GLFW_REQUIRE_INIT();

    // The default is OpenGL with minimum version 1.0
    memset(&_glfw.hints.context, 0, sizeof(_glfw.hints.context));
    _glfw.hints.context.client = GLFW_OPENGL_API;
    _glfw.hints.context.source = GLFW_NATIVE_CONTEXT_API;
    _glfw.hints.context.major  = 1;
    _glfw.hints.context.minor  = 0;

    // The default is a focused, visible, resizable window with decorations
    memset(&_glfw.hints.m_window, 0, sizeof(_glfw.hints.m_window));
    _glfw.hints.m_window.resizable    = GLFW_TRUE;
    _glfw.hints.m_window.visible      = GLFW_TRUE;
    _glfw.hints.m_window.decorated    = GLFW_TRUE;
    _glfw.hints.m_window.focused      = GLFW_TRUE;
    _glfw.hints.m_window.autoIconify  = GLFW_TRUE;
    _glfw.hints.m_window.centerCursor = GLFW_TRUE;
    _glfw.hints.m_window.focusOnShow  = GLFW_TRUE;

    // The default is 24 bits of color, 24 bits of depth and 8 bits of stencil,
    // double buffered
    memset(&_glfw.hints.framebuffer, 0, sizeof(_glfw.hints.framebuffer));
    _glfw.hints.framebuffer.redBits      = 8;
    _glfw.hints.framebuffer.greenBits    = 8;
    _glfw.hints.framebuffer.blueBits     = 8;
    _glfw.hints.framebuffer.alphaBits    = 8;
    _glfw.hints.framebuffer.depthBits    = 24;
    _glfw.hints.framebuffer.stencilBits  = 8;
    _glfw.hints.framebuffer.doublebuffer = GLFW_TRUE;

    // The default is to select the highest available refresh rate
    _glfw.hints.refreshRate = GLFW_DONT_CARE;

    // The default is to use full Retina resolution framebuffers
    _glfw.hints.m_window.ns.retina = GLFW_TRUE;
}

GLFWAPI void glfwWindowHint(int hint, int value)
{
    _GLFW_REQUIRE_INIT();

    switch (hint)
    {
        case GLFW_RED_BITS:
            _glfw.hints.framebuffer.redBits = value;
            return;
        case GLFW_GREEN_BITS:
            _glfw.hints.framebuffer.greenBits = value;
            return;
        case GLFW_BLUE_BITS:
            _glfw.hints.framebuffer.blueBits = value;
            return;
        case GLFW_ALPHA_BITS:
            _glfw.hints.framebuffer.alphaBits = value;
            return;
        case GLFW_DEPTH_BITS:
            _glfw.hints.framebuffer.depthBits = value;
            return;
        case GLFW_STENCIL_BITS:
            _glfw.hints.framebuffer.stencilBits = value;
            return;
        case GLFW_ACCUM_RED_BITS:
            _glfw.hints.framebuffer.accumRedBits = value;
            return;
        case GLFW_ACCUM_GREEN_BITS:
            _glfw.hints.framebuffer.accumGreenBits = value;
            return;
        case GLFW_ACCUM_BLUE_BITS:
            _glfw.hints.framebuffer.accumBlueBits = value;
            return;
        case GLFW_ACCUM_ALPHA_BITS:
            _glfw.hints.framebuffer.accumAlphaBits = value;
            return;
        case GLFW_AUX_BUFFERS:
            _glfw.hints.framebuffer.auxBuffers = value;
            return;
        case GLFW_STEREO:
            _glfw.hints.framebuffer.stereo = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_DOUBLEBUFFER:
            _glfw.hints.framebuffer.doublebuffer = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_TRANSPARENT_FRAMEBUFFER:
            _glfw.hints.framebuffer.transparent = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_SAMPLES:
            _glfw.hints.framebuffer.samples = value;
            return;
        case GLFW_SRGB_CAPABLE:
            _glfw.hints.framebuffer.sRGB = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_RESIZABLE:
            _glfw.hints.m_window.resizable = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_DECORATED:
            _glfw.hints.m_window.decorated = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FOCUSED:
            _glfw.hints.m_window.focused = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_AUTO_ICONIFY:
            _glfw.hints.m_window.autoIconify = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FLOATING:
            _glfw.hints.m_window.floating = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_MAXIMIZED:
            _glfw.hints.m_window.maximized = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_VISIBLE:
            _glfw.hints.m_window.visible = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_COCOA_RETINA_FRAMEBUFFER:
            _glfw.hints.m_window.ns.retina = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_WIN32_KEYBOARD_MENU:
            _glfw.hints.m_window.win32.keymenu = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_COCOA_GRAPHICS_SWITCHING:
            _glfw.hints.context.nsgl.offline = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_SCALE_TO_MONITOR:
            _glfw.hints.m_window.scaleToMonitor = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CENTER_CURSOR:
            _glfw.hints.m_window.centerCursor = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_FOCUS_ON_SHOW:
            _glfw.hints.m_window.focusOnShow = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_MOUSE_PASSTHROUGH:
            _glfw.hints.m_window.mousePassthrough = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CLIENT_API:
            _glfw.hints.context.client = value;
            return;
        case GLFW_CONTEXT_CREATION_API:
            _glfw.hints.context.source = value;
            return;
        case GLFW_CONTEXT_VERSION_MAJOR:
            _glfw.hints.context.major = value;
            return;
        case GLFW_CONTEXT_VERSION_MINOR:
            _glfw.hints.context.minor = value;
            return;
        case GLFW_CONTEXT_ROBUSTNESS:
            _glfw.hints.context.robustness = value;
            return;
        case GLFW_OPENGL_FORWARD_COMPAT:
            _glfw.hints.context.forward = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CONTEXT_DEBUG:
            _glfw.hints.context.debug = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_CONTEXT_NO_ERROR:
            _glfw.hints.context.noerror = value ? GLFW_TRUE : GLFW_FALSE;
            return;
        case GLFW_OPENGL_PROFILE:
            _glfw.hints.context.profile = value;
            return;
        case GLFW_CONTEXT_RELEASE_BEHAVIOR:
            _glfw.hints.context.release = value;
            return;
        case GLFW_REFRESH_RATE:
            _glfw.hints.refreshRate = value;
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window hint 0x%08X", hint);
}

GLFWAPI void glfwWindowHintString(int hint, const char* value)
{
    assert(value != NULL);

    _GLFW_REQUIRE_INIT();

    switch (hint)
    {
        case GLFW_COCOA_FRAME_NAME:
            strncpy(_glfw.hints.m_window.ns.frameName, value,
                    sizeof(_glfw.hints.m_window.ns.frameName) - 1);
            return;
        case GLFW_X11_CLASS_NAME:
            strncpy(_glfw.hints.m_window.x11.className, value,
                    sizeof(_glfw.hints.m_window.x11.className) - 1);
            return;
        case GLFW_X11_INSTANCE_NAME:
            strncpy(_glfw.hints.m_window.x11.instanceName, value,
                    sizeof(_glfw.hints.m_window.x11.instanceName) - 1);
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window hint string 0x%08X", hint);
}

GLFWAPI void glfwDestroyWindow(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;

    _GLFW_REQUIRE_INIT();

    // Allow closing of NULL (to match the behavior of free)
    if (m_window == NULL)
        return;

    // Clear all callbacks to avoid exposing a half torn-down window object
    memset(&m_window->callbacks, 0, sizeof(m_window->callbacks));

    // The window's context must not be current on another thread when the
    // window is destroyed
    if (m_window == _glfwPlatformGetTls(&_glfw.contextSlot))
        glfwMakeContextCurrent(NULL);

    _glfw.platform.destroyWindow(m_window);

    // Unlink window from global linked list
    {
        _GLFWwindow** prev = &_glfw.windowListHead;

        while (*prev != m_window)
            prev = &((*prev)->next);

        *prev = m_window->next;
    }

    _glfw_free(m_window);
}

GLFWAPI int glfwWindowShouldClose(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(0);
    return m_window->shouldClose;
}

GLFWAPI void glfwSetWindowShouldClose(GLFWwindow* handle, int value)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();
    m_window->shouldClose = value;
}

GLFWAPI void glfwSetWindowTitle(GLFWwindow* handle, const char* title)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);
    assert(title != NULL);

    _GLFW_REQUIRE_INIT();
    _glfw.platform.setWindowTitle(m_window, title);
}

GLFWAPI void glfwSetWindowIcon(GLFWwindow* handle,
                               int count, const GLFWimage* images)
{
    int i;
    _GLFWwindow* m_window = (_GLFWwindow*) handle;

    assert(m_window != NULL);
    assert(count >= 0);
    assert(count == 0 || images != NULL);

    _GLFW_REQUIRE_INIT();

    if (count < 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid image count for window icon");
        return;
    }

    for (i = 0; i < count; i++)
    {
        assert(images[i].pixels != NULL);

        if (images[i].width <= 0 || images[i].height <= 0)
        {
            _glfwInputError(GLFW_INVALID_VALUE,
                            "Invalid image dimensions for window icon");
            return;
        }
    }

    _glfw.platform.setWindowIcon(m_window, count, images);
}

GLFWAPI void glfwGetWindowPos(GLFWwindow* handle, int* xpos, int* ypos)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    if (xpos)
        *xpos = 0;
    if (ypos)
        *ypos = 0;

    _GLFW_REQUIRE_INIT();
    _glfw.platform.getWindowPos(m_window, xpos, ypos);
}

GLFWAPI void glfwSetWindowPos(GLFWwindow* handle, int xpos, int ypos)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    if (m_window->monitor)
        return;

    _glfw.platform.setWindowPos(m_window, xpos, ypos);
}

GLFWAPI void glfwGetWindowSize(GLFWwindow* handle, int* width, int* height)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    if (width)
        *width = 0;
    if (height)
        *height = 0;

    _GLFW_REQUIRE_INIT();
    _glfw.platform.getWindowSize(m_window, width, height);
}

GLFWAPI void glfwSetWindowSize(GLFWwindow* handle, int width, int height)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);
    assert(width >= 0);
    assert(height >= 0);

    _GLFW_REQUIRE_INIT();

    m_window->videoMode.width  = width;
    m_window->videoMode.height = height;

    _glfw.platform.setWindowSize(m_window, width, height);
}

GLFWAPI void glfwSetWindowSizeLimits(GLFWwindow* handle,
                                     int minwidth, int minheight,
                                     int maxwidth, int maxheight)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    if (minwidth != GLFW_DONT_CARE && minheight != GLFW_DONT_CARE)
    {
        if (minwidth < 0 || minheight < 0)
        {
            _glfwInputError(GLFW_INVALID_VALUE,
                            "Invalid window minimum size %ix%i",
                            minwidth, minheight);
            return;
        }
    }

    if (maxwidth != GLFW_DONT_CARE && maxheight != GLFW_DONT_CARE)
    {
        if (maxwidth < 0 || maxheight < 0 ||
            maxwidth < minwidth || maxheight < minheight)
        {
            _glfwInputError(GLFW_INVALID_VALUE,
                            "Invalid window maximum size %ix%i",
                            maxwidth, maxheight);
            return;
        }
    }

    m_window->minwidth  = minwidth;
    m_window->minheight = minheight;
    m_window->maxwidth  = maxwidth;
    m_window->maxheight = maxheight;

    if (m_window->monitor || !m_window->resizable)
        return;

    _glfw.platform.setWindowSizeLimits(m_window,
                                       minwidth, minheight,
                                       maxwidth, maxheight);
}

GLFWAPI void glfwSetWindowAspectRatio(GLFWwindow* handle, int numer, int denom)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);
    assert(numer != 0);
    assert(denom != 0);

    _GLFW_REQUIRE_INIT();

    if (numer != GLFW_DONT_CARE && denom != GLFW_DONT_CARE)
    {
        if (numer <= 0 || denom <= 0)
        {
            _glfwInputError(GLFW_INVALID_VALUE,
                            "Invalid window aspect ratio %i:%i",
                            numer, denom);
            return;
        }
    }

    m_window->numer = numer;
    m_window->denom = denom;

    if (m_window->monitor || !m_window->resizable)
        return;

    _glfw.platform.setWindowAspectRatio(m_window, numer, denom);
}

GLFWAPI void glfwGetFramebufferSize(GLFWwindow* handle, int* width, int* height)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    if (width)
        *width = 0;
    if (height)
        *height = 0;

    _GLFW_REQUIRE_INIT();
    _glfw.platform.getFramebufferSize(m_window, width, height);
}

GLFWAPI void glfwGetWindowFrameSize(GLFWwindow* handle,
                                    int* left, int* top,
                                    int* right, int* bottom)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    if (left)
        *left = 0;
    if (top)
        *top = 0;
    if (right)
        *right = 0;
    if (bottom)
        *bottom = 0;

    _GLFW_REQUIRE_INIT();
    _glfw.platform.getWindowFrameSize(m_window, left, top, right, bottom);
}

GLFWAPI void glfwGetWindowContentScale(GLFWwindow* handle,
                                       float* xscale, float* yscale)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    if (xscale)
        *xscale = 0.f;
    if (yscale)
        *yscale = 0.f;

    _GLFW_REQUIRE_INIT();
    _glfw.platform.getWindowContentScale(m_window, xscale, yscale);
}

GLFWAPI float glfwGetWindowOpacity(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(1.f);
    return _glfw.platform.getWindowOpacity(m_window);
}

GLFWAPI void glfwSetWindowOpacity(GLFWwindow* handle, float opacity)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);
    assert(opacity == opacity);
    assert(opacity >= 0.f);
    assert(opacity <= 1.f);

    _GLFW_REQUIRE_INIT();

    if (opacity != opacity || opacity < 0.f || opacity > 1.f)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid window opacity %f", opacity);
        return;
    }

    _glfw.platform.setWindowOpacity(m_window, opacity);
}

GLFWAPI void glfwIconifyWindow(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();
    _glfw.platform.iconifyWindow(m_window);
}

GLFWAPI void glfwRestoreWindow(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();
    _glfw.platform.restoreWindow(m_window);
}

GLFWAPI void glfwMaximizeWindow(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    if (m_window->monitor)
        return;

    _glfw.platform.maximizeWindow(m_window);
}

GLFWAPI void glfwShowWindow(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    if (m_window->monitor)
        return;

    _glfw.platform.showWindow(m_window);

    if (m_window->focusOnShow)
        _glfw.platform.focusWindow(m_window);
}

GLFWAPI void glfwRequestWindowAttention(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    _glfw.platform.requestWindowAttention(m_window);
}

GLFWAPI void glfwHideWindow(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    if (m_window->monitor)
        return;

    _glfw.platform.hideWindow(m_window);
}

GLFWAPI void glfwFocusWindow(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    _glfw.platform.focusWindow(m_window);
}

GLFWAPI int glfwGetWindowAttrib(GLFWwindow* handle, int attrib)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(0);

    switch (attrib)
    {
        case GLFW_FOCUSED:
            return _glfw.platform.windowFocused(m_window);
        case GLFW_ICONIFIED:
            return _glfw.platform.windowIconified(m_window);
        case GLFW_VISIBLE:
            return _glfw.platform.windowVisible(m_window);
        case GLFW_MAXIMIZED:
            return _glfw.platform.windowMaximized(m_window);
        case GLFW_HOVERED:
            return _glfw.platform.windowHovered(m_window);
        case GLFW_FOCUS_ON_SHOW:
            return m_window->focusOnShow;
        case GLFW_MOUSE_PASSTHROUGH:
            return m_window->mousePassthrough;
        case GLFW_TRANSPARENT_FRAMEBUFFER:
            return _glfw.platform.framebufferTransparent(m_window);
        case GLFW_RESIZABLE:
            return m_window->resizable;
        case GLFW_DECORATED:
            return m_window->decorated;
        case GLFW_FLOATING:
            return m_window->floating;
        case GLFW_AUTO_ICONIFY:
            return m_window->autoIconify;
        case GLFW_DOUBLEBUFFER:
            return m_window->doublebuffer;
        case GLFW_CLIENT_API:
            return m_window->context.client;
        case GLFW_CONTEXT_CREATION_API:
            return m_window->context.source;
        case GLFW_CONTEXT_VERSION_MAJOR:
            return m_window->context.major;
        case GLFW_CONTEXT_VERSION_MINOR:
            return m_window->context.minor;
        case GLFW_CONTEXT_REVISION:
            return m_window->context.revision;
        case GLFW_CONTEXT_ROBUSTNESS:
            return m_window->context.robustness;
        case GLFW_OPENGL_FORWARD_COMPAT:
            return m_window->context.forward;
        case GLFW_CONTEXT_DEBUG:
            return m_window->context.debug;
        case GLFW_OPENGL_PROFILE:
            return m_window->context.profile;
        case GLFW_CONTEXT_RELEASE_BEHAVIOR:
            return m_window->context.release;
        case GLFW_CONTEXT_NO_ERROR:
            return m_window->context.noerror;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window attribute 0x%08X", attrib);
    return 0;
}

GLFWAPI void glfwSetWindowAttrib(GLFWwindow* handle, int attrib, int value)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();

    value = value ? GLFW_TRUE : GLFW_FALSE;

    switch (attrib)
    {
        case GLFW_AUTO_ICONIFY:
            m_window->autoIconify = value;
            return;

        case GLFW_RESIZABLE:
            m_window->resizable = value;
            if (!m_window->monitor)
                _glfw.platform.setWindowResizable(m_window, value);
            return;

        case GLFW_DECORATED:
            m_window->decorated = value;
            if (!m_window->monitor)
                _glfw.platform.setWindowDecorated(m_window, value);
            return;

        case GLFW_FLOATING:
            m_window->floating = value;
            if (!m_window->monitor)
                _glfw.platform.setWindowFloating(m_window, value);
            return;

        case GLFW_FOCUS_ON_SHOW:
            m_window->focusOnShow = value;
            return;

        case GLFW_MOUSE_PASSTHROUGH:
            m_window->mousePassthrough = value;
            _glfw.platform.setWindowMousePassthrough(m_window, value);
            return;
    }

    _glfwInputError(GLFW_INVALID_ENUM, "Invalid window attribute 0x%08X", attrib);
}

GLFWAPI GLFWmonitor* glfwGetWindowMonitor(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    return (GLFWmonitor*) m_window->monitor;
}

GLFWAPI void glfwSetWindowMonitor(GLFWwindow* wh,
                                  GLFWmonitor* mh,
                                  int xpos, int ypos,
                                  int width, int height,
                                  int refreshRate)
{
    _GLFWwindow* m_window = (_GLFWwindow*) wh;
    _GLFWmonitor* monitor = (_GLFWmonitor*) mh;
    assert(m_window != NULL);
    assert(width >= 0);
    assert(height >= 0);

    _GLFW_REQUIRE_INIT();

    if (width <= 0 || height <= 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE,
                        "Invalid window size %ix%i",
                        width, height);
        return;
    }

    if (refreshRate < 0 && refreshRate != GLFW_DONT_CARE)
    {
        _glfwInputError(GLFW_INVALID_VALUE,
                        "Invalid refresh rate %i",
                        refreshRate);
        return;
    }

    m_window->videoMode.width       = width;
    m_window->videoMode.height      = height;
    m_window->videoMode.refreshRate = refreshRate;

    _glfw.platform.setWindowMonitor(m_window, monitor,
                                    xpos, ypos, width, height,
                                    refreshRate);
}

GLFWAPI void glfwSetWindowUserPointer(GLFWwindow* handle, void* pointer)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT();
    m_window->userPointer = pointer;
}

GLFWAPI void* glfwGetWindowUserPointer(GLFWwindow* handle)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    return m_window->userPointer;
}

GLFWAPI GLFWwindowposfun glfwSetWindowPosCallback(GLFWwindow* handle,
                                                  GLFWwindowposfun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowposfun, m_window->callbacks.pos, cbfun);
    return cbfun;
}

GLFWAPI GLFWwindowsizefun glfwSetWindowSizeCallback(GLFWwindow* handle,
                                                    GLFWwindowsizefun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowsizefun, m_window->callbacks.size, cbfun);
    return cbfun;
}

GLFWAPI GLFWwindowclosefun glfwSetWindowCloseCallback(GLFWwindow* handle,
                                                      GLFWwindowclosefun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowclosefun, m_window->callbacks.close, cbfun);
    return cbfun;
}

GLFWAPI GLFWwindowrefreshfun glfwSetWindowRefreshCallback(GLFWwindow* handle,
                                                          GLFWwindowrefreshfun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowrefreshfun, m_window->callbacks.refresh, cbfun);
    return cbfun;
}

GLFWAPI GLFWwindowfocusfun glfwSetWindowFocusCallback(GLFWwindow* handle,
                                                      GLFWwindowfocusfun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowfocusfun, m_window->callbacks.focus, cbfun);
    return cbfun;
}

GLFWAPI GLFWwindowiconifyfun glfwSetWindowIconifyCallback(GLFWwindow* handle,
                                                          GLFWwindowiconifyfun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowiconifyfun, m_window->callbacks.iconify, cbfun);
    return cbfun;
}

GLFWAPI GLFWwindowmaximizefun glfwSetWindowMaximizeCallback(GLFWwindow* handle,
                                                            GLFWwindowmaximizefun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowmaximizefun, m_window->callbacks.maximize, cbfun);
    return cbfun;
}

GLFWAPI GLFWframebuffersizefun glfwSetFramebufferSizeCallback(GLFWwindow* handle,
                                                              GLFWframebuffersizefun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWframebuffersizefun, m_window->callbacks.fbsize, cbfun);
    return cbfun;
}

GLFWAPI GLFWwindowcontentscalefun glfwSetWindowContentScaleCallback(GLFWwindow* handle,
                                                                    GLFWwindowcontentscalefun cbfun)
{
    _GLFWwindow* m_window = (_GLFWwindow*) handle;
    assert(m_window != NULL);

    _GLFW_REQUIRE_INIT_OR_RETURN(NULL);
    _GLFW_SWAP(GLFWwindowcontentscalefun, m_window->callbacks.scale, cbfun);
    return cbfun;
}

GLFWAPI void glfwPollEvents(void)
{
    _GLFW_REQUIRE_INIT();
    _glfw.platform.pollEvents();
}

GLFWAPI void glfwWaitEvents(void)
{
    _GLFW_REQUIRE_INIT();
    _glfw.platform.waitEvents();
}

GLFWAPI void glfwWaitEventsTimeout(double timeout)
{
    _GLFW_REQUIRE_INIT();
    assert(timeout == timeout);
    assert(timeout >= 0.0);
    assert(timeout <= DBL_MAX);

    if (timeout != timeout || timeout < 0.0 || timeout > DBL_MAX)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid time %f", timeout);
        return;
    }

    _glfw.platform.waitEventsTimeout(timeout);
}

GLFWAPI void glfwPostEmptyEvent(void)
{
    _GLFW_REQUIRE_INIT();
    _glfw.platform.postEmptyEvent();
}

