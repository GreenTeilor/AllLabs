package by.bsuir.springbootproject.dto;

import jakarta.validation.constraints.Digits;
import jakarta.validation.constraints.Email;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Past;
import jakarta.validation.constraints.Pattern;
import jakarta.validation.constraints.Size;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import lombok.experimental.SuperBuilder;

import java.math.BigDecimal;
import java.time.LocalDate;
import java.util.List;

@SuperBuilder
@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class UserDto extends BaseDto {
    @Pattern(regexp = "[A-Za-z]+", message = "Incorrect user name")
    @NotBlank(message = "Blank user name")
    private String name;

    @Pattern(regexp = "[A-Za-z]+", message = "Incorrect user lastName")
    @NotBlank(message = "Blank user lastName")
    private String lastName;

    @Email(message = "Incorrect user email")
    @NotBlank(message = "Blank user email")
    private String email;

    @Past(message = "User birthdate is in future")
    @NotNull(message = "Empty user birthDate")
    private LocalDate birthDate;

    @NotNull(message = "Empty user registrationDate")
    private LocalDate registrationDate;

    @Digits(integer = 6, fraction = 2, message = "User balance doesn't correspond to balance format")
    @NotNull(message = "Empty user balance")
    private BigDecimal balance;

    @Size(min = 3, message = "User password length is less than 3 chars")
    @NotNull(message = "Empty user password")
    private String password;

    @Size(min = 10, max = 90, message = "User address length is less than 10 or more than 90")
    private String address;

    @Pattern(regexp = "^\\+375((29)|(44)|(25)|(33))[0-9]{7}$", message = "Incorrect user phone number")
    private String phoneNumber;

    @NotNull(message = "Empty user orders")
    private List<OrderDto> orders;
}
