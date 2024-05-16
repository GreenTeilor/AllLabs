package by.bsuir.publisher.exceptions;

import by.bsuir.publisher.dto.responses.ErrorDto;
import lombok.Getter;

@Getter
public class ServiceException extends Exception {
    private final ErrorDto errorDto;

    public ServiceException(ErrorDto errorDto) {
        this.errorDto = errorDto;
    }
}
