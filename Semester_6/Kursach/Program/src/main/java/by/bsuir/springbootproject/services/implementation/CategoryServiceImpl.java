package by.bsuir.springbootproject.services.implementation;

import by.bsuir.springbootproject.constants.PagesPaths;
import by.bsuir.springbootproject.constants.RequestAttributesNames;
import by.bsuir.springbootproject.constants.Values;
import by.bsuir.springbootproject.entities.Category;
import by.bsuir.springbootproject.entities.PagingParams;
import by.bsuir.springbootproject.exceptions.NoResourceFoundException;
import by.bsuir.springbootproject.repositories.CategoryRepository;
import by.bsuir.springbootproject.services.CategoryService;
import lombok.RequiredArgsConstructor;
import org.springframework.data.domain.PageRequest;
import org.springframework.data.domain.Pageable;
import org.springframework.data.domain.Sort;
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
        categoryRepository.save(category);
        return new ModelAndView("redirect:/admin");
    }

    @Override
    @Transactional
    public ModelAndView create(Category category) {
        categoryRepository.save(category);
        return new ModelAndView(PagesPaths.CATEGORY_PAGE);
    }

    @Override
    public ModelAndView read(PagingParams params) {
        if (params.getPageNumber() < 0) {
            params.setPageNumber(Values.DEFAULT_START_PAGE);
        }
        ModelAndView modelAndView = new ModelAndView(PagesPaths.HOME_PAGE);
        Pageable paging = PageRequest.of(params.getPageNumber(), params.getPageSize(), Sort.by("name").ascending());
        modelAndView.addObject(RequestAttributesNames.CATEGORIES, categoryRepository.findAll(paging).getContent());
        return modelAndView;
    }

    @Override
    @Transactional
    public Category update(Category category) throws NoResourceFoundException {
        categoryRepository.findById(category.getId()).orElseThrow(() ->
                new NoResourceFoundException("No category with id " + category.getId() + " found"));
        return categoryRepository.save(category);
    }

    @Override
    @Transactional
    public void delete(int id) {
        categoryRepository.deleteById(id);
    }
}
