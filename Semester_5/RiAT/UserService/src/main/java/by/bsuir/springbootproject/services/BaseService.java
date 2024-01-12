package by.bsuir.springbootproject.services;

import by.bsuir.springbootproject.dto.BaseDto;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.exceptions.UserAlreadyExistsException;

public interface BaseService<T extends BaseDto> {
    T create(T entity) throws UserAlreadyExistsException;

    T update(T entity) throws NoResourceFoundException;

    void delete(int id);
}
