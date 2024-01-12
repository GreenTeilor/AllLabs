package by.bsuir.lab1.task13;

import by.bsuir.lab1.task12.Book;

import java.util.Objects;

public class ProgrammerBook extends Book {
    private String language;
    private int level;

    public ProgrammerBook() {
        super();
    }

    public ProgrammerBook(String title, String author, int price, String language, int level) {
        super(title, author, price);
        this.language = language;
        this.level = level;
    }

    public String getLanguage() {
        return language;
    }

    public void setLanguage(String language) {
        this.language = language;
    }

    public int getLevel() {
        return level;
    }

    public void setLevel(int level) {
        this.level = level;
    }

    @Override
    public int hashCode() {
        int prime = 1151;
        int hash = super.hashCode();
        hash = prime * hash + Objects.hash(language, level);
        return hash;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!super.equals(o)) return false;
        if (!(o instanceof ProgrammerBook book)) return false;
        return Objects.equals(language, book.language) &&
                Objects.equals(level, book.level);
    }

    @Override
    public String toString() {
        return String.format("ProgrammerBook(super=%s, language=%s, level=%d)", super.toString(), language, level);
    }
}
