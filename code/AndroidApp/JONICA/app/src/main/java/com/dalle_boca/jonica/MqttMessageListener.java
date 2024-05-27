package com.dalle_boca.jonica;

import org.eclipse.paho.client.mqttv3.MqttMessage;

public interface MqttMessageListener {
    void onMessageReceived(String topic, MqttMessage message);
}