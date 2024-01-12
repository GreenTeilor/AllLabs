package by.bsuir.domain;

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
public class User extends BaseEntity {
    private String name;
    private String lastName;
    private String email;
    private LocalDate birthDate;
    private LocalDate registrationDate;
    private BigDecimal balance;
    private String password;
    private String address;
    private String phoneNumber;
    private List<Order> orders;
    private List<Role> roles;

    public boolean hasRole(String role) {
        return roles.stream().map(Role::getName).toList().contains(role);
    }
}