package by.bsuir.springbootproject.dto.converters;

import by.bsuir.springbootproject.dto.ProductDto;
import by.bsuir.springbootproject.entities.Product;
import by.bsuir.springbootproject.repositories.CategoryRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.Optional;

@Component
@RequiredArgsConstructor
public class ProductConverter implements Converter<ProductDto, Product> {

    private final CategoryRepository categoryRepository;

    @Override
    public ProductDto toDto(Product product) {
        return Optional.ofNullable(product).map(p -> ProductDto.builder().
                        id(p.getId()).
                        name(p.getName()).
                        description(p.getDescription()).
                        imagePath(p.getImagePath()).
                        categoryName(p.getCategory().getName()).
                        price(p.getPrice()).
                        build()).
                orElse(null);
    }

    @Override
    public Product fromDto(ProductDto productDto) {
        return Optional.ofNullable(productDto).map(p -> Product.builder().
                        id(p.getId()).
                        name(p.getName()).
                        description(p.getDescription()).
                        imagePath(p.getImagePath()).
                        category(categoryRepository.findByName(productDto.getCategoryName()).orElse(null)).
                        price(p.getPrice()).
                        build()).
                orElse(null);
    }
}
