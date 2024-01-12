package by.bsuir.springmvcproject.exceptions;

public class NoProductsInOrderException extends Exception {
    public NoProductsInOrderException(String message) {
        super(message);
    }
}
