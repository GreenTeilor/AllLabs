package by.bsuir.springbootproject.dto;

import com.opencsv.bean.CsvBindByName;
import jakarta.validation.constraints.Digits;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;

@SuperBuilder
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class ProductDto extends BaseDto{
    @Size(min = 1, max = 50, message = "Product name is empty or longer than 50 chars")
    @NotNull(message = "Product name is empty")
    @CsvBindByName
    private String name;

    @Size(min = 1, max = 350, message = "Product description is empty or longer than 350 chars")
    @NotNull(message = "Product description is empty")
    @CsvBindByName
    private String description;

    @Size(min = 1, max = 50, message = "Product imagePath is empty or longer than 50 chars")
    @NotNull(message = "Product imagePath is empty")
    @CsvBindByName
    private String imagePath;

    @Size(min = 1, max = 50, message = "Product categoryName is empty or longer than 50 chars")
    @NotNull(message = "Product categoryName is empty")
    @CsvBindByName
    private String categoryName;

    @Digits(integer = 6, fraction = 2, message = "Product price doesn't correspond to price format")
    @NotNull(message = "Product price is empty")
    @CsvBindByName
    private BigDecimal price;
}
