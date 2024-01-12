package by.bsuir.springmvcproject.repositories.impl;

import by.bsuir.springmvcproject.entities.Category;
import by.bsuir.springmvcproject.entities.PagingParams;
import by.bsuir.springmvcproject.repositories.CategoryRepository;
import jakarta.persistence.EntityManager;
import jakarta.persistence.PersistenceContext;
import lombok.RequiredArgsConstructor;
import org.hibernate.query.Query;
import org.hibernate.Session;
import org.springframework.stereotype.Repository;

import java.util.List;
import java.util.Optional;

@Repository
@RequiredArgsConstructor
public class CategoryRepositoryImpl implements CategoryRepository {
    private final static String GET_CATEGORIES_QUERY = "select c from Category c";
    private final static String FIND_BY_NAME_QUERY = "select c from Category c where c.name=:name";

    @PersistenceContext
    private final EntityManager manager;

    @Override
    public Category create(Category category) {
        Session session = manager.unwrap(Session.class);
        session.persist(category);
        return category;
    }

    @Override
    public List<Category> read(PagingParams params) {
        Session session = manager.unwrap(Session.class);
        Query<Category> query = session.createQuery(GET_CATEGORIES_QUERY, Category.class);
        query.setFirstResult((params.getPageNumber() - 1) * params.getPageSize());
        query.setMaxResults(params.getPageSize());
        return query.getResultList();
    }

    @Override
    public Category update(Category category) {
        Session session = manager.unwrap(Session.class);
        return session.merge(category);
    }

    @Override
    public void delete(int id) {
        Session session = manager.unwrap(Session.class);
        Category category = session.get(Category.class, id);
        session.remove(category);
    }

    @Override
    public Optional<Category> findById(int id) {
        Session session = manager.unwrap(Session.class);
        Category category = session.get(Category.class, id);
        return Optional.ofNullable(category);
    }

    @Override
    public Optional<Category> findByName(String name) {
        Session session = manager.unwrap(Session.class);
        Query<Category> query = session.createQuery(FIND_BY_NAME_QUERY, Category.class);
        query.setParameter("name", name);
        return Optional.ofNullable(query.getSingleResult());
    }
}
