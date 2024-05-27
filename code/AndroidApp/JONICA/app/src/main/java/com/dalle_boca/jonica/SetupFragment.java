package com.dalle_boca.jonica;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;
import androidx.lifecycle.Observer;
import androidx.lifecycle.ViewModelProvider;
import androidx.recyclerview.widget.LinearLayoutManager;
import androidx.recyclerview.widget.RecyclerView;
import com.dalle_boca.jonica.viewmodel.OptionViewModel;

import java.util.ArrayList;
import java.util.List;

public class SetupFragment extends Fragment implements OptionAdapter.OptionClickListener {

    private OptionViewModel optionViewModel;
    private RecyclerView recyclerView;
    private OptionAdapter optionAdapter;

    private MqttManager mqttManager;
    private static final String MQTT_SETUP_TOPIC = "/setup";

    @Nullable
    @Override
    public View onCreateView(@NonNull LayoutInflater inflater, @Nullable ViewGroup container, @Nullable Bundle savedInstanceState) {
        return inflater.inflate(R.layout.fragment_setup, container, false);
    }

    @Override
    public void onViewCreated(@NonNull View view, @Nullable Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

//        mqttManager = new MqttManager();

        recyclerView = view.findViewById(R.id.recyclerView);
        recyclerView.setLayoutManager(new LinearLayoutManager(getContext()));

        optionViewModel = new ViewModelProvider(requireActivity()).get(OptionViewModel.class);

        List<Option> options = new ArrayList<>();
        options.add(new Option("Unique object segregation in single containers", "Segregates objects by shape and color between 3 singles containers in positions A, B, or C"));
        options.add(new Option("Unique object segregation in double containers", "Segregates objects by shape and color between 3 double containers in positions A-B, C-D, or E-F"));
        options.add(new Option("Color Segregation", "Segregates objects by color between 2 double containers in positions A-B, or C-D"));
        options.add(new Option("Shape Segregation", "Segregates objects by shape 2 double containers in positions A-B, or C-D"));

        optionAdapter = new OptionAdapter(options, new OptionAdapter.OptionClickListener() {
            @Override
            public void onOptionClick(int position) {
                optionViewModel.selectOption(position);
            }
        }, optionViewModel.getSelectedOption());

        recyclerView.setAdapter(optionAdapter);

        optionViewModel.getSelectedOption().observe(getViewLifecycleOwner(), new Observer<Integer>() {
            @SuppressLint("NotifyDataSetChanged")
            @Override
            public void onChanged(Integer selectedPosition) {
                optionAdapter.notifyDataSetChanged();
            }
        });
    }

    @Override
    public void onOptionClick(int position) {
//        mqttManager.publishMessage(MQTT_SETUP_TOPIC, String.valueOf(position));
    }
}
