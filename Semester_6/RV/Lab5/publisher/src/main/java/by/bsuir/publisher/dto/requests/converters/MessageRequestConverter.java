package by.bsuir.publisher.dto.requests.converters;

import by.bsuir.publisher.domain.Message;
import by.bsuir.publisher.dto.requests.MessageRequestDto;
import org.mapstruct.Mapper;

@Mapper(componentModel = "spring")
public interface MessageRequestConverter {
    Message fromDto(MessageRequestDto message);
}
