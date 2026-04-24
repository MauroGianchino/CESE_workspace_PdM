# API Drivers: TMP117 & TLC5923

Este directorio contiene la implementación de las capas de abstracción (API) para los periféricos principales del proyecto **Temperature Monitor**. El objetivo de estos drivers es desacoplar la lógica de bajo nivel (registros y protocolos de comunicación) de la lógica de aplicación. Se hace hincapié en los drivers de los circuitos integrados utilizados.

## 📋 Contenidos

1. [TMP117 - Sensor de Temperatura](#tmp117---sensor-de-temperatura)
2. [TLC5923 - Driver de LEDs](#tlc5923---driver-de-leds)

---

## 🌡️ TMP117 - Sensor de Temperatura

El **TMP117** es un sensor de temperatura digital de alta precisión (±0.1 °C). Este driver gestiona la comunicación a través del bus **I2C**.

La idea es proporcionar una interfaz de alto nivel para obtener lecturas térmicas precisas y configurar parámetros operativos sin necesidad de manipular manualmente los registros internos del sensor en cada llamada.

### Funcionalidades principales
* **Lectura de Temperatura:** Obtención de datos y conversión automática a grados Celsius.
* **Configuración de Alertas:** Definición de límites de temperatura (High/Low limits) para el uso de interrupciones.

---

## 💡 TLC5923 - Driver de LEDs

El **TLC5923** es un controlador de corriente constante de 16 canales. En este proyecto, se encarga de la retroalimentación visual del sistema de monitoreo.
La idea es facilitar el control de múltiples salidas de corriente constante para LEDs. Su comunicación es por SPI.

### Funcionalidades principales
* **Control de Canales:** Encendido, apagado y control de estado de los 16 canales de forma independiente.
* **Dot Correction:** Ajuste fino de la corriente de salida para homogeneizar el brillo entre los distintos LEDs.
* **Sincronización:** Manejo de las señales de control (Latch, Blank) para evitar parpadeos no deseados durante la actualización de datos.

