package by.bsuir.springmvcproject.services;

import by.bsuir.springmvcproject.entities.Category;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.IOException;

public interface CategoryService extends BaseService<Category>{
    ModelAndView saveCategory(Category category, MultipartFile image) throws IOException;
}
