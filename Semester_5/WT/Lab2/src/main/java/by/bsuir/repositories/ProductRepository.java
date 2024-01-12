package by.bsuir.repositories;

import by.bsuir.domain.PagingParams;
import by.bsuir.domain.Product;
import by.bsuir.exceptions.ConnectionException;
import lombok.NoArgsConstructor;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;
import java.util.Optional;

@NoArgsConstructor
public class ProductRepository {
    private final static ConnectionPool pool = ConnectionPool.getInstance();
    private final static String GET_PRODUCTS_BY_CATEGORY_NAME = "SELECT * FROM products WHERE category = ? LIMIT ?, ?";
    private final static String GET_PRODUCT_BY_ID = "SELECT * FROM products WHERE id = ?";
    private final static String GET_ORDER_PRODUCTS = "SELECT * FROM orders_products JOIN products ON orders_products.productId = products.id WHERE orderId = ?";
    private final static String PERSIST_PRODUCT = "INSERT INTO products (name, description, imagePath, category, price) VALUES (?, ?, ?, ?, ?)";

    public List<Product> getProductsByCategory(String category, PagingParams params) throws ConnectionException, SQLException {
        List<Product> result = new ArrayList<>();
        Connection connection = pool.getConnection();
        try (PreparedStatement statement = connection.prepareStatement(GET_PRODUCTS_BY_CATEGORY_NAME)) {
            int startPosition = params.getPageNumber() * params.getPageSize();
            statement.setString(1, category);
            statement.setInt(2, startPosition);
            statement.setInt(3, params.getPageSize());
            ResultSet set = statement.executeQuery();
            while (set.next()) {
                result.add(Product.
                        builder().
                        id(set.getInt("id")).
                        name(set.getString("name")).
                        description(set.getString("description")).
                        imagePath(set.getString("imagePath")).
                        category(set.getString("category")).
                        price(set.getBigDecimal("price")).
                        build());
            }
            set.close();
        } finally {
            pool.returnConnection(connection);
        }
        return result;
    }

    public Optional<Product> getProductById(int id) throws ConnectionException, SQLException {
        Optional<Product> product = Optional.empty();
        Connection connection = pool.getConnection();
        try (PreparedStatement statement = connection.prepareStatement(GET_PRODUCT_BY_ID)) {
            statement.setInt(1, id);
            ResultSet set = statement.executeQuery();
            if (set.next()) {
                product =  Optional.of(Product.
                        builder().
                        id(set.getInt("id")).
                        name(set.getString("name")).
                        description(set.getString("description")).
                        imagePath(set.getString("imagePath")).
                        category(set.getString("category")).
                        price(set.getBigDecimal("price")).
                        build());
            }
            set.close();
            return product;
        } finally {
            pool.returnConnection(connection);
        }
    }

    public List<Product> getOrderProducts(int orderId) throws ConnectionException, SQLException {
        List<Product> result = new ArrayList<>();
        Connection connection = pool.getConnection();
        try (PreparedStatement statement = connection.prepareStatement(GET_ORDER_PRODUCTS)) {
            statement.setInt(1, orderId);
            ResultSet set = statement.executeQuery();
            while (set.next()) {
                result.add(Product.
                        builder().
                        id(set.getInt("id")).
                        name(set.getString("name")).
                        description(set.getString("description")).
                        imagePath(set.getString("imagePath")).
                        category(set.getString("category")).
                        price(set.getBigDecimal("price")).
                        build());
            }
            set.close();
        } finally {
            pool.returnConnection(connection);
        }
        return result;
    }

    public void persist(Product product) throws ConnectionException, SQLException {
        Connection connection = pool.getConnection();
        try (PreparedStatement statement = connection.prepareStatement(PERSIST_PRODUCT)) {
            statement.setString(1, product.getName());
            statement.setString(2, product.getDescription());
            statement.setString(3, product.getImagePath());
            statement.setString(4, product.getCategory());
            statement.setBigDecimal(5, product.getPrice());
            statement.execute();
        } finally {
            pool.returnConnection(connection);
        }
    }
}
