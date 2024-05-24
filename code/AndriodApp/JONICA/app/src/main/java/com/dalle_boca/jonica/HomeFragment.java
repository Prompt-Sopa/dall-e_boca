package com.dalle_boca.jonica;

import android.app.ActionBar;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.ServiceConnection;
import android.os.Build;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;

import android.os.IBinder;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowInsets;
import android.view.WindowInsetsController;
import android.widget.ImageButton;

import org.eclipse.paho.android.service.MqttService;

public class HomeFragment extends Fragment {
    private ImageButton buttonPlay;
    private ImageButton buttonPause;
    private ImageButton buttonStop;
    private MqttManager mqttManager;
    private static final String MQTT_MODE_TOPIC = "/mode";
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rootView = inflater.inflate(R.layout.fragment_home, container, false);

        rootView.setSystemUiVisibility(
                View.SYSTEM_UI_FLAG_IMMERSIVE
                        | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                        | View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                        | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
        );

//        mqttManager = new MqttManager();

        buttonPlay = rootView.findViewById(R.id.button_play);
        buttonPause = rootView.findViewById(R.id.button_pause);
        buttonStop = rootView.findViewById(R.id.button_stop);

        buttonPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonPlay.setImageResource(R.drawable.ic_play_button_pressed);
                buttonPause.setImageResource(R.drawable.ic_pause_button);
                buttonStop.setImageResource(R.drawable.ic_stop_button);

//                mqttManager.publishMessage(MQTT_MODE_TOPIC, "play");
            }
        });
        buttonPause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonPlay.setImageResource(R.drawable.ic_play_button);
                buttonPause.setImageResource(R.drawable.ic_pause_button_pressed);
                buttonStop.setImageResource(R.drawable.ic_stop_button);

//                mqttManager.publishMessage(MQTT_MODE_TOPIC, "pause");
            }
        });

        buttonStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonPlay.setImageResource(R.drawable.ic_play_button);
                buttonPause.setImageResource(R.drawable.ic_pause_button);
                buttonStop.setImageResource(R.drawable.ic_stop_button_pressed);

//                mqttManager.publishMessage(MQTT_MODE_TOPIC, "stop");
            }
        });

        return rootView;
    }
}