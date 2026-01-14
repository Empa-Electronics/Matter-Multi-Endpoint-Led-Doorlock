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

Bu projenin build edilebilmesi için esp-matter içerisindeki examples klasöründe olması gerekiyor.
```sh
cd esp-matter/examples
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
