package com.dalle_boca.jonica;

import android.util.Log;

import org.eclipse.paho.client.mqttv3.IMqttMessageListener;
import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.util.ArrayList;

public class MqttMessageHandler implements IMqttMessageListener {
    private static final String TAG = "MqttMessageHandler";
    private ArrayList<MqttMessageListener> messageListeners = new ArrayList<>();

    @Override
    public void messageArrived(String topic, MqttMessage message) throws Exception {
        Log.d(TAG, "MQTT message arrived on topic " + topic);
        // Notificar a todos los oyentes registrados que se ha recibido un mensaje MQTT
        for (MqttMessageListener listener : messageListeners) {
            listener.onMessageReceived(topic, message);
        }
    }

    public void addMessageListener(MqttMessageListener listener) {
        // Registrar un oyente para recibir mensajes MQTT
        messageListeners.add(listener);
    }

    public void removeMessageListener(MqttMessageListener listener) {
        // Eliminar un oyente registrado para dejar de recibir mensajes MQTT
        messageListeners.remove(listener);
    }
}