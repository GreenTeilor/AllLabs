package by.bsuir.publisher.dto.responses.converters;

import by.bsuir.publisher.domain.Message;
import by.bsuir.publisher.dto.responses.MessageResponseDto;
import org.mapstruct.Mapper;

import java.util.List;

@Mapper(componentModel = "spring", uses = MessageResponseConverter.class)
public interface CollectionMessageResponseConverter {
    List<MessageResponseDto> toListDto(List<Message> messages);
}
