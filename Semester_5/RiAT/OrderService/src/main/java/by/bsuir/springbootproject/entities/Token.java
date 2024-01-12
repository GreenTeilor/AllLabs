package by.bsuir.springbootproject.entities;

import jakarta.persistence.Entity;
import jakarta.persistence.Table;
import jakarta.validation.constraints.NotNull;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

@Getter
@Setter
@SuperBuilder
@NoArgsConstructor
@Entity
@Table(name = "refresh_tokens")
public class Token extends BaseEntity {
    @NotNull(message = "Not inputted")
    private String token;

    @NotNull(message = "Not inputted")
    private String username;
}
