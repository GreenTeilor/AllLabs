package by.bsuir.springbootproject.dto.converters;

import by.bsuir.springbootproject.dto.CategoryDto;
import by.bsuir.springbootproject.entities.Category;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.List;
import java.util.Optional;

@Component
@RequiredArgsConstructor
public class CategoryConverter implements Converter<CategoryDto, Category> {

    private final ProductConverter productConverter;

    @Override
    public CategoryDto toDto(Category category) {
        return Optional.ofNullable(category).map(c -> CategoryDto.builder().
                        id(c.getId()).
                        name(c.getName()).
                        imagePath(c.getImagePath()).
                        products(Optional.ofNullable(c.getProducts()).map(products -> products.stream().map(productConverter::toDto).toList()).orElse(List.of())).
                        build()).
                orElse(null);
    }

    @Override
    public Category fromDto(CategoryDto categoryDto) {
        return Optional.ofNullable(categoryDto).map(c -> Category.builder().
                        id(c.getId()).
                        name(c.getName()).
                        imagePath(c.getImagePath()).
                        products(Optional.ofNullable(c.getProducts()).map(products -> products.stream().map(productConverter::fromDto).toList()).orElse(List.of())).
                        build()).
                orElse(null);
    }
}
