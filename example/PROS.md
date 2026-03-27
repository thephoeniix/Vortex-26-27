
---

# 🤖 PROS + Control de Robots (VEX)

<p align="center">
  <img src="example/images/PROS.png" width="500"/>
</p>

---

## 🚀 ¿Qué es PROS?

* 🧠 Sensores que miden
* 🎯 Control que corrige
* 🤖 Robots que ganan

---

# 🛠️ Instalación

<p align="center">
  <img src="example/images/PROS_extensiones.png" width="500"/>
</p>

1. Abre VS Code
2. Ve a extensiones
3. Busca **PROS**
4. Instala

---

# 📁 Crear proyecto

<p align="center">
  <img src="example/images/CreateProject.png" width="400"/>
  <img src="example/images/Create_PROS.png" width="400"/>
</p>

1. Click en **Create Project**
2. Selecciona:

   * V5
   * Latest (Recommended)

---

# 📂 Estructura del proyecto

<p align="center">
  <img src="example/images/LIB_Project.png" width="500"/>
</p>

💡 Aquí encontrarás:

* `src/`
* `include/`
* `main.cpp`

---

# 📄 Archivo principal

<p align="center">
  <img src="example/images/main.png" width="500"/>
</p>

```cpp
src/main.cpp
```

---

# ⚙️ Inicialización

<p align="center">
  <img src="example/images/ultimate_main.png" width="500"/>
</p>

```cpp
void initialize() {
  pros::lcd::initialize();
}
```

---

# ⚙️ Hardware Setup

```cpp
pros::MotorGroup left_mg({8, 10});
pros::MotorGroup right_mg({1, 2});

pros::Imu imu(5);

pros::Controller master(pros::E_CONTROLLER_MASTER);
```

---

# 📡 Sensores

<p align="center">
  <img src="example/images/IMU.png" width="300"/>
  <img src="example/images/ENC.png" width="300"/>
</p>

* IMU → orientación
* Encoders → movimiento

💡 360° = 1 rotación

---

# ❓ ¿Por qué falla un robot?

```cpp
error = target - actual;
```

👉 Porque no tiene retroalimentación (feedback)

---

# 🔁 Sistema de control

```
Sensor → Error → Control → Movimiento
```

---

# 🎮 CONTROL DEL ROBOT (Manual)

<p align="center">
  <img src="example/images/Control.png" width="500"/>
</p>

<p align="center">
  <img src="https://media.giphy.com/media/l0HlBO7eyXzSZkJri/giphy.gif" width="400"/>
</p>

---

## 🧠 ¿Qué estamos haciendo?

Controlar el robot en tiempo real con el joystick.

---

## 🔁 Estructura base

```cpp
void opcontrol() {
  while (true) {

  }
}
```

---

## 🎯 Paso 1: Leer joystick

```cpp
int power = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
int turn  = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);
```

---

## ⚠️ Paso 2: Deadband

```cpp
if (abs(power) < 5) power = 0;
if (abs(turn) < 5) turn = 0;
```

---

## 🔀 Paso 3: Mezcla

```cpp
int left_power  = power + turn;
int right_power = power - turn;
```

---

## 🚗 Paso 4: Movimiento

```cpp
left_mg.move(left_power);
right_mg.move(right_power);
```

---

## ⏱️ Paso 5: Delay

```cpp
pros::delay(20);
```

---

## ✅ Código completo

```cpp
void opcontrol() {
  while (true) {

    int power = -master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
    int turn  = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X);

    if (abs(power) < 5) power = 0;
    if (abs(turn) < 5) turn = 0;

    int left_power  = power + turn;
    int right_power = power - turn;

    left_mg.move(left_power);
    right_mg.move(right_power);

    pros::delay(20);
  }
}
```

---

# 🤖 MOVIMIENTO AUTÓNOMO

<p align="center">
  <img src="https://media.giphy.com/media/3o7aD2saalBwwftBIY/giphy.gif" width="400"/>
</p>



# 🧭 Tutorial: TURN (Girar paso a paso)

<p align="center">
  <img src="example/images/IMU.png" width="350"/>
</p>

<p align="center">
  <img src="https://media.giphy.com/media/3o7aD2saalBwwftBIY/giphy.gif" width="350"/>
</p>

---

## 🧠 ¿Qué vamos a hacer?

Hacer que el robot gire hasta un ángulo específico usando el IMU.

---

## 🧩 Paso 1: Reiniciar orientación

```cpp
imu.tare_yaw();
```

💡 Esto pone el ángulo en **0°**

---

## 📡 Paso 2: Leer el ángulo actual

```cpp
double yaw = imu.get_yaw();
```

👉 Nos dice hacia dónde está mirando el robot

---

## 🛑 Paso 3: Condición de paro

```cpp
if (yaw >= angleDeg) break;
```

💡 Cuando llegue al ángulo → se detiene

---

## 🔄 Paso 4: Girar

```cpp
left_mg.move(-speed);
right_mg.move(speed);
```

👉 Un lado avanza, el otro retrocede → gira

---

## ⏱️ Paso 5: Delay

```cpp
pros::delay(20);
```

---

## ✅ Código completo

```cpp
void turn(double angleDeg) {
  imu.tare_yaw();
  const int speed = 50;

  while (true) {
    double yaw = imu.get_yaw();

    if (yaw >= angleDeg) break;

    left_mg.move(-speed);
    right_mg.move(speed);

    pros::delay(20);
  }

  left_mg.brake();
  right_mg.brake();
}
```

---

# 🚗 Tutorial: DRIVE (Avanzar paso a paso)

<p align="center">
  <img src="https://media.giphy.com/media/l0MYt5jPR6QX5pnqM/giphy.gif" width="350"/>
</p>



## 🧠 ¿Qué vamos a hacer?

Hacer que el robot avance por un tiempo determinado.

---

## 🧩 Paso 1: Definir velocidad

```cpp
int speed = 60;
```

---

## ⏱️ Paso 2: Guardar tiempo inicial

```cpp
uint32_t start = pros::millis();
```

💡 Guarda el momento en que empieza

---

## 🔁 Paso 3: Loop con tiempo

```cpp
while ((pros::millis() - start) < time_ms)
```

👉 Se ejecuta hasta que pase el tiempo

---

## 🚗 Paso 4: Mover motores

```cpp
left_mg.move(speed);
right_mg.move(speed);
```

---

## ⏱️ Paso 5: Delay

```cpp
pros::delay(20);
```

---

## 🛑 Paso 6: Detener

```cpp
left_mg.brake();
right_mg.brake();
```

---

## ✅ Código completo

```cpp
void drive(double time_ms) {
  int speed = 60;
  uint32_t start = pros::millis();

  while ((pros::millis() - start) < time_ms) {
    left_mg.move(speed);
    right_mg.move(speed);
    pros::delay(20);
  }

  left_mg.brake();
  right_mg.brake();
}
```

---

# 🎯 Diferencia clave

| Función | Usa sensor | Precisión |
| ------- | ---------- | --------- |
| DRIVE   | ❌ No       | Baja      |
| TURN    | ✅ Sí (IMU) | Alta      |

---

💡 **Tip importante:**

* `drive` → fácil pero impreciso
* `turn` → más preciso porque usa sensor


---

# 🤖 IMPLEMENTACIÓN FINAL

```cpp
void autonomous() {
  turn(90);
  drive(2000);
}
```

