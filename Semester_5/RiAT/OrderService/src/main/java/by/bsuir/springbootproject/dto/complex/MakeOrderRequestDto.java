package by.bsuir.springbootproject.dto.complex;

import by.bsuir.springbootproject.dto.CartDto;
import jakarta.validation.Valid;
import jakarta.validation.constraints.NotNull;
import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
public class MakeOrderRequestDto {
    @NotNull(message = "CartDto is null")
    @Valid
    private CartDto cartDto;

    @NotNull(message = "userId is null")
    private Integer userId;
}
