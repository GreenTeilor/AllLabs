package by.bsuir.springbootproject.entities;

import jakarta.validation.constraints.Min;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;
import lombok.Getter;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

@SuperBuilder
@Getter
@Setter
public class Statistics {
    @NotNull(message = "Not inputted")
    int userId;

    @Min(value = 0, message = "Min is 0")
    int daysRegistered;

    @Min(value = 0, message = "Min is 0")
    int orderCount;

    @Min(value = 0, message = "Min is 0")
    int booksCount;

    @Size(min = 10, max = 50, message = "Category length has to be from 10 to 50")
    String favoriteCategory;
}
