# 🖥️ Monitoreo de Temperatura con ESP32 y MAX6675

Este repositorio contiene el código para un **monitor de temperatura** utilizando un sensor **MAX6675** y un **ESP32**. El código permite leer la temperatura desde el sensor y enviarla a un servidor a través de WiFi.

El código para el servidor y la visualización de los datos del ESP32 puede encontrarse en el repositorio [Realtime Monitor](https://github.com/ESCALOS/realtime-monitor).

El código del ESP32 se encuentra en el archivo [TermocuplaESP32.ino](https://github.com/ESCALOS/ESP32-MAX6675).

## 🛠️ Tecnologías Utilizadas

- **ESP32**: Microcontrolador para manejar la lectura del sensor y la conexión WiFi.
- **MAX6675**: Sensor para medir la temperatura con termocupla tipo K.
- **WiFi**: Para conexión a Internet.
- **HTTPClient**: Para enviar datos al servidor en formato JSON.

## 📋 Requisitos

- **ESP32**: Asegúrate de tener un ESP32 programable.
- **Sensor MAX6675**: Este sensor debe estar conectado a los pines adecuados del ESP32.
- **Conexión WiFi**: El ESP32 se conecta a una red WiFi para enviar los datos.

## ⚙️ Configuración del Proyecto

1. **Conexión del sensor MAX6675**: 
   - `MISO` (DO) a pin 19
   - `CS` a pin 5
   - `CLK` a pin 18

2. **Conexión WiFi**:
   Asegúrate de ingresar los datos correctos de tu red WiFi en las variables `ssid` y `password`.

   ```cpp
   const char* ssid = "SSID";      // Cambia "SSID" por el nombre de tu red WiFi
   const char* password = "PASSWORD";  // Cambia "PASSWORD" por tu contraseña
   ```
3. Servidor API: Modifica la variable serverUrl con la dirección IP de tu servidor donde se enviarán los datos de temperatura.
   ```cpp
   String serverUrl = "http://SERVER_IP:4000/api/temperature"; // Cambia SERVER_IP por la IP de tu servidor
   ```

## 🧩 Funcionamiento

1. El ESP32 se conecta a la red WiFi utilizando las credenciales proporcionadas.
2. Una vez conectado, el ESP32 comienza a leer la temperatura desde el sensor **MAX6675** conectado a los pines configurados en el código.
3. Cada segundo, el ESP32 envía el valor de la temperatura al servidor a través de una solicitud HTTP POST en formato JSON.
4. El servidor debe estar configurado para recibir y manejar estos datos en la ruta `/api/temperature`. La temperatura se envía como un objeto JSON con la siguiente estructura:

    ```json
    {
      "value": 25.00
    }
    ```

5. El ESP32 también muestra la respuesta del servidor en el monitor serial, lo que permite verificar si la solicitud se realizó correctamente.

## 📥 Instalación y Uso

1. Clona este repositorio y abre el archivo `.ino` en el IDE de Arduino.
2. Conecta tu **ESP32** al puerto correcto y selecciona el tipo de placa adecuado en el IDE de Arduino.
3. Asegúrate de tener las bibliotecas necesarias instaladas:
   - **WiFi**: Para la conexión a la red WiFi.
   - **HTTPClient**: Para realizar solicitudes HTTP.
   - **MAX6675**: Para leer los datos del sensor de temperatura.
4. Modifica las credenciales de WiFi (`ssid` y `password`) en el código.
5. Modifica la URL del servidor en `serverUrl` para que apunte a tu servidor que recibirá los datos.
6. Carga el código al ESP32.
7. Abre el monitor serial para verificar que el ESP32 se conecta correctamente a WiFi y envía las temperaturas al servidor.

## 🤝 Contribuciones

¡Las contribuciones son bienvenidas! Si deseas colaborar, por favor sigue estos pasos:

1. Haz un fork del repositorio.
2. Crea una rama nueva: `git checkout -b feature/nueva-funcionalidad`.
3. Realiza tus cambios y haz commit: `git commit -m "Agrega nueva funcionalidad"`.
4. Haz push a tu rama: `git push origin feature/nueva-funcionalidad`.
5. Abre un Pull Request.

## 📄 Licencia

Este proyecto está bajo la licencia MIT. Consulta el archivo [LICENSE](LICENSE) para más detalles.

## 📫 Contacto

Si tienes dudas o sugerencias, no dudes en abrir un issue o escribir a stornblood6969@gmail.com.
