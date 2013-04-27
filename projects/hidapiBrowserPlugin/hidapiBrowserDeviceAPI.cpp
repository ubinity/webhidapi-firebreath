#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "hidapiBrowserDeviceAPI.h"

#include <hidapi.h>
#include <string.h>

#define HID_MAX 65

int hidapiBrowserDeviceAPI::digitToHex(int digit) {
    if ((digit >= '0') && (digit <= '9')) {
        return digit - '0';
    }
    else
    if ((digit >= 'A') && (digit <= 'F')) {
        return (digit - 'A') + 10;
    }
    else
    if ((digit >= 'a') && (digit <= 'f')) {
        return (digit - 'a') + 10;
    }
    return -1;
}

int hidapiBrowserDeviceAPI::hexToBinary(const std::string& data, unsigned char *targetBin, size_t length) {
    int dataLength = data.length();
    if ((dataLength % 2) != 0) {
        return -1;
    }
    if ((dataLength / 2) > length) {
	return -1;
    }
    for (int i=0; i<dataLength; i += 2) {
        int d1, d2;
        d1 = digitToHex(data[i]);
        d2 = digitToHex(data[i + 1]);
        if ((d1 < 0) || (d2 < 0)) {
            return false;
        }
        targetBin[i / 2] = (d1 << 4) + d2;
    } 
    return (dataLength / 2);
}

std::string hidapiBrowserDeviceAPI::binaryToHex(const unsigned char *sourceBinary, size_t length) {
    std::string result;
    for (int i=0; i<length; i++) {
        int digit = sourceBinary[i];
        result.push_back(HEXDIGITS[(digit >> 4) & 0x0f]);
        result.push_back(HEXDIGITS[digit & 0x0f]);
    }
    return result;
}

int hidapiBrowserDeviceAPI::plugin_hid_write(const std::string& data) {    
    unsigned char buffer[HID_MAX];
    if (device == NULL) {
        return -100;
    }
    if (data.length() > (sizeof(buffer) * 2)) {
        return -101;
    }
    int convertedLength = hexToBinary(data, buffer, sizeof(buffer));
    if (convertedLength < 0) {
        return convertedLength;
    }
    int result = hid_write(device, buffer, convertedLength);
    return result;
}

std::string hidapiBrowserDeviceAPI::plugin_hid_read(const size_t size, const boost::optional<int>& timeoutMs) {    
    unsigned char buffer[HID_MAX];
    int result;
    if (device == NULL) {
        return "";
    }
    if (size > sizeof(buffer)) {
        return "";
    }
    if (timeoutMs) {
        result = hid_read_timeout(device, buffer, size, *timeoutMs);
    }
    else {
        result = hid_read(device, buffer, size);
    }
    if (result < 0) {
        return "";
    }
    return binaryToHex(buffer, result);    
}

int hidapiBrowserDeviceAPI::plugin_hid_send_feature_report(const std::string& data) {
    unsigned char buffer[HID_MAX];
    if (device == NULL) {
        return -100;
    }
    if (data.length() > (sizeof(buffer) * 2)) {
        return -101;
    }
    int convertedLength = hexToBinary(data, buffer, sizeof(buffer));
    if (convertedLength < 0) {
        return convertedLength;
    }
    int result = hid_send_feature_report(device, buffer, convertedLength);
    return result;
}

std::string hidapiBrowserDeviceAPI::plugin_hid_get_feature_report(const size_t size) {
    unsigned char buffer[HID_MAX];
    int result;
    if (device == NULL) {
        return "";
    }
    if (size > sizeof(buffer)) {
        return "";
    }
    result = hid_get_feature_report(device, buffer, size);
    if (result < 0) {
        return "";
    }
    return binaryToHex(buffer, result);
}

int hidapiBrowserDeviceAPI::plugin_hid_setnonblocking(int nonblock) {
    if (device == NULL) {
	return -100;
    }
    return hid_set_nonblocking(device, nonblock);
}

void hidapiBrowserDeviceAPI::plugin_hid_close() {
    if (device != NULL) {
        hid_close(device);
        device = NULL;
    }
    hidapiBrowserPlugin::lockTable.erase(path);
}

const std::string hidapiBrowserDeviceAPI::HEXDIGITS = "0123456789ABCDEF";


