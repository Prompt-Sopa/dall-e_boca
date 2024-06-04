package com.dalle_boca.jonica.viewmodel;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class OptionViewModel extends ViewModel {
    private final MutableLiveData<Integer> selectedOption = new MutableLiveData<>();

    public LiveData<Integer> getSelectedOption() {
        return selectedOption;
    }

    public void selectOption(int index) {
        selectedOption.setValue(index);
    }
}
