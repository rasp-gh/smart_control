\# Smart Controller



A modern C++ application for environmental monitoring and automated hardware control via MQTT and Linux sysfs/libgpiod. Designed for embedded Linux platforms (e.g., Raspberry Pi).



\## 🚀 Key Features

\- \*\*Modern C++ Architecture\*\*: Utilizes `std::optional` (C++17) for robust hardware error-handling without exceptions.

\- \*\*Hardware Abstraction\*\*: Clean decoupling of the DHT11 sensor (via IIO sysfs) and digital actuators (via modern `libgpiod`).

\- \*\*Event-Driven Control\*\*: Integrated asynchronous MQTT telemetry pipeline with Paho MQTT.

\- \*\*Automated CI/CD Documentation\*\*: Self-generating API documentation via Doxygen and GitHub Actions.



\## 🛠️ Tech Stack

\- \*\*Language\*\*: C++17

\- \*\*Libraries\*\*: `libgpiod` (v2.x preferred), `paho-mqtt-cpp`

\- \*\*Build System\*\*: CMake



\## 📦 Architecture \& Decoupling

This project demonstrates professional object-oriented design patterns for embedded systems:

1\. \*\*Interfaces vs. Implementation\*\*: All public APIs are thoroughly documented in header files using Doxygen format. Source files are kept clean and maintainable.

2\. \*\*Fail-Safe Processing\*\*: Hardware reads return wrapped optionals. If a sensor fails or returns a corrupted value (e.g., outside boundaries), the system catches it safely without crashing the main telemetry loop.



\## 📖 API Documentation

The complete API reference is automatically built and deployed on every push.  

🔗 \*\*\[View the Live Doxygen Documentation Here](https://YOUR\_GITHUB\_USERNAME.github.io/YOUR\_REPOSITORY\_NAME/)\*\*



\## 🔧 Building the Project

```bash

mkdir build \&\& cd build

cmake ..

make

./SmartController

```



