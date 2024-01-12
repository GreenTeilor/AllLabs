package by.bsuir.springbootproject.repositories;

import by.bsuir.springbootproject.entities.Product;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface ProductRepository extends JpaRepository<Product, Integer> {
    List<Product> findAllByCategory_Name(String categoryName);
}
