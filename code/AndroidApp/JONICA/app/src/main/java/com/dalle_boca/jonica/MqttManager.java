package com.dalle_boca.jonica;

import android.util.Log;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttClient;
import org.eclipse.paho.client.mqttv3.MqttConnectOptions;
import org.eclipse.paho.client.mqttv3.MqttException;
import org.eclipse.paho.client.mqttv3.MqttMessage;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;

import java.util.ArrayList;

public class MqttManager {
    private static final String TAG = "MqttManager";
    private static final String MQTT_BROKER = "tcp://192.168.100.29:1883";
    private static final String MQTT_CLIENT_ID = "AndroidClient";

    private MqttClient mqttClient;
    private ArrayList<MqttMessageListener> messageListeners = new ArrayList<>();
    private MqttMessageHandler messageHandler = new MqttMessageHandler();

    public MqttManager() {
        // Inicializar el cliente MQTT
        try {
            mqttClient = new MqttClient(MQTT_BROKER, MQTT_CLIENT_ID, new MemoryPersistence());
            MqttConnectOptions options = new MqttConnectOptions();
            options.setCleanSession(true);
            mqttClient.connect(options);
            Log.d(TAG, "MQTT Connected");
        } catch (MqttException e) {
            e.printStackTrace();
            Log.e(TAG, "MQTT no se pudo conectar");
        }
    }

    public void publishMessage(String topic, String message) {
        if (mqttClient != null && mqttClient.isConnected()) {
            try {
                mqttClient.publish(topic, new MqttMessage(message.getBytes()));
                Log.d(TAG, "Message published: " + message);
            } catch (MqttException e) {
                e.printStackTrace();
            }
        } else {
            Log.e(TAG, "Not connected to MQTT broker");
        }
    }

    public void subscribeToTopic(String topic) {
        try {
            mqttClient.subscribe(topic, messageHandler);
            Log.d(TAG, "Subscribed to topic: " + topic);
        } catch (MqttException e) {
            e.printStackTrace();
        }
    }

    public void addMessageListener(MqttMessageListener listener) {
        // Registrar un oyente para recibir mensajes MQTT
        messageHandler.addMessageListener(listener);
    }

    public void removeMessageListener(MqttMessageListener listener) {
        // Eliminar un oyente registrado para dejar de recibir mensajes MQTT
        messageHandler.removeMessageListener(listener);
    }
}
