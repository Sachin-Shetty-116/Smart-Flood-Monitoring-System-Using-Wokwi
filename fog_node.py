import json
import paho.mqtt.client as mqtt

BROKER = "broker.hivemq.com"
PORT = 1883
SENSOR_TOPIC = "sachin-flood-demo-01/sensor"
PROCESSED_TOPIC = "sachin-flood-demo-01/processed"


def on_connect(client, userdata, flags, reason_code, properties):
    if reason_code == 0:
        print("Fog Node Connected to MQTT!")
        client.subscribe(SENSOR_TOPIC)
        print("Subscribed to:", SENSOR_TOPIC)
    else:
        print("MQTT connection failed:", reason_code)


def on_message(client, userdata, message):
    try:
        data = json.loads(message.payload.decode())
        raw_value = int(data["raw"])
        level = int(data["level"])

        if level < 40:
            status, led, buzzer = "NORMAL", "GREEN", "OFF"
        elif level < 70:
            status, led, buzzer = "HIGH", "YELLOW", "OFF"
        else:
            status, led, buzzer = "FLOOD ALERT", "RED", "ON"

        result = {
            "raw": raw_value,
            "level": level,
            "status": status,
            "led": led,
            "buzzer": buzzer
        }
        client.publish(PROCESSED_TOPIC, json.dumps(result), retain=True)
        print("Processed Data:", result)
    except (ValueError, KeyError, json.JSONDecodeError) as error:
        print("Invalid sensor message:", error)


client = mqtt.Client(
    callback_api_version=mqtt.CallbackAPIVersion.VERSION2,
    client_id="Flood-Fog-Node"
)
client.on_connect = on_connect
client.on_message = on_message

print("Starting Flood Detection Fog Node...")
client.connect(BROKER, PORT, 60)
client.loop_forever()
