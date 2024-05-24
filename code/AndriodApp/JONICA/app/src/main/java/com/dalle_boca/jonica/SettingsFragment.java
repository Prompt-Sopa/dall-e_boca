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
            Color.MAGENTA,
            Color.CYAN,
            Color.BLUE,
            Color.YELLOW,
            Color.RED,
            Color.GREEN,
    };

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rootView = inflater.inflate(R.layout.fragment_settings, container, false);

        Classifier1 = rootView.findViewById(R.id.classifier_1);
        Classifier2 = rootView.findViewById(R.id.classifier_2);
        Classifier3 = rootView.findViewById(R.id.classifier_3);
        Classifier4 = rootView.findViewById(R.id.classifier_4);
        Classifier5 = rootView.findViewById(R.id.classifier_5);
        Classifier6 = rootView.findViewById(R.id.classifier_6);
        Classifier7 = rootView.findViewById(R.id.classifier_7);
        Classifier8 = rootView.findViewById(R.id.classifier_8);

        Classifier1.setColorFilter(colors[0]);
        Classifier2.setColorFilter(colors[1]);
        Classifier3.setColorFilter(colors[2]);
        Classifier4.setColorFilter(colors[3]);
        Classifier5.setColorFilter(colors[4]);
        Classifier6.setColorFilter(colors[5]);

        return rootView;
    }

    @Override
    public void onMessageReceived(String topic, MqttMessage message) {

    }
}