/*
 * Copyright (C) 2012 Igalia S.L.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "PlatformWebView.h"

#include "HeadlessViewBackend.h"
#include <WebKit/WKRetainPtr.h>
#include <WebKit/WKView.h>

namespace TestWebKitAPI {

PlatformWebView::PlatformWebView(WKContextRef contextRef, WKPageGroupRef pageGroupRef)
    : m_window(nullptr)
{
    WKRetainPtr<WKPageConfigurationRef> configuration = adoptWK(WKPageConfigurationCreate());
    WKPageConfigurationSetContext(configuration.get(), contextRef);
    WKPageConfigurationSetPageGroup(configuration.get(), pageGroupRef);

    initialize(configuration.get());
}

PlatformWebView::PlatformWebView(WKPageConfigurationRef configuration)
    : m_window(nullptr)
{
    initialize(configuration);
}

PlatformWebView::PlatformWebView(WKPageRef relatedPage)
    : m_window(nullptr)
{
    WKRetainPtr<WKPageConfigurationRef> configuration = adoptWK(WKPageConfigurationCreate());
    WKPageConfigurationSetContext(configuration.get(), WKPageGetContext(relatedPage));
    WKPageConfigurationSetPageGroup(configuration.get(), WKPageGetPageGroup(relatedPage));
    WKPageConfigurationSetRelatedPage(configuration.get(), relatedPage);

    initialize(configuration.get());
}

PlatformWebView::~PlatformWebView()
{
    if (m_backend)
        wpe_view_backend_destroy(m_backend);

    delete m_window;
}

void PlatformWebView::initialize(WKPageConfigurationRef configuration)
{
    const char* useHeadlessViewBackend = g_getenv("WPE_USE_HEADLESS_VIEW_BACKEND");
    if (useHeadlessViewBackend && strcmp(useHeadlessViewBackend, "0"))
        m_window = new HeadlessViewBackend;
    else
        m_backend = wpe_view_backend_create();

    m_view = WKViewCreate(m_window ? m_window->backend() : m_backend, configuration);
}

WKPageRef PlatformWebView::page() const
{
    return WKViewGetPage(m_view);
}

void PlatformWebView::resizeTo(unsigned width, unsigned height)
{
    // FIXME: implement this.
}

void PlatformWebView::simulateSpacebarKeyPress()
{
    // FIXME: implement this.
}

void PlatformWebView::simulateAltKeyPress()
{
    // FIXME: implement this.
}

void PlatformWebView::simulateRightClick(unsigned x, unsigned y)
{
    // FIXME: implement this.
}

void PlatformWebView::simulateMouseMove(unsigned x, unsigned y, WKEventModifiers)
{
    // FIXME: implement this.
}

} // namespace TestWebKitAPI
