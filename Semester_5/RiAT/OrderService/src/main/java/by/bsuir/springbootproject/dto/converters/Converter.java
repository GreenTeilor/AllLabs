package by.bsuir.springbootproject.dto.converters;

import by.bsuir.springbootproject.dto.BaseDto;
import by.bsuir.springbootproject.entities.BaseEntity;

public interface Converter <T extends BaseDto, E extends BaseEntity>{
    T toDto(E entityObject);
    E fromDto(T dtoObject);
}
