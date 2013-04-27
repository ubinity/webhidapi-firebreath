webhidapi-firebreath
====================

Browser plug-in interface to HIDAPI using FireBreath, exposing methods through JavaScript interfaces (for Linux, Windows, OS X)

See also webhidapi-java for the same interface with more coffee and more exploits

How to build
-------------

  * Download FireBreath from http://www.firebreath.org/
  * Download hidapi from http://www.signal11.us/oss/hidapi/, copy it to external/hidapi from the FireBreath root directory
  * Rebuild FireBreath "makefiles" with prepmake - see http://colonelpanic.net/2010/11/firebreath-tips-working-with-source-control/
  * Build FireBreath plug-in for your target platform(s) - http://www.firebreath.org/display/documentation/Building+FireBreath+Plugins

How to use 
-----------

An example is provided into test/testHidapiBrowserPluginDirect.html

Note that if you're running Linux, the device needs to be accessible by any user - this is usually done with a udev rules such as 

	SUBSYSTEMS=="usb", ATTRS{idVendor}=="vid", ATTRS{idProduct}=="pid", MODE="0660", GROUP="yourgroup"

All data is exchanged as hexadecimal strings, such as "0102ABCDEF"

The direct plug-in API is used to enumerate and open the device

  * Enumerate to find your device, using `hid_enumerate(vid, pid)` with optional vid, pid - this returns an array of  JavaScript lists containing the following items
      * path : path to use to communicate with the device
      * locked : set to 1 if the device is already opened by another instance of the plug-in
      * vendor_id  
      * product_id  
      * serial_number 
      * manufacturer_string
      * product_string
      * usage_page
      * usage
      * interface_number
  * Open the device with `hid_open_path(path)` - this returns a JavaScript object used to communicate with the device or an undefined value if it failed (typically on Linux when the device cannot be accessed)

If your device uses HID interrupts or Input/Output reports

  * `hid_write(data)` to write data, returning the size of the data written or a negative error code
  * `hid_read(size, timeoutMs)` to read data, returning the data - the timeoutMs parameter is optional

If your device uses HID Feature reports

  * `hid_send_feature_report(data)` to write data, returning the size of the data written or a negative error code
  * `hid_get_feature_report(size)` to read data, returning the data

Finally to close the device 

  * `hid_close()`

If you need to use the non-blocking API

  * `hid_set_nonblocking(1)` : enable non-blocking mode
  * `hid_set_nonblocking(0)` : disable non-blocking mode (default) 

