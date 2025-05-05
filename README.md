# Proyecto Robot Sumo

## Descripción
Este proyecto consiste en el diseño y programación de un robot de sumo utilizando Arduino para la asignatura de Sistemas Multidisciplinares de Percepción (SMP) en la Universidad de Granada (UGR).

## Objetivo
El objetivo principal es crear un robot autónomo capaz de detectar y empujar a otros robots fuera de un área de combate circular (dohyo), siguiendo las reglas tradicionales de las competiciones de sumo robótico.

## Componentes Utilizados
- Arduino (placa de control)
- Puente H L298N (control de motores)
- Motores DC
- Sensores ultrasónicos HC-SR04 (3 unidades: centro, izquierda y derecha)
- Sensores infrarrojos (2 unidades: izquierda y derecha)
- Pantalla LCD I2C
- Cables y conectores
- Chasis y estructura mecánica

## Conexiones
### Motores
- Motor Izquierdo:
  - IN1: Pin 7
  - IN2: Pin 8
  - ENA: Pin 9 (control de velocidad)
- Motor Derecho:
  - IN3: Pin 13
  - IN4: Pin 12
  - ENB: Pin 11 (control de velocidad)

### Sensores Ultrasónicos
- Sensor Centro:
  - Trigger: Pin 4
  - Echo: Pin 5
- Sensor Izquierda:
  - Trigger: Pin 2
  - Echo: Pin 3
- Sensor Derecha:
  - Trigger: Pin 6
  - Echo: Pin 10

### Sensores Infrarrojos
- Sensor Izquierda: Pin A2
- Sensor Derecha: Pin A3

### Pantalla LCD
- Conexión I2C (dirección 0x27)

## Funcionamiento
El robot opera siguiendo esta lógica:

1. **Detección de Líneas**: Los sensores infrarrojos detectan el borde del dohyo (línea blanca). Cuando se detecta el borde:
   - Si se detecta en el sensor izquierdo, el robot gira a la derecha
   - Si se detecta en el sensor derecho, el robot gira a la izquierda

2. **Detección de Oponentes**: Los sensores ultrasónicos detectan la presencia de oponentes:
   - Si se detecta al frente, el robot avanza a máxima potencia
   - Si se detecta a la derecha, el robot gira a la derecha
   - Si se detecta a la izquierda, el robot gira a la izquierda

3. **Movimientos**:
   - Avance: Ambos motores a máxima potencia (255)
   - Giro derecha/izquierda: Rotación con potencia reducida (190)

4. **Interfaz de Usuario**:
   - La pantalla LCD muestra información sobre el estado actual del robot:
     - Detección de líneas ("Linea izq", "Linea der")
     - Dirección de ataque ("ataca delan", "ataca der", "ataca izq")

## Estructura del Código
El código está organizado en varias funciones principales:

- `setup()`: Inicialización de pines, sensores, motores y pantalla LCD
- `loop()`: Bucle principal que gestiona la lógica de detección y movimiento
- `motorAvanza()`: Controla el avance del robot
- `motorGiraIzq()`: Controla el giro a la izquierda
- `motorGiraDer()`: Controla el giro a la derecha
- `sensores()`: Gestiona la lectura de los sensores ultrasónicos y determina la dirección del oponente

## Archivos del Proyecto
- `CodigoFinal.ino`: Código Arduino completo
- `CodigoFinal_2.pdf`: Documentación del código
- `Presentacion Robot.pdf`: Presentación del proyecto
- `TestRobot.mp4`: Video de prueba del robot

## Pasos Seguidos en el Desarrollo
1. Diseño conceptual del robot y selección de componentes
2. Montaje del chasis y estructura mecánica
3. Conexión de componentes electrónicos
4. Programación de funciones básicas de movimiento
5. Implementación de la detección de líneas (sensores infrarrojos)
6. Implementación de la detección de oponentes (sensores ultrasónicos)
7. Integración de la pantalla LCD para información visual
8. Pruebas y ajustes de parámetros
9. Documentación del proyecto

## Mejoras Futuras
- Optimización de algoritmos de detección
- Mejora de la estrategia de combate
- Implementación de modos de comportamiento adicionales
- Reducción del consumo energético

## Autores
- Juan Navarro Maldonado
- Joaquin Sergio Garcia Ibañez
