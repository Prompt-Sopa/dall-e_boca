package com.dalle_boca.jonica;

import android.os.Bundle;

import androidx.fragment.app.Fragment;

import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

import android.graphics.Color;
import android.os.Bundle;
import android.widget.Button;

import com.github.mikephil.charting.charts.BarChart;
import com.github.mikephil.charting.components.XAxis;
import com.github.mikephil.charting.components.YAxis;
import com.github.mikephil.charting.data.BarData;
import com.github.mikephil.charting.data.BarDataSet;
import com.github.mikephil.charting.data.BarEntry;
import com.github.mikephil.charting.formatter.IndexAxisValueFormatter;
import com.github.mikephil.charting.utils.ColorTemplate;

import org.eclipse.paho.client.mqttv3.MqttMessage;

import java.util.ArrayList;
public class StatisticsFragment extends Fragment implements MqttMessageListener {
    Button buttonReset;
    // variable for our bar chart
    BarChart barChart;
    // variable for our bar data.
    BarData barData;
    // variable for our bar data set.
    BarDataSet barDataSet;
    // array list for storing entries.
    ArrayList barEntriesArrayList;
    private MqttManager mqttManager;
    private static final String MQTT_OBJECT_CUBE_RED_TOPIC = "/object/cube/red";
    private static final String MQTT_OBJECT_CUBE_GREEN_TOPIC = "/object/cube/green";
    private static final String MQTT_OBJECT_SPHERE_RED_TOPIC = "/object/sphere/red";
    private static final String MQTT_OBJECT_SPHERE_GREEN_TOPIC = "/object/sphere/green";
    private static final String MQTT_OBJECT_RESET = "/object/reset";
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container, Bundle savedInstanceState) {
        // Inflate the layout for this fragment
        View rootView = inflater.inflate(R.layout.fragment_statistics, container, false);

        mqttManager = new MqttManager();
        mqttManager.addMessageListener((MqttMessageListener) this);

        buttonReset = rootView.findViewById(R.id.button_reset);

        // initializing variable for bar chart.
        barChart = rootView.findViewById(R.id.idBarChart);

        // calling method to get bar entries.
        barEntriesArrayList = new ArrayList<>();
        for (int i = 0; i < 4; i++) { // 6 es el número de barras
            barEntriesArrayList.add(new BarEntry(i + 1, 0)); // El segundo parámetro es el valor inicial
        }

        // creating a new bar data set.
        barDataSet = new BarDataSet(barEntriesArrayList, "JONICA");

        // creating a new bar data and passing our bar data set.
        barData = new BarData(barDataSet);

        // below line is to set data to our bar chart.
        barChart.setData(barData);

        // adding color to our bar data set.
        barDataSet.setColors(ColorTemplate.PASTEL_COLORS);

        // setting text color.
        barDataSet.setValueTextColor(Color.BLACK);

        // setting text size
        barDataSet.setValueTextSize(16f);
        barChart.getDescription().setEnabled(false);

        XAxis xAxis = barChart.getXAxis();
        xAxis.setPosition(XAxis.XAxisPosition.BOTTOM); // Posición de las etiquetas en la parte inferior
        xAxis.setGranularity(1f); // Espaciado entre las etiquetas
        xAxis.setValueFormatter(new IndexAxisValueFormatter(new String[]{"", "cube_red", "cube_green", "sphere_red", "sphere_green"}));

        // setting axis
        YAxis yAxis = barChart.getAxisLeft();
        yAxis.setAxisMinimum(0f); // Mínimo valor del eje Y
        yAxis.setAxisMaximum(10f); // Máximo valor del eje Y, ajusta según sea necesario

        barChart.getAxisRight().setEnabled(false); // Deshabilitar eje derecho si no es necesario

        mqttManager.subscribeToTopic(MQTT_OBJECT_CUBE_RED_TOPIC);
        mqttManager.subscribeToTopic(MQTT_OBJECT_CUBE_GREEN_TOPIC);
        mqttManager.subscribeToTopic(MQTT_OBJECT_SPHERE_RED_TOPIC);
        mqttManager.subscribeToTopic(MQTT_OBJECT_SPHERE_GREEN_TOPIC);
        buttonReset.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v){
                mqttManager.publishMessage(MQTT_OBJECT_CUBE_RED_TOPIC, "0");
                mqttManager.publishMessage(MQTT_OBJECT_CUBE_GREEN_TOPIC, "0");
                mqttManager.publishMessage(MQTT_OBJECT_SPHERE_RED_TOPIC, "0");
                mqttManager.publishMessage(MQTT_OBJECT_SPHERE_GREEN_TOPIC, "0");
                mqttManager.publishMessage(MQTT_OBJECT_RESET, "True");
            }
        });

        return rootView;
    }

    @Override
    public void onMessageReceived(String topic, MqttMessage message) {
        // Manejar el mensaje MQTT recibido
        if (topic.equals(MQTT_OBJECT_CUBE_RED_TOPIC)) {
            // Actualizar el valor de la barra correspondiente al motor 1
            float newValue = Float.parseFloat(message.toString());
            updateBarEntry(0, newValue); // Suponiendo que el valor del motor 1 está en la primera posición de barEntriesArrayList
        }
        if (topic.equals(MQTT_OBJECT_CUBE_GREEN_TOPIC)) {
            // Actualizar el valor de la barra correspondiente al motor 1
            float newValue = Float.parseFloat(message.toString());
            updateBarEntry(1, newValue); // Suponiendo que el valor del motor 1 está en la primera posición de barEntriesArrayList
        }
        if (topic.equals(MQTT_OBJECT_SPHERE_RED_TOPIC)) {
            // Actualizar el valor de la barra correspondiente al motor 1
            float newValue = Float.parseFloat(message.toString());
            updateBarEntry(2, newValue); // Suponiendo que el valor del motor 1 está en la primera posición de barEntriesArrayList
        }
        if (topic.equals(MQTT_OBJECT_SPHERE_GREEN_TOPIC)) {
            // Actualizar el valor de la barra correspondiente al motor 1
            float newValue = Float.parseFloat(message.toString());
            updateBarEntry(3, newValue); // Suponiendo que el valor del motor 1 está en la primera posición de barEntriesArrayList
        }
    }

    private void updateBarEntry(int index, float newValue) {
        if (index >= 0 && index < barEntriesArrayList.size()) {
            BarEntry entry = (BarEntry) barEntriesArrayList.get(index);
            entry.setY(newValue);
            barEntriesArrayList.set(index, entry);

            // Notificar al gráfico que los datos han cambiado y actualizarlo en el hilo principal
            requireActivity().runOnUiThread(() -> {
                barDataSet.notifyDataSetChanged();
                barChart.notifyDataSetChanged();
                barChart.invalidate();
            });
        }
    }
}