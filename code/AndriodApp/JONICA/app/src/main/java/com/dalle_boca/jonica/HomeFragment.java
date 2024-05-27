package com.dalle_boca.jonica;

import android.annotation.SuppressLint;
import android.os.Bundle;

import androidx.annotation.NonNull;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;

import com.dalle_boca.jonica.viewmodel.ButtonViewModel;

public class HomeFragment extends Fragment {
    private ButtonViewModel buttonViewModel;
    private Button buttonRun;
    private Button buttonStop;
    private MqttManager mqttManager;
    private static final String MQTT_MODE_TOPIC = "/mode";
    @SuppressLint("MissingInflatedId")
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        //View rootView = inflater.inflate(R.layout.fragment_home, container, false);
        // Inflate the layout for this fragment
        return inflater.inflate(R.layout.fragment_home, container, false);
    }
    @SuppressLint("SetJavaScriptEnabled")
    @Override
    public void onViewCreated(@NonNull View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        buttonRun = view.findViewById(R.id.button_run);
        buttonStop = view.findViewById(R.id.button_stop);

        WebView webView = view.findViewById(R.id.camera_feed);
        webView.setWebViewClient(new WebViewClient());
        webView.getSettings().setJavaScriptEnabled(true);
        webView.loadUrl("http://192.168.1.5:5000");

//        mqttManager = new MqttManager();

        buttonViewModel = new ViewModelProvider(requireActivity()).get(ButtonViewModel.class);

        buttonViewModel.getIsRunActive().observe(getViewLifecycleOwner(), new Observer<Boolean>() {
            @Override
            public void onChanged(Boolean isActive) {
                buttonRun.setBackgroundResource(isActive ? R.drawable.button_background_active_green : R.drawable.button_background);
            }
        });

        buttonViewModel.getIsStopActive().observe(getViewLifecycleOwner(), new Observer<Boolean>() {
            @Override
            public void onChanged(Boolean isActive) {
                buttonStop.setBackgroundResource(isActive ? R.drawable.button_background_active_red : R.drawable.button_background);
            }
        });

        buttonRun.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonViewModel.activateRun();
//                mqttManager.publishMessage(MQTT_MODE_TOPIC, "run");
            }
        });

        buttonStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonViewModel.activateStop();
//                mqttManager.publishMessage(MQTT_MODE_TOPIC, "stop");
            }
        });
    }
}