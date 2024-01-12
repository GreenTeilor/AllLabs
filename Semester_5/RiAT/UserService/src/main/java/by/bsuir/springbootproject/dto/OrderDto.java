package by.bsuir.springbootproject.dto;

import jakarta.validation.constraints.Digits;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

@SuperBuilder
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class OrderDto extends BaseDto{
    @NotNull(message = "Order date is empty")
    private LocalDate date;

    @NotNull(message = "Order list of products is empty")
    private List<ProductDto> products;

    @NotNull(message = "Order userId is empty")
    private int userId;

    @Digits(integer = 6, fraction = 2, message = "Order price doesn't correspond to price format")
    private BigDecimal price;
}
