// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.

#ifndef CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
#define CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_

#include "include/cef_client.h"

#include <list>

class CCefBrowserEventHandler : public CefClient,
					  public CefContextMenuHandler,
                      public CefLifeSpanHandler,
                      public CefLoadHandler {
 public:
  CCefBrowserEventHandler();
  ~CCefBrowserEventHandler();

  // CefClient methods:
  virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
    return this;
  }
  virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE {
    return this;
  }
  virtual CefRefPtr<CefContextMenuHandler> GetContextMenuHandler() { return this; }
  // CefLifeSpanHandler methods:
  virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
  virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

  // CefLoadHandler methods:
  virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
                           CefRefPtr<CefFrame> frame,
                           ErrorCode errorCode,
                           const CefString& errorText,
                           const CefString& failedUrl) OVERRIDE;
  // CefContextMenuHandler methods:
  virtual void OnBeforeContextMenu(CefRefPtr<CefBrowser> browser,
	  CefRefPtr<CefFrame> frame,
	  CefRefPtr<CefContextMenuParams> params,
	  CefRefPtr<CefMenuModel> model) OVERRIDE;

  // Member accessors.
  CefRefPtr<CefBrowser> GetBrowser() { return m_Browser; }
  bool IsClosing() { return m_bIsClosing; }

 private:
	 CefRefPtr<CefBrowser> m_Browser;
	 int m_BrowserId;
	 bool m_bIsClosing;
  // Include the default reference counting implementation.
  IMPLEMENT_REFCOUNTING(CCefBrowserEventHandler);
};

#endif  // CEF_TESTS_CEFSIMPLE_SIMPLE_HANDLER_H_
