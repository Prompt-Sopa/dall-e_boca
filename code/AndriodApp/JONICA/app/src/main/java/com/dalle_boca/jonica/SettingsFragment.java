package com.dalle_boca.jonica;

import android.graphics.Color;
import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;

import org.eclipse.paho.client.mqttv3.MqttMessage;

public class SettingsFragment extends Fragment implements MqttMessageListener {
    private ImageView Classifier1;
    private ImageView Classifier2;
    private ImageView Classifier3;
    private ImageView Classifier4;
    private ImageView Classifier5;
    private ImageView Classifier6;
    private ImageView Classifier7;
    private ImageView Classifier8;
    private int colors[] = {
            Color.GRAY,
            Color.MAGENTA,
            Color.CYAN,
            Color.BLUE,
            Color.YELLOW,
            Color.RED,
            Color.GREEN,
    };

//    private MqttManager mqttManager;
    // Agrupa por ID a los lugares de los contenedores
    private static final String MQTT_CLASSIFIER_POS_1_TOPIC = "/classifier/pos/1";
    private static final String MQTT_CLASSIFIER_POS_2_TOPIC = "/classifier/pos/2";
    private static final String MQTT_CLASSIFIER_POS_3_TOPIC = "/classifier/pos/3";
    private static final String MQTT_CLASSIFIER_POS_4_TOPIC = "/classifier/pos/4";
    private static final String MQTT_CLASSIFIER_POS_5_TOPIC = "/classifier/pos/5";
    private static final String MQTT_CLASSIFIER_POS_6_TOPIC = "/classifier/pos/6";
    private static final String MQTT_CLASSIFIER_POS_7_TOPIC = "/classifier/pos/7";
    private static final String MQTT_CLASSIFIER_POS_8_TOPIC = "/classifier/pos/8";

    // Escribe la ID dónde se deberían guardar
    private static final String MQTT_CLASSIFIER_OBJ_CR_TOPIC = "/classifier/object/cube_red";
    private static final String MQTT_CLASSIFIER_OBJ_CG_TOPIC = "/classifier/object/cube_green";
    private static final String MQTT_CLASSIFIER_OBJ_SG_TOPIC = "/classifier/object/sphere_green";

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rootView = inflater.inflate(R.layout.fragment_settings, container, false);

//        mqttManager = new MqttManager();
//        mqttManager.addMessageListener((MqttMessageListener) this);

        Classifier1 = rootView.findViewById(R.id.classifier_1);
        Classifier2 = rootView.findViewById(R.id.classifier_2);
        Classifier3 = rootView.findViewById(R.id.classifier_3);
        Classifier4 = rootView.findViewById(R.id.classifier_4);
        Classifier5 = rootView.findViewById(R.id.classifier_5);
        Classifier6 = rootView.findViewById(R.id.classifier_6);
        Classifier7 = rootView.findViewById(R.id.classifier_7);
        Classifier8 = rootView.findViewById(R.id.classifier_8);

//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_1_TOPIC);
//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_2_TOPIC);
//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_3_TOPIC);
//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_4_TOPIC);
//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_5_TOPIC);
//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_6_TOPIC);
//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_7_TOPIC);
//        mqttManager.subscribeToTopic(MQTT_CLASSIFIER_POS_8_TOPIC);

        return rootView;
    }

//    @Override
    public void onMessageReceived(String topic, MqttMessage message) {
//        switch(topic){
//            case MQTT_CLASSIFIER_POS_1_TOPIC:
//                paintContainer(Classifier1, message);
//                break;
//            case MQTT_CLASSIFIER_POS_2_TOPIC:
//                paintContainer(Classifier2, message);
//                break;
//            case MQTT_CLASSIFIER_POS_3_TOPIC:
//                paintContainer(Classifier3, message);
//                break;
//            case MQTT_CLASSIFIER_POS_4_TOPIC:
//                paintContainer(Classifier4, message);
//                break;
//            case MQTT_CLASSIFIER_POS_5_TOPIC:
//                paintContainer(Classifier5, message);
//                break;
//            case MQTT_CLASSIFIER_POS_6_TOPIC:
//                paintContainer(Classifier6, message);
//                break;
//            case MQTT_CLASSIFIER_POS_7_TOPIC:
//                paintContainer(Classifier7, message);
//                break;
//            case MQTT_CLASSIFIER_POS_8_TOPIC:
//                paintContainer(Classifier8, message);
//                break;
//        }
    }

    public void paintContainer(ImageView container, MqttMessage value){
        int containerId = Integer.parseInt(value.toString());
        container.setColorFilter(colors[containerId]);
    }
}