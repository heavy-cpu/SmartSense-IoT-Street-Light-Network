# Node Details for Smart Street Light IoT System

----------------------------------------
Edge Node (Central Controller)
----------------------------------------
Device: ESP32 or ESP8266

Responsibilities:
- Serves as the master coordinator for all street light end nodes
- Connects to WiFi and communicates with Blynk, ThingSpeak, or other IoT dashboards
- Receives ON/OFF status updates from each end node, as well as basic sensor data (ambient light and motion)
- Enables monitoring, logging, and remote control for street lights via the IoT dashboard
- Sends ON/OFF control commands to individual end nodes based on sensor input or remote requests

Connections:
- WiFi to cloud dashboard
- Wireless communication (e.g., WiFi or RF) with end nodes

----------------------------------------
End Node (Lamp Post Controller)
----------------------------------------
Device: ESP8266 (one for each street lamp)

Responsibilities:
- Measures ambient light using an LDR sensor (determines night or day)
- Detects motion using a PIR sensor
- Controls the connected street light (LED/bulb) using ON or OFF states only
    - OFF during daylight or when no motion detected at night
    - ON during darkness and when motion is detected
- Reports ON/OFF status and sensor readings (light level, motion detected) to the edge node
- Receives ON/OFF control commands from edge node

Connections for each End Node:
- LDR Sensor: A0 (analog input) for light measurement
- PIR Motion Sensor: D5 (digital input) for motion detection
- LED/Bulb: D1 (digital output; relay/driver as required)
- WiFi connection for communication with edge node

Example Configuration:
  End Node 1:
    - Board: ESP8266
    - LDR: A0
    - PIR: D5
    - LED/Bulb: D1

  End Node 2:
    - Board: ESP8266
    - LDR: A0
    - PIR: D5
    - LED/Bulb: D2

  ... (repeat for each lamp post as needed)

----------------------------------------
Data Flow and Control
----------------------------------------
- Each end node senses light and motion, switches its lamp ON or OFF accordingly, and reports current status to the edge node.
- Edge node collects ON/OFF statuses and pushes aggregated data to the IoT dashboard for monitoring and analytics.
- Users can view street light activity and basic sensor history remotely via the dashboard.

----------------------------------------

*Note: Only ON/OFF light control is supported at this stage. Dimming functionality is not implemented or tested yet. Future versions may add adaptive brightness features.*

