// Copyright (c) 2013 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
#include "stdafx.h"
#include "CefBrowserApp.h"

#include <string>

#include "include/cef_browser.h"
#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"

CCefBrowserApp::CCefBrowserApp() {
}

int CCefBrowserApp::Init(HINSTANCE hInstance)
{
	CefMainArgs main_args(hInstance);
	CefRefPtr<CCefBrowserApp> app(new CCefBrowserApp);
	// Execute the sub-process logic, if any. This will either return immediately for the browser
	// process or block until the sub-process should exit.
	int exit_code = CefExecuteProcess(main_args, app.get(),NULL);
	if (exit_code >= 0) {
		// The sub-process terminated, exit now.
		return exit_code;
	}
	// Specify CEF global settings here.
	CefSettings settings;
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop=true;
	settings.command_line_args_disabled = true;
	settings.single_process=false;
	CefInitialize(main_args, settings, app.get(), NULL);
	return -1;
}
void CCefBrowserApp::OnContextInitialized() {
  // do nothing here, because we will create browser in my own dialog
}
