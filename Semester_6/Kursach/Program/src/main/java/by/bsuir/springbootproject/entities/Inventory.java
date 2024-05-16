package by.bsuir.springbootproject.entities;

import jakarta.persistence.Entity;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.OneToOne;
import jakarta.persistence.Table;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@Entity
@Table(name = "inventory")
public class Inventory extends BaseEntity {
    @OneToOne
    @JoinColumn(name = "productId", referencedColumnName = "id")
    private Product product;

    private Integer amount;
}
