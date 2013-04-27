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

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "hidapiBrowserPluginAPI.h"

#include <hidapi.h>

#define CONVERT_WSTRING(x) (x != NULL ? std::wstring(x) : std::wstring())

FB::VariantList hidapiBrowserPluginAPI::plugin_hid_enumerate(const boost::optional<int>& vendor_id, const boost::optional<int>& product_id) {
    FB::VariantList list;
    struct hid_device_info *deviceInfo;
    unsigned short vendorId, productId;
    vendorId = (vendor_id ? (unsigned short)*vendor_id : 0);
    productId = (product_id ? (unsigned short)*product_id : 0);
    deviceInfo = hid_enumerate(vendorId, productId);
    while (deviceInfo != NULL) {
        FB::VariantMap deviceInfoMap;
	if (deviceInfo->path == NULL) {
		continue; // should never happen, but just in case
	}
        deviceInfoMap["path"] = std::string(deviceInfo->path);
        deviceInfoMap["vendor_id"] = deviceInfo->vendor_id;
        deviceInfoMap["product_id"] = deviceInfo->product_id;
        deviceInfoMap["serial_number"] = CONVERT_WSTRING(deviceInfo->serial_number);
        deviceInfoMap["release_number"] = deviceInfo->release_number;
        deviceInfoMap["manufacturer_string"] = CONVERT_WSTRING(deviceInfo->manufacturer_string);
        deviceInfoMap["product_string"] = CONVERT_WSTRING(deviceInfo->product_string);
        deviceInfoMap["usage_page"] = deviceInfo->usage_page;
        deviceInfoMap["usage"] = deviceInfo->usage;
        deviceInfoMap["interface_number"] = deviceInfo->interface_number;
        std::string pathCopy = deviceInfo->path;
        std::transform(pathCopy.begin(), pathCopy.end(), pathCopy.begin(), ::toupper);
        if (hidapiBrowserPlugin::lockTable.count(pathCopy) == 1) {
            deviceInfoMap["locked"] = hidapiBrowserPlugin::lockTable[pathCopy];
        }
        else {
            deviceInfoMap["locked"] = 0;
        }
        list.push_back(deviceInfoMap);
        deviceInfo = deviceInfo->next;
    }
    if (deviceInfo != NULL) {
        hid_free_enumeration(deviceInfo);
    }
    return list;
}

hidapiBrowserDeviceAPIPtr hidapiBrowserPluginAPI::plugin_hid_open_path(const std::string& path) {
    boost::shared_ptr<hidapiBrowserDeviceAPI> nullPointer;    
    std::string pathCopy = path;
    std::transform(pathCopy.begin(), pathCopy.end(), pathCopy.begin(), ::toupper);
    if ((hidapiBrowserPlugin::lockTable.count(pathCopy) == 1) && (hidapiBrowserPlugin::lockTable[pathCopy] == 1)) {
        return nullPointer;
    }
    hid_device *hidDevice = hid_open_path(path.c_str());
    if (hidDevice == NULL) {
        return nullPointer;
    }
    hidapiBrowserPlugin::lockTable[pathCopy] = 1;
    return boost::make_shared<hidapiBrowserDeviceAPI>(m_plugin, m_host, hidDevice, pathCopy);
}

///////////////////////////////////////////////////////////////////////////////
/// @fn hidapiBrowserPluginPtr hidapiBrowserPluginAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
hidapiBrowserPluginPtr hidapiBrowserPluginAPI::getPlugin()
{
    hidapiBrowserPluginPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read-only property version
std::string hidapiBrowserPluginAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

