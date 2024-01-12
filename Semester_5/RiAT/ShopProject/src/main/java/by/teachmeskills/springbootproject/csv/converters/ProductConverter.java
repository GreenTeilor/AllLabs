package by.teachmeskills.springbootproject.csv.converters;

import by.teachmeskills.springbootproject.csv.ProductCsv;
import by.teachmeskills.springbootproject.entities.Product;
import by.teachmeskills.springbootproject.repositories.CategoryRepository;
import lombok.RequiredArgsConstructor;
import org.springframework.stereotype.Component;

import java.util.Optional;

@Component
@RequiredArgsConstructor
public class ProductConverter {
    private final CategoryRepository categoryRepository;

    public ProductCsv toCsv(Product product) {
        return Optional.ofNullable(product).map(p -> ProductCsv.builder().
                id(p.getId()).
                name(p.getName()).
                description(p.getDescription()).
                imagePath(p.getImagePath()).
                categoryName(p.getCategory().getName()).
                price(p.getPrice()).
                build()).orElse(null);
    }

    public Product fromCsv(ProductCsv productCsv) {
        return Optional.ofNullable(productCsv).map(p -> Product.builder().
                id(p.getId()).
                name(p.getName()).
                description(p.getDescription()).
                imagePath(p.getImagePath()).
                category(categoryRepository.findByName(p.getCategoryName()).orElse(null)).
                price(p.getPrice()).
                build()).orElse(null);
    }
}
