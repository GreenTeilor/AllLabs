package by.bsuir.springmvcproject.entities;

import com.opencsv.bean.CsvBindByName;
import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;
import jakarta.validation.constraints.Size;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.util.List;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@Entity
@Table(name = "categories")
public class Category extends BaseEntity {
    @Size(min = 1, max = 50, message = "Пустое или длиннее 50 символов")
    @CsvBindByName
    private String name;

    @Size(min = 1, max = 50, message = "Пустое или длиннее 50 символов")
    @CsvBindByName
    private String imagePath;

    @OneToMany(cascade = CascadeType.ALL, fetch = FetchType.LAZY, mappedBy = "category")
    List<Product> products;
}
