#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for hidapiBrowserPlugin
#
#\**********************************************************/

set(PLUGIN_NAME "hidapiBrowserPlugin")
set(PLUGIN_PREFIX "HBP")
set(COMPANY_NAME "Ubinity")

# ActiveX constants:
set(FBTYPELIB_NAME hidapiBrowserPluginLib)
set(FBTYPELIB_DESC "hidapiBrowserPlugin 1.0 Type Library")
set(IFBControl_DESC "hidapiBrowserPlugin Control Interface")
set(FBControl_DESC "hidapiBrowserPlugin Control Class")
set(IFBComJavascriptObject_DESC "hidapiBrowserPlugin IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "hidapiBrowserPlugin ComJavascriptObject Class")
set(IFBComEventSource_DESC "hidapiBrowserPlugin IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 3b8c42d0-319f-5310-a1d2-c63e289dcbe9)
set(IFBControl_GUID 8d835e47-dc02-54a0-a7b4-2f832b12be1e)
set(FBControl_GUID 3a9ea44a-1a59-51ef-a0d0-9f99b9503358)
set(IFBComJavascriptObject_GUID 6b5efb13-6170-5a31-bfa6-26282f9a788d)
set(FBComJavascriptObject_GUID 58e09590-2b06-5df4-af38-429e3dadeb06)
set(IFBComEventSource_GUID 0d98d689-fc47-5e56-b86d-3c519188e7a1)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID abf9bb95-8be7-5108-83f6-6b6fbd065f07)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID cb0c50f0-c5c5-50c0-b736-31f3a88c2e46)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "Ubinity.hidapiBrowserPlugin")
set(MOZILLA_PLUGINID "ubinity.com/hidapiBrowserPlugin")

# strings
set(FBSTRING_CompanyName "Ubinity")
set(FBSTRING_PluginDescription "Firebreath mapping of hidapi")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2013 Ubinity")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}.dll")
set(FBSTRING_ProductName "hidapiBrowserPlugin")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "hidapiBrowserPlugin")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "hidapiBrowserPlugin_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-hidapibrowserplugin")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 0)
set(FBMAC_USE_COCOA 0)
set(FBMAC_USE_COREGRAPHICS 0)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
