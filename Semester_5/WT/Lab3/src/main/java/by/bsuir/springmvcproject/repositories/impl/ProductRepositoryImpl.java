package by.bsuir.springmvcproject.repositories.impl;

import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.entities.Product;
import by.bsuir.springmvcproject.entities.SearchCriteria;
import by.bsuir.springmvcproject.repositories.ProductRepository;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import lombok.RequiredArgsConstructor;
import org.hibernate.Session;
import org.hibernate.query.Query;
import org.springframework.stereotype.Repository;

import java.math.BigDecimal;
import java.util.List;
import java.util.Optional;

@Repository
@RequiredArgsConstructor
public class ProductRepositoryImpl implements ProductRepository {
    private final static String GET_CATEGORY_PRODUCTS_QUERY = "select p from Product p where p.category.name=:category";
    private final static String GET_PRODUCTS_QUERY = "select p from Product p";
    private final static String SEARCH_PRODUCTS_QUERY = "select p from Product p where (p.name like :name " +
            "or p.description like :description) AND p.category.name like :category AND p.price>=:fromPrice AND p.price<=:toPrice " +
            "order by p.name asc";

    @PersistenceContext
    private final EntityManager manager;

    @Override
    public List<Product> getCategoryProducts(String category, PagingParams params) {
        Session session = manager.unwrap(Session.class);
        Query<Product> query = session.createQuery(GET_CATEGORY_PRODUCTS_QUERY, Product.class);
        query.setParameter("category", category);
        query.setFirstResult((params.getPageNumber() - 1) * params.getPageSize());
        query.setMaxResults(params.getPageSize());
        return query.getResultList();
    }

    @Override
    public Optional<Product> getProductById(int id) {
        Session session = manager.unwrap(Session.class);
        return Optional.ofNullable(session.get(Product.class, id));
    }

    @Override
    public List<Product> findProducts(SearchCriteria criteria) {
        Session session = manager.unwrap(Session.class);
        Query<Product> query = session.createQuery(SEARCH_PRODUCTS_QUERY, Product.class);
        String searchPattern = "%" + criteria.getKeyWords().trim() + "%";
        query.setParameter("name", searchPattern);
        query.setParameter("description", searchPattern);
        query.setParameter("category", criteria.getSearchCategory() != null ? criteria.getSearchCategory() : "%%");
        query.setParameter("fromPrice", criteria.getPriceFrom() != null ? criteria.getPriceFrom() : BigDecimal.valueOf(-2000_000_000));
        query.setParameter("toPrice", criteria.getPriceTo() != null ? criteria.getPriceTo() : BigDecimal.valueOf(2000_000_000));
        query.setFirstResult((criteria.getPageNumber() - 1) * criteria.getPageSize());
        query.setMaxResults(criteria.getPageSize());
        return query.getResultList();
    }

    @Override
    public Product create(Product product) {
        Session session = manager.unwrap(Session.class);
        session.persist(product);
        return product;
    }

    @Override
    public List<Product> read(PagingParams params) {
        Session session = manager.unwrap(Session.class);
        Query<Product> query = session.createQuery(GET_PRODUCTS_QUERY, Product.class);
        query.setFirstResult((params.getPageNumber() - 1) * params.getPageSize());
        query.setMaxResults(params.getPageSize());
        return query.getResultList();
    }

    @Override
    public Product update(Product product) {
        Session session = manager.unwrap(Session.class);
        return session.merge(product);
    }

    @Override
    public void delete(int id) {
        Session session = manager.unwrap(Session.class);
        Product user = session.get(Product.class, id);
        session.remove(user);
    }
}
