package com.dalle_boca.jonica;

public class Option {
    private String title;
    private String description;

    public Option(String title, String description) {
        this.title = title;
        this.description = description;
    }

    public String getTitle() {
        return title;
    }

    public String getDescription() {
        return description;
    }
}
