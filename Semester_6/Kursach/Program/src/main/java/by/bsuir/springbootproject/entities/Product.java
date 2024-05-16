package by.bsuir.springbootproject.entities;

import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.JoinTable;
import jakarta.persistence.ManyToMany;
import jakarta.persistence.ManyToOne;
import jakarta.persistence.Table;
import jakarta.validation.constraints.Digits;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;
import java.util.List;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@Entity
@Table(name = "products")
public class Product extends BaseEntity{
    @Size(min = 1, max = 50, message = "Пустое или длиннее 50 символов")
    private String name;

    @Size(min = 1, max = 350, message = "Пустое или длиннее 350 символов")
    private String description;

    @NotNull(message = "Не введено")
    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(name = "products_images",
            joinColumns = { @JoinColumn(name = "productId") },
            inverseJoinColumns = { @JoinColumn(name = "imageId") })
    private List<Image> images;

    @NotNull(message = "Не введено")
    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(name = "products_labels",
            joinColumns = { @JoinColumn(name = "productId") },
            inverseJoinColumns = { @JoinColumn(name = "labelId") })
    private List<Label> labels;

    @ManyToOne
    @JoinColumn(name = "publisher", referencedColumnName = "id")
    private Publisher publisher;

    @ManyToOne
    @JoinColumn(name = "author", referencedColumnName = "id")
    private Author author;

    @Size(min = 1, max = 50, message = "Пустое или длиннее 50 символов")
    @ManyToOne
    @JoinColumn(name = "category", referencedColumnName = "name")
    private Category category;

    @Digits(integer = 6, fraction = 2, message = "Не соответствует формату цены")
    private BigDecimal price;
}
