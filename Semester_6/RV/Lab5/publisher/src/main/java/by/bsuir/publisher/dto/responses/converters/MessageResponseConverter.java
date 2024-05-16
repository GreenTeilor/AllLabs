package by.bsuir.publisher.dto.responses.converters;

import by.bsuir.publisher.domain.Message;
import by.bsuir.publisher.dto.responses.MessageResponseDto;
import org.mapstruct.Mapper;

@Mapper(componentModel = "spring")
public interface MessageResponseConverter {
    MessageResponseDto toDto(Message message);
    Message fromDto(MessageResponseDto messageResponseDto);
}
