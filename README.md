# Matter Multi-Endpoint LED & Doorlock

Bu proje, ESP Matter kullanarak çoklu endpoint desteği ile LED ve kapı kilidi kontrolü sağlayan bir Matter cihazı örneğidir.

## Özellikler

- 🔒 Matter protokolü desteği
- 💡 LED kontrolü
- 🚪 Kapı kilidi kontrolü
- 🔌 Çoklu endpoint desteği
- 📱 Matter-uyumlu cihazlarla komisyon

## Hızlı Başlangıç

### Projeyi Klonlama

```sh
git clone git@github.com:Empa-Electronics/Matter-Multi-Endpoint-Led-Doorlock.git
cd Matter-Multi-Endpoint-Led-Doorlock
```

### Derleme ve Yükleme

ESP-IDF ve ESP Matter ortamınızı kurduktan sonra:

```sh
idf.py set-target esp32c6
idf.py build
idf.py flash monitor
```

Daha fazla bilgi için [ESP Matter dokümantasyonunu](https://docs.espressif.com/projects/esp-matter/en/latest/esp32/developing.html) inceleyebilirsiniz.

## 1. Additional Environment Setup

No additional setup is required.

## 2. Post Commissioning Setup

No additional setup is required.

## 3. Device Performance

### 3.1 Memory usage

The following is the Memory and Flash Usage.

-   `Bootup` == Device just finished booting up. Device is not
    commissionined or connected to wifi yet.
-   `After Commissioning` == Device is conneted to wifi and is also
    commissioned and is rebooted.
-   device used: esp32c3_devkit_m
-   tested on:
    [6a244a7](https://github.com/espressif/esp-matter/commit/6a244a7b1e5c70b0aa1bf57254f19718b0755d95)
    (2022-06-16)

|                         | Bootup | After Commissioning |
|:-                       |:-:     |:-:                  |
|**Free Internal Memory** |108KB   |105KB                |

**Flash Usage**: Firmware binary size: 1.26MB

This should give you a good idea about the amount of free memory that is
available for you to run your application's code.

Applications that do not require BLE post commissioning, can disable it using app_ble_disable() once commissioning is complete. It is not done explicitly because of a known issue with esp32c3 and will be fixed with the next IDF release (v4.4.2).
