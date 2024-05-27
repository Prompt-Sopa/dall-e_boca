package com.dalle_boca.jonica.viewmodel;

import androidx.lifecycle.LiveData;
import androidx.lifecycle.MutableLiveData;
import androidx.lifecycle.ViewModel;

public class ButtonViewModel extends ViewModel {
    private final MutableLiveData<Boolean> isRunActive = new MutableLiveData<>(false);
    private final MutableLiveData<Boolean> isStopActive = new MutableLiveData<>(true);

    public LiveData<Boolean> getIsRunActive() {
        return isRunActive;
    }

    public LiveData<Boolean> getIsStopActive() {
        return isStopActive;
    }

    public void activateRun() {
        isRunActive.setValue(true);
        isStopActive.setValue(false);
    }

    public void activateStop() {
        isRunActive.setValue(false);
        isStopActive.setValue(true);
    }
}