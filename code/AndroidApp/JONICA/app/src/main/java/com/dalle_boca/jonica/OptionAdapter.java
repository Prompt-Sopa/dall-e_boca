package com.dalle_boca.jonica;

import android.annotation.SuppressLint;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;
import androidx.annotation.NonNull;
import androidx.lifecycle.LiveData;
import androidx.recyclerview.widget.RecyclerView;
import java.util.List;

public class OptionAdapter extends RecyclerView.Adapter<OptionAdapter.OptionViewHolder> {

    private final List<Option> options;
    private final OptionClickListener optionClickListener;
    private LiveData<Integer> selectedOption;

    public OptionAdapter(List<Option> options, OptionClickListener optionClickListener, LiveData<Integer> selectedOption) {
        this.options = options;
        this.optionClickListener = optionClickListener;
        this.selectedOption = selectedOption;
    }

    @NonNull
    @Override
    public OptionViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.item_option, parent, false);
        return new OptionViewHolder(view);
    }

    @Override
    public void onBindViewHolder(@NonNull OptionViewHolder holder, @SuppressLint("RecyclerView") int position) {
        Option option = options.get(position);
        holder.title.setText(option.getTitle());
        holder.description.setText(option.getDescription());
        holder.itemView.setBackgroundColor(
                selectedOption.getValue() != null && selectedOption.getValue() == position ?
                        holder.itemView.getResources().getColor(R.color.selected) :
                        holder.itemView.getResources().getColor(android.R.color.transparent)
        );
        holder.itemView.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                optionClickListener.onOptionClick(position);
            }
        });
    }

    @Override
    public int getItemCount() {
        return options.size();
    }

    public interface OptionClickListener {
        void onOptionClick(int position);
    }

    public static class OptionViewHolder extends RecyclerView.ViewHolder {
        TextView title;
        TextView description;

        public OptionViewHolder(@NonNull View itemView) {
            super(itemView);
            title = itemView.findViewById(R.id.title);
            description = itemView.findViewById(R.id.description);
        }
    }
}
