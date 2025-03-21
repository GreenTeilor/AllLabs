package by.bsuir.springbootproject.entities;

import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.JoinTable;
import jakarta.persistence.ManyToMany;
import jakarta.persistence.Table;
import jakarta.validation.constraints.Digits;
import jakarta.validation.constraints.NotNull;
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
@Entity
@Table(name = "orders")
public class Order extends BaseEntity{
    @NotNull(message = "Not inputted")
    private LocalDate date;

    @NotNull(message = "Not inputted")
    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(name = "orders_products",
            joinColumns = { @JoinColumn(name = "orderId") },
            inverseJoinColumns = { @JoinColumn(name = "productId") })
    private List<Product> products;

    @NotNull(message = "Not inputted")
    private int userId;

    @Digits(integer = 6, fraction = 2, message = "Doesn't meet price format")
    private BigDecimal price;
}
