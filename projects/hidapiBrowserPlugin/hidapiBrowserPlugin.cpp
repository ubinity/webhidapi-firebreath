/*
************************************************************************
Copyright (c) 2013 UBINITY SAS 

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*************************************************************************
*/

/**********************************************************\

  Auto-generated hidapiBrowserPlugin.cpp

  This file contains the auto-generated main plugin object
  implementation for the hidapiBrowserPlugin project

\**********************************************************/

#include "hidapiBrowserPluginAPI.h"

#include "hidapiBrowserPlugin.h"
#include <hidapi.h>

///////////////////////////////////////////////////////////////////////////////
/// @fn hidapiBrowserPlugin::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void hidapiBrowserPlugin::StaticInitialize()
{
    hid_init();
}

///////////////////////////////////////////////////////////////////////////////
/// @fn hidapiBrowserPlugin::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void hidapiBrowserPlugin::StaticDeinitialize()
{
    hid_exit();
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  hidapiBrowserPlugin constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
hidapiBrowserPlugin::hidapiBrowserPlugin()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  hidapiBrowserPlugin destructor.
///////////////////////////////////////////////////////////////////////////////
hidapiBrowserPlugin::~hidapiBrowserPlugin()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void hidapiBrowserPlugin::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

void hidapiBrowserPlugin::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<hidapiBrowserPlugin> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr hidapiBrowserPlugin::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<hidapiBrowserPluginAPI>(FB::ptr_cast<hidapiBrowserPlugin>(shared_from_this()), m_host);
}

bool hidapiBrowserPlugin::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool hidapiBrowserPlugin::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool hidapiBrowserPlugin::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
bool hidapiBrowserPlugin::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *)
{
    // The window is attached; act appropriately
    return false;
}

bool hidapiBrowserPlugin::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    return false;
}

std::map<std::string, int> hidapiBrowserPlugin::lockTable;
