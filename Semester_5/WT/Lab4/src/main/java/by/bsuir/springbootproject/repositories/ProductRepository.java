package by.bsuir.springbootproject.repositories;

import by.bsuir.springbootproject.entities.Product;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;

import java.util.List;

public interface ProductRepository extends JpaRepository<Product, Integer>, JpaSpecificationExecutor<Product> {
    List<Product> findAllByCategory_Name(String category, Pageable paging);
    List<Product> findAllByCategory_Name(String category);
}
