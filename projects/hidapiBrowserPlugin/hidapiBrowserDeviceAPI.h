#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "hidapiBrowserPlugin.h"
#include <hidapi.h>

#ifndef H_hidapiBrowserDeviceAPI
#define H_hidapiBrowserDeviceAPI

FB_FORWARD_PTR(hidapiBrowserDeviceAPI);

class hidapiBrowserDeviceAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn hidapiBrowserDeviceAPI::hidapiBrowserDeviceAPI(const hidapiBrowserPluginPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    hidapiBrowserDeviceAPI(const hidapiBrowserPluginWeakPtr& plugin, const FB::BrowserHostPtr& host, hid_device *deviceParam, const std::string& pathParam) :
        m_plugin(plugin), m_host(host), device(deviceParam), path(pathParam)
    {
        registerMethod("hid_read", make_method(this, &hidapiBrowserDeviceAPI::plugin_hid_read));
        registerMethod("hid_write", make_method(this, &hidapiBrowserDeviceAPI::plugin_hid_write));
	registerMethod("hid_setnonblocking", make_method(this, &hidapiBrowserDeviceAPI::plugin_hid_setnonblocking));
	registerMethod("hid_send_feature_report", make_method(this, &hidapiBrowserDeviceAPI::plugin_hid_send_feature_report));
	registerMethod("hid_get_feature_report", make_method(this, &hidapiBrowserDeviceAPI::plugin_hid_get_feature_report));
        registerMethod("close", make_method(this, &hidapiBrowserDeviceAPI::plugin_hid_close));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn hidapiBrowserDeviceAPI::~hidapiBrowserDeviceAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~hidapiBrowserDeviceAPI() {
        plugin_hid_close();
    };

    int digitToHex(int digit);
    int hexToBinary(const std::string& data, unsigned char *targetBin, size_t targetLength);
    std::string binaryToHex(const unsigned char *sourceBinary, size_t length);

    int plugin_hid_write(const std::string& data);
    std::string plugin_hid_read(const size_t size, const boost::optional<int>& timeoutMs);
    int plugin_hid_send_feature_report(const std::string& data);
    std::string plugin_hid_get_feature_report(const size_t size);
    int plugin_hid_setnonblocking(int nonblock);
    void plugin_hid_close();

private:
    static const std::string HEXDIGITS;
    hidapiBrowserPluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
    hid_device *device;
    std::string path;
};

#endif // H_hidapiBrowserDeviceAPI

