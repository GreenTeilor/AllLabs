package by.bsuir.publisher.dto.requests;

import jakarta.validation.constraints.Size;
import lombok.Data;
import lombok.EqualsAndHashCode;
import lombok.NoArgsConstructor;
import lombok.experimental.SuperBuilder;

@SuperBuilder
@NoArgsConstructor
@Data
@EqualsAndHashCode
public class MessageRequestDto {
    private Long id;
    private Long storyId;

    @Size(min = 3, max = 32)
    private String content;
}
