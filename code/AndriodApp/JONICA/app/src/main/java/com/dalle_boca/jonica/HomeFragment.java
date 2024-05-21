package com.dalle_boca.jonica;

import android.app.ActionBar;
import android.os.Build;
import android.os.Bundle;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.content.ContextCompat;
import androidx.fragment.app.Fragment;
import androidx.fragment.app.FragmentActivity;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowInsets;
import android.view.WindowInsetsController;
import android.widget.ImageButton;

public class HomeFragment extends Fragment {
    private ImageButton buttonPlay;
    private ImageButton buttonPause;
    private ImageButton buttonStop;
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rootView = inflater.inflate(R.layout.fragment_home, container, false);

        buttonPlay = rootView.findViewById(R.id.button_play);
        buttonPause = rootView.findViewById(R.id.button_pause);
        buttonStop = rootView.findViewById(R.id.button_stop);

        buttonPlay.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonPlay.setImageResource(R.drawable.ic_play_button_pressed);
                buttonPause.setImageResource(R.drawable.ic_pause_button);
                buttonStop.setImageResource(R.drawable.ic_stop_button);

                // TODO: Publicar en MQTT que diga "play"
            }
        });
        buttonPause.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonPlay.setImageResource(R.drawable.ic_play_button);
                buttonPause.setImageResource(R.drawable.ic_pause_button_pressed);
                buttonStop.setImageResource(R.drawable.ic_stop_button);

                // TODO: Publicar en MQTT que diga "pause"
            }
        });

        buttonStop.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                buttonPlay.setImageResource(R.drawable.ic_play_button);
                buttonPause.setImageResource(R.drawable.ic_pause_button);
                buttonStop.setImageResource(R.drawable.ic_stop_button_pressed);

                // TODO: Publicar en MQTT que diga "stop"
            }
        });

        return rootView;
    }
}