package by.bsuir.springmvcproject.repositories;

import by.bsuir.springmvcproject.entities.Category;
import by.bsuir.springmvcproject.entities.Product;
import by.bsuir.springmvcproject.entities.SearchCriteria;
import jakarta.persistence.criteria.CriteriaBuilder;
import jakarta.persistence.criteria.CriteriaQuery;
import jakarta.persistence.criteria.Join;
import jakarta.persistence.criteria.Predicate;
import jakarta.persistence.criteria.Root;
import lombok.RequiredArgsConstructor;
import org.springframework.data.jpa.domain.Specification;
import org.springframework.lang.NonNull;

import java.util.ArrayList;
import java.util.List;

@RequiredArgsConstructor
public class ProductSearchSpecification implements Specification<Product> {
    private final SearchCriteria searchCriteriaDto;

    @Override
    public Predicate toPredicate(@NonNull Root<Product> root, @NonNull CriteriaQuery<?> query, @NonNull CriteriaBuilder criteriaBuilder) {
        List<Predicate> predicates = new ArrayList<>();

        if (searchCriteriaDto.getKeyWords() != null && !searchCriteriaDto.getKeyWords().isBlank()) {
            predicates.add(criteriaBuilder.or(criteriaBuilder.like(root.get("name"),
                            "%" + searchCriteriaDto.getKeyWords() + "%"),
                    criteriaBuilder.like(root.get("description"),
                            "%" + searchCriteriaDto.getKeyWords() + "%")));
        }

        if (searchCriteriaDto.getPriceFrom() != null) {
            predicates.add(criteriaBuilder.greaterThanOrEqualTo(root.get("price"), searchCriteriaDto.getPriceFrom()));
        }

        if (searchCriteriaDto.getPriceTo() != null) {
            predicates.add(criteriaBuilder.lessThanOrEqualTo(root.get("price"), searchCriteriaDto.getPriceTo()));
        }

        if (searchCriteriaDto.getSearchCategory() != null && !searchCriteriaDto.getSearchCategory().isBlank()) {
            Join<Product, Category> productCategoryJoin = root.join("category");
            predicates.add(criteriaBuilder.and(criteriaBuilder.like(productCategoryJoin.get("name"),
                    "%" + searchCriteriaDto.getSearchCategory() + "%")));
        }

        return criteriaBuilder.and(predicates.toArray(new Predicate[0]));
    }
}
