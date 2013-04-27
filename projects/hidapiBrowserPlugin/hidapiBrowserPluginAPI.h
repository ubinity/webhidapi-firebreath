/**********************************************************\

  Auto-generated hidapiBrowserPluginAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "hidapiBrowserPlugin.h"
#include "hidapiBrowserDeviceAPI.h"

#ifndef H_hidapiBrowserPluginAPI
#define H_hidapiBrowserPluginAPI

class hidapiBrowserPluginAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn hidapiBrowserPluginAPI::hidapiBrowserPluginAPI(const hidapiBrowserPluginPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    hidapiBrowserPluginAPI(const hidapiBrowserPluginPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        registerMethod("hid_enumerate", make_method(this, &hidapiBrowserPluginAPI::plugin_hid_enumerate));
        registerMethod("hid_open_path", make_method(this, &hidapiBrowserPluginAPI::plugin_hid_open_path));
        
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &hidapiBrowserPluginAPI::get_version));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn hidapiBrowserPluginAPI::~hidapiBrowserPluginAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~hidapiBrowserPluginAPI() {};

    hidapiBrowserPluginPtr getPlugin();

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    FB::VariantList plugin_hid_enumerate(const boost::optional<int>& vendor_id, const boost::optional<int>& product_id);

    hidapiBrowserDeviceAPIPtr plugin_hid_open_path(const std::string& path);


private:
    hidapiBrowserPluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

#endif // H_hidapiBrowserPluginAPI

