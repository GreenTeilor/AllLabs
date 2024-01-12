package by.bsuir.domain;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
public class Product extends BaseEntity{
    private String name;
    private String description;
    private String imagePath;
    private String category;
    private BigDecimal price;
}
