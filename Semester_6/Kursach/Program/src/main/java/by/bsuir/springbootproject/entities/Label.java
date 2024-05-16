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
@Table(name = "labels")
public class Label extends BaseEntity {
    @Size(min = 1, max = 50, message = "Пустое или длиннее 50 символов")
    private String name;
}
