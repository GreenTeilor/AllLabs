package by.bsuir.springbootproject.exceptions;

public class NoProductsInOrderException extends Exception {
    public NoProductsInOrderException(String message) {
        super(message);
    }
}
