package by.bsuir.springbootproject.entities;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.validation.constraints.Size;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@Entity
@Table(name = "images")
public class Image extends BaseEntity {
    @Size(min = 1, max = 150, message = "Пустое или длиннее 150 символов")
    private String path;
}
