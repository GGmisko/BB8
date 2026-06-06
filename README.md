# BB8 ROS2 + ESP32 WiFi Controller

## Descripción

Este proyecto implementa un prototipo de BB8 controlado mediante ROS2 y una ESP32-S3 conectada por WiFi.

La arquitectura permite controlar el robot utilizando `teleop_twist_keyboard`, enviando comandos ROS2 (`/cmd_vel`) a una ESP32 mediante sockets TCP sobre WiFi.

## Arquitectura

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

## Hardware

### Electrónica

* ESP32-S3 Zero
* Driver L298N
* 2 Motores DC con reductora
* 2 Baterías Li-Ion 3.7V
* Chasis BB8
* Cableado Dupont

### Conexiones

#### Motor izquierdo

| ESP32   | L298N |
| ------- | ----- |
| GPIO 32 | IN1   |
| GPIO 33 | IN2   |

#### Motor derecho

| ESP32   | L298N |
| ------- | ----- |
| GPIO 25 | IN3   |
| GPIO 26 | IN4   |

#### Alimentación

| Origen    | Destino      |
| --------- | ------------ |
| 5V L298N  | VIN/5V ESP32 |
| GND L298N | GND ESP32    |

## Software

### ESP32

La ESP32:

* Se conecta a la red WiFi.
* Abre un servidor TCP en el puerto 8888.
* Recibe comandos:

  * w → adelante
  * s → atrás
  * a → izquierda
  * d → derecha
  * x → detener

### ROS2

El nodo `cmdvel_to_esp32.py`:

* Se suscribe a `/cmd_vel`
* Convierte mensajes Twist a comandos de movimiento
* Envía los comandos mediante TCP a la ESP32

## Dependencias

ROS2 Humble:

```bash
sudo apt install ros-humble-teleop-twist-keyboard
```

Python:

```bash
pip install setuptools
```

## Compilación

```bash
cd ~/misko_ws

colcon build --symlink-install

source install/setup.bash
```

## Ejecución

### Terminal 1

Ejecutar nodo puente ROS2 → ESP32

```bash
source ~/misko_ws/install/setup.bash

ros2 run bb8_controller cmdvel_to_esp32
```

### Terminal 2

Ejecutar teleoperación

```bash
source /opt/ros/humble/setup.bash

ros2 run teleop_twist_keyboard teleop_twist_keyboard
```

### Terminal 3 (Opcional)

Verificar mensajes

```bash
ros2 topic echo /cmd_vel
```

## Controles

```text
i  -> adelante
,  -> atrás
j  -> izquierda
l  -> derecha
k  -> detener
```

## Estado actual

* Simulación Gazebo en desarrollo.
* Comunicación ROS2 ↔ ESP32 funcional.
* Control WiFi funcional.
* Control de motores funcional.
* Integración BB8 física en desarrollo.

```
```
