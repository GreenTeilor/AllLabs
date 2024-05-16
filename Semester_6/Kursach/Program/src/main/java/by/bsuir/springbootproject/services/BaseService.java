package by.bsuir.springbootproject.services;

import by.bsuir.springbootproject.entities.BaseEntity;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.exceptions.UserAlreadyExistsException;
import org.springframework.web.servlet.ModelAndView;

public interface BaseService<T extends BaseEntity> {
    ModelAndView create(T entity) throws UserAlreadyExistsException;

    ModelAndView read(PagingParams params);

    T update(T entity) throws NoResourceFoundException;

    void delete(int id);
}
