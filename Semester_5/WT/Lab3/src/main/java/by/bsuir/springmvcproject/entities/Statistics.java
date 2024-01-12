package by.bsuir.springmvcproject.entities;

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
    @NotNull(message = "Не введено")
    int userId;

    @Min(value = 0, message = "Минимум 0")
    int daysRegistered;

    @Min(value = 0, message = "Минимум 0")
    int orderCount;

    @Min(value = 0, message = "Минимум 0")
    int booksCount;

    @Size(min = 10, max = 50, message = "Длина категории должна быть от 10 до 50 символов включительно")
    String favoriteCategory;
}
