package by.bsuir.domain;

import lombok.Getter;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

@SuperBuilder
@Getter
@Setter
public class Statistics {
    int userId;
    int daysRegistered;
    int orderCount;
    int booksCount;
    String favoriteCategory;
}
