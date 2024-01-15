#include "NimBLELibraryWrapper.h"
#include <NimBLEDevice.h>
#include <NimBLEServer.h>

uint NimBLELibraryWrapper::_numberOfInstances = 0;

struct WrapperPrivateData: public BLECharacteristicCallbacks,
                           BLEServerCallbacks {
    NimBLEAdvertising* pNimBLEAdvertising;
    bool BLEDeviceRunning = false;
    bool wifiSettingsEnabled;
    bool batteryServiceEnabled;

    // BLEServer
    NimBLEServer* pBLEServer;

    // BLEServices
    NimBLEService* pBLEDownloadService;
    NimBLEService* pBLESettingsService;
    NimBLEService* pBLEBatteryService;

    // BLECharacteristics
    NimBLECharacteristic* pTransferChararacteristic;
    NimBLECharacteristic* pNumberOfSamplesCharacteristic;
    NimBLECharacteristic* pSampleHistoryIntervalCharacteristic;

    NimBLECharacteristic* pWifiSsidCharacteristic;
    NimBLECharacteristic* pWifiPasswordCharacteristic;

    NimBLECharacteristic* pBatteryLevelCharacteristic;

    // BLEServerCallbacks
    void onConnect(BLEServer* serverInst);
    void onDisconnect(BLEServer* serverInst);

    // BLECharacteristicCallbacks
    void onWrite(BLECharacteristic* characteristic);
    void onSubscribe(NimBLECharacteristic* pCharacteristic,
                     ble_gap_conn_desc* desc, uint16_t subValue);

    // DataProvider Callbacks
    IProviderCallbacks* providerCallbacks = nullptr;
};

void WrapperPrivateData::onConnect(NimBLEServer* serverInst) {
    if (providerCallbacks != nullptr) {
        providerCallbacks->onConnectionEvent();
    }
}

void WrapperPrivateData::onDisconnect(BLEServer* serverInst) {
    if (providerCallbacks != nullptr) {
        providerCallbacks->onConnectionEvent();
    }
}

void WrapperPrivateData::onSubscribe(NimBLECharacteristic* pCharacteristic,
                                     ble_gap_conn_desc* desc,
                                     uint16_t subValue) {
    if ((providerCallbacks != nullptr) && (subValue == 1)) {
        providerCallbacks->onDownloadRequest();
    }
}

void WrapperPrivateData::onWrite(BLECharacteristic* characteristic) {
    if (characteristic->getUUID().toString().compare(
            SAMPLE_HISTORY_INTERVAL_UUID) == 0) {
        std::string value = characteristic->getValue();
        uint32_t sampleIntervalMs =
            value[0] | (value[1] << 8) | (value[2] << 16) | (value[3] << 24);
        if (providerCallbacks != nullptr) {
            providerCallbacks->onHistoryIntervalChange(sampleIntervalMs);
        }
    } else if (wifiSettingsEnabled &&
               characteristic->getUUID().toString().compare(WIFI_SSID_UUID) ==
                   0) {
        providerCallbacks->onWifiSsidChange(characteristic->getValue());
    } else if (wifiSettingsEnabled &&
               characteristic->getUUID().toString().compare(WIFI_PWD_UUID) ==
                   0) {
        providerCallbacks->onWifiPasswordChange(characteristic->getValue());
    }
}

WrapperPrivateData* NimBLELibraryWrapper::_data = nullptr;

NimBLELibraryWrapper::NimBLELibraryWrapper(bool enableWifiSettings,
                                           bool enableBatteryService) {
    if (NimBLELibraryWrapper::_numberOfInstances == 0) {
        _data = new WrapperPrivateData();
        ++NimBLELibraryWrapper::_numberOfInstances;
        _data->wifiSettingsEnabled = enableWifiSettings;
        _data->batteryServiceEnabled = enableBatteryService;
    }
}

NimBLELibraryWrapper::~NimBLELibraryWrapper() {
    if (NimBLELibraryWrapper::_numberOfInstances == 1) {
        delete _data;
        _deinit();
        --NimBLELibraryWrapper::_numberOfInstances;
    }
}

void NimBLELibraryWrapper::_deinit() {
    if (_data->BLEDeviceRunning) {
        NimBLEDevice::deinit(true);
        _data->BLEDeviceRunning = false;
    }
}

void NimBLELibraryWrapper::init() {
    if (_data->BLEDeviceRunning == true) {
        return;
    }
    NimBLEDevice::init(GADGET_NAME);
    _data->BLEDeviceRunning = true;

    _data->pNimBLEAdvertising = NimBLEDevice::getAdvertising();
    // Helps with iPhone connection issues (copy/paste)
    _data->pNimBLEAdvertising->setMinPreferred(0x06);
    _data->pNimBLEAdvertising->setMaxPreferred(0x12);

    // Initialize BLEServer
    _data->pBLEServer =
        NimBLEDevice::createServer(); // NimBLEDevice has ownership
    _data->pBLEServer->setCallbacks(_data);

    // Create Services
    _createDownloadService();
    if (_data->batteryServiceEnabled) {
        _createBatteryService();
    }
    if (_data->wifiSettingsEnabled) {
        _createSettingsService();
    }
}

void NimBLELibraryWrapper::setAdvertisingData(const std::string& data) {
    NimBLEAdvertisementData advert;
    advert.setName(GADGET_NAME);
    advert.setManufacturerData(data);
    _data->pNimBLEAdvertising->setAdvertisementData(advert);
}

void NimBLELibraryWrapper::startAdvertising() {
    _data->pNimBLEAdvertising->start();
}

void NimBLELibraryWrapper::stopAdvertising() {
    _data->pNimBLEAdvertising->stop();
}

std::string NimBLELibraryWrapper::getDeviceAddress() {
    return NimBLEDevice::getAddress().toString();
}

bool NimBLELibraryWrapper::characteristicSetValue(const char* uuid,
                                                  const uint8_t* data,
                                                  size_t size) {
    NimBLECharacteristic* pCharacteristic = _lookupCharacteristic(uuid);
    if (nullptr == pCharacteristic) {
        return false;
    }
    pCharacteristic->setValue(data, size);
    return true;
}

bool NimBLELibraryWrapper::characteristicSetValue(const char* uuid, int value) {
    NimBLECharacteristic* pCharacteristic = _lookupCharacteristic(uuid);
    if (nullptr == pCharacteristic) {
        return false;
    }
    pCharacteristic->setValue(value);
    return true;
}

std::string NimBLELibraryWrapper::characteristicGetValue(const char* uuid) {
    NimBLECharacteristic* pCharacteristic = _lookupCharacteristic(uuid);
    if (nullptr == pCharacteristic) {
        return "";
    }
    return pCharacteristic->getValue();
}

bool NimBLELibraryWrapper::characteristicNotify(const char* uuid) {
    NimBLECharacteristic* pCharacteristic = _lookupCharacteristic(uuid);
    if (nullptr == pCharacteristic) {
        return false;
    }
    pCharacteristic->notify(true);
    return true;
}

void NimBLELibraryWrapper::setProviderCallbacks(
    IProviderCallbacks* providerCallbacks) {
    _data->providerCallbacks = providerCallbacks;
}

void NimBLELibraryWrapper::_createDownloadService() {
    // Create service
    _data->pBLEDownloadService =
        _data->pBLEServer->createService(DOWNLOAD_SERVICE_UUID);

    // Create characteristics
    _data->pNumberOfSamplesCharacteristic =
        _data->pBLEDownloadService->createCharacteristic(NUMBER_OF_SAMPLES_UUID,
                                                         NIMBLE_PROPERTY::READ);
    _data->pNumberOfSamplesCharacteristic->setValue(0);

    _data->pSampleHistoryIntervalCharacteristic =
        _data->pBLEDownloadService->createCharacteristic(
            SAMPLE_HISTORY_INTERVAL_UUID,
            NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
    _data->pSampleHistoryIntervalCharacteristic->setCallbacks(_data);

    _data->pTransferChararacteristic =
        _data->pBLEDownloadService->createCharacteristic(
            DOWNLOAD_PACKET_UUID, NIMBLE_PROPERTY::NOTIFY);
    _data->pTransferChararacteristic->setCallbacks(_data);

    _data->pBLEDownloadService->start();
}

void NimBLELibraryWrapper::_createSettingsService() {
    // Create Service
    _data->pBLESettingsService =
        _data->pBLEServer->createService(SETTINGS_SERVICE_UUID);

    // Create Characteristics
    _data->pWifiSsidCharacteristic =
        _data->pBLESettingsService->createCharacteristic(
            WIFI_SSID_UUID, NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::WRITE);
    _data->pWifiSsidCharacteristic->setValue("ssid placeholder");
    _data->pWifiSsidCharacteristic->setCallbacks(_data);

    _data->pWifiPasswordCharacteristic =
        _data->pBLESettingsService->createCharacteristic(
            WIFI_PWD_UUID, NIMBLE_PROPERTY::WRITE);
    _data->pWifiPasswordCharacteristic->setValue("n/a");
    _data->pWifiPasswordCharacteristic->setCallbacks(_data);

    _data->pBLESettingsService->start();
}

void NimBLELibraryWrapper::_createBatteryService() {
    _data->pBLEBatteryService =
        _data->pBLEServer->createService(BATTERY_SERVICE_UUID);
    _data->pBatteryLevelCharacteristic =
        _data->pBLEBatteryService->createCharacteristic(BATTERY_LEVEL_UUID,
                                                        NIMBLE_PROPERTY::READ);

    _data->pBatteryLevelCharacteristic->setValue(0);
    _data->pBLEBatteryService->start();
}

NimBLECharacteristic*
NimBLELibraryWrapper::_lookupCharacteristic(const char* uuid) {
    NimBLECharacteristic* pCharacteristic = nullptr;
    pCharacteristic = _data->pBLEDownloadService->getCharacteristic(uuid);
    if (pCharacteristic != nullptr) {
        return pCharacteristic;
    }
    if (_data->batteryServiceEnabled) {
        pCharacteristic = _data->pBLEBatteryService->getCharacteristic(uuid);
        if (pCharacteristic != nullptr) {
            return pCharacteristic;
        }
    }
    return pCharacteristic;
}