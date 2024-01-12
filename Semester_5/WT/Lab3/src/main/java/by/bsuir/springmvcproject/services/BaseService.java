package by.bsuir.springmvcproject.services;

import by.bsuir.springmvcproject.entities.BaseEntity;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.exceptions.NoResourceFoundException;
import by.bsuir.springmvcproject.exceptions.UserAlreadyExistsException;
import org.springframework.web.servlet.ModelAndView;

public interface BaseService<T extends BaseEntity> {
    ModelAndView create(T entity) throws UserAlreadyExistsException;

    ModelAndView read(PagingParams params);

    T update(T entity) throws NoResourceFoundException;

    void delete(int id);
}
