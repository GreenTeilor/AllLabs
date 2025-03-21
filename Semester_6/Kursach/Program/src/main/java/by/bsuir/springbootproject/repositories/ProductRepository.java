package by.bsuir.springbootproject.repositories;

import by.bsuir.springbootproject.entities.Product;
import org.springframework.data.domain.Pageable;
import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.data.jpa.repository.JpaSpecificationExecutor;
import org.springframework.stereotype.Repository;

import java.util.List;

@Repository
public interface ProductRepository extends JpaRepository<Product, Integer>, JpaSpecificationExecutor<Product> {
    List<Product> findAllByCategory_Name(String category, Pageable paging);
    List<Product> findAllByCategory_Name(String category);
}
