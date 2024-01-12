package by.bsuir.springbootproject.controllers;

import by.bsuir.springbootproject.dto.UserDto;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.exceptions.UserAlreadyExistsException;
import by.bsuir.springbootproject.services.UserService;
import io.swagger.v3.oas.annotations.Operation;
import io.swagger.v3.oas.annotations.media.Content;
import io.swagger.v3.oas.annotations.media.Schema;
import io.swagger.v3.oas.annotations.responses.ApiResponse;
import io.swagger.v3.oas.annotations.responses.ApiResponses;
import io.swagger.v3.oas.annotations.tags.Tag;
import jakarta.annotation.Nullable;
import jakarta.validation.Valid;
import jakarta.validation.constraints.NotBlank;
import jakarta.validation.constraints.NotNull;
import lombok.RequiredArgsConstructor;
import org.springframework.validation.annotation.Validated;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;


@Tag(name = "user", description = "User endpoints")
@RestController
@RequestMapping("/user")
@RequiredArgsConstructor
@Validated
public class UserController {
    private final UserService userService;

    @Operation(
            summary = "Register user",
            description = "Register user by name, lastName, email, password, birthDate")
    @ApiResponses(value = {
            @ApiResponse(
                    responseCode = "200",
                    description = "User was registered\tUser already exists",
                    content = {@Content(schema = @Schema(implementation = UserDto.class)),
                            @Content(schema = @Schema(implementation = String.class))}
            )
    })
    @PostMapping("/register")
    public UserDto register(@io.swagger.v3.oas.annotations.parameters.RequestBody(description = "User object") @Valid @RequestBody UserDto userDto) throws UserAlreadyExistsException {
        return userService.create(userDto);
    }

    @PostMapping("/login")
    public UserDto login(@NotBlank String email, @NotNull String password) {
        return userService.login(email, password);
    }

    @GetMapping("/read")
    public List<UserDto> getAllUsers() {
        return userService.read();
    }

    @PostMapping("/update")
    public UserDto updateUser(@NotNull @Valid @RequestBody UserDto userDto) throws NoResourceFoundException {
        return userService.update(userDto);
    }

    @DeleteMapping("/delete")
    public void deleteUser(@NotNull Integer userId) {
        userService.delete(userId);
    }

    @PostMapping("/modifyInfo")
    public UserDto modifyUserInfo(@Nullable String address, @Nullable String phoneNumber, @NotNull Integer userId) throws NoResourceFoundException {
        return userService.addAddressAndPhoneNumberInfo(address, phoneNumber, userId);
    }

    @PostMapping("/getById")
    public UserDto getUserById(@NotNull Integer userId) throws NoResourceFoundException {
        return userService.getUserById(userId);
    }
}
