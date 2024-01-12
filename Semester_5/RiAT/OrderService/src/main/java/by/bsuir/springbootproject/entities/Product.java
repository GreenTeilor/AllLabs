package by.bsuir.springbootproject.entities;

import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;
import jakarta.validation.constraints.Digits;
import jakarta.validation.constraints.Size;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@Entity
@Table(name = "products")
public class Product extends BaseEntity{
    @Size(min = 1, max = 50, message = "Empty or longer than 50 characters")
    private String name;

    @Size(min = 1, max = 350, message = "Empty or longer than 350 characters")
    private String description;

    @Size(min = 1, max = 50, message = "Empty or longer than 50 characters")
    private String imagePath;

    @Size(min = 1, max = 50, message = "Empty or longer than 50 characters")
    @ManyToOne
    @JoinColumn(name = "category", referencedColumnName = "name")
    private Category category;

    @Digits(integer = 6, fraction = 2, message = "Doesn't meet price format")
    private BigDecimal price;
}
