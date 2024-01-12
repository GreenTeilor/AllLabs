package by.bsuir.springbootproject.entities;

import jakarta.persistence.CascadeType;
import jakarta.persistence.Entity;
import jakarta.persistence.FetchType;
import jakarta.persistence.JoinColumn;
import jakarta.persistence.JoinTable;
import jakarta.persistence.ManyToMany;
import jakarta.persistence.OneToMany;
import jakarta.persistence.Table;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Past;
import jakarta.validation.constraints.Pattern;
import jakarta.validation.constraints.Size;
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
@Table(name = "users")
public class User extends BaseEntity {
    @Pattern(regexp = "[A-Za-z]+", message = "Incorrect name")
    @NotBlank(message = "Can't be blank")
    private String name;

    @Pattern(regexp = "[A-Za-z]+", message = "Incorrect lastName")
    @NotBlank(message = "Can't be blank")
    private String lastName;

    @Email(message = "Incorrect email")
    @NotBlank(message = "Can't be blank")
    private String email;

    @Past(message = "Future date inputted")
    @NotNull(message = "Not inputted")
    private LocalDate birthDate;

    private LocalDate registrationDate;
    private BigDecimal balance;

    @Size(min = 3, message = "Min 3 characters")
    private String password;

    @Size(min = 10, max = 90, message = "Address length has to be from 10 to 90")
    private String address;

    @Pattern(regexp = "^\\+375((29)|(44)|(25)|(33))[0-9]{7}$", message = "Incorrect phone number")
    private String phoneNumber;

    @OneToMany(fetch = FetchType.EAGER, cascade = CascadeType.MERGE)
    @JoinColumn(name = "userId")
    private List<Order> orders;
}