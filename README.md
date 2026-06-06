# BB8 ROS2 + ESP32 WiFi Controller

## Descripción

Este proyecto implementa un prototipo de robot BB8 controlado mediante ROS2 Jazzy y una ESP32 conectada por WiFi.

La comunicación entre ROS2 y la ESP32 se realiza mediante sockets TCP. Los comandos generados por `teleop_twist_keyboard` son publicados en el tópico `/cmd_vel`, traducidos a comandos de movimiento y enviados por WiFi a la ESP32, que controla los motores a través de un puente H L298N.

---

## Arquitectura del Sistema

```text
Teleop Keyboard
       │
       ▼
    /cmd_vel
       │
       ▼
cmdvel_to_esp32.py
       │
    TCP WiFi
       │
       ▼
      ESP32
       │
       ▼
      L298N
       │
       ▼
   Motores DC
```

---

## Estructura del Proyecto

```text
misko_ws/
└── src/
    ├── bb8_controller/
    │   ├── bb8_controller/
    │   │   ├── __init__.py
    │   │   └── cmdvel_to_esp32.py
    │   ├── package.xml
    │   ├── setup.py
    │   └── setup.cfg
    │
    └── prueba_motores/
        ├── platformio.ini
        └── src/
            └── main.cpp
```

---

## Hardware

### Componentes

* ESP32
* Driver L298N
* 2 motores DC con reductora
* Batería para alimentación
* Chasis BB8
* Cableado Dupont

---

## Conexiones

### Motor izquierdo

| ESP32   | L298N |
| ------- | ----- |
| GPIO 32 | IN1   |
| GPIO 33 | IN2   |

### Motor derecho

| ESP32   | L298N |
| ------- | ----- |
| GPIO 25 | IN3   |
| GPIO 26 | IN4   |

### Alimentación

| Origen    | Destino        |
| --------- | -------------- |
| 5V L298N  | VIN / 5V ESP32 |
| GND L298N | GND ESP32      |

> Importante: la ESP32 y el L298N deben compartir la misma referencia de tierra (GND).

---

## Funcionamiento

### ESP32

La ESP32:

* Se conecta a una red WiFi.
* Abre un servidor TCP en el puerto 8888.
* Recibe comandos de movimiento.
* Controla los motores mediante el L298N.

### Comandos soportados

| Comando | Acción    |
| ------- | --------- |
| w       | Adelante  |
| s       | Atrás     |
| a       | Izquierda |
| d       | Derecha   |
| x       | Detener   |

---

## ROS2

El nodo `cmdvel_to_esp32.py`:

* Se suscribe al tópico `/cmd_vel`.
* Convierte mensajes `Twist` en comandos de movimiento.
* Envía los comandos mediante TCP a la ESP32.

---

## Dependencias

### ROS2 Jazzy

```bash
sudo apt install ros-jazzy-teleop-twist-keyboard
```

### Python

```bash
pip install setuptools
```

### PlatformIO

```bash
pip install platformio
```

---

## Compilación del Workspace

```bash
cd ~/misko_ws

colcon build --symlink-install

source install/setup.bash
```

---

## Carga del Firmware en la ESP32

Desde la carpeta del proyecto PlatformIO:

```bash
cd ~/misko_ws/src/prueba_motores

pio run --target upload
```

Monitor serial:

```bash
pio device monitor -b 115200
```

---

## Ejecución

### Terminal 1

Ejecutar el nodo puente ROS2 → ESP32

```bash
source ~/misko_ws/install/setup.bash

ros2 run bb8_controller cmdvel_to_esp32
```

---

### Terminal 2

Ejecutar teleoperación

```bash
source /opt/ros/jazzy/setup.bash

ros2 run teleop_twist_keyboard teleop_twist_keyboard
```

---

### Terminal 3 (Opcional)

Visualizar los mensajes publicados en `/cmd_vel`

```bash
ros2 topic echo /cmd_vel
```

---

## Controles

```text
u    i    o
j    k    l
m    ,    .
```

Principales:

```text
i  -> Adelante
,  -> Atrás
j  -> Izquierda
l  -> Derecha
k  -> Detener
```

---

## Estado Actual

* Comunicación ROS2 ↔ ESP32 funcional.
* Comunicación TCP por WiFi funcional.
* Control de motores funcional.
* Integración con teleop_twist_keyboard funcional.
* Plataforma BB8 en desarrollo.
* Integración con Gazebo en desarrollo.

---

## Autores

Proyecto desarrollado como parte del prototipo BB8 basado en ROS2 Jazzy y ESP32.
