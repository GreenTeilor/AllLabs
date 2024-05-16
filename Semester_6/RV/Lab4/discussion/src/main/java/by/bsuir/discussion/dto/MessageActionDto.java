package by.bsuir.discussion.dto;

import lombok.Data;
import lombok.NoArgsConstructor;
import lombok.experimental.SuperBuilder;

@SuperBuilder
@NoArgsConstructor
@Data
public class MessageActionDto {
    MessageActionTypeDto action;
    Object data;
}
