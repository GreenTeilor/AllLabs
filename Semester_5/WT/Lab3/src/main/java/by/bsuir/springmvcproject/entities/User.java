package by.bsuir.springmvcproject.entities;

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
    @Pattern(regexp = "[A-Za-z]+", message = "Некорректное имя")
    @NotBlank(message = "Не должно быть пустым")
    private String name;

    @Pattern(regexp = "[A-Za-z]+", message = "Некорректная фамилилия")
    @NotBlank(message = "Не должно быть пустым")
    private String lastName;

    @Email(message = "Некорректный email")
    @NotBlank(message = "Не должно быть пустым")
    private String email;

    @Past(message = "Указана еще не наступившая дата")
    @NotNull(message = "Не введено")
    private LocalDate birthDate;

    private LocalDate registrationDate;
    private BigDecimal balance;

    @Size(min = 3, message = "Минимум 3 символа")
    private String password;

    @Size(min = 10, max = 90, message = "Длина адреса должна быть в пределах от 10 до 90 символов")
    private String address;

    @Pattern(regexp = "^\\+375((29)|(44)|(25)|(33))[0-9]{7}$", message = "Некорректный номер телефона")
    private String phoneNumber;

    @OneToMany(fetch = FetchType.EAGER, cascade = CascadeType.MERGE)
    @JoinColumn(name = "userId")
    private List<Order> orders;

    @ManyToMany(fetch = FetchType.EAGER)
    @JoinTable(name = "users_roles",
            joinColumns = { @JoinColumn(name = "userId") },
            inverseJoinColumns = { @JoinColumn(name = "roleId") })
    private List<Role> roles;

}