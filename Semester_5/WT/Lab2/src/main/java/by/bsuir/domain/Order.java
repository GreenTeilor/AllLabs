package by.bsuir.domain;

import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
public class Order extends BaseEntity{
    private LocalDate date;
    private List<Product> products;
    private int userId;
    private BigDecimal price;
}
