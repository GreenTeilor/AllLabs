package by.bsuir.publisher.exceptions;

import by.bsuir.publisher.dto.responses.ErrorDto;
import jakarta.validation.ConstraintViolationException;
import org.springframework.dao.DataIntegrityViolationException;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.ExceptionHandler;
import org.springframework.web.bind.annotation.RestControllerAdvice;

import java.util.concurrent.TimeoutException;

@RestControllerAdvice
public class GlobalControllerExceptionHandler {
    @ExceptionHandler(value = { NoEntityExistsException.class, EntityExistsException.class })
    protected ResponseEntity<ErrorDto> handleEntityExceptions(Exception e) {
        return new ResponseEntity<>(ErrorDto.builder().
                code(HttpStatus.BAD_REQUEST.value() + "00").
                message(e.getMessage()).
                build(), HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(value = { NullPointerException.class })
    protected ResponseEntity<ErrorDto> handleNullPointerException() {
        return new ResponseEntity<>(ErrorDto.builder().
                code(HttpStatus.BAD_REQUEST.value() + "00").
                message(Messages.NullPointerException).
                build(), HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(value = { ConstraintViolationException.class })
    protected ResponseEntity<ErrorDto> handleConstraintViolationException(ConstraintViolationException e) {
        return new ResponseEntity<>(ErrorDto.builder().
                code(HttpStatus.BAD_REQUEST.value() + "00").
                message(e.getMessage()).
                build(), HttpStatus.BAD_REQUEST);
    }

    @ExceptionHandler(value = { DataIntegrityViolationException.class })
    protected ResponseEntity<ErrorDto> handleDataIntegrityViolationException(DataIntegrityViolationException e) {
        return new ResponseEntity<>(ErrorDto.builder().
                code(HttpStatus.FORBIDDEN.value() + "00").
                message(e.getMessage()).
                build(), HttpStatus.FORBIDDEN);
    }

    @ExceptionHandler(value = { ServiceException.class })
    protected ResponseEntity<ErrorDto> handleServiceException(ServiceException e) {
        ErrorDto error = e.getErrorDto();
        return new ResponseEntity<>(ErrorDto.builder().
                code(error.getCode()).
                message(error.getMessage()).
                build(), HttpStatus.valueOf(Integer.parseInt(error.getCode().substring(0, 3))));
    }

    @ExceptionHandler(value = { TimeoutException.class })
    protected ResponseEntity<ErrorDto> handleServiceException() {
        return new ResponseEntity<>(ErrorDto.builder().
                code(HttpStatus.REQUEST_TIMEOUT.value() + "00").
                message("Request timeout").
                build(), HttpStatus.REQUEST_TIMEOUT);
    }
}
