package by.bsuir.springmvcproject.services.impl;

import by.bsuir.springmvcproject.constants.PagesPaths;
import by.bsuir.springmvcproject.constants.RequestAttributesNames;
import by.bsuir.springmvcproject.constants.Values;
import by.bsuir.springmvcproject.entities.Category;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.exceptions.NoResourceFoundException;
import by.bsuir.springmvcproject.repositories.CategoryRepository;
import by.bsuir.springmvcproject.services.CategoryService;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;
import org.springframework.web.multipart.MultipartFile;
import org.springframework.web.servlet.ModelAndView;

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;

@Service
@RequiredArgsConstructor
@Transactional(readOnly = true)
public class CategoryServiceImpl implements CategoryService {
    private final CategoryRepository categoryRepository;

    @Override
    @Transactional
    public ModelAndView saveCategory(Category category, MultipartFile image) throws IOException {
        String fileName = image.getOriginalFilename();
        image.transferTo(new File("src\\main\\webapp\\assets\\" + fileName));
        category.setImagePath("assets/" + fileName);
        category.setProducts(new ArrayList<>());
        categoryRepository.create(category);
        return new ModelAndView("redirect:/admin");
    }

    @Override
    @Transactional
    public ModelAndView create(Category category) {
        categoryRepository.create(category);
        return new ModelAndView(PagesPaths.CATEGORY_PAGE);
    }

    @Override
    public ModelAndView read(PagingParams params) {
        if (params.getPageNumber() < 0) {
            params.setPageNumber(Values.DEFAULT_START_PAGE);
        }
        ModelAndView modelAndView = new ModelAndView(PagesPaths.HOME_PAGE);
        modelAndView.addObject(RequestAttributesNames.CATEGORIES, categoryRepository.read(params));
        return modelAndView;
    }

    @Override
    @Transactional
    public Category update(Category category) throws NoResourceFoundException {
        categoryRepository.findById(category.getId()).orElseThrow(() ->
                new NoResourceFoundException("No category with id " + category.getId() + " found"));
        return categoryRepository.create(category);
    }

    @Override
    @Transactional
    public void delete(int id) {
        categoryRepository.delete(id);
    }
}
